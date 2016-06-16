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

#ifndef NODE_CRYPTO_BIGNUMBER_H_
#define NODE_CRYPTO_BIGNUMBER_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <cstddef>
#include <cstdint>
#include <node/scoped_array.h>

struct bignum_st;

namespace node
{
    class bignumber
    {
    public:
        bignumber(void);
        bignumber(const bignumber&);
        bignumber(std::uint32_t);
        ~bignumber(void);

        void set_uint32(std::uint32_t);
        void set_uint64(std::uint64_t);
        void set_binary(const std::uint8_t*, int);
        void set_hex_str(const char*);
        void set_rand(int);

        bool is_zero(void) const;
        bignumber mod_exp(const bignumber&, const bignumber&);
        bignumber exp(const bignumber&);
        int get_num_bytes(void) const;
        struct bignum_st* bn(void) const;
        std::uint32_t as_uint32(void) const;
        std::uint8_t* as_byte_array(int = 0);
        const char* as_hex_str(void) const;
        const char* as_dec_str(void) const;
        static void free_str(void*);

        bignumber& operator=(const bignumber&);
        bignumber& operator+=(const bignumber&);
        bignumber operator+(const bignumber&);
        bignumber& operator-=(const bignumber&);
        bignumber operator-(const bignumber&);
        bignumber& operator*=(const bignumber&);
        bignumber operator*(const bignumber&);
        bignumber& operator/=(const bignumber&);
        bignumber operator/(const bignumber&);
        bignumber& operator%=(const bignumber&);
        bignumber operator%(const bignumber&);

    private:
        struct bignum_st* bn_;
        scoped_array<std::uint8_t> array_;
    };
}

#endif // NODE_CRYPTO_BIGNUMBER_H_
