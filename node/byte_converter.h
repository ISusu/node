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

#ifndef NODE_BYTE_CONVERTER_H_
#define NODE_BYTE_CONVERTER_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <cstddef>
#include <algorithm>
#include <cstdint>
#include <node/platform.h>

namespace node {
    namespace byte_converter {

        template<std::size_t T>
        inline void convert(char* value)
        {
            std::swap(*value, *(value + T - 1));
            convert < T - 2 >(value + 1);
        }

        template<> inline void convert<0>(char*) {}
        template<> inline void convert<1>(char*) {}

        template<typename T>
        inline void apply(T* value)
        {
            convert<sizeof(T)>((char*)(value));
        }


#if defined(ENDIAN_BIG)
        template<typename T> inline void endian_convert(T& value) { apply<T>(&value); }
        template<typename T> inline void endian_convert_reverse(T&) { }
#else
        template<typename T> inline void endian_convert(T&) { }
        template<typename T> inline void endian_convert_reverse(T& value) { apply<T>(&value); }
#endif

        template<typename T> void endian_convert(T*);
        template<typename T> void endian_convert_reverse(T*);
        inline void endian_convert(std::uint8_t&) { }
        inline void endian_convert(std::int8_t&)  { }
        inline void endian_convert_reverse(std::uint8_t&) { }
        inline void endian_convert_reverse(std::int8_t&) { }

    }
}

#endif // NODE_BYTE_CONVERTER_H_
