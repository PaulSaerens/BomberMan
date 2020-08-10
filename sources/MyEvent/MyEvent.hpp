/*
** EPITECH PROJECT, 2020
** menu
** File description:
** Event
*/

#pragma once

#include "irrlicht.h"

class MyEvent : public irr::IEventReceiver
{
private:
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];

    struct SMouseState
    {
        irr::core::position2di Position;
        bool LeftButtonDown;
        SMouseState() : LeftButtonDown(false) {}
    } MouseState;

public:
    MyEvent();
    ~MyEvent();

    virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
    virtual bool OnEvent(const irr::SEvent &event);
    const SMouseState &GetMouseState(void) const;
    const irr::core::position2di getPosMouse(void) const;
};
