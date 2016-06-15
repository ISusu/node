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

#ifndef NODE_THREAD_MUTEX_POSIX_H_
#define NODE_THREAD_MUTEX_POSIX_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <assert.h>
#include <pthread.h>
#include <node/noncopyable.h>

namespace node
{
	class mutex_impl : private noncopyable
	{
	public:
		mutex_impl(void);
		~mutex_impl(void) {
			::pthread_mutex_destroy(&mutex_);
		}

		void lock_impl(void) {
			assert(::pthread_mutex_lock(&mutex_) == 0);
		}

		void unlock_impl(void) {
			assert(::pthread_mutex_unlock(&mutex_) == 0);
		}

		bool try_lock_impl(void) {
			return (::pthread_mutex_trylock(&mutex_) == 0);
		}

	private:
		pthread_mutex_t mutex_;
	};
}

#endif /* NODE_THREAD_MUTEX_POSIX_H_ */
