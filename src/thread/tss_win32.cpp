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

#include "node/thread/tss_win32.h"
#include <assert.h>

namespace node
{
    tss_impl::tss_impl(void)
        : tls_index_(::TlsAlloc())
    {
        assert(tls_index_ != TLS_OUT_OF_INDEXES);
    }

    tss_impl::~tss_impl(void)
    {
        assert(::TlsFree(tls_index_));
    }

    void* tss_impl::get_impl(void) const
    {
        return ::TlsGetValue(tls_index_);
    }

    void tss_impl::set_impl(const void* value)
    {
        assert(::TlsSetValue(tls_index_, const_cast<void*>(value)));
    }
}