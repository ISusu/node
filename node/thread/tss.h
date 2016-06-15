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

#ifndef NODE_THREAD_TSS_H_
#define NODE_THREAD_TSS_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <node/noncopyable.h>
#include <node/platform.h>
#if defined(PLATFORM_WINDOWS)
#include <node/thread/tss_win32.h>
#else
#error "platform not support"
#endif // defined(PLATFORM_WINDOWS)

namespace node
{
    class tss : private tss_impl
    {
    public:
        tss(void) {}
        ~tss(void) {}

        void* get(void) const { return get_impl(); }
        void set(void* value) { set_impl(value); }
    };

    template<typename T>
    class thread_specific_ptr : private noncopyable
    {
    public:
        thread_specific_ptr(T* = 0);
        ~thread_specific_ptr(void);

        T* release(void);
        void reset(T* = 0);

        T* get(void) const;
        T* operator->(void) const;
        T& operator*(void) const;

    private:
        tss tss_;
    };

    //-------------------------------------------------------------------------
    template<typename T> thread_specific_ptr<T>::thread_specific_ptr(T* value  /* = 0 */)
        : tss_()
    {
        tss_.set(value);
    }
    template<typename T> thread_specific_ptr<T>::~thread_specific_ptr(void)
    {
        reset();
    }
    template<typename T> T* thread_specific_ptr<T>::release(void)
    {
        T* value = static_cast<T*>(tss_.get());
        tss_.set(0);
        return value;
    }
    template<typename T> void thread_specific_ptr<T>::reset(T* new_value /* = 0 */)
    {
        T* current_value = static_cast<T*>(tss_.get());
        tss_.set(new_value);
        if (current_value) {
            delete current_value;
        }
    }
    template<typename T> T* thread_specific_ptr<T>::get(void) const
    {
        return static_cast<T*>(tss_.get());
    }
    template <typename T> T* thread_specific_ptr<T>::operator->(void) const
    {
        return static_cast<T*>(tss_.get());
    }
    template <typename T> T& thread_specific_ptr<T>::operator*(void) const
    {
        return *(static_cast<T*>(tss_.get()));
    }
}

#endif // NODE_THREAD_TSS_H_
