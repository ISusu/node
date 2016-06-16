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

#ifndef NODE_NET_BUFFER_EVENT_H_
#define NODE_NET_BUFFER_EVENT_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <event2/bufferevent.h>

namespace node {
    namespace net {

        class event_loop;

        class buffer_event
        {
        public:
            buffer_event(void);
            ~buffer_event(void);

            bool init(evutil_socket_t, int, void*);
            void set_callbacks(bufferevent_data_cb, bufferevent_data_cb, bufferevent_event_cb);

        private:
            friend class event_loop;

            struct ::bufferevent* buff_ev_;
            void* user_data_;
        };

    }
}

#endif // NODE_NET_BUFFER_EVENT_H_
