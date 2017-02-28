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


#ifndef YACE_LOGGER_H
#define YACE_LOGGER_H

#define YACE_LOG_DEBUG   1
#define YACE_LOG_WARNING 2

namespace YACE {

    /**
     * Sets a flag to give information about the logging. The available flags
     * to be used are YACE_LOG_*. Usually handled by the Game_init() function.
     */
    void logger_setFlag(int flag, bool value);

    /**
     * This function logs debug messages and is only recorded if the logger
     * was initialized with the debug flag enabled. This flag is usually
     * automatically set by the Game_init() function. Disabled by default.
     * @param msg The message to be logged
     */
    void logger_debug(const char* msg, ...);

    /**
     * This function logs information messages.
     * @param msg The message to be logged
     */
    void logger_info(const char* msg, ...);

    /**
     * This function logs warning messages (to the standard buffer) and is only
     * recorded if the logger was initialized with the warning flag enabled.
     * This flag is usually automatically set by the Game_init() function.
     * Disabled by default.
     * @param msg The message to be logged
     */
    void logger_warning(const char* msg, ...);

    /**
     * This function logs error messages to the ERROR buffer.
     * @param msg The message to be logged
     */
    void logger_error(const char* msg, ...);
}

#endif /* YACE_LOGGER_H */
