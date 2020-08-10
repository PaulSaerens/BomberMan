/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MainMenu
*/

#include "MainMenu.hpp"
#include <iostream>

//XCEPTIONS ON FILES

/////////////////////////////////////////////////////////////////////
//MainMenu::MainMenuEventReceiver handling events on game main menu
/////////////////////////////////////////////////////////////////////

MainMenu::MainMenuEventReceiver::MainMenuEventReceiver(irr::IrrlichtDevice *device, MainMenu &mainMenu)
    : _device(device), _mainMenu(mainMenu)
{
    anyKeyIsDown();
}

void MainMenu::MainMenuEventReceiver::anyKeyIsDown()
{
    for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
        _KeyIsDown[i] = false;
}

bool MainMenu::MainMenuEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
    return _KeyIsDown[keyCode];
}

bool MainMenu::MainMenuEventReceiver::Clicked(irr::s32 id)
{
    switch (id) {
        case GAMETYPE::QUIT:
            _mainMenu._type = GAMETYPE::QUIT;
            return true;
        case GAMETYPE::SOLO:
            _mainMenu._type = GAMETYPE::SOLO;
            return true;
        case GAMETYPE::MULTIPLAYER:
            _mainMenu._type = GAMETYPE::MULTIPLAYER;
            return true;
        default:
            _mainMenu._type = GAMETYPE::NONE;
            return false;
    }
    return false;
}

bool MainMenu::MainMenuEventReceiver::OnEvent(const irr::SEvent &event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		_KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	if (event.EventType == irr::EET_GUI_EVENT)
	{
		irr::s32 id = event.GUIEvent.Caller->getID();
		switch(event.GUIEvent.EventType) {
			case irr::gui::EGET_BUTTON_CLICKED:
				return Clicked(id);
			default:
				_mainMenu._type = GAMETYPE::NONE;
				break;
		}
	}
	return false;
}

///////////////////////////////////////////////////
//Main menu handling display, events of buttons
///////////////////////////////////////////////////

MainMenu::MainMenu(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver)
    : AMenu(device, driver), _receiver(_device, *this)
{
    _guienv->addImage(_device->getVideoDriver()->getTexture("extra/menu/MenuBack.png"), irr::core::position2d<int>(0, 0));
    if (!_guienv)
        throw("Can't load Main Menu background");

}

void MainMenu::createButton(std::string buttonName,
    irr::core::rect<irr::s32> rectPos, const irr::io::path &filename, enum GAMETYPE buttonFunction)
{
    auto button = _guienv->addButton(rectPos, 0, buttonFunction);
    button->setImage(_driver->getTexture(filename + ".png"));
    button->setPressedImage(_driver->getTexture(filename + "_yellow.png"));
    if (!button)
        throw ExceptionMenu("can't load button texture");
    button->setScaleImage(true);
    button->setUseAlphaChannel(true);
    button->setDrawBorder(0);
   _buttons[buttonName] = button;
}

void MainMenu::setScrollsBar(std::string scrollbarName, irr::core::rect<irr::s32>rectScrollBar, irr::s32 pos)
{
    auto scrollBar = _guienv->addScrollBar(true, rectScrollBar);
    scrollBar->setMax(100);
    scrollBar->setPos(pos);
    if (!scrollBar)
        throw ExceptionMenu("can't set Main Menu scrollbar");
    _scrollbars[scrollbarName] = scrollBar;
}

void MainMenu::setMainButtons()
{
    createButton("single", irr::core::rect<irr::s32>(800, 350, 800 + 300, 350 + 100), "extra/menu/singleplayer", GAMETYPE::SOLO);
    createButton("multi", irr::core::rect<irr::s32>(800, 465, 800 + 300, 465 + 100), "extra/menu/multiplayer", GAMETYPE::MULTIPLAYER);
    createButton("quit", irr::core::rect<irr::s32>(800, 580, 800 + 300, 580 + 100), "extra/menu/quit", GAMETYPE::QUIT);
}

void MainMenu::setAudioControllers()
{
    setTextImage("music", irr::core::rect<irr::s32>(1650, 760, 1650 + 150, 760 + 30), "extra/menu/music.png");
    setTextImage("sound", irr::core::rect<irr::s32>(1650, 860, 1650 + 150, 860 + 30), "extra/menu/sound.png");
    setScrollsBar("musicScrollbar", irr::core::rect<irr::s32>(1700, 800, 1700 + 150, 800 + 15), _audio->getMusicVolume());
    setScrollsBar("soundScrollbar", irr::core::rect<irr::s32>(1700, 900, 1700 + 150, 900 + 15), _audio->getSoundVolume());
}

void MainMenu::initMenu()
{
    _receiver.anyKeyIsDown();
    _type = GAMETYPE::NONE;
    _device->setEventReceiver(&_receiver);
    _audio = std::make_unique<MyAudio>();
    setMainButtons();
    setAudioControllers();
}

void MainMenu::audioControl()
{
    if (!_scrollbars.empty()) {
        if ((float)_scrollbars["musicScrollbar"]->getPos() != _audio->getMusicVolume())
            _audio->setMusicVolume((float)_scrollbars["musicScrollbar"]->getPos());
        if ((float)_scrollbars["soundScrollbar"]->getPos() != _audio->getSoundVolume())
            _audio->setSoundVolume((float)_scrollbars["soundScrollbar"]->getPos());
    }
}

void MainMenu::launchGame()
{
    GameHandler game(_device, _type);
    game.Launch();
}

GAMETYPE MainMenu::checkButtons()
{
    switch(_type) {
        case (GAMETYPE::SOLO):
            launchGame();
            break;
        case (GAMETYPE::MULTIPLAYER):
            launchGame();
            break;
        case (GAMETYPE::QUIT):
            _scrollbars.clear();
            _texts.clear();
            _buttons.clear();
            return GAMETYPE::QUIT;
        default:
            break;
    }
    return GAMETYPE::NONE;
}

void MainMenu::mainLoop(void)
{
    initMenu();
    while (_device->run()) {
        _audio->play(MyAudio::MENU);
        drawMenu();
        if (_type != GAMETYPE::NONE) {
            _audio->stop(MyAudio::MENU);
            _audio->play(MyAudio::CLIC);
            if (checkButtons() == GAMETYPE::QUIT) {
                _device->closeDevice();
	            _device->run();
	            _device->drop();
                exit(0);
            }
        }
        audioControl();
        _driver->endScene();
    }
}