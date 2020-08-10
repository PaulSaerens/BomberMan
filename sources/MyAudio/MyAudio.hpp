/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MyAudio
*/

#pragma once

#include <SFML/Audio.hpp>
#include <vector>
#include <memory>

class MyAudio
{
public:
    typedef enum {
        MENU,
        GAME,
        START,
        PAUSE,
        CLIC,
        WIN,
        LOSE,
        DEATH,
        WALK,
        DROP,
        TIMER,
        EXPLOSION,
        ERROR,
        POWER,
    } SOUND;

    MyAudio();
    ~MyAudio();

    void play(SOUND idx);
    void pause(SOUND idx);
    void stop(SOUND idx);
    void setMusicVolume(float volume);
    void setSoundVolume(float volume);
    float getMusicVolume();
    float getSoundVolume();

private:
    void NewSound(std::string filename, float volume, bool loop);

    std::vector<std::unique_ptr<sf::Music>> _sounds;
    float _volSound;
    float _volMusic;
};
