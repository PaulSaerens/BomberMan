/*
** EPITECH PROJECT, 2020
** GameHandler.hpp
** File description:
** GameHandler.hpp
*/


#ifndef GAMEHANDLER_HPP_
#define GAMEHANDLER_HPP_

#include "BombermanCore.hpp"
#include "AMenu.hpp"
#include "MainMenu/EndMenu.hpp"
#include "MapHandler.hpp"
#include "Player/Player.hpp"
#include <vector>
#include <string>
#include <cmath>

class GameHandler {
    public:
        GameHandler(irr::IrrlichtDevice *device, GAMETYPE nbPlayer);
        ~GameHandler();
        void Launch();
    protected:
    private:
        void singlePlayerLoop();
        void multiPlayerLoop();

        void handleEndGame(void);

        int exploadBlocks(int bombID);
        int removeVisibleBlock(int y, int x);

        std::shared_ptr<MapHandler> _map;

        GAMETYPE _type;

        irr::IrrlichtDevice *_device;
        irr::video::IVideoDriver *_driver;
        irr::scene::ISceneManager *_smgr;

        std::vector<std::shared_ptr<Object>> _characters;
        std::shared_ptr<MyEvent> _receiver;
};

#endif /* !GAMEHandler_HPP_ */
