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

#ifndef NODE_BYTE_BUFFER_INL_
#define NODE_BYTE_BUFFER_INL_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <cassert>
#include <cstring>
#include <node/byte_converter.h>
#include <node/byte_buffer.h>

namespace node
{
    inline const char* byte_buffer_exception::what(void) const throw()
    {
        return &message_[0];
    }

    //-------------------------------------------------------------------------
    inline byte_buffer::size_type byte_buffer::capacity(void) const
    {
        return storage_.capacity();
    }

    inline byte_buffer::size_type byte_buffer::size(void) const
    {
        return storage_.size();
    }

    inline void byte_buffer::resize(size_type new_res)
    {
        storage_.resize(new_res);
    }

    inline const std::uint8_t* byte_buffer::rptr(byte_buffer::size_type pos) const
    {
        assert(storage_.size() > 0 && pos >= 0 && pos < storage_.size());
        return &storage_[pos];
    }

    inline std::uint8_t* byte_buffer::wptr(byte_buffer::size_type pos)
    {
        assert(storage_.size() > 0 && pos >= 0 && pos < storage_.size());
        return &storage_[pos];
    }

    inline byte_buffer::size_type byte_buffer::rpos(void) const
    {
        return rpos_;
    }

    inline void byte_buffer::rpos(byte_buffer::size_type pos)
    {
        rpos_ = pos;
    }

    inline byte_buffer::size_type byte_buffer::wpos(void) const
    {
        return wpos_;
    }

    inline void byte_buffer::wpos(byte_buffer::size_type pos)
    {
        wpos_ = pos;
    }

    inline void byte_buffer::append(const std::uint8_t* str, byte_buffer::size_type length)
    {
        if (length == 0) {
            return;
        }

        if ((length + wpos_) > MAX_SIZE) {
            throw byte_buffer_exception(true, wpos_, length, size());
        }

        if (storage_.capacity() < (length + wpos_)) {
            storage_.resize(length + wpos_);
        }

        memcpy(&storage_[wpos_], str, length);
        wpos_ += length;
    }

    inline void byte_buffer::append(const byte_buffer& buf)
    {
        append(buf.rptr(0), buf.size());
    }

    inline void byte_buffer::read(std::uint8_t* str, byte_buffer::size_type length)
    {
        if ((rpos_ + length) > size())
        {
            throw byte_buffer_exception(false, rpos_, length, size());
        }
        memcpy(str, &storage_[rpos_], length);
        rpos_ += length;
    }

    template<typename T> inline T byte_buffer::read(void)
    {
        T _ret = read<T>(rpos_);
        rpos_ += sizeof(T);
        return _ret;
    }

    inline void byte_buffer::put(byte_buffer::size_type pos, const std::uint8_t* str, byte_buffer::size_type length)
    {
        if ((pos + length) > size()) {
            throw byte_buffer_exception(true, pos, length, size());
        }
        memcpy(&storage_[pos], str, length);
    }

    //-------------------------------------------------------------------------
    inline byte_buffer& byte_buffer::operator>>(std::uint8_t& value)
    {
        value = read<std::uint8_t>();
        return *this;
    }

    inline byte_buffer& byte_buffer::operator>>(std::int8_t& value)
    {
        value = read<std::int8_t>();
        return *this;
    }

    inline byte_buffer& byte_buffer::operator>>(std::uint16_t& value)
    {
        value = read<std::uint16_t>();
        return *this;
    }

    inline byte_buffer& byte_buffer::operator>>(std::int16_t& value)
    {
        value = read<std::int16_t>();
        return *this;
    }

    inline byte_buffer& byte_buffer::operator>>(std::uint32_t& value)
    {
        value = read<std::uint32_t>();
        return *this;
    }

    inline byte_buffer& byte_buffer::operator>>(std::int32_t& value)
    {
        value = read<std::int32_t>();
        return *this;
    }

    inline byte_buffer& byte_buffer::operator>>(std::uint64_t& value)
    {
        value = read<std::uint64_t>();
        return *this;
    }

    inline byte_buffer& byte_buffer::operator>>(std::int64_t& value)
    {
        value = read<std::int64_t>();
        return *this;
    }

    inline byte_buffer& byte_buffer::operator>>(std::string& value)
    {
        value.clear();
        while (rpos_ < size())
        {
            char _c = read<char>();
            if (_c == '\0')
            {
                break;
            }
            value += _c;
        }
        return *this;
    }

    inline byte_buffer& byte_buffer::operator>>(float& value)
    {
        value = read<float>();
        return *this;
    }

    inline byte_buffer& byte_buffer::operator>>(double& value)
    {
        value = read<double>();
        return *this;
    }

    inline byte_buffer& byte_buffer::operator<<(std::uint8_t value)
    {
        append<std::uint8_t>(value);
        return *this;
    }

    inline byte_buffer& byte_buffer::operator<<(std::int8_t value)
    {
        append<std::int8_t>(value);
        return *this;
    }

    inline byte_buffer& byte_buffer::operator<<(std::uint16_t value)
    {
        append<std::uint16_t>(value);
        return *this;
    }

    inline byte_buffer& byte_buffer::operator<<(std::int16_t value)
    {
        append<std::int16_t>(value);
        return *this;
    }

    inline byte_buffer& byte_buffer::operator<<(std::uint32_t value)
    {
        append<std::uint32_t>(value);
        return *this;
    }

    inline byte_buffer& byte_buffer::operator<<(std::int32_t value)
    {
        append<std::int32_t>(value);
        return *this;
    }

    inline byte_buffer& byte_buffer::operator<<(const std::uint64_t& value)
    {
        append<std::uint64_t>(value);
        return *this;
    }

    inline byte_buffer& byte_buffer::operator<<(const std::int64_t& value)
    {
        append<std::int64_t>(value);
        return *this;
    }

    inline byte_buffer& byte_buffer::operator<<(const std::string& value)
    {
        append((const std::uint8_t*)value.c_str(), value.size());
        append<std::uint8_t>(0);
        return *this;
    }

    inline byte_buffer& byte_buffer::operator<<(const float& value)
    {
        append<float>(value);
        return *this;
    }

    inline byte_buffer& byte_buffer::operator<<(const double& value)
    {
        append<double>(value);
        return *this;
    }

    //-------------------------------------------------------------------------
    template<typename T> inline void byte_buffer::append(const T& value)
    {
        T temp = value;
        byte_converter::endian_convert(temp);
        append((const std::uint8_t*)&temp, sizeof(T));
    }

    template<typename T> inline T byte_buffer::read(byte_buffer::size_type pos)
    {
        if (pos + sizeof(T) > size()) {
            throw byte_buffer_exception(false, pos, sizeof(T), size());
        }
        T ret = *((T const*)&storage_[pos]);
        byte_converter::endian_convert(ret);
        return ret;
    }

    template<typename T> inline void byte_buffer::put(byte_buffer::size_type pos, T& value)
    {
        byte_converter::endian_convert(value);
        put(pos, (const std::uint8_t*)&value, sizeof(T));
    }

    template<> inline void byte_buffer::put(byte_buffer::size_type pos, std::string& value)
    {
        put(pos, (const std::uint8_t*)value.c_str(), value.size());
    }
}

#endif // NODE_BYTE_BUFFER_INL_
