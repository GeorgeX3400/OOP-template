//
// Created by ASUS-ROG on 10.04.2024.
//

#ifndef OOP_TEMPLATE_BULLET_H
#define OOP_TEMPLATE_BULLET_H
#include <raylib-cpp.hpp>
#include <iostream>
#include "MovableObject.h"
class Bullet : public MovableObject{

    raylib::Vector2 direction;
    raylib::Vector2 spawnPosition;

public:
    Bullet(raylib::Vector2 origin, raylib::Vector2 target);
    friend std::ostream& operator<<(std::ostream& os, const Bullet& p);
    void Draw() override;
    void handleMovement() override;
    [[maybe_unused]]Object* clone() const override;
};


#endif //OOP_TEMPLATE_BULLET_H
