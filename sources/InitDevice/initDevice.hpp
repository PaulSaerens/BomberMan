/*
** EPITECH PROJECT, 2020
** InitDevice.hpp
** File description:
** InitDevice.hpp
*/


#ifndef INITDEVICE_HPP_
#define INITDEVICE_HPP_

#include "irrlicht.h"
#include "IrrlichtDevice.h"
#include "driverChoice.h"
#include "MyEvent.hpp"
#include "MyAudio.hpp"

class Device {
    public:
        Device(const irr::u32 &width, const irr::u32 &height);
        ~Device() = default;
        irr::IrrlichtDevice *getDevice();
        MyEvent *getReceiver();
        MyAudio *getAudio();
    private:
        irr::IrrlichtDevice *_device;
        irr::u32 _deviceWidth;
        irr::u32 _deviceHeight;
        irr::IrrlichtDevice *initDevice();
        MyAudio _audio;
        MyEvent _receiver;
};
#endif /* !INITDEVICE_HPP_ */
