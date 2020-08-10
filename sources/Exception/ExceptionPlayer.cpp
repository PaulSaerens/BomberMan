/*
** EPITECH PROJECT, 2020
** ExceptionPlayer.cpp
** File description:
** ExceptionPlayer.cpp
*/

#include "ExceptionPlayer.hpp"

ExceptionPlayer::ExceptionPlayer(const std::string &message) throw() : Exception("Player Error: " + message)
{
}
