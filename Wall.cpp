//
// Created by ASUS-ROG on 15.04.2024.
//

#include "Wall.h"

Wall::Wall(float w, float h, raylib::Vector2 pos) : Object(raylib::Rectangle(pos, raylib::Vector2(w, h))){}

std::ostream &operator<<(std::ostream &os, const Wall &p) {
    os << "Position: x-> " << p.GetBody().GetX() << "y-> " << p.GetBody().GetY() << '\n';
    return os;
}


void Wall::Draw() {
    body.Draw(Color{80, 0, 0, 230});
}

Object *Wall::clone() const {
    return new Wall(*this);
}
