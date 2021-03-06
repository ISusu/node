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

#include "node/crypto/sha1.h"
#include <cstdarg>
#include "node/crypto/bignumber.h"

namespace node
{
    sha1_hash::sha1_hash(void)
    {
        SHA1_Init(&sha_ctx_);
    }

    sha1_hash::~sha1_hash(void)
    {
        SHA1_Init(&sha_ctx_);
    }

    void sha1_hash::initialize(void)
    {
        SHA1_Init(&sha_ctx_);
    }

    void sha1_hash::finalize(void)
    {
        SHA1_Final(digest_, &sha_ctx_);
    }

    void sha1_hash::update_bignumbers(bignumber* bn, ...)
    {
        std::va_list arg;
        bignumber* xbn;

        va_start(arg, bn);
        xbn = bn;
        while (xbn)
        {
            update_data(xbn->as_byte_array(), xbn->get_num_bytes());
            xbn = va_arg(arg, bignumber*);
        }
        va_end(arg);
    }

    void sha1_hash::update_data(const std::uint8_t* str, std::size_t length)
    {
        SHA1_Update(&sha_ctx_, (const void*)str, length);
    }

    void sha1_hash::update_data(const std::string& str)
    {
        SHA1_Update(&sha_ctx_, (const void*)str.c_str(), str.length());
    }

    const std::uint8_t* sha1_hash::digest(void) const
    {
        return &digest_[0];
    }

    std::size_t sha1_hash::length(void) const
    {
        return SHA_DIGEST_LENGTH;
    }
}