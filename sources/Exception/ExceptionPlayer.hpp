/*
** EPITECH PROJECT, 2020
** ExceptionPlayer.hpp
** File description:
** ExceptionPlayer.hpp
*/

#ifndef EXCEPTION_PLAYER_HPP
#define EXCEPTION_PLAYER_HPP

#include <string>
#include <exception>

#include "Exception.hpp"

class ExceptionPlayer : public Exception {
    public:
        ExceptionPlayer(const std::string &message) throw();
        ~ExceptionPlayer() = default;
};

#endif /* !EXCEPTION_PLAYER_HPP */
