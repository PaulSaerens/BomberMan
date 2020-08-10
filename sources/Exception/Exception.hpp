/*
** EPITECH PROJECT, 2020
** Exception.hpp
** File description:
** Exception.hpp
*/

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>
#include <iostream>

class Exception : public std::exception {
    public:
        Exception(const std::string &message) throw();
        ~Exception() = default;
        const char* what() const throw();
    protected:
        std::string _message;
};

#endif /* !EXCEPTION_HPP */