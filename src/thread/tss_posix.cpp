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

#include "node/thread/tss_posix.h"
#include <assert.h>

namespace node
{
    tss_impl::tss_impl(void)
        : tls_key_()
    {
        assert(::pthread_key_create(&tls_key_, NULL) == 0);
    }

    tss_impl::~tss_impl(void)
    {
        assert(::pthread_key_delete(tls_key_) == 0);
    }

    void* tss_impl::get_impl(void) const
    {
        return ::pthread_getspecific(tls_key_);
    }

    void tss_impl::set_impl(const void* value)
    {
        assert(::pthread_setspecific(tls_key_, value));
    }
}
