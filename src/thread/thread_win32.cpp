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

#include "node/thread/thread_win32.h"
#include <assert.h>
#include "node/thread/runnable.h"

namespace node
{
    thread_impl::thread_impl(void)
        : id_(0)
        , handle_(-1L)
        , runnable_(NULL)
        , priority_(PRIO_NORMAL_IMPL)
        , start_event_()
    {

    }

    thread_impl::~thread_impl(void)
    {
        if (handle_ != -1L) {
            ::CloseHandle((HANDLE)handle_);
        }
    }

    bool thread_impl::start_impl(runnable* runnable)
    {
        assert(handle_ == -1L);
        this->runnable_ = runnable;
        handle_ = _beginthreadex(NULL, 0, thread_impl::_proc,
            this, 0, (unsigned int*)&id_);
        if (handle_ == -1L) {
            return false;
        }
        start_event_.wait();
        return true;
    }

    void thread_impl::join_impl(void)
    {
        assert(handle_ != -1L);
        if (handle_ != -1L) {
            ::WaitForSingleObject(HANDLE(handle_), INFINITE);
        }
    }

    bool thread_impl::joinable_impl(void)
    {
        return handle_ != -1L;
    }

    bool thread_impl::set_priority_impl(int new_priority)
    {
        if (::SetThreadPriority((HANDLE)handle_, new_priority)) {
            priority_ = priority(new_priority);
            return true;
        }
        return false;
    }

    unsigned int thread_impl::_proc(void* arg)
    {
        assert(arg != NULL);
        thread_impl* th = static_cast<thread_impl*>(arg);
        th->start_event_.set();
        th->runnable_->run();
        return 0;
    }

    thread_impl::id this_thread_impl::get_id_impl(void)
    {
        return ::GetCurrentThreadId();
    }

    void this_thread_impl::sleep_impl(long milliseconds)
    {
        ::Sleep((DWORD)milliseconds);
    }
}