/*
** EPITECH PROJECT, 2020
** EndMenu.cpp
** File description:
** EndMenu.cpp
*/

#include "EndMenu.hpp"

EndMenu::EndMenuEventReceiver::EndMenuEventReceiver(irr::IrrlichtDevice *device, EndMenu &endMenu)
    : _device(device), _endMenu(endMenu)
{
    anyKeyIsDown();
}

void EndMenu::EndMenuEventReceiver::anyKeyIsDown()
{
    for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
        _KeyIsDown[i] = false;
}

bool EndMenu::EndMenuEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
    return _KeyIsDown[keyCode];
}

bool EndMenu::EndMenuEventReceiver::Clicked(irr::s32 id)
{
    switch (id) {
        case ENDTYPE::E_QUIT:
            _endMenu._type = ENDTYPE::E_QUIT;
            return true;
        case ENDTYPE::E_MAINMENU:
            _endMenu._type = ENDTYPE::E_MAINMENU;
            return true;
        default:
            _endMenu._type = ENDTYPE::E_NONE;
            return false;
    }
    return false;
}

bool EndMenu::EndMenuEventReceiver::OnEvent(const irr::SEvent &event)
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
				_endMenu._type = ENDTYPE::E_NONE;
				break;
		}
	}
	return false;
}

EndMenu::EndMenu(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver)
    : AMenu(device, driver), _receiver(_device, *this)
{
    clearScene();
    _guienv->addImage(_device->getVideoDriver()->getTexture("extra/menu/EndMenu.png"), irr::core::position2d<int>(0, 0));
    if (!_guienv)
        throw ExceptionMenu("can't load background image for Ending Menu");
}

void EndMenu::createButton(std::string buttonName,
    irr::core::rect<irr::s32> rectPos, const irr::io::path &filename, ENDTYPE buttonFunction)
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

void EndMenu::setMainButtons()
{
    createButton("single", irr::core::rect<irr::s32>(800, 550, 800 + 300, 550 + 100 ), "extra/menu/mainmenu", ENDTYPE::E_MAINMENU);
    createButton("quit", irr::core::rect<irr::s32>(800, 665, 800 + 300, 665 + 100), "extra/menu/quit", ENDTYPE::E_QUIT);
}

void EndMenu::initMenu()
{
    _receiver.anyKeyIsDown();
    _type = ENDTYPE::E_NONE;
    _device->setEventReceiver(&_receiver);
    _audio = std::make_unique<MyAudio>();
    setMainButtons();
}

void EndMenu::drawMenu()
{
    _device->getCursorControl()->setVisible(true);
    _driver->beginScene(true, true, irr::video::SColor(255,100,101,140));
    _guienv->drawAll();
}

ENDTYPE EndMenu::endMenuLoop()
{
    initMenu();
        while (_device->run()) {
        _audio->play(MyAudio::MENU);
        drawMenu();
        if (_type != ENDTYPE::E_NONE) {
            _audio->stop(MyAudio::MENU);
            _audio->play(MyAudio::CLIC);
            if (_type == ENDTYPE::E_MAINMENU) {
                clearScene();
                auto mainMenu = std::make_unique<MainMenu>(_device, _driver);
                mainMenu->mainLoop();
            }
            if (_type == ENDTYPE::E_QUIT) {
                _texts.clear();
                _buttons.clear();
                _device->closeDevice();
	            _device->run();
	            _device->drop();
                exit(0);
            }

        }
        _driver->endScene();
    }
    return ENDTYPE::E_NONE;
}
