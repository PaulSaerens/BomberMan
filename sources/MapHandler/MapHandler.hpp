/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapHandler
*/

#ifndef MAPHANDLER_HPP_
#define MAPHANDLER_HPP_

#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include "irrlicht.h"
#include "Object.hpp"
#include "Box/Box.hpp"
#include "Bomb/Bomb.hpp"
#include "Fire/Fire.hpp"
#include "Floor/Floor.hpp"
#include "Player/Player.hpp"
#include "Wall/Wall.hpp"

class MapHandler {
    public:
        MapHandler();
        MapHandler(irr::IrrlichtDevice *device, irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver);
        ~MapHandler() = default;

        std::shared_ptr<Object> newObject(char point);
        /* --- SET --- */
        void loadMap();
        void setAllColision();
        void setPositionMapObjects();
        void exploadBlocks(int radius, irr::core::vector3df bombPos);
        void deleteFire();

        /* --- GET --- */
        std::string getMapPositions(int x, int y) const;
        std::vector<std::shared_ptr<Object>> getObjects();
        std::vector<std::vector<std::string>> getMapElems();
        std::vector<std::shared_ptr<Object>> getCharacters();

    private:
            /* --- BLOCK --- */
        void exploadSurrounding(int radius, irr::core::vector3df bombPos);
        void removeUp(int radius, irr::core::vector3df bombPos);
        void removeDown(int radius, irr::core::vector3df bombPos);
        void removeLeft(int radius, irr::core::vector3df bombPos);
        void removeRight(int radius, irr::core::vector3df bombPos);
        void deleteColision(int pos);

        bool _up;
        bool _down;
        bool _left;
        bool _right;

            /* --- PLAYER --- */
        void makePlayerDieFromBomb(int radius, irr::core::vector3df bombPos);

        std::vector<std::shared_ptr<Object>> _characters;

            /* --- FIRE --- */
        void createFire(float x, float y, float z);

        std::vector<std::shared_ptr<Fire>> _fire;


        irr::IrrlichtDevice *_device;
        irr::scene::ISceneManager *_smgr;
        irr::video::IVideoDriver *_driver;


        std::vector<std::shared_ptr<Object>> _mapObjects;
        std::vector<std::vector<std::string>> _mapElems;
        std::shared_ptr<Object> _floor;

        MyAudio _audio;
        bool getMapElements();
        void addCamera();
};

#endif /* !MAPHANDLER_HPP_ */
