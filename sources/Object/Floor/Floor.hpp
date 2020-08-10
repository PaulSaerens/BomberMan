/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Box
*/

#ifndef FLOOR_HPP_
#define FLOOR_HPP_

#include <string>
#include <vector>
#include <memory>
#include "irrlicht.h"
#include "Object.hpp"

class Floor : public Object {
    public:
        Floor(irr::scene::ISceneNode *node, irr::scene::ISceneManager *smgr);
        Floor(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver);

        ~Floor();

    private:
        irr::scene::ISceneManager *_smgr;
        std::vector<std::shared_ptr<Object>> _objects;
};

#endif /* !FLOOR_HPP_ */
