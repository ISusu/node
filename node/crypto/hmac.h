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

#ifndef NODE_CRYPTO_HMAC_H_
#define NODE_CRYPTO_HMAC_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <cstddef>
#include <cstdint>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <node/noncopyable.h>

namespace node
{
    class bignumber;

    class hmac_hash : private noncopyable
    {
    public:
        const static int SEED_KEY_SIZE = 16;

        hmac_hash(void);
        ~hmac_hash(void);

        void initialize(void);
        void finalize(void);

        void update_bignumber(bignumber*);
        void update_data(const std::uint8_t*, std::size_t);
        
        const std::uint8_t* digest(void) const;
        std::size_t length(void) const;

    private:
        HMAC_CTX hmac_ctx_;
        std::uint8_t key_[SEED_KEY_SIZE];
        std::uint8_t digest_[SHA_DIGEST_LENGTH];
    };
}

#endif // NODE_CRYPTO_HMAC_H_
