/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Object
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <string>
#include <memory>
#include <vector>
#include "irrlicht.h"
#include "Object.hpp"
#include "MyEvent.hpp"
#include "MyAudio.hpp"
#include "Bomb/Bomb.hpp"

enum class DIRECTION {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

enum P_ACTION {
	NO = -1,
    MOVE_UP = 0,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	PLACE_BOMB
};

class Player : public Object {
    public:
        Player(irr::scene::ISceneNode *node);
        Player(irr::scene::ISceneNode *node, irr::video::IVideoDriver *driver);
        Player(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver);

        ~Player();

        void setColision(irr::scene::ISceneManager *smgr, irr::scene::IMesh *mesh, irr::scene::ISceneNode *node);
        void setColision(irr::scene::ISceneManager *smgr, irr::scene::IMesh *mesh, irr::scene::ISceneNode *node, irr::core::vector3df vect);
        void removeColision(irr::scene::ISceneManager *smgr, irr::scene::IMesh *mesh, irr::scene::ISceneNode *node);
        void removeColision(irr::scene::ISceneManager *smgr, irr::scene::IMesh *mesh, irr::scene::ISceneNode *node, irr::core::vector3df vect);
        void setPlayerId(int playerId);
        DIRECTION getDirection();
        void move();
        void placeBomb(irr::u32 time);
        void removeBomb();
        std::shared_ptr<Object> getBomb();

    private:
        irr::u32 _then;
        irr::u32 _betweenBomb;

        int _ani;
        DIRECTION _dir;
        float _speed;
        int _orient;
        bool _moving;
        MyAudio _audio;
        std::vector<irr::EKEY_CODE> _playerControls;
        void setControls();
        enum P_ACTION getPlayerMovement();
        int _playerID;
        std::vector<std::shared_ptr<Object>> _bombs;
        irr::scene::ISceneManager *_smgr;
        irr::video::IVideoDriver *_driver;
        void animation();
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
};

#endif /* !PLAYER_HPP_ */
