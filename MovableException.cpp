//
// Created by ASUS-ROG on 27.05.2024.
//

#include "MovableException.h"

MovableException::MovableException(const std::string& msg) : std::runtime_error(msg){
    std::cout << "MovableException occurred: " << msg << '\n';
}

MovableException::MovableException(const MovableException &other) : std::runtime_error(other) {
    std::cout << "cc MovableException";
}

MovableException &MovableException::operator=(const MovableException &other) {
    std::runtime_error::operator=(other);
    std::cout << "op= copiere MovableException\n";
    return *this;
}
