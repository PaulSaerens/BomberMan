/*
** EPITECH PROJECT, 2020
** main.cpp
** File description:
** main.cpp
*/

#include <iostream>
#include "BombermanCore/BombermanCore.hpp"
#include "Exception.hpp"


int main()
{
    BombermanCore core(1920, 1080);
    try {
        core.RunMenu();
    } catch (Exception &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    } catch (...) {
        std::cerr << "Unknown Error" << std::endl;
        return (84);
    }
    return (0);
}