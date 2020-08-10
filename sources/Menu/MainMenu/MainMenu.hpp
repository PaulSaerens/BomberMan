/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MainMenu
*/

#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_

#include <memory>
#include "irrlicht.h"
#include "AMenu.hpp"
#include "MyAudio.hpp"
#include "GameHandler.hpp"

class MainMenu : public AMenu{
    public:
        class MainMenuEventReceiver : public irr::IEventReceiver
        {
            public:
                MainMenuEventReceiver(irr::IrrlichtDevice *, MainMenu &);
                ~MainMenuEventReceiver() = default;
                virtual bool OnEvent(const irr::SEvent &event);
                virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
                bool Clicked(irr::s32 id);
                bool Hovered(irr::s32 id);
                void anyKeyIsDown();
            private:
                MainMenu &_mainMenu;
                irr::IrrlichtDevice *_device;
		        bool _KeyIsDown[irr::KEY_KEY_CODES_COUNT];
        };
    public:
        MainMenu(irr::IrrlichtDevice *, irr::video::IVideoDriver *);
        ~MainMenu() = default;
        void mainLoop(void);
    private:
        //          Buttons           //
        enum GAMETYPE _type;
        void createButton(std::string buttonName,
            irr::core::rect<irr::s32> rectPos, const irr::io::path &filename, enum GAMETYPE buttonFunction);
        GAMETYPE checkButtons();
        void launchGame();
        //          Scrollbars and audio Control          //
        std::unordered_map<std::string, irr::gui::IGUIScrollBar*> _scrollbars;
        std::unique_ptr<MyAudio> _audio;
        void setScrollsBar(std::string textName, irr::core::rect<irr::s32>rectScrollBar, irr::s32 pos);

        //      Core Main Menu             //
        MainMenu::MainMenuEventReceiver _receiver;
        void initMenu();
        void setAudioControllers();
        void setMainButtons();
        void audioControl();
};

#endif /* !MAINMENU_HPP_ */
