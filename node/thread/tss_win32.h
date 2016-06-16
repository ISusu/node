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

#ifndef NODE_THREAD_TSS_WIN32_H_
#define NODE_THREAD_TSS_WIN32_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <node/noncopyable.h>

namespace node
{
    class tss_impl : private noncopyable
    {
    public:
        tss_impl(void);
        ~tss_impl(void);

        void* get_impl(void) const;
        void set_impl(const void*);

    private:
        DWORD tls_index_;
    };
}

#endif // NODE_THREAD_TSS_WIN32_H_
