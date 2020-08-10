/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Object
*/

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <string>
#include <memory>
#include "MyEvent.hpp"
#include "irrlicht.h"

class Object {
    public:
        Object();
        Object(irr::scene::ISceneNode *node);
        Object(irr::scene::ISceneNode *node, irr::video::IVideoDriver *driver);
        Object(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver);

        ~Object();

        virtual void setPosition(irr::f32, irr::f32, irr::f32);
        virtual void updatePosition(irr::f32, irr::f32, irr::f32);
        virtual void setBreak(bool val);
        virtual void setAlive(bool val);
        virtual void setAnimated(bool val);
        virtual void setColision(irr::scene::ISceneManager *smgr, irr::scene::IMesh *mesh, irr::scene::ISceneNode *node);
        virtual void setColision(irr::scene::ISceneManager *smgr, irr::scene::IMesh *mesh, irr::scene::ISceneNode *node, irr::core::vector3df vect);
        virtual void removeColision(irr::scene::ISceneManager *smgr, irr::scene::IMesh *mesh, irr::scene::ISceneNode *node);
        virtual void removeColision(irr::scene::ISceneManager *smgr, irr::scene::IMesh *mesh, irr::scene::ISceneNode *node, irr::core::vector3df vect);
        virtual void setTexture(const std::string &path, irr::video::IVideoDriver *driver);
        virtual void setEvents(std::shared_ptr<MyEvent>);
        /* - Blocks - */
        virtual void setVisibility(bool);
        virtual void setNode(irr::scene::ISceneNode *node);
        /* - Player - */
        virtual void move();
        virtual void placeBomb(irr::u32 time);
        virtual void removeBomb();
        virtual std::shared_ptr<Object> getBomb();
        virtual void setPlayerId(int playerId);
        /* - Bomb - */
        virtual bool isBombExploading(irr::u32 time);
        virtual void setTime(irr::u32 time);
        virtual int getRadius();

        virtual irr::scene::ISceneNode *getNode();
        virtual irr::scene::IAnimatedMeshSceneNode *getNodeAnimated();
        virtual irr::core::vector3df getPosition();
        virtual bool canBreak();
        virtual bool isAlive();
        virtual bool isBlock();
        virtual bool isAnimated();


    protected:
        irr::scene::ISceneNode *_node;
        irr::scene::IAnimatedMeshSceneNode *_nodeAnimated;
        bool _animated;
        bool _break;
        bool _alive;
        bool _block;
        irr::core::vector3df _pos;
        std::shared_ptr<MyEvent> _receiver;
};

#endif /* !OBJECT_HPP_ */
