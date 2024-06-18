//
// Created by ASUS-ROG on 05.05.2024.
//

#ifndef OOP_COIN_H
#define OOP_COIN_H
#include <raylib-cpp.hpp>
#include "Object.h"
class Coin : public Object{
    raylib::Color color;
    int pointsOnCatch;
public:
    Coin();
    Coin(int size, raylib::Color c, int points);
    int GetPointsOnCatch();
    void Draw() override;
};


#endif //OOP_COIN_H
