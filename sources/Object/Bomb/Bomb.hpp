/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Object
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "irrlicht.h"
#include "Object.hpp"
#include "MyAudio.hpp"

class Bomb : public Object {
    public:
        Bomb(irr::scene::ISceneNode *node);
        Bomb(irr::scene::ISceneNode *node, irr::video::IVideoDriver *driver);
        Bomb(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver);

        bool isBombExploading(irr::u32 time);
        void setTime(irr::u32 time);
        int getRadius();
    private:

        irr::u32 _time;
        int _radius;
        MyAudio _audio;
};

#endif /* !BOMB_HPP_ */
