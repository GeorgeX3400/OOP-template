//
// Created by ASUS-ROG on 15.04.2024.
//

#ifndef OOP_WALL_H
#define OOP_WALL_H
#include <raylib-cpp.hpp>
#include <iostream>
#include "Object.h"
class Wall : public Object{


public:

    Wall(float w, float h, raylib::Vector2 pos);
    Object* clone() const override;
    void Draw() override;
};


#endif //OOP_WALL_H
