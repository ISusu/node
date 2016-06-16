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

#ifndef NODE_SCOPED_PTR_H_
#define NODE_SCOPED_PTR_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <node/macros.h>

namespace node
{
    template<class T>
    class scoped_ptr
    {
    public:
        scoped_ptr(T* ptr = NULL) : ptr_(ptr) {}
        ~scoped_ptr(void) { SAFE_DEL(ptr_); }

        T* operator->(void)
        {
            return ptr_;
        }

        operator bool(void) const
        {
            return ptr_ != NULL;
        }

        T* get(void)
        {
            return ptr_;
        }

        void reset(T* ptr = NULL)
        {
            SAFE_DEL(ptr_);
            ptr_ = ptr;
        }

    private:
        T* ptr_;
    };
}

#endif // NODE_SCOPED_PTR_H_
