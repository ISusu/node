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

#include "node/net/acceptor.h"
#include <cassert>
#include "node/net/stream_socket_factory.h"

namespace node {
    namespace net {

        acceptor::acceptor(event_loop* main_loop, 
            stream_socket_factory* ss_factory)
            : main_loop_(main_loop)
            , ss_factory_(ss_factory_)
            , net_workers_(NULL)
            , ev_listener_(NULL)
        {

        }

        acceptor::acceptor(workers* workers, 
            stream_socket_factory* ss_factory)
            : main_loop_(NULL)
            , ss_factory_(ss_factory_)
            , net_workers_(workers)
            , ev_listener_(NULL)
        {

        }

    }
}