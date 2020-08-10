/*
** EPITECH PROJECT, 2020
** ExceptionPlayer.cpp
** File description:
** ExceptionPlayer.cpp
*/

#include "ExceptionMap.hpp"

ExceptionMap::ExceptionMap(const std::string &message) throw() : Exception("Map Error: " + message)
{
}
