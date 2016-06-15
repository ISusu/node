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

#include "node/thread/thread_posix.h"
#include <cassert>
#include <unistd.h>
#include <sched.h>
#include "node/thread/runnable.h"

namespace node
{
	thread_impl::thread_impl(void)
		: id_(0)
		, runnable_(NULL)
		, priority_(PRIO_NORMAL_IMPL)
		, start_event_() {
	}

	thread_impl::~thread_impl(void) {
	}

	bool thread_impl::start_impl(runnable* runnable) {
		assert(id_ == 0L);
		this->runnable_ = runnable;
		if (::pthread_create(&id_, NULL, thread_impl::_proc, this) == 0) {
			start_event_.wait();
			return true;
		}
		id_ = 0L;
		return false;
	}
	void thread_impl::join_impl(void) {
		assert(id_ != 0L);
		if (id_ != 0L) {
			::pthread_join(id_, NULL);
		}
	}

	bool thread_impl::joinable_impl(void) {
		return id_ != 0L;
	}

	bool thread_impl::set_priority_impl(int new_priority) {
#if defined(_POSIX_THREAD_PRIORITY_SCHEDULING)
		int policy;
		pthread_attr_t thread_attr;
		struct sched_param thread_param;
		if (::pthread_attr_getschedpolicy(&thread_attr, &policy) != 0) {
			return false;
		}
		if (::pthread_attr_getschedparam(&thread_attr, &thread_param) != 0) {
			return false;
		}
		int priority_min = ::sched_get_priority_min(policy);
		int priority_max = ::sched_get_priority_max(policy);
		int priority_step = (priority_max - priority_min) / 5;
		thread_param.sched_priority = priority_min + priority_step * new_priority;
		if (::pthread_attr_setschedparam(&thread_attr, &thread_param) != 0) {
			return false;
		}
		priority_ = priority(new_priority);
#endif
		return true;
	}

	void* thread_impl::_proc(void* arg) {
		assert(arg != NULL);
		thread_impl* th = static_cast<thread_impl*>(arg);
		th->start_event_.set();
		th->runnable_->run();
		return 0;
	}

	thread_impl::id this_thread_impl::get_id_impl(void) {
		return ::pthread_self();
	}

	void this_thread_impl::sleep_impl(long milliseconds) {
		::usleep(int(milliseconds * 1000));
	}
}
