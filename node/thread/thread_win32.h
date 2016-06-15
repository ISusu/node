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

#ifndef NODE_THREAD_THREAD_WIN32_H_
#define NODE_THREAD_THREAD_WIN32_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <process.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <node/noncopyable.h>
#include <node/thread/event.h>

namespace node
{
    class runnable;

    class thread_impl : private noncopyable
    {
    public:
        enum priority
        {
            PRIO_LOWEST_IMPL = THREAD_PRIORITY_LOWEST,
            PRIO_LOW_IMPL = THREAD_PRIORITY_BELOW_NORMAL,
            PRIO_NORMAL_IMPL = THREAD_PRIORITY_NORMAL,
            PRIO_HIGH_IMPL = THREAD_PRIORITY_ABOVE_NORMAL,
            PRIO_HIGHEST_IMPL = THREAD_PRIORITY_HIGHEST
        };
        typedef DWORD   id;

        thread_impl(void);
        ~thread_impl(void);

        bool start_impl(runnable*);
        void join_impl(void);
        bool joinable_impl(void);
        bool set_priority_impl(int);
        priority get_priority_impl(void) const { return priority_; }
        id get_id_impl(void) const { return id_; }

    private:
        static unsigned int __stdcall _proc(void*);

        id id_;
        uintptr_t handle_;
        runnable* runnable_;
        priority priority_;
        event start_event_;
    };

    class this_thread_impl : private noncopyable
    {
    private:
        this_thread_impl(void){}
        ~this_thread_impl(void){}

    public:
        static thread_impl::id get_id_impl(void);
        static void sleep_impl(long);
    };
}

#endif // NODE_THREAD_THREAD_WIN32_H_
