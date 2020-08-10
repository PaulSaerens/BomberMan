/*
** EPITECH PROJECT, 2020
** EndMenu.hpp
** File description:
** EndMenu.cpp
*/

#ifndef ENDMENU_HPP_
#define ENDMENU_HPP_

#include <memory>
#include "irrlicht.h"
#include "AMenu.hpp"
#include "MyAudio.hpp"
#include "BombermanCore.hpp"

enum ENDTYPE {
    E_NONE = -1,
    E_MAINMENU = 0,
    E_QUIT,
};

class EndMenu : public AMenu {
    public:
        class EndMenuEventReceiver : public irr::IEventReceiver
            {
                public:
                    EndMenuEventReceiver(irr::IrrlichtDevice *, EndMenu &);
                    ~EndMenuEventReceiver() = default;
                    virtual bool OnEvent(const irr::SEvent &event);
                    virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
                    bool Clicked(irr::s32 id);
                    bool Hovered(irr::s32 id);
                    void anyKeyIsDown();
                private:
                    EndMenu &_endMenu;
                    irr::IrrlichtDevice *_device;
	    	        bool _KeyIsDown[irr::KEY_KEY_CODES_COUNT];
            };
    public:
        EndMenu(irr::IrrlichtDevice *, irr::video::IVideoDriver *);
        ENDTYPE endMenuLoop();
    private:
        enum ENDTYPE _type;
        std::unique_ptr<MyAudio> _audio;

        EndMenu::EndMenuEventReceiver _receiver;
        void createButton(std::string, irr::core::rect<irr::s32>, const irr::io::path &, enum ENDTYPE buttonFunction);
        std::unordered_map<std::string, irr::gui::IGUIButton *> _buttons;

        void initMenu();
        void setMainButtons();
        void drawMenu();
};

#endif /* !ENDMENU_HPP_ */
