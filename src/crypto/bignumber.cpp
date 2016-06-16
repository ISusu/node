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

#include "node/crypto/bignumber.h"
#include <memory.h>
#include <cassert>
#include <new>
#include <algorithm>
#include <openssl/bn.h>

namespace node
{
    bignumber::bignumber(void)
        : bn_(BN_new())
        , array_()
    {
        assert(bn_ != NULL);
    }

    bignumber::bignumber(const bignumber& value)
        : bn_(BN_dup(value.bn_))
        , array_()
    {
        assert(bn_ != NULL);
    }

    bignumber::bignumber(std::uint32_t value)
        : bn_(BN_new())
        , array_()
    {
        assert(bn_ != NULL);
        BN_set_word(bn_, value);
    }

    bignumber::~bignumber(void)
    {
        BN_free(bn_);
    }

    void bignumber::set_uint32(std::uint32_t value)
    {
        BN_set_word(bn_, value);
    }

    void bignumber::set_uint64(std::uint64_t value)
    {
        BN_add_word(bn_, (std::uint32_t)(value >> 32));
        BN_lshift(bn_, bn_, 32);
        BN_add_word(bn_, (std::uint32_t)(value & 0xFFFFFFFF));
    }

    void bignumber::set_binary(const std::uint8_t* str, int length)
    {
        std::uint8_t temp[1000];
        for (int i = 0; i < length; ++i) {
            temp[i] = str[length - 1 - i];
        }
        BN_bin2bn(temp, length, bn_);
    }

    void bignumber::set_hex_str(const char* str)
    {
        BN_hex2bn(&bn_, str);
    }

    void bignumber::set_rand(int bits)
    {
        BN_rand(bn_, bits, 0, 1);
    }

    bool bignumber::is_zero(void) const
    {
        return BN_is_zero(bn_) != 0;
    }

    bignumber bignumber::mod_exp(const bignumber& bn1, const bignumber& bn2)
    {
        bignumber ret;
        BN_CTX* bn_ctx;

        bn_ctx = BN_CTX_new();
        assert(bn_ctx != NULL);
        BN_mod_exp(ret.bn_, bn_, bn1.bn_, bn2.bn_, bn_ctx);
        BN_CTX_free(bn_ctx);

        return ret;
    }

    bignumber bignumber::exp(const bignumber& bn)
    {
        bignumber ret;
        BN_CTX* bn_ctx;

        bn_ctx = BN_CTX_new();
        assert(bn_ctx != NULL);
        BN_exp(ret.bn_, bn_, bn.bn_, bn_ctx);
        BN_CTX_free(bn_ctx);

        return ret;
    }

    int bignumber::get_num_bytes(void) const
    {
        return BN_num_bytes(bn_);
    }

    struct bignum_st* bignumber::bn(void) const
    {
        return bn_;
    }

    std::uint32_t bignumber::as_uint32(void) const
    {
        return (std::uint32_t)BN_get_word(bn_);
    }

    std::uint8_t* bignumber::as_byte_array(int min_size)
    {
        int length = NODE_MAX(min_size, get_num_bytes());
        array_.reset(new (std::nothrow) std::uint8_t[length]);
        assert(array_);
        if (length > get_num_bytes()) {
            memset((void*)array_.get(), 0, length);
        }
        BN_bn2bin(bn_, (unsigned char*)array_.get());
        std::reverse(array_.get(), array_.get() + length);
        return array_.get();
    }

    const char* bignumber::as_hex_str(void) const
    {
        return BN_bn2hex(bn_);
    }

    const char* bignumber::as_dec_str(void) const
    {
        return BN_bn2dec(bn_);
    }

    void bignumber::free_str(void* str)
    {
        assert(str != NULL);
        OPENSSL_free(str);
    }

    bignumber& bignumber::operator=(const bignumber& bn)
    {
        BN_copy(bn_, bn.bn_);
        return *this;
    }

    bignumber& bignumber::operator+=(const bignumber& bn)
    {
        BN_add(bn_, bn_, bn.bn_);
        return *this;
    }

    bignumber bignumber::operator+(const bignumber& bn)
    {
        bignumber temp(*this);
        return temp += bn;
    }

    bignumber& bignumber::operator-=(const bignumber& bn)
    {
        BN_sub(bn_, bn_, bn.bn_);
        return *this;
    }

    bignumber bignumber::operator-(const bignumber& bn)
    {
        bignumber temp(*this);
        return temp -= bn;
    }

    bignumber& bignumber::operator*=(const bignumber& bn)
    {
        BN_CTX* bn_ctx;

        bn_ctx = BN_CTX_new();
        assert(bn_ctx != NULL);
        BN_mul(bn_, bn_, bn.bn_, bn_ctx);
        BN_CTX_free(bn_ctx);

        return *this;
    }

    bignumber bignumber::operator*(const bignumber& bn)
    {
        bignumber temp(*this);
        return temp *= bn;
    }

    bignumber& bignumber::operator/=(const bignumber& bn)
    {
        BN_CTX* bn_ctx;

        bn_ctx = BN_CTX_new();
        assert(bn_ctx != NULL);
        BN_div(bn_, NULL, bn_, bn.bn_, bn_ctx);
        BN_CTX_free(bn_ctx);

        return *this;
    }

    bignumber bignumber::operator/(const bignumber& bn)
    {
        bignumber temp(*this);
        return temp /= bn;
    }

    bignumber& bignumber::operator%=(const bignumber& bn)
    {
        BN_CTX* bn_ctx;

        bn_ctx = BN_CTX_new();
        assert(bn_ctx != NULL);
        BN_mod(bn_, bn_, bn.bn_, bn_ctx);
        BN_CTX_free(bn_ctx);

        return *this;
    }

    bignumber bignumber::operator%(const bignumber& bn)
    {
        bignumber temp(*this);
        return temp %= bn;
    }
}