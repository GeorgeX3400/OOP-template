//
// Created by ASUS-ROG on 27.05.2024.
//

#include "ObjectException.h"

ObjectException::ObjectException(const std::string& msg) : std::runtime_error(msg){
    std::cout << "ObjectException occurred: " << msg << '\n';
}

ObjectException::ObjectException(const ObjectException &other) : std::runtime_error(other) {
    std::cout << "cc ObjectException";
}

ObjectException &ObjectException::operator=(const ObjectException &other) {
    std::runtime_error::operator=(other);
    std::cout << "op= copiere ObjectException\n";
    return *this;
}
