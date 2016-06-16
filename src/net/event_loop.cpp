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

#include "node/net/event_loop.h"
#include <cassert>
#include "node/net/event_.h"
#include "node/net/buffer_event.h"

namespace node {
    namespace net {

        event_loop::event_loop(void)
            : ev_base_(::event_base_new())
        {
            assert(ev_base_ != NULL);
        }

        event_loop::~event_loop(void)
        {
            ::event_base_free(ev_base_);
        }

        bool event_loop::add_event(const event& evt)
        {
            assert(evt.event_);
            event_base_set(ev_base_, evt.event_);
            if (evt.timeout_) {
                return (event_add(evt.event_, &evt.tv_) == 0);
            }
            return (event_add(evt.event_, NULL) == 0);
        }

        void event_loop::del_event(const event& evt)
        {
            assert(evt.event_);
            event_del(evt.event_);
        }

        bool event_loop::add_event(const buffer_event& evt)
        {
            assert(evt.buff_ev_);
            return (::bufferevent_base_set(ev_base_, evt.buff_ev_) == 0);
        }

        void event_loop::del_event(const buffer_event& evt)
        {
            assert(evt.buff_ev_);
            ::bufferevent_disable(evt.buff_ev_, EV_READ | EV_WRITE);
        }

        bool event_loop::loop(void)
        {
            return (::event_base_dispatch(ev_base_) == 0);
        }

        bool event_loop::loop_once(void)
        {
            return (::event_base_loop(ev_base_, 
                EVLOOP_ONCE | EVLOOP_NONBLOCK) == 0);
        }

        bool event_loop::loop_break(void)
        {
            return (::event_base_loopbreak(ev_base_) == 0);
        }

    }
}