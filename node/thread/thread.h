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

#ifndef NODE_THREAD_THREAD_H_
#define NODE_THREAD_THREAD_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <node/platform.h>
#if defined(PLATFORM_WINDOWS)
#include <node/thread/thread_win32.h>
#elif defined(PLATFORM_LINUX)
#include <node/thread/thread_posix.h>
#else
#error "node threads unavailable on this platform"
#endif // defined(PLATFORM_WINDOWS)

namespace node
{
    class thread : private thread_impl
    {
    public:
        enum priority
        {
            PRIO_LOWEST = PRIO_LOWEST_IMPL,
            PRIO_LOW = PRIO_LOW_IMPL,
            PRIO_NORMAL = PRIO_NORMAL_IMPL,
            PRIO_HIGH = PRIO_HIGH_IMPL,
            PRIO_HIGHEST = PRIO_HIGHEST_IMPL
        };
        typedef thread_impl::id	id;

        thread(void) : thread_impl() {}
        ~thread(void) {}

        bool start(runnable* runnable) { return start_impl(runnable); }
        void join(void) { join_impl(); }
        bool joinable_impl(void) { return joinable_impl(); }
        bool set_priority(int new_priority) { return set_priority_impl(new_priority); }
        priority get_priority(void) const { return priority(get_priority_impl()); }
        id get_id(void) const { return get_id_impl(); }
    };

    class this_thread : private this_thread_impl
    {
    public:
        static thread::id get_id(void) { return get_id_impl(); }
        static void sleep(long milliseconds) { return sleep_impl(milliseconds); }

    private:
        this_thread(void);
        ~this_thread(void);
    };
}

#endif // NODE_THREAD_THREAD_H_
