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


#ifndef YACE_EVENT_H
#define YACE_EVENT_H

#include <stdint.h>

//===============Event IDs===============//

//Mouse Events
#define YACE_EVENT_MOUSE                 0x00000F
#define YACE_EVENT_MOUSE_MOVE            0x000001
#define YACE_EVENT_MOUSE_BUTTON_DOWN     0x000002
#define YACE_EVENT_MOUSE_BUTTON_UP       0x000004
#define YACE_EVENT_MOUSE_WHEEL           0x000008

//Keyboard Events
#define YACE_EVENT_KEY                   0x0000F0
#define YACE_EVENT_KEY_DOWN              0x000010
#define YACE_EVENT_KEY_UP                0x000020

//Window Events
#define YACE_EVENT_WINDOW                0x00FF00
#define YACE_EVENT_WINDOW_CLOSE          0x000100
#define YACE_EVENT_WINDOW_RESIZE         0x000200
#define YACE_EVENT_WINDOW_MAXIMISE       0x000400
#define YACE_EVENT_WINDOW_MINIMISE       0x000800

//Joystick Events
#define YACE_EVENT_JOYSTICK              0xFF0000
#define YACE_EVENT_JOYSTICK_BUTTON_DOWN  0x010000
#define YACE_EVENT_JOYSTICK_BUTTON_UP    0x020000
#define YACE_EVENT_JOYSTICK_AXIS         0x040000
#define YACE_EVENT_JOYSTICK_CONNECED     0x080000
#define YACE_EVENT_JOYSTICK_DISCONNECTED 0x100000
#define YACE_EVENT_JOYSTICK_BATTERY_LOW  0x200000
#define YACE_EVENT_JOYSTICK_CHARGING     0x400000
#define YACE_EVENT_JOYSTICK_DISCHARGING  0x800000

namespace YACE {

//=============Event Structs=============//

    struct Event {
        Event(uint32_t t) : type(t) {};
        const uint32_t type = 0;
    };

//Mouse Events

    struct MouseEvent : public Event {
        MouseEvent(uint32_t t) : Event(t) {};
        int x;
        int y;
    };

    struct EventMouseMove : public MouseEvent {
        EventMouseMove() : MouseEvent(YACE_EVENT_MOUSE_MOVE) {};
        int dx;
        int dy;
    };

    struct EventMouseButtonDown : public MouseEvent {
        EventMouseButtonDown() : MouseEvent(YACE_EVENT_MOUSE_BUTTON_DOWN) {};
        int button;
    };

    struct EventMouseButtonUp : public MouseEvent {
        EventMouseButtonUp() : MouseEvent(YACE_EVENT_MOUSE_BUTTON_UP) {};
        int button;
    };

    struct EventMouseWheel : public MouseEvent {
        EventMouseWheel() : MouseEvent(YACE_EVENT_MOUSE_WHEEL) {};
        int scroll;
    };

//Keyboard Events

    struct EventKeyDown : public Event {
        EventKeyDown() : Event(YACE_EVENT_KEY_DOWN) {};
        int keycode;
        int scancode;
    };

    struct EventKeyUp : public Event {
        EventKeyUp() : Event(YACE_EVENT_KEY_UP) {};
        int keycode;
        int scancode;
    };

//Window Events

    struct EventWindowClose : public Event {
        EventWindowClose() : Event(YACE_EVENT_WINDOW_CLOSE) {};
    };

    struct EventWindowResize : public Event {
        EventWindowResize() : Event(YACE_EVENT_WINDOW_RESIZE) {};
        int width;
        int height;
    };

    struct EventWindowMaximise : public Event {
        EventWindowMaximise() : Event(YACE_EVENT_WINDOW_MAXIMISE) {};
        int width;
        int height;
    };

    struct EventWindowMinimise : public Event {
        EventWindowMinimise() : Event(YACE_EVENT_WINDOW_MINIMISE) {};
        int width;
        int height;
    };

//Joystick Events

    struct JoystickEvent : public Event {
        JoystickEvent(uint32_t t) : Event(t) {};
        uint8_t joystickID;
    };

    struct EventJoystickButtonDown : public JoystickEvent {
        EventJoystickButtonDown()
            : JoystickEvent(YACE_EVENT_JOYSTICK_BUTTON_DOWN) {};
        int button;
    };

    struct EventJoystickButtonUp : public JoystickEvent {
        EventJoystickButtonUp()
            : JoystickEvent(YACE_EVENT_JOYSTICK_BUTTON_UP) {};
        int button;
    };

    struct EventJoystickAxis : public JoystickEvent {
        EventJoystickAxis() : JoystickEvent(YACE_EVENT_JOYSTICK_AXIS) {};
        int axis;
        int delta;
        int value;
    };

    struct EventJoystickConnected : public JoystickEvent {
        EventJoystickConnected()
            : JoystickEvent(YACE_EVENT_JOYSTICK_CONNECED) {};
    };

    struct EventJoystickDisconnected : public JoystickEvent {
        EventJoystickDisconnected()
            : JoystickEvent(YACE_EVENT_JOYSTICK_DISCONNECTED) {};
    };

    struct EventJoystickBatteryLow : public JoystickEvent {
        EventJoystickBatteryLow()
            : JoystickEvent(YACE_EVENT_JOYSTICK_BATTERY_LOW) {};
    };

    struct EventJoystickCharging : public JoystickEvent {
        EventJoystickCharging()
            : JoystickEvent(YACE_EVENT_JOYSTICK_CHARGING) {};
    };

    struct EventJoystickDischarging : public JoystickEvent {
        EventJoystickDischarging()
            : JoystickEvent(YACE_EVENT_JOYSTICK_DISCHARGING) {};
    };

//============Event Functions============//

    /**
     * Callback function for the event listener. The parameter "event" is the
     * event struct, which is only guaranteed to have the generic eventType
     * field. From there, the user is expected to cast the event struct to
     * the appropiate extended event struct.
     */
    typedef void (*EventCallback)(Event &event);

    /**
     * Adds a new event listener that will be notified when an event of the
     * specified types is sent.
     * @param function The callback to be called when the event is received.
     * @param events A bitfield of the events this listener can receive.
     */
    void event_registerListener(EventCallback function, uint32_t events);

    /**
     * Sends an event to all the registered listeners.
     * @param event The event to be sent.
     */
    void event_send(Event &event);

}

#endif /* YACE_EVENT_H */
