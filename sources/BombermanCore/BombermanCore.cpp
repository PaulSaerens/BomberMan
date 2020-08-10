/*
** EPITECH PROJECT, 2020
** BombermanMain.cpp
** File description:
** BombermanMain.cpp
*/

#include "BombermanCore.hpp"
#include "GameHandler.hpp"
#include "ExceptionIndie.hpp"

BombermanCore::BombermanCore(int width, int height)
{
    _gameIsRunning = true;
    _width = width;
    _height = height;
    _device = irr::createDevice(irr::video::EDT_OPENGL,
    irr::core::dimension2d<irr::u32>(1920, 1080), 16, false, false, false, 0);
    if (!_device)
        throw (ExceptionIndie("Can't create device"));
    _driver = _device->getVideoDriver();
        if (!_driver)
        throw (ExceptionIndie("Can't get driver"));
}

BombermanCore::~BombermanCore()
{
}

void BombermanCore::RunMenu()
{
    _device->setWindowCaption(L"BOMBERMAN");
    auto mainMenu = std::make_unique<MainMenu>(_device, _driver);
    mainMenu->mainLoop();
}
