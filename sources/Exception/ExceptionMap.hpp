/*
** EPITECH PROJECT, 2020
** ExceptionPlayer.hpp
** File description:
** ExceptionMap.hpp
*/

#ifndef EXCEPTION_MAP_HPP
#define EXCEPTION_MAP_HPP

#include <string>
#include <exception>

#include "Exception.hpp"

class ExceptionMap : public Exception {
    public:
        ExceptionMap(const std::string &message) throw();
        ~ExceptionMap() = default;
};

#endif /* !EXCEPTION_MAP_HPP */
