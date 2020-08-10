/*
** EPITECH PROJECT, 2020
** ExceptionArcade.cpp
** File description:
** ExceptionArcade
*/

#include "ExceptionIndie.hpp"

ExceptionIndie::ExceptionIndie(const std::string &message) throw() : Exception("Indie Error: " + message)
{
}