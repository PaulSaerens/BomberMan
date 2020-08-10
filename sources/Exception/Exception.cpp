/*
** EPITECH PROJECT, 2020
** Exception.cpp
** File description:
** Exception.cpp
*/

#include "Exception.hpp"

Exception::Exception(const std::string &message) throw()
{
    this->_message = message;
}

const char* Exception::what() const throw()
{
    return (this->_message.data());
}