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


#ifndef YACE_GAME_H
#define YACE_GAME_H

#define YACE_INIT_WINDOW  1
#define YACE_INIT_RENDER  2
#define YACE_INIT_AUDIO   4
#define YACE_INIT_NETWORK 8
#define YACE_INIT_ALL     16

namespace YACE {

    /**
     * This is the main init function to start the engine.
     * @param isServer Server flag, set it to true if the current instance
     * is a server.
     * @param uniqueString Unique string for this instance, to do with some
     * windows-specific code. TODO: Figure out if we really need this.
     * @param flags Flags used for identifying which engine parts are to be
     * loaded. Use YACE_INIT_* flags.
     * @return true if core initialized successfully, false otherwise
     */
    bool game_init(bool isServer, const char* uniqueString, int flags);
}

#endif /* YACE_GAME_H */