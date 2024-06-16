//
// Created by ASUS-ROG on 05.05.2024.
//

#include "Coin.h"


void Coin::Draw() {
    body.Draw(color);
}



Coin::Coin() : Object(raylib::Rectangle(30, 30, 10, 10)), color(raylib::Color::Brown()), pointsOnCatch(1){}

Object *Coin::clone() const {
    return new Coin(*this);
}

Coin::Coin(int size, raylib::Color c, int points) : Object(raylib::Rectangle(0, 0, size, size)),
            color(c){
    pointsOnCatch = points;
}


int Coin::GetPointsOnCatch() {return pointsOnCatch;}
