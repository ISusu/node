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

#ifndef NODE_NET_EVENT__H_
#define NODE_NET_EVENT__H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <event2/event.h>

namespace node {
    namespace net {

        class event_loop;

        class event
        {
        public:
            event(void*, event_callback_fn);
            ~event(void);

            bool init_net(evutil_socket_t, short);
            bool init_timeout(short, const struct timeval&);

        private:
            friend class event_loop;

            void* user_data_;
            event_callback_fn ev_cb_fn_;
            struct ::event* event_;
            struct timeval tv_;
            bool timeout_;
        };

    }
}

#endif // NODE_NET_EVENT__H_
