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

#include "node/net/buffer_event.h"
#include <cassert>

namespace node {
    namespace net {

        buffer_event::buffer_event(void)
            : buff_ev_(NULL)
            , user_data_(NULL)
        {

        }

        buffer_event::~buffer_event(void)
        {
            if (buff_ev_ != NULL) {
                ::bufferevent_free(buff_ev_);
            }
        }

        bool buffer_event::init(evutil_socket_t fd, int options, void* user_data)
        {
            user_data_ = user_data;
            buff_ev_ = ::bufferevent_socket_new(NULL, fd, options);
            return (buff_ev_ != NULL);
        }

        void buffer_event::set_callbacks(bufferevent_data_cb read_cb, 
            bufferevent_data_cb write_cb, bufferevent_event_cb event_cb)
        {
            ::bufferevent_setcb(buff_ev_, read_cb, write_cb, event_cb, user_data_);
        }

    }
}