/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Box
*/

#include "Box.hpp"
#include "ExceptionObject.hpp"

Box::Box(irr::scene::ISceneNode *node)
{
    _node = node;
    _nodeAnimated = nullptr;
    _animated = false;
    _alive = true;
    _break = true;
    _block = true;
}

Box::Box(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver)
{
    _nodeAnimated = nullptr;
    _animated = false;
    _alive = true;
    _break = true;
    _block = true;

    irr::scene::IMesh *cube = smgr->getGeometryCreator()->createCubeMesh(irr::core::vector3df(1.f, 1.f, 1.f));
    if (!cube)
        throw ExceptionObject("Error : Couldn't create a cube");
    _node = smgr->addMeshSceneNode(cube);
    if (!_node)
        throw ExceptionObject("Error : Couldn't create a node");
}

Box::~Box()
{
}