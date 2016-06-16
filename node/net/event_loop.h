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

#ifndef NODE_NET_EVENT_LOOP_H_
#define NODE_NET_EVENT_LOOP_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <ctime>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <node/noncopyable.h>

namespace node {
    namespace net {

        class event;
        class buffer_event;

        class event_loop : private noncopyable
        {
        public:
            event_loop(void);
            ~event_loop(void);

            bool add_event(const event&);
            void del_event(const event&);
            bool add_event(const buffer_event&);
            void del_event(const buffer_event&);

            bool loop(void);
            bool loop_once(void);
            bool loop_break(void);

        private:
            struct event_base* ev_base_;
        };

    }
}

#endif // NODE_NET_EVENT_LOOP_H_
