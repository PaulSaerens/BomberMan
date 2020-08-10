/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapHandler
*/

#include "MapHandler.hpp"
#include "ExceptionMap.hpp"
#include <iostream>

MapHandler::MapHandler()
{
    _device = nullptr;
    _driver = nullptr;
    _smgr = nullptr;
}

MapHandler::MapHandler(irr::IrrlichtDevice *device, irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver)
{
    getMapElements();
    _device = device;
    _smgr = smgr;
    _driver = driver;
}

std::shared_ptr<Object> MapHandler::newObject(char point)
{
    std::shared_ptr<Object> retObject;

    switch (point) {
    case '0':
        retObject = std::make_shared<Object>();
        break;
    case '3':
        retObject = std::make_shared<Player>(_smgr, _driver);
        _characters.push_back(retObject);
        break;
    case '1':
        retObject = std::make_shared<Wall>(_smgr, _driver);
        retObject->setTexture("extra/map/textures/solidblock.png", _driver);
        break;
    case '2':
        retObject = std::make_shared<Box>(_smgr, _driver);
        retObject->setTexture("extra/map/textures/explodableblock.png", _driver);
        break;
    default:
        return nullptr;
    }
    return retObject;
}

void MapHandler::setAllColision()
{
    for (size_t i = 0; i < _characters.size(); i++) {
        for (auto x : _mapObjects) {
            if (x->isBlock() == true)
                _characters[i]->setColision(_smgr,
                                            _smgr->getGeometryCreator()->createCubeMesh(irr::core::vector3df(0.8f, 2.0f, 0.8f)),
                                            x->getNode());
        }
    }
}

void MapHandler::setPositionMapObjects()
{
    size_t position = 0;

    for (size_t i = 0;  i < _mapElems.size(); i++) {
        for (size_t j = 0; j < _mapElems[i].size(); j++) {
                if (_mapObjects[position]->isBlock() == true)
                    _mapObjects[position]->setPosition(i, 0.5, j);
                if (_mapObjects[position]->isAnimated() == true)
                    _mapObjects[position]->setPosition(i, 0, j);
                position++;
        }
    }
}

void MapHandler::addCamera()
{
    auto lastLineMiddleNode = _mapObjects[_mapObjects.size() - 10]->getNode();
    auto middleLineMiddleNode = _mapObjects[_mapObjects.size()/2 + 1];
    auto posNodeToWatch = middleLineMiddleNode->getNode()->getPosition();

    _smgr->addCameraSceneNode(lastLineMiddleNode, irr::core::vector3df(0, 20, 0),
        irr::core::vector3df(10.f, 0.5f, 11.f), true);
}

std::vector<std::shared_ptr<Object>> MapHandler::getCharacters()
{
    return _characters;
}

void MapHandler::loadMap()
{
    std::shared_ptr<Object> obj;

    irr::scene::ILightSceneNode *light = _smgr->addLightSceneNode(0, irr::core::vector3df(0.f, 100.f, 0.f),
                                                                    irr::video::SColorf(255.f,255.f,255.f,255.f),
                                                                    1500);
    irr::video::ITexture *sky = _driver->getTexture("extra/map/textures/sky.png");

    _smgr->addSkyBoxSceneNode(sky, sky, sky, sky, sky, sky);

    _floor = std::make_shared<Floor>(_smgr, _driver);
    for (size_t i = 0;  i < _mapElems.size(); i++) {
        for (size_t j = 0; j < _mapElems[i].size(); j++) {
            obj = newObject(_mapElems[i][j].c_str()[0]);
            if (obj != nullptr)
                _mapObjects.push_back(obj);
        }
    }
    setPositionMapObjects();
    setAllColision();
    addCamera();
}

std::string MapHandler::getMapPositions(int x, int y) const
{
    return _mapElems[x][y];
}

std::vector<std::string> checkMapFormat(std::string line)
{
    size_t inLinePos;
    std::vector<std::string> toPushBack;
    std::string wellFormated;

    for (inLinePos = 0; inLinePos < line.size(); inLinePos++) {
        if (line[inLinePos] < '0' || line[inLinePos] > '7') {
            std::cout << "Wrong Map Format";
            return {};
        }
        wellFormated = {line.substr(inLinePos, 1)};
        toPushBack.push_back(wellFormated);
    }
    if (inLinePos != 21)
        return {};
    return toPushBack;
}

bool MapHandler::getMapElements()
{
    std::string mapPath = "extra/map/map.txt";
    size_t nbLine = 0;
    std::vector<std::string> tmp;

    std::ifstream infile(mapPath);
    if (infile) {
        for (std::string line; getline(infile, line); nbLine++) {
            tmp = checkMapFormat(line);
            if (tmp.empty())
                throw(ExceptionMap("Wrong Format"));
            _mapElems.push_back(tmp);
        }
        if (nbLine !=21)
            throw(ExceptionMap("Wrong Format"));
        return true;
    }
    throw(ExceptionMap("Fail to open file : " + mapPath));
    return false;
}

std::vector<std::vector<std::string>> MapHandler::getMapElems()
{
    return _mapElems;
}

std::vector<std::shared_ptr<Object>> MapHandler::getObjects()
{
    return _mapObjects;
}


/* ----  BOMB  ---- */


int roundItUp(float a)
{
    int exces = a;

    if (a - exces > 0.5f)
        return exces + 1;
    return exces;
}

void MapHandler::makePlayerDieFromBomb(int radius, irr::core::vector3df bombPos)
{
    int playerx = 0;
    int playerz = 0;
    int bombx = 0;
    int bombz = 0;

    for (auto x : _characters) {
        int playerx = roundItUp(x->getPosition().X);
        int playerz = roundItUp(x->getPosition().Z);
        int bombx = roundItUp(bombPos.X);
        int bombz = roundItUp(bombPos.Z);

        if (playerx >= bombx - radius && playerx <= bombx + radius && playerz == bombz)
            x->setAlive(false);
        if (playerz >= bombz - radius && playerz <= bombz + radius && playerx == bombx)
            x->setAlive(false);
    }
}

void MapHandler::deleteColision(int pos)
{
    _mapObjects[pos]->setAlive(false);
    _mapObjects[pos]->getNode()->setPosition(irr::core::vector3df(10,1000,10));
}

void MapHandler::removeUp(int radius, irr::core::vector3df bombPos)
{
    int width = _mapElems[0].size();
    int x = roundItUp(bombPos.X);
    int z = roundItUp(bombPos.Z);
    int upBlock = (x - radius) * width + z;

    if (!_mapObjects[upBlock])
        return;
    if (_mapObjects[upBlock]->isBlock() == true && _mapObjects[upBlock]->canBreak() == false && _mapObjects[upBlock]->isAlive() == true) {
        _up = true;
        return;
    }
    createFire(x - radius, 0.5f, z);
    if (_mapObjects[upBlock]->isBlock() == true && _mapObjects[upBlock]->canBreak() == true && _mapObjects[upBlock]->isAlive() == true) {
        deleteColision(upBlock);
        _up = true;
    }
}

void MapHandler::removeDown(int radius, irr::core::vector3df bombPos)
{
    int width = _mapElems[0].size();
    int x = roundItUp(bombPos.X);
    int z = roundItUp(bombPos.Z);
    int downBlock = (x + radius) * width + z;

    if (!_mapObjects[downBlock])
        return;
    if (_mapObjects[downBlock]->isBlock() == true && _mapObjects[downBlock]->canBreak() == false && _mapObjects[downBlock]->isAlive() == true) {
        _down = true;
        return;
    }
    createFire(x + radius, 0.5f, z);
    if (_mapObjects[downBlock]->isBlock() == true && _mapObjects[downBlock]->canBreak() == true && _mapObjects[downBlock]->isAlive() == true) {
        deleteColision(downBlock);
        _down = true;
    }
}

void MapHandler::removeLeft(int radius, irr::core::vector3df bombPos)
{
    int width = _mapElems[0].size();
    int x = roundItUp(bombPos.X);
    int z = roundItUp(bombPos.Z);
    int leftBlock = x * width + z - radius;

    if (!_mapObjects[leftBlock])
        return;
    if (_mapObjects[leftBlock]->isBlock() == true && _mapObjects[leftBlock]->canBreak() == false && _mapObjects[leftBlock]->isAlive() == true) {
        _left = true;
        return;
    }
    createFire(x, 0.5f, z - radius);
    if (_mapObjects[leftBlock]->isBlock() == true && _mapObjects[leftBlock]->canBreak() == true && _mapObjects[leftBlock]->isAlive() == true) {
        deleteColision(leftBlock);
        _left = true;
    }
}

void MapHandler::removeRight(int radius, irr::core::vector3df bombPos)
{
    int width = _mapElems[0].size();
    int x = roundItUp(bombPos.X);
    int z = roundItUp(bombPos.Z);
    int rightBlock = x * width + z + radius;

    if (!_mapObjects[rightBlock])
        return;
    if (_mapObjects[rightBlock]->isBlock() == true && _mapObjects[rightBlock]->canBreak() == false && _mapObjects[rightBlock]->isAlive() == true) {
        _right = true;
        return;
    }
    createFire(x, 0.5f, z + radius);
    if (_mapObjects[rightBlock]->isBlock() == true && _mapObjects[rightBlock]->canBreak() == true && _mapObjects[rightBlock]->isAlive() == true) {
        deleteColision(rightBlock);
        _right = true;
    }
}

void MapHandler::exploadSurrounding(int radius, irr::core::vector3df bombPos)
{
    _right = false;
    _left = false;
    _down = false;
    _up = false;

    for (int i = 1; i <= radius; i++) {
        if (_up == false)
            removeUp(i, bombPos);
        if (_down == false)
        removeDown(i, bombPos);
        if (_left == false)
            removeLeft(i, bombPos);
        if (_right == false)
            removeRight(i, bombPos);
    }
}

void MapHandler::exploadBlocks(int radius, irr::core::vector3df bombPos)
{
    int stop = 0;

    _audio.play(MyAudio::EXPLOSION);
    exploadSurrounding(radius, bombPos);
    makePlayerDieFromBomb(radius, bombPos);
}

void MapHandler::createFire(float x, float y, float z)
{
    std::shared_ptr<Fire> fire = std::make_shared<Fire>(_smgr, _driver);

    fire->setTime(_device->getTimer()->getTime());
    fire->getNode()->setPosition(irr::core::vector3df(x,y,z));

    _fire.push_back(fire);
}

void MapHandler::deleteFire()
{
    if (_fire.empty() == true || !_fire.begin()->get())
        return;
    for (auto x : _fire) {
        if (_device->getTimer()->getTime() - x->getTime() <= 1000)
            break;
        else {
            x->getNode()->setVisible(false);
            x->setAlive(false);
        }
    }
    while (_fire.empty() == false && _fire.begin()->get()->isAlive() == false) {
        _fire.erase(_fire.begin());
    }
}