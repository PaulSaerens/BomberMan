/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Object
*/

#include "Object.hpp"
#include "ExceptionObject.hpp"

Object::Object()
{
    _node = nullptr;
    _nodeAnimated = nullptr;
    _animated = false;
    _alive = false;
    _break = false;
    _block = false;
}

Object::Object(irr::scene::ISceneNode *node)
{
    _node = nullptr;
    _nodeAnimated = nullptr;
    _animated = false;
    _alive = false;
    _break = false;
    _block = false;
}

Object::Object(irr::scene::ISceneNode *node, irr::video::IVideoDriver *driver)
{
    _node = nullptr;
    _nodeAnimated = nullptr;
    _animated = false;
    _alive = false;
    _break = false;
    _block = false;
}

Object::Object(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver)
{
    _node = nullptr;
    _nodeAnimated = nullptr;
    _animated = false;
    _alive = false;
    _block = false;
    _break = false;
}

Object::~Object()
{
}

/* ---- SET ---- */

void Object::setPosition(irr::f32 x, irr::f32 y, irr::f32 z)
{
    if (_node) {
        _pos = _node->getPosition();
        _pos.X = x;
        _pos.Y = y;
        _pos.Z = z;
        _node->setPosition(_pos);
    }
    else if (_nodeAnimated) {
        _pos = _nodeAnimated->getPosition();
        _pos.X = x;
        _pos.Y = y;
        _pos.Z = z;
        _nodeAnimated->setPosition(_pos);
    }
}

void Object::updatePosition(irr::f32 x, irr::f32 y, irr::f32 z)
{
    if (_node) {
        _pos = _node->getPosition();
        _pos.X += x;
        _pos.Y += y;
        _pos.Z += z;
        _nodeAnimated->setPosition(_pos);
    }
    else if (_nodeAnimated) {
        _pos = _nodeAnimated->getPosition();
        _pos.X += x;
        _pos.Y += y;
        _pos.Z += z;
        _nodeAnimated->setPosition(_pos);
    }
}

void Object::setNode(irr::scene::ISceneNode *node)
{
    _node = node;
}

void Object::setBreak(bool val)
{
    _break = val;
}

void Object::setAlive(bool val)
{
    _alive = val;
}

void Object::setAnimated(bool val)
{
    _animated = val;
}

void Object::setVisibility(bool val)
{
    if (_nodeAnimated)
        _node->setVisible(val);
    else if (_node)
        _node->setVisible(val);
}

void Object::setColision(irr::scene::ISceneManager *smgr, irr::scene::IMesh *mesh, irr::scene::ISceneNode *node)
{
}

void Object::setColision(irr::scene::ISceneManager *smgr, irr::scene::IMesh *mesh, irr::scene::ISceneNode *node, irr::core::vector3df vect)
{
}

void Object::removeColision(irr::scene::ISceneManager *smgr, irr::scene::IMesh *mesh, irr::scene::ISceneNode *node)
{
}

void Object::removeColision(irr::scene::ISceneManager *smgr, irr::scene::IMesh *mesh, irr::scene::ISceneNode *node, irr::core::vector3df vect)
{
}

void Object::setTexture(const std::string &path, irr::video::IVideoDriver *driver)
{
    if (!driver->getTexture(path.c_str()))
        throw ExceptionObject("Can't open file : " + path);
    _node->setMaterialTexture(0, driver->getTexture(path.c_str()));
    _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

void Object::move()
{
}

void Object::placeBomb(irr::u32 time)
{
}

void Object::removeBomb()
{
}

void Object::setPlayerId(int playerId)
{
}

std::shared_ptr<Object> Object::getBomb()
{
    return nullptr;
}


void Object::setEvents(std::shared_ptr<MyEvent> event)
{
    _receiver = event;
}

/* ---- GET ---- */

irr::scene::ISceneNode *Object::getNode()
{
    return _node;
}

irr::scene::IAnimatedMeshSceneNode *Object::getNodeAnimated()
{
    return _nodeAnimated;
}

irr::core::vector3df Object::getPosition()
{
    return _pos;
}

bool Object::canBreak()
{
    return _break;
}

bool Object::isAlive()
{
    return _alive;
}

bool Object::isBlock()
{
    return _block;
}

bool Object::isAnimated()
{
    return _animated;
}



bool Object::isBombExploading(irr::u32 time)
{
    return false;
}

void Object::setTime(irr::u32 time)
{
}

int Object::getRadius()
{
    return 0;
}