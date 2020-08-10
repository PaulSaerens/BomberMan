/*
** EPITECH PROJECT, 2020
** menu
** File description:
** Event
*/

#include "MyEvent.hpp"

MyEvent::MyEvent()
{
    for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
}

MyEvent::~MyEvent()
{
}

bool MyEvent::IsKeyDown(irr::EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

const MyEvent::SMouseState &MyEvent::GetMouseState(void) const
{
    return MouseState;
}

bool MyEvent::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
        switch(event.MouseInput.Event) {
        case irr::EMIE_MOUSE_MOVED:
            MouseState.Position.X = event.MouseInput.X;
            MouseState.Position.Y = event.MouseInput.Y;
            break;
        case irr::EMIE_LMOUSE_PRESSED_DOWN:
            MouseState.LeftButtonDown = true;
            break;
        case irr::EMIE_LMOUSE_LEFT_UP:
            MouseState.LeftButtonDown = false;
            break;
        default:
            break;
        }
    }
    return false;
}

const irr::core::position2di MyEvent::getPosMouse(void) const
{
    return MouseState.Position;
}
