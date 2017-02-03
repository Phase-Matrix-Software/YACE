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


#include "YACE_Logger.h"

#include <ctime>
#include <stdarg.h>
#include <cstdio>
#include <cstring>

int flags = 0x00;

void YACE::Logger_setFlag(int flag, bool value)
{
    if (value) {
        flags |= flag;
    } else {
        flags &= ~flag;
    }
}

void getTime(char* buffer)
{
    time_t rawtime = time(nullptr);
    struct tm* timeinfo = localtime(&rawtime);
    strftime(buffer, 11, "[%H:%M:%S]", timeinfo);
}

//TODO: Log to a file
void output(std::FILE* stream, const char* type, char* msg, va_list argptr)
{
    char timebuf[10];
    char buffer[10 + 6 + 1 + strlen(msg) + 1];
    getTime(timebuf);
    sprintf(buffer, "%s%s %s\n", timebuf, type, msg);
    vfprintf(stream, buffer, argptr);
}

void YACE::Logger_debug(char* msg, ...)
{
    if (!(flags & YACE_LOG_DEBUG)) return;
    va_list argptr;
    va_start(argptr, msg);
    output(stdout, "[DBG ]", msg, argptr);
    va_end(argptr);
}

void YACE::Logger_warning(char* msg, ...)
{
    if (!(flags & YACE_LOG_WARNING)) return;
    va_list argptr;
    va_start(argptr, msg);
    output(stdout, "[WARN]", msg, argptr);
    va_end(argptr);
}

void YACE::Logger_info(char* msg, ...)
{
    va_list argptr;
    va_start(argptr, msg);
    output(stdout, "[INFO]", msg, argptr);
    va_end(argptr);
}

void YACE::Logger_error(char* msg, ...)
{
    va_list argptr;
    va_start(argptr, msg);
    output(stderr, "[ERR ]", msg, argptr);
    va_end(argptr);
}
