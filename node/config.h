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

#ifndef NODECPP_FOUNDATION_CONFIG_H_
#define NODECPP_FOUNDATION_CONFIG_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#ifndef PLATFORM_WINDOWS
#define PLATFORM_WINDOWS
#endif // PLATFORM_WINDOWS

#ifndef ARCH_X86
#define ARCH_X86
#endif // ARCH_X86

#ifndef ENDIAN_LITTLE
#define ENDIAN_LITTLE
#endif // ENDIAN_LITTLE

#endif // NODECPP_FOUNDATION_CONFIG_H_
