//
// Created by ASUS-ROG on 18.04.2024.
//

#include "MovableObject.h"


MovableObject &MovableObject::operator=(const MovableObject &other) {
    Object::operator=(other);
    up = other.up;
    down = other.down;
    left = other.left;
    right = other.right;
    hasCollided = other.hasCollided;
    std::cout << "op= MovableObject\n";
    return *this;

}

MovableObject::MovableObject(const MovableObject& other) = default;

MovableObject::MovableObject(raylib::Rectangle r) : Object(r),
                        up{raylib::Rectangle{body.GetX() + 1, body.GetY() - 2, 18, 1}},
                        down{raylib::Rectangle{body.GetX() + 1, body.GetY() + body.GetHeight() + 1, 18, 1}},
                        left{raylib::Rectangle{body.GetX() - 2.2f, body.GetY(), 1, 20}},
                        right{raylib::Rectangle{body.GetX() + body.GetWidth() + 1.2f, body.GetHeight(), 1, 20}}{}

void MovableObject::afisare(std::ostream &os) const {
    os << "Position: x-> " << body.GetX() << "y-> " << body.GetY() << '\n';
    os << "Collisions:\n" << "up-> " << ((hasCollided[0]) ? "true\n" : "false\n");
    os << "down-> " << ((hasCollided[1]) ? "true\n" : "false\n");
    os << "left-> " << ((hasCollided[2]) ? "true\n" : "false\n");
    os << "right-> " << ((hasCollided[3]) ? "true\n" : "false\n");
}

MovableObject::~MovableObject() = default;



