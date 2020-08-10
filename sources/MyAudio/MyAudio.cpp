/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MyAudio
*/

#include "MyAudio.hpp"
#include <iostream>

MyAudio::MyAudio()
{
    _volMusic = 5;
    _volSound = 15;
    NewSound("./extra/sounds/menu.wav", _volMusic, true);
    NewSound("./extra/sounds/game.wav", _volMusic, true);
    NewSound("./extra/sounds/start.wav", _volSound, true);
    NewSound("./extra/sounds/pause.wav", _volSound, true);
    NewSound("./extra/sounds/clic.wav", _volSound, false);
    NewSound("./extra/sounds/win.wav", _volSound, false);
    NewSound("./extra/sounds/lose.wav", _volSound, false);
    NewSound("./extra/sounds/death.wav", _volSound, false);
    NewSound("./extra/sounds/step.wav", _volSound, false);
    NewSound("./extra/sounds/drop.wav", _volSound, false);
    NewSound("./extra/sounds/clock.wav", _volSound, false);
    NewSound("./extra/sounds/explosion.wav", _volSound, false);
    NewSound("./extra/sounds/error.wav", _volSound, false);
    NewSound("./extra/sounds/power-up.wav", _volSound, false);
}

MyAudio::~MyAudio()
{
}

void MyAudio::NewSound(std::string filename, float volume, bool loop)
{
    auto newsound = std::make_unique<sf::Music>();

    if (!newsound->openFromFile(filename))
        return;
    newsound->setVolume(volume);
    newsound->setLoop(loop);
    _sounds.push_back(std::move(newsound));
}

void MyAudio::play(SOUND idx)
{
    if (_sounds[idx] && _sounds[idx]->getStatus() != sf::Music::Playing)
        _sounds[idx]->play();
}

void MyAudio::pause(SOUND idx)
{
    if (_sounds[idx] && _sounds[idx]->getStatus() != sf::Music::Paused)
        _sounds[idx]->pause();
}

void MyAudio::stop(SOUND idx)
{
    if (_sounds[idx] && _sounds[idx]->getStatus() != sf::Music::Stopped)
        _sounds[idx]->stop();
}

void MyAudio::setMusicVolume(float volume)
{
    if (volume < 0 || volume > 100 || volume == _volMusic)
        return;
    _volMusic = volume;
    _sounds[MENU]->setVolume(volume);
    _sounds[GAME]->setVolume(volume);
}

void MyAudio::setSoundVolume(float volume)
{
    if (volume < 0 || volume > 100 || volume == _volSound)
        return;
    _volSound = volume;
    _sounds[START]->setVolume(volume);
    _sounds[WIN]->setVolume(volume);
    _sounds[LOSE]->setVolume(volume);
    _sounds[PAUSE]->setVolume(volume);
    _sounds[CLIC]->setVolume(volume);
    _sounds[DEATH]->setVolume(volume);
    _sounds[WALK]->setVolume(volume);
    _sounds[DROP]->setVolume(volume);
    _sounds[EXPLOSION]->setVolume(volume);
    _sounds[ERROR]->setVolume(volume);
    _sounds[POWER]->setVolume(volume);
}

float MyAudio::getMusicVolume()
{
    return _volMusic;
}

float MyAudio::getSoundVolume()
{
    return _volSound;
}
