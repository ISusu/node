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

#include "node/byte_buffer.h"
#include <cassert>
#include "node/os/string.h"

namespace node
{
    byte_buffer_exception::byte_buffer_exception(bool add, std::size_t pos, 
        std::size_t op_size, std::size_t buf_size)
    {
        node::snprintf(message_, EXCEP_BUFF_SIZE, 
            "Try %s %d bytes at pos(%d), buffer size(%d)", 
            add ? "add" : "read", op_size, pos, buf_size);
    }

    byte_buffer_exception::byte_buffer_exception(const byte_buffer_exception& excep)
    {
        memcpy(&message_[0], &excep.message_[0], EXCEP_BUFF_SIZE);
    }

    byte_buffer_exception::~byte_buffer_exception(void) throw()
    {

    }


    byte_buffer::byte_buffer(void)
        : rpos_(0)
        , wpos_(0)
        , storage_()
    {
        storage_.reserve(DEFAULT_SIZE);
    }

    byte_buffer::byte_buffer(size_type _res)
        : rpos_(0)
        , wpos_(0)
        , storage_()
    {
        storage_.reserve(_res);
    }

    byte_buffer::byte_buffer(const byte_buffer& _buf)
        : rpos_(0)
        , wpos_(0)
        , storage_(_buf.storage_)
    {

    }

    byte_buffer::~byte_buffer(void)
    {

    }
}
