/* Copyright (C) 2017 Sam Bazley and Arnau Bigas
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include "YACE_Event.h"
#include <vector>
#include <utility>

static std::vector< std::pair<uint32_t, YACE::EventCallback> > eventListeners;

void YACE::event_registerListener(YACE::EventCallback function, uint32_t events)
{
    eventListeners.push_back(
            std::pair<uint32_t, YACE::EventCallback>(events, function));
}

void YACE::event_send(YACE::Event &event)
{
    for(std::pair<uint32_t, YACE::EventCallback> listener : eventListeners) {
        if(listener.first & event.type) {
            listener.second(event);
        }
    }
}
