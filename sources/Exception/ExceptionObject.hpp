/*
** EPITECH PROJECT, 2020
** ExceptionPlayer.hpp
** File description:
** ExceptionObject.hpp
*/

#ifndef EXCEPTION_OBJECT_HPP
#define EXCEPTION_OBJECT_HPP

#include <string>
#include <exception>

#include "Exception.hpp"

class ExceptionObject : public Exception {
    public:
        ExceptionObject(const std::string &message) throw();
        ~ExceptionObject() = default;
};

#endif /* !EXCEPTION_ObjExceptionObject_HPP */
