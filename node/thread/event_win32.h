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

#ifndef NODE_THREAD_EVENT_WIN32_H_
#define NODE_THREAD_EVENT_WIN32_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <assert.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <node/noncopyable.h>

namespace node
{
    class event_impl : private noncopyable
    {
    public:
        event_impl(bool auto_reset, bool init_state);
        ~event_impl(void);

        void set_impl(void) { assert(::SetEvent(event_)); }
        void reset_impl(void) { assert(::ResetEvent(event_)); }
        void wait_impl(void) 
        { assert(::WaitForSingleObject(event_, INFINITE) != WAIT_FAILED); }
        void wait_impl(long milliseconds) 
        { assert(::WaitForSingleObject(event_, milliseconds) != WAIT_FAILED); }

    private:
        HANDLE event_;
    };
}

#endif // NODE_THREAD_EVENT_WIN32_H_
