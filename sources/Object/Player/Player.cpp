/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Player
*/

#include "Player.hpp"
#include "ExceptionPlayer.hpp"

Player::Player(irr::scene::ISceneNode *node) : Object(node)
{
    _animated = true;
    _moving = false;
    _block = false;
    _break = false;
    _alive = true;
    _speed = 0.02;
    _ani = 0;
    _smgr = nullptr;
    _driver = nullptr;
    _betweenBomb = 3000;
}

Player::Player(irr::scene::ISceneNode *node, irr::video::IVideoDriver *driver) : Object(node, driver)
{
    _animated = true;
    _block = false;
    _break = false;
    _alive = true;
    _moving = false;
    _speed = 0.02;
    _ani = 0;
    _smgr = nullptr;
    _driver = driver;
    _betweenBomb = 3000;
}

Player::Player(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver) : Object()
{
    _animated = true;
    _block = false;
    _break = false;
    _alive = true;
    _moving = false;
    _speed = 0.02;
    _ani = 0;
    _smgr = smgr;
    _driver = driver;
    _betweenBomb = 3000;

    irr::scene::IAnimatedMesh *mesh = smgr->getMesh("extra/Character/Bomberman.MD3");
    if (!mesh)
        throw (ExceptionPlayer("Can't load 3D model for player"));
    if (!driver->getTexture("extra/Character/BlackBombermanTextures.png"))
        throw (ExceptionPlayer("Can't load texture for player"));

    _nodeAnimated = smgr->addAnimatedMeshSceneNode(mesh);

    if (_nodeAnimated) {
        _nodeAnimated->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _nodeAnimated->setFrameLoop(27, 76);
        _nodeAnimated->setAnimationSpeed(30);
        _nodeAnimated->setMaterialTexture(0, driver->getTexture("extra/Character/BlackBombermanTextures.png"));
    } else
        throw ExceptionPlayer("Can't add Animated scene node");
}

Player::~Player()
{
}

void Player::setColision(irr::scene::ISceneManager *smgr, irr::scene::IMesh *mesh, irr::scene::ISceneNode *node)
{
    irr::scene::ITriangleSelector *select = smgr->createOctreeTriangleSelector(mesh, node, 128);

    if (!select)
        throw ExceptionPlayer("Can't create selector for colision");
    irr::scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(select, node, irr::core::vector3df(0.5f,0.5f,0.5f),
                                                                                irr::core::vector3df(0,0,0),
                                                                                irr::core::vector3df(0,0,0));
    select->drop();
    _nodeAnimated->addAnimator(anim);
    anim->drop();
}

void Player::setColision(irr::scene::ISceneManager *smgr, irr::scene::IMesh *mesh, irr::scene::ISceneNode *node, irr::core::vector3df vect)
{
    irr::scene::ITriangleSelector *select = smgr->createOctreeTriangleSelector(mesh, node, 128);

    if (!select)
        throw ExceptionPlayer("Can't create selector for colision");
    irr::scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(select, node, vect,
                                                                                irr::core::vector3df(0,0,0),
                                                                                irr::core::vector3df(0,0,0));
    select->drop();
    _nodeAnimated->addAnimator(anim);
    anim->drop();
}

/* ---- Movement ---- */

void Player::moveUp()
{
    updatePosition(-_speed, 0, 0);
    _orient = 90;
    _dir = DIRECTION::UP;
    _audio.play(MyAudio::WALK);
}

void Player::moveDown()
{
    updatePosition(_speed, 0, 0);
    _orient = 270;
    _dir = DIRECTION::DOWN;
    _audio.play(MyAudio::WALK);

}

void Player::moveLeft()
{
    updatePosition(0, 0, -_speed);
    _orient = 0;
    _dir = DIRECTION::LEFT;
    _audio.play(MyAudio::WALK);
}

void Player::moveRight()
{
    updatePosition(0, 0, _speed);
    _orient = 180;
    _dir = DIRECTION::RIGHT;
    _audio.play(MyAudio::WALK);
}

void Player::animation()
{
    if (_moving) {
        _nodeAnimated->setFrameLoop(_ani, 26);
        _nodeAnimated->setAnimationSpeed(30);
        _ani++;
        if (_ani >= 27)
            _ani = 0;
    } else {
        _nodeAnimated->setFrameLoop(27, 76);
        _nodeAnimated->setAnimationSpeed(1);
        _ani = 0;
    }
}

void Player::setControls()
{
    switch(_playerID) {
        case 0:
        _playerControls.push_back(irr::KEY_KEY_A);
        _playerControls.push_back(irr::KEY_KEY_Z);
        _playerControls.push_back(irr::KEY_KEY_Q);
        _playerControls.push_back(irr::KEY_KEY_S);
        _playerControls.push_back(irr::KEY_KEY_D);
        break;
        case 1:
        _playerControls.push_back(irr::KEY_KEY_I);
        _playerControls.push_back(irr::KEY_KEY_O);
        _playerControls.push_back(irr::KEY_KEY_K);
        _playerControls.push_back(irr::KEY_KEY_L);
        _playerControls.push_back(irr::KEY_KEY_M);
        break;
    }
}

enum P_ACTION Player::getPlayerMovement()
{
    setControls();
    for (auto controls : _playerControls) {
        if (_receiver.get()->IsKeyDown(controls)) {
            switch (controls) {
                case irr::KEY_KEY_A:
                case irr::KEY_KEY_I:
                    return P_ACTION::PLACE_BOMB;
                case irr::KEY_KEY_Z:
                case irr::KEY_KEY_O:
                    return P_ACTION::MOVE_UP;
                case irr::KEY_KEY_S:
                case irr::KEY_KEY_L:
                    return P_ACTION::MOVE_DOWN;
                case irr::KEY_KEY_Q:
                case irr::KEY_KEY_K:
                    return P_ACTION::MOVE_LEFT;
                case irr::KEY_KEY_M:
                case irr::KEY_KEY_D:
                    return P_ACTION::MOVE_RIGHT;
                default:
                    return P_ACTION::NO;
            }
        }
    }
    return P_ACTION::NO;
}

void Player::removeBomb()
{
    _bombs[0]->getNodeAnimated()->setVisible(false);
    _bombs.erase(_bombs.begin());
}

std::shared_ptr<Object> Player::getBomb()
{
    if (_bombs.empty() == false)
        return _bombs[0];
    return nullptr;
}

void Player::placeBomb(irr::u32 time)
{
    if (!_then && getPlayerMovement() == P_ACTION::PLACE_BOMB) {
        std::shared_ptr<Object> newBomb = std::make_shared<Bomb>(_smgr, _driver);
        newBomb->setPosition(_pos.X, _pos.Y, _pos.Z);
        newBomb->setTime(time);
        _bombs.push_back(newBomb);
        _then = time;
    }

    if (getPlayerMovement() == P_ACTION::PLACE_BOMB && time - _then >= _betweenBomb) {
        std::shared_ptr<Bomb> newBomb = std::make_shared<Bomb>(_smgr, _driver);
        newBomb->setPosition(_pos.X, _pos.Y, _pos.Z);
        newBomb->setTime(time);
        _bombs.push_back(newBomb);
        _then = time;
    }
}

void Player::move()
{
    _pos = _nodeAnimated->getPosition();

    switch(getPlayerMovement()) {
        case MOVE_UP:
            _moving = true;
            moveUp();
            break;
        case MOVE_DOWN:
            _moving = true;
            moveDown();
            break;
        case MOVE_LEFT:
            _moving = true;
            moveLeft();
            break;
        case MOVE_RIGHT:
            _moving = true;
            moveRight();
            break;
        default:
            _moving = false;
    }
    animation();
    setPosition(_pos.X, _pos.Y, _pos.Z);
    _nodeAnimated->setRotation(irr::core::vector3df(0, _orient, 0));
}

/* ---- GET ---- */

DIRECTION Player::getDirection()
{
    return _dir;
}

void Player::removeColision(irr::scene::ISceneManager *smgr, irr::scene::IMesh *mesh, irr::scene::ISceneNode *node)
{
    irr::scene::ITriangleSelector *select = smgr->createOctreeTriangleSelector(mesh, node, 0);

    if (!select)
        return; // TODO : throw
    irr::scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(select, node, irr::core::vector3df(0.5f,0.5f,0.5f),
                                                                                irr::core::vector3df(0,0,0),
                                                                                irr::core::vector3df(0,0,0));
    select->drop();
    _nodeAnimated->addAnimator(anim);
    anim->drop();

}

void Player::removeColision(irr::scene::ISceneManager *smgr, irr::scene::IMesh *mesh, irr::scene::ISceneNode *node, irr::core::vector3df vect)
{
    irr::scene::ITriangleSelector *select = smgr->createOctreeTriangleSelector(mesh, node, 0);

    if (!select)
        return; // TODO : throw
    irr::scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(select, node, vect,
                                                                                irr::core::vector3df(0,0,0),
                                                                                irr::core::vector3df(0,0,0));
    select->drop();
    _nodeAnimated->addAnimator(anim);
    anim->drop();

}

void Player::setPlayerId(int playerID)
{
    _playerID = playerID;
}