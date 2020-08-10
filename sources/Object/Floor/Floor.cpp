/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Floor
*/

#include "Floor.hpp"
#include "ExceptionObject.hpp"

Floor::Floor(irr::scene::ISceneNode *node, irr::scene::ISceneManager *smgr) : Object(node)
{
    _smgr = smgr;
}

Floor::Floor(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver) : Object(nullptr)
{
    irr::core::dimension2d<irr::f32> tile(1,1);
    irr::core::dimension2d<irr::u32> tileSize(20, 20);

    irr::scene::IMesh *mesh = smgr->getGeometryCreator()->createPlaneMesh(tile, tileSize);

    _node = smgr->addMeshSceneNode(mesh);

    if (!driver->getTexture("extra/map/textures/floor.png"))
        throw ExceptionObject("Can't load texture for floor");

    if (_node) {
        _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _node->setMaterialTexture(0, driver->getTexture("extra/map/textures/floor.png"));
        _node->setPosition(irr::core::vector3df(9.5f, 0, 10));
        _node->setScale(irr::core::vector3df(1.2f, 0, 1.2f));
    }
}

Floor::~Floor()
{
}