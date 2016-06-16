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

#ifndef NODE_NET_ACCEPTOR_H_
#define NODE_NET_ACCEPTOR_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <string>
#include <event2/listener.h>
#include <node/auto_ptr.h>
#include <node/noncopyable.h>
#include <node/net/worker.h>

namespace node {
    namespace net {

        class event_loop;
        class stream_socket_factory;

        class acceptor : private noncopyable
        {
        public:
            acceptor(event_loop*, stream_socket_factory*);
            acceptor(workers*, stream_socket_factory*);
            ~acceptor(void);

            bool open(const std::string&, int, int);
            void suspend(void);
            void resume(void);

        private:
            event_loop* main_loop_;
            workers* net_workers_;
            node::auto_ptr<stream_socket_factory> ss_factory_;
            
            struct ::evconnlistener* ev_listener_;
        };
    }
}

#endif // NODE_NET_ACCEPTOR_H_
