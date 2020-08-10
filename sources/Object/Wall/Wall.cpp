/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Wall
*/

#include "Wall.hpp"
#include "ExceptionObject.hpp"

Wall::Wall(irr::scene::ISceneNode *node)
{
    _node = node;
    _nodeAnimated = nullptr;
    _animated = false;
    _alive = true;
    _break = false;
    _block = true;
}

Wall::Wall(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver)
{
    _nodeAnimated = nullptr;
    _animated = false;
    _alive = true;
    _break = false;
    _block = true;

    irr::scene::IMesh *cube = smgr->getGeometryCreator()->createCubeMesh(irr::core::vector3df(1.f, 1.f, 1.f));
    if (!cube)
        throw ExceptionObject("Error : Couldn't create a cube");
    _node = smgr->addMeshSceneNode(cube);
    if (!_node)
        throw ExceptionObject("Error : Couldn't create a node");
    _node = smgr->addMeshSceneNode(cube);
}

Wall::~Wall()
{
}