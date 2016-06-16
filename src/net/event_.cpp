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

#include "node/net/event_.h"

namespace node {
    namespace net {

        event::event(void* user_data,event_callback_fn ev_cb_fn)
            : user_data_(user_data)
            , ev_cb_fn_(ev_cb_fn)
            , event_(NULL)
            , timeout_(false)
        {
            tv_.tv_sec = tv_.tv_usec = 0;
        }

        event::~event(void)
        {
            if (event_ != NULL) {
                event_free(event_);
            }
        }

        bool event::init_net(evutil_socket_t fd, short flags)
        {
            event_ = event_new(NULL, fd, flags, ev_cb_fn_, user_data_);
            return (event_ != NULL);
        }

        bool event::init_timeout(short flags, const struct timeval& tv)
        {
            tv_.tv_sec = tv.tv_sec; tv_.tv_usec = tv.tv_usec;
            event_ = event_new(NULL, -1, flags | EV_TIMEOUT, ev_cb_fn_, user_data_);
            return (event_ != NULL);
        }

    }
}