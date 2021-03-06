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

#ifndef NODE_THREAD_MUTEX_H_
#define NODE_THREAD_MUTEX_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <node/noncopyable.h>
#include <node/platform.h>
#if defined(PLATFORM_WINDOWS)
#include <node/thread/mutex_win32.h>
#elif defined(PLATFORM_LINUX)
#include <node/thread/mutex_posix.h>
#else
#error "node threads unavailable on this platform"
#endif // defined(PLATFORM_WINDOWS)

namespace node
{
    class empty_mutex : private noncopyable
    {
    public:
        empty_mutex(void) {}
        ~empty_mutex(void) {}

        void lock(void) {}
        void unlock(void) {}
        bool try_lock(void) { return true; }
    };

    class mutex : private mutex_impl
    {
    public:
        mutex(void) {}
        ~mutex(void) {}

        void lock(void) { lock_impl(); }
        void unlock(void) { unlock_impl(); }
        bool try_lock(void) { return try_lock_impl(); }
    };
}

#endif // NODE_THREAD_MUTEX_H_
