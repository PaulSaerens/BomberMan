/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Wall
*/

#ifndef WALL_HPP_
#define WALL_HPP_

#include <string>
#include "irrlicht.h"
#include "Object.hpp"

class Wall : public Object {
    public:
        Wall(irr::scene::ISceneNode *node);
        Wall(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver);

        ~Wall();
};

#endif /* !WALL_HPP_ */
