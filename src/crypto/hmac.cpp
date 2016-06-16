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

#include "node/crypto/hmac.h"
#include <cassert>
#include <cstring>
#include "node/crypto/bignumber.h"

namespace node
{
    hmac_hash::hmac_hash(void)
    {
        std::uint8_t temp[SEED_KEY_SIZE] = { 0x38, 0xA7, 0x83, 0x15, 0xF8, 0x92,
            0x25, 0x30, 0x71, 0x98, 0x67, 0xB1, 0x8C, 0x4, 0xE2, 0xAA };
        memcpy(&key_, &temp, SEED_KEY_SIZE);
        HMAC_CTX_init(&hmac_ctx_);
        HMAC_Init_ex(&hmac_ctx_, &key_, SEED_KEY_SIZE, EVP_sha1(), NULL);
    }

    hmac_hash::~hmac_hash(void)
    {
        memset(&key_, 0x00, SEED_KEY_SIZE);
        HMAC_CTX_cleanup(&hmac_ctx_);
    }

    void hmac_hash::initialize(void)
    {
        HMAC_Init_ex(&hmac_ctx_, &key_, SEED_KEY_SIZE, EVP_sha1(), NULL);
    }

    void hmac_hash::finalize(void)
    {
        std::uint32_t size = 0;
        HMAC_Final(&hmac_ctx_, digest_, &size);
        assert(size == SHA_DIGEST_LENGTH);
    }

    void hmac_hash::update_bignumber(bignumber* bn)
    {
        update_data(bn->as_byte_array(), bn->get_num_bytes());
    }

    void hmac_hash::update_data(const std::uint8_t* str, std::size_t length)
    {
        HMAC_Update(&hmac_ctx_, str, length);
    }

    const std::uint8_t* hmac_hash::digest(void) const
    {
        return &digest_[0];
    }

    std::size_t hmac_hash::length(void) const
    {
        return SHA_DIGEST_LENGTH;
    }
}