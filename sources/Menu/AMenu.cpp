/*
** EPITECH PROJECT, 2020
** AMenu.cpp
** File description:
** AMenu.cpp
*/

#include "AMenu.hpp"

AMenu::AMenu(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver)
{
    _device = device;
    _driver = driver;
    _guienv = _device->getGUIEnvironment();
    _smgr = _device->getSceneManager();
}


void AMenu::setTextImage(std::string textName, irr::core::rect<irr::s32>rectImage, const irr::io::path &filename)
{
    auto imageText = _guienv->addImage(rectImage);
    imageText->setImage(_driver->getTexture(filename));
    if (!imageText)
        throw ExceptionMenu("can't load Image");
    _texts[textName] = imageText;
}

void AMenu::drawMenu()
{
    _device->getCursorControl()->setVisible(true);
    _driver->beginScene(true, true, irr::video::SColor(255,100,101,140));
    _guienv->drawAll();
}

void AMenu::clearScene()
{
    _guienv->clear();
    _smgr->clear();
}