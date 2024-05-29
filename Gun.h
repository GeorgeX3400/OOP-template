//
// Created by ASUS-ROG on 15.04.2024.
//

#ifndef OOP_GUN_H
#define OOP_GUN_H

#include <raylib-cpp.hpp>
#include <iostream>
#include "Bullet.h"

class Gun{
    std::vector<Bullet> bullets;

public:
    Gun() {}
    std::vector<Bullet>& GetBullets();
    friend std::ostream& operator<<(std::ostream& os, const Gun& p);
    void handleShooting(raylib::Vector2 origin);
};


#endif //OOP_GUN_H
