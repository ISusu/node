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

#ifndef NODE_CRYPTO_SHA1_H_
#define NODE_CRYPTO_SHA1_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <cstddef>
#include <cstdint>
#include <string>
#include <openssl/sha.h>
#include <openssl/crypto.h>
#include <node/noncopyable.h>

namespace node
{
    class bignumber;

    class sha1_hash : private noncopyable
    {
    public:
        sha1_hash(void);
        ~sha1_hash(void);

        void initialize(void);
        void finalize(void);

        void update_bignumbers(bignumber*, ...);
        void update_data(const std::uint8_t*, std::size_t);
        void update_data(const std::string&);

        const std::uint8_t* digest(void) const;
        std::size_t length(void) const;

    private:
        SHA_CTX sha_ctx_;
        std::uint8_t digest_[SHA_DIGEST_LENGTH];
    };
}

#endif // NODE_CRYPTO_SHA1_H_
