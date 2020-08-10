/*
** EPITECH PROJECT, 2020
** BombermanMain.hpp
** File description:
** BombermanMain.hpp
*/


#ifndef BOMBERMANCORE_HPP
#define BOMBERMANCORE_HPP

#include "MainMenu/MainMenu.hpp"
#include <memory>
#include "MyAudio.hpp"

class BombermanCore {
    public:
        BombermanCore(int width, int height);
        ~BombermanCore();
        void RunMenu();

    protected:
    private:
        int _width;
        int _height;
        bool _gameIsRunning;
        irr::IrrlichtDevice * _device;
        irr::video::IVideoDriver *_driver;
    };

#endif /* !BombermanCore */
