//
// Created by ASUS-ROG on 27.05.2024.
//

#ifndef OOP_MOVABLEEXCEPTION_H
#define OOP_MOVABLEEXCEPTION_H
#include <stdexcept>
#include <iostream>


class MovableException : public std::runtime_error {
protected:
    MovableException(std::string msg);
    MovableException(const MovableException& other);
    MovableException& operator=(const MovableException& other);

};


#endif //OOP_MOVABLEEXCEPTION_H
