/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Object
*/

#ifndef FIRE_HPP_
#define FIRE_HPP_

#include <string>
#include <memory>
#include <vector>
#include "irrlicht.h"
#include "Object.hpp"

class Fire : public Object {
    public:
        Fire(irr::scene::ISceneNode *node);
        Fire(irr::scene::ISceneNode *node, irr::video::IVideoDriver *driver);
        Fire(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver);
        ~Fire();

        void setTime(irr::u32 time);
        irr::u32 getTime() const;

    private:
        irr::u32 _then;
};

#endif /* !FIRE_HPP_ */
