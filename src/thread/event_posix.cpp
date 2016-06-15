/******************************************************************************
 * Copyright (C) 671643387@qq.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *****************************************************************************/

#include "node/thread/event_posix.h"
#include <errno.h>
#include <assert.h>
#include <sys/time.h>
#include <pthread.h>
#include <ctime>
#include <new>
#include "node/auto_ptr.h"
using node::auto_ptr;

///////////////////////////////////////////////////////////////////////////////
struct internal_event_t {
	bool state;
	bool manual_reset;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
};

struct internal_event_t* internal_event_create(bool manual_reset, bool init_state) {
	auto_ptr<struct internal_event_t> new_event(new (std::nothrow) struct internal_event_t);
	if (!new_event) {
		return NULL;
	}
	new_event->state = init_state;
	new_event->manual_reset = manual_reset;
	if (::pthread_mutex_init(&(new_event->mutex), NULL)) {
		return NULL;
	}
	if (::pthread_cond_init(&(new_event->cond), NULL)) {
		::pthread_mutex_destroy(&(new_event->mutex));
		return NULL;
	}
	return new_event.release();
}

void internal_event_destroy(struct internal_event_t* event) {
	auto_ptr<struct internal_event_t> del_event(event);
	::pthread_cond_destroy(&(del_event->cond));
	::pthread_mutex_destroy(&(del_event->mutex));
}

int internal_event_set(struct internal_event_t* event) {
	if (::pthread_mutex_lock(&(event->mutex)) != 0) {
		return -1;
	}

	{
		event->state = true;
		if (event->manual_reset) {
			if (::pthread_cond_broadcast(&(event->cond))) {
				return -1;
			}
		} else {
			if (::pthread_cond_signal(&(event->cond))) {
				return -1;
			}
		}
	}

	if (::pthread_mutex_unlock(&(event->mutex)) != 0) {
		return -1;
	}
	return 0;
}

int internal_event_reset(struct internal_event_t* event) {
	if (::pthread_mutex_lock(&(event->mutex)) != 0) {
		return -1;
	}

	{
		event->state = false;
	}

	if (::pthread_mutex_unlock(&(event->mutex)) != 0) {
		return -1;
	}
	return 0;
}

int internal_event_wait(struct internal_event_t* event) {
	if (::pthread_mutex_lock(&(event->mutex)) != 0) {
		return -1;
	}

	{
		while (!event->state) {
			if (::pthread_cond_wait(&(event->cond), &(event->mutex))) {
				::pthread_mutex_unlock(&(event->mutex));
				return -1;
			}
		}
		if (!event->manual_reset) {
			event->state = false;
		}
	}

	if (::pthread_mutex_unlock(&(event->mutex)) != 0) {
		return -1;
	}
	return 0;
}
int internal_event_timedwait(struct internal_event_t* event, long milliseconds) {
	int rc = 0;
	struct timespec abstime;
	struct timeval tv;
	::gettimeofday(&tv, NULL);
	abstime.tv_sec = tv.tv_sec + milliseconds / 1000;
	abstime.tv_nsec = tv.tv_usec * 1000 + (milliseconds % 1000) * 1000000;
	if (abstime.tv_nsec >= 1000000000) {
		abstime.tv_nsec -= 1000000000;
		abstime.tv_sec += 1;
	}

	if (::pthread_mutex_lock(&(event->mutex)) != 0) {
		return -1;
	}

	{
		while (!event->state) {
			if ((rc = ::pthread_cond_timedwait(&(event->cond), &(event->mutex),
					&abstime))) {
				if (rc == ETIMEDOUT)
					break;
				::pthread_mutex_unlock(&(event->mutex));
				return -1;
			}
		}
		if (rc == 0 && !event->manual_reset) {
			event->state = false;
		}
	}

	if (::pthread_mutex_unlock(&(event->mutex)) != 0) {
		return -1;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
namespace node
{
	event_impl::event_impl(bool auto_reset, bool init_state)
	 : event_(internal_event_create(!auto_reset, init_state)) {
		assert(event_ != NULL);
	}

	event_impl::~event_impl(void) {
		if (event_ != NULL) {
			internal_event_destroy (event_);
		}
	}

	void event_impl::set_impl(void) {
		assert(internal_event_set(event_) == 0);
	}

	void event_impl::reset_impl(void) {
		assert(internal_event_reset(event_) == 0);
	}

	void event_impl::wait_impl(void) {
		assert(internal_event_wait(event_) == 0);
	}

	void event_impl::wait_impl(long milliseconds) {
		assert(internal_event_timedwait(event_, milliseconds) == 0);
	}
}
