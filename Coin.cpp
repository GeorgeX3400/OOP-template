//
// Created by ASUS-ROG on 05.05.2024.
//

#include "Coin.h"


void Coin::Draw() {
    body.Draw(Color{220, 200, 10, 255});
}



Coin::Coin() : Object(raylib::Rectangle(30, 30, 10, 10)){}

Object *Coin::clone() const {
    return new Coin(*this);
}
