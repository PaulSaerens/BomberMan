/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** ExceptionFile
*/

#ifndef EXCEPTIONMENU_HPP_
#define EXCEPTIONMENU_HPP_

#include <string>
#include <exception>

#include "Exception.hpp"

class ExceptionMenu : public Exception {
    public:
        ExceptionMenu(const std::string &message) throw();
        ~ExceptionMenu() = default;
};

#endif /* !EXCEPTIONMenu_HPP_ */
