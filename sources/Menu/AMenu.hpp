/*
** EPITECH PROJECT, 2020
** AMenu.hpp
** File description:
** AMenu.hpp
*/

#ifndef AMENU_HPP_
#define AMENU_HPP_

#include "ExceptionMenu.hpp"
#include <unordered_map>
#include "irrlicht.h"

enum GAMETYPE {
    NONE = -1,
    SOLO = 0,
    MULTIPLAYER,
    QUIT,
};

class AMenu {
    public:
        explicit AMenu(irr::IrrlichtDevice *, irr::video::IVideoDriver *);
        virtual ~AMenu() = default;
    protected:
        irr::IrrlichtDevice *_device;
	    irr::video::IVideoDriver *_driver;
	    irr::gui::IGUIEnvironment *_guienv;
	    irr::scene::ISceneManager *_smgr;
        std::unordered_map<std::string, irr::gui::IGUIButton *> _buttons;
        std::unordered_map<std::string, irr::gui::IGUIImage*> _texts;
        void setTextImage(std::string, irr::core::rect<irr::s32>, const irr::io::path &);
        void drawMenu();
        void clearScene();
};

#endif /* !AMENU_HPP_ */
