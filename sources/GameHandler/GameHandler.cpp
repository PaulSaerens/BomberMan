/*
** EPITECH PROJECT, 2020
** GameHandler.cpp
** File description:
** GameHandler.cpp
*/

#include "GameHandler.hpp"

GameHandler::GameHandler(irr::IrrlichtDevice *device, GAMETYPE nbPlayer)
{
    _device = device;
    _driver = _device->getVideoDriver();
    _smgr = _device->getSceneManager();

    _driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
    _map = std::make_unique<MapHandler>(_device, _smgr, _driver);
    _receiver = std::make_shared<MyEvent>();
    _type = nbPlayer;

    _map->loadMap();
    _characters = _map->getCharacters();
    for (int playerID = 0; playerID < 2; playerID++)
        _characters[playerID]->setPlayerId(playerID);
    _device->setEventReceiver(_receiver.get());
    for (auto i : _characters)
        i->setEvents(_receiver);
}

GameHandler::~GameHandler()
{
}

void GameHandler::singlePlayerLoop()
{

    while (_device->run()) {
        _device->getCursorControl()->setVisible(false);
        _driver->beginScene(true, true, irr::video::SColor(255,100,101,140));

        _characters[0]->move();
        _characters[0]->placeBomb(_device->getTimer()->getTime());
        if (_characters[0]->getBomb() && _characters[0]->getBomb()->isBombExploading(_device->getTimer()->getTime()) == true) {
            _map->exploadBlocks(_characters[0]->getBomb()->getRadius(), _characters[0]->getBomb()->getPosition());
            _characters[0]->removeBomb();
        }
        _map->deleteFire();
        _smgr->drawAll();
        _driver->endScene();
        handleEndGame();
    }
}

void GameHandler::multiPlayerLoop()
{
    while (_device->run()) {
        _device->getCursorControl()->setVisible(false);
        _driver->beginScene(true, true, irr::video::SColor(255,100,101,140));
        for (int i = 0; i < 2; i++) {
            _characters[i]->move();
            _characters[i]->placeBomb(_device->getTimer()->getTime());
            if (_characters[i]->getBomb() && _characters[i]->getBomb()->isBombExploading(_device->getTimer()->getTime()) == true) {
                _map->exploadBlocks(_characters[i]->getBomb()->getRadius(), _characters[i]->getBomb()->getPosition());
                _characters[i]->removeBomb();
            }
            _map->deleteFire();
            handleEndGame();
        }
        _smgr->drawAll();
        _driver->endScene();
    }

}


void GameHandler::Launch()
{
    if (_type == GAMETYPE::SOLO)
        singlePlayerLoop();
    else if (_type == GAMETYPE::MULTIPLAYER)
        multiPlayerLoop();
}

void GameHandler::handleEndGame(void)
{
    if (!_characters.empty() && !_characters[0]->isAlive()) {
        _characters.clear();
        auto end = std::make_unique<EndMenu>(_device, _driver);
        end->endMenuLoop();
    }
}