/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** ExceptionFile
*/

#include "ExceptionMenu.hpp"

ExceptionMenu::ExceptionMenu(const std::string &message) throw() : Exception("Menu Error:" + message)
{
}
