/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Box
*/

#ifndef BOX_HPP_
#define BOX_HPP_

#include <string>
#include "irrlicht.h"
#include "Object.hpp"

class Box : public Object {
    public:
        Box(irr::scene::ISceneNode *node);
        Box(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver);

        ~Box();
};

#endif /* !BOX_HPP_ */
