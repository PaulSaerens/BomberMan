/*
** EPITECH PROJECT, 2020
** ExceptionINDIE
** File description:
** ExceptionINDIE
*/

#ifndef EXCEPTION_INDIE
#define EXCEPTION_INDIE

#include <string>
#include "Exception.hpp"

class ExceptionIndie : public Exception {
    public:
        ExceptionIndie(const std::string &message) throw();
        ~ExceptionIndie() = default;
};

#endif /* !EXCEPTION_INDIE */