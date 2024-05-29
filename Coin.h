//
// Created by ASUS-ROG on 05.05.2024.
//

#ifndef OOP_COIN_H
#define OOP_COIN_H
#include <raylib-cpp.hpp>
#include "Object.h"
class Coin : public Object{
public:
    Coin();
    void Draw() override;
    Object* clone() const override;;
};


#endif //OOP_COIN_H
