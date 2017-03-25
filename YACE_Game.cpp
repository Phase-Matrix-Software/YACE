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


#include "YACE_Game.h"
#include "YACE_Timer.h"
#include "YACE_Logger.h"
#include <vector>

/*
 * Update at 60Hz
 */
#define TARGET_TPS 60.f

/*
 * Use microsecond accuracy
 * Milliseconds probably aren't a good idea, because 0-16 isn't really
 * a very big range. 0-166666 should be much better.
 */                       // 1/(1000^2)=microseconds
#define LOOP_TIMING_ACCURACY 1000*1000

/*
 * Check if >500µs since last update rate check
 * If this value is too low, the tick rate might be inaccurate.
 * ie 0.5µs or 1.499µs will round to 1µs, which is a high percentage inaccuracy
 * or 9.5µs or 10.499µs will round to 10µs, which is a low percentage inaccuracy
 * If this value is too high, ticks may be late, or too infrequent
 */
#define TICK_CHECK_TIME_ACCURACY 500

//used to check when a second has passed
static YACE::Timer<unsigned char, std::ratio<1>> second;
//used for game loop timings
static
    YACE::Timer<unsigned long, std::ratio<1, LOOP_TIMING_ACCURACY>> updateTick;

static unsigned long long ticks = 0;      // total ticks
static unsigned long long frames = 0;     // total frames
static unsigned long fps;                 // frames per last second
static unsigned long tps;                 // ticks per last second
static unsigned long long lastFrames = 0; // total frames as of last second
static unsigned long long lastTicks = 0;  // total ticks as of last second

static bool running;

static std::vector<YACE::FuncPointer> updateHooks;
static std::vector<YACE::FuncPointer> renderHooks;
static std::vector<YACE::FuncPointer> cleanupHooks;

bool YACE::game_init(bool isServer, const char* uniqueString, int flags)
{
    if (flags & YACE_INIT_DEBUG_OUTPUT) {
        logger_setFlag(YACE_LOG_DEBUG, true);
    }

    if (flags & YACE_INIT_WARNING_OUTPUT) {
        logger_setFlag(YACE_LOG_WARNING, false);
    }

    return true;
}

void YACE::game_loop()
{
    running = true;

    second.reset();
    second.start();
    updateTick.reset();
    updateTick.start();

    /*
     * This is used instead of directly checking .getTime() to correct for any
     * slow downs. ie if a tick takes too long, and the next tick is delayed,
     * the loop will tick faster to compensate.
     */
    double time = 0;

    while (running) {
        //Check if getTime() is high enough to avoid inaccuracy
        if (updateTick.getTime() >= TICK_CHECK_TIME_ACCURACY) {
            time += updateTick.getTime();
            updateTick.reset();
        }

        //Check if enough time has passed to tick
        while (time >= LOOP_TIMING_ACCURACY / TARGET_TPS) {
            time -= LOOP_TIMING_ACCURACY / TARGET_TPS;

            for (FuncPointer hook : updateHooks) {
                hook();
            }

            ticks++;
        }

        for (FuncPointer hook : renderHooks) {
            hook();
        }

        frames++;

        /*
         * No slow down compensation code is used here because this stuff
         * isn't really that important.
         */
        if (second.getTime() >= 1) {
            fps = frames - lastFrames;
            lastFrames = frames;
            tps = ticks - lastTicks;
            lastTicks = ticks;
            second.reset();
            logger_debug("TPS: %lu, FPS: %lu\n", tps, fps);
        }
    }
    for (FuncPointer hook : cleanupHooks) {
        hook();
    }
}

void YACE::game_addUpdateHook(FuncPointer function)
{
    updateHooks.push_back(function);
}

void YACE::game_addRenderHook(FuncPointer function)
{
    renderHooks.push_back(function);
}

void YACE::game_addCleanupHook(FuncPointer function)
{
    cleanupHooks.push_back(function);
}

void YACE::game_stop()
{
    running = false;
}
