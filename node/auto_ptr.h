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

#ifndef NODE_AUTO_PTR_H_
#define NODE_AUTO_PTR_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <node/macros.h>

namespace node
{
    template<class T>
    class auto_ptr
    {
    public:
        auto_ptr(T* ptr = 0) : ptr_(ptr) {}
        auto_ptr(const auto_ptr& ptr) : ptr_(ptr.release()) {}
        ~auto_ptr(void) { SAFE_DEL(ptr) }

        void operator=(const auto_ptr& ptr)
        {
            SAFE_DEL(ptr);
            ptr_ = ptr.release();
        }

        T* operator->(void)
        {
            return ptr_;
        }

        T* operator->(void) const
        {
            return ptr_;
        }

        T& operator*(void) const
        {
            return *ptr_;
        }

        operator bool(void) const
        {
            return ptr_ != 0;
        }

        T* get(void)
        {
            return ptr_;
        }

        T* get(void) const
        {
            return ptr_;
        }

        T* release(void) const
        {
            T* ptr = ptr_;
            ptr_ = 0;
            return ptr;
        }

        void reset(T* ptr = 0)
        {
            SAFE_DEL(ptr_);
            ptr_ = ptr;
        }

    private:
        mutable T* ptr_;
    };
}

#endif // NODE_AUTO_PTR_H_
