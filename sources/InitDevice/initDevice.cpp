/*
** EPITECH PROJECT, 2020
** initDevice.cpp
** File description:
** initDevice.cpp
*/

#include "initDevice.hpp"

Device::Device(const irr::u32 &width, const irr::u32 &height)
{
    _deviceWidth = width;
    _deviceHeight = height;
    initDevice();
    if (!_device)
        return;
}

irr::IrrlichtDevice *Device::initDevice()
{
    irr::video::E_DRIVER_TYPE driverType = irr::driverChoiceConsole();
    irr::core::dimension2d<irr::u32> driverDimensions = irr::core::dimension2d<irr::u32>(_deviceWidth, _deviceHeight);
    _device = irr::createDevice(driverType, driverDimensions, 16, false, false, false, 0);
    return _device;
}

irr::IrrlichtDevice *Device::getDevice()
{
    return _device;
}

MyEvent *Device::getReceiver()
{
    return &_receiver;
}

MyAudio *Device::getAudio()
{
    return &_audio;
}