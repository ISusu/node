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

#ifndef NODE_BYTE_BUFFER_H_
#define NODE_BYTE_BUFFER_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <exception>

namespace node
{
    class byte_buffer_exception : public std::exception
    {
    public:
        const static std::size_t EXCEP_BUFF_SIZE = 128;

        byte_buffer_exception(bool, std::size_t, 
            std::size_t, std::size_t);
        byte_buffer_exception(const byte_buffer_exception&);
        ~byte_buffer_exception(void);

        const char* what(void) const throw();

    private:
        char message_[EXCEP_BUFF_SIZE];
    };


    class byte_buffer
    {
    public:
        typedef std::vector<std::uint8_t>   storage;
        typedef storage::size_type          size_type;
        typedef byte_buffer                 self;

        const static size_type DEFAULT_SIZE = 0x1000;
        const static size_type MAX_SIZE = 0x1000000;

        byte_buffer(void);
        byte_buffer(size_type);
        byte_buffer(const byte_buffer&);
        ~byte_buffer(void);

        size_type capacity(void) const;
        size_type size(void) const;
        void resize(size_type);

        const std::uint8_t* rptr(size_type) const;
        std::uint8_t* wptr(size_type);

        size_type rpos(void) const;
        void rpos(size_type);

        size_type wpos(void) const;
        void wpos(size_type);

        void append(const std::uint8_t*, size_type);
        void append(const byte_buffer&);

        void read(std::uint8_t*, size_type);
        template<typename T> T read(void);

        void put(size_type, const std::uint8_t*, size_type);

        self& operator>>(std::uint8_t&);
        self& operator>>(std::int8_t&);
        self& operator>>(std::uint16_t&);
        self& operator>>(std::int16_t&);
        self& operator>>(std::uint32_t&);
        self& operator>>(std::int32_t&);
        self& operator>>(std::uint64_t&);
        self& operator>>(std::int64_t&);
        self& operator>>(std::string&);
        self& operator>>(float&);
        self& operator>>(double&);

        self& operator<<(std::uint8_t);
        self& operator<<(std::int8_t);
        self& operator<<(std::uint16_t);
        self& operator<<(std::int16_t);
        self& operator<<(std::uint32_t);
        self& operator<<(std::int32_t);
        self& operator<<(const std::uint64_t&);
        self& operator<<(const std::int64_t&);
        self& operator<<(const std::string&);
        self& operator<<(const float&);
        self& operator<<(const double&);

    private:
        template<typename T> void append(const T&);
        template<typename T> T read(size_type);
        template<typename T> void put(size_type, T&);

        size_type rpos_;
        size_type wpos_;
        storage storage_;
    };
}

#include <node/byte_buffer.inl>

#endif // NODE_BYTE_BUFFER_H_
