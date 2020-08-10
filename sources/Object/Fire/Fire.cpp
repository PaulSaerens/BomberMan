/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Fire
*/

#include "Fire.hpp"
#include "ExceptionObject.hpp"

Fire::Fire(irr::scene::ISceneNode *node) : Object(node)
{
    _animated = true;
    _block = false;
    _break = false;
    _alive = true;
}

Fire::Fire(irr::scene::ISceneNode *node, irr::video::IVideoDriver *driver) : Object(node, driver)
{
    _animated = true;
    _block = false;
    _break = false;
    _alive = true;
}

Fire::Fire(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver) : Object()
{
    _animated = true;
    _block = false;
    _break = false;
    _alive = true;

    if (!driver->getTexture("extra/Fire/fire.bmp"))
        throw (ExceptionObject("Can't load texture for fire"));

    irr::scene::IMesh *cube = smgr->getGeometryCreator()->createSphereMesh(0.4, 16, 16);
    _node = smgr->addMeshSceneNode(cube);
    _node->setMaterialTexture(0, driver->getTexture("extra/Fire/fire.bmp"));
    _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

Fire::~Fire()
{
}

void Fire::setTime(irr::u32 time)
{
    _then = time;
}

irr::u32 Fire::getTime() const
{
    return _then;
}
