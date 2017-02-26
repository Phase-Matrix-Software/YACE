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


#ifndef YACE_TIMER_H
#define YACE_TIMER_H

#include <chrono>

namespace YACE {
    template<typename T, class R>//<type returned by getTime(), duration ratio>
    class Timer {
        public:
            /**
             * Gets the time between now, and when the timer was last reset,
             * excluding any time that the timer was paused.
             * @return timer duration
             */
            T getTime()
            {
                if (paused) return totalTimeBeforePause;
                return std::chrono::duration_cast<std::chrono::duration<T, R>>
                    (std::chrono::high_resolution_clock::now() - lastStartTime)
                    .count();
            }
            /**
             * Starts or resumes the timer. reset() should be called before
             * this function is called for the first time.
             */
            void start()
            {
                if (!paused) return;
                lastStartTime = std::chrono::high_resolution_clock::now();
                paused = false;
            }
            /**
             * Pauses the timer.
             */
            void pause()
            {
                if (paused) return;
                paused = true;
                totalTimeBeforePause += getTime();
            }
            /**
             * Resets the timer.
             */
            void reset()
            {
                lastStartTime = std::chrono::high_resolution_clock::now();
                totalTimeBeforePause = 0;
            }
        private:
            std::chrono::high_resolution_clock::time_point lastStartTime;
            T totalTimeBeforePause;
            bool paused = true;
    };
}

#endif /* YACE_TIMER_H */
