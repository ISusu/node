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

#ifndef NODE_ATOMIC_VALUE_H_
#define NODE_ATOMIC_VALUE_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <cassert>
#include <cstdint>
#include <node/thread/mutex.h>
#include <node/thread/lock_guard.h>
namespace node
{

    template<typename T>
    class atomic_value
    {
    public:
        atomic_value(const T &value) 
            : mutex_(), value_(value) {  }
        atomic_value(const atomic_value& value) 
            : mutex_(), value_(value.value_) {  }
        ~atomic_value(void){  }

        T operator++(void)
        {
            lock_guard<mutex> guard(mutex_);
            return ++value_;
        }

        T operator--(void)
        {
            lock_guard<mutex> guard(mutex_);
            return --value_;
        }

        atomic_value& operator=(const T& value)
        {
            lock_guard<mutex> guard(mutex_);
            value_ = value;
            return *this;
        }

        operator T(void) const { return value_; }

    private:
        mutex mutex_;
        volatile T value_;
    };

    typedef atomic_value<std::int8_t> atomic_value_int8;
    typedef atomic_value<std::uint8_t> atomic_value_uint8;
    typedef atomic_value<std::int16_t> atomic_value_int16;
    typedef atomic_value<std::uint16_t> atomic_value_uint16;
    typedef atomic_value<std::int32_t> atomic_value_int32;
    typedef atomic_value<std::uint32_t> atomic_value_uint32;
    typedef atomic_value<std::int64_t> atomic_value_int64;
    typedef atomic_value<std::uint64_t> atomic_value_uint64;

}

#endif // NODE_ATOMIC_VALUE_H_
