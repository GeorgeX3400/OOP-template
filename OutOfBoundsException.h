//
// Created by ASUS-ROG on 27.05.2024.
//

#ifndef OOP_OUTOFBOUNDSEXCEPTION_H
#define OOP_OUTOFBOUNDSEXCEPTION_H
#include <iostream>
#include "MovableException.h"

class OutOfBoundsException : public MovableException{
public:
    OutOfBoundsException(std::string msg);

};


#endif //OOP_OUTOFBOUNDSEXCEPTION_H
