/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#include "Bomb.hpp"
#include "ExceptionObject.hpp"

Bomb::Bomb(irr::scene::ISceneNode *node) : Object(node)
{
    _animated = true;
    _block = false;
    _break = false;
    _alive = true;
    _radius = 1;
}

Bomb::Bomb(irr::scene::ISceneNode *node, irr::video::IVideoDriver *driver) : Object(node, driver)
{
    _animated = true;
    _block = false;
    _break = false;
    _alive = true;
    _radius = 1;
}

Bomb::Bomb(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver) : Object()
{
    _animated = true;
    _block = false;
    _break = false;
    _alive = true;
    _radius = 1;


    irr::scene::IAnimatedMesh *mesh = smgr->getMesh("extra/Bomb/Bomb.obj");
    if (!mesh)
        throw (ExceptionObject("Can't load 3D model for bomb with file : extra/Bomb/Bomb.obj"));
    if (!driver->getTexture("extra/Bomb/Bomb.png"))
        throw (ExceptionObject("Can't load texture for bomb with file : extra/Bomb/Bomb.png"));

    _nodeAnimated = smgr->addAnimatedMeshSceneNode(mesh);

    if (_nodeAnimated) {
        _nodeAnimated->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _nodeAnimated->setFrameLoop(27, 76);
        _nodeAnimated->setAnimationSpeed(30);
        _nodeAnimated->setMaterialTexture(0, driver->getTexture("extra/Bomb/Bomb.png"));
        _nodeAnimated->setScale(irr::core::vector3df(0.2f, 0.2f, 0.2f));
    } else
        throw ExceptionObject("Can't add Animated scene node");
}

bool Bomb::isBombExploading(irr::u32 time)
{
    if (time - _time >= 5000)
        return true;
    _audio.play(MyAudio::TIMER);
    return false;
}

void Bomb::setTime(irr::u32 time)
{
    _time = time;
}

int Bomb::getRadius()
{
    return _radius;
}