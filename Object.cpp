//
// Created by ASUS-ROG on 18.04.2024.
//

#include "Object.h"

raylib::Vector2 Object::GetPosition() {return body.GetPosition();}

void Object::SetPosition(raylib::Vector2 pos) {
    body.SetPosition(pos);
}

raylib::Rectangle  Object::GetBody() const {return body;}


Object::Object() = default;

Object::Object(raylib::Rectangle r) : body{r} {}

std::ostream &operator<<(std::ostream &os, const Object &o) {
    os << "Position: x-> " << o.body.GetX() << "y-> " << o.body.GetY() << '\n';
    return os;
}

void Object::afisare(std::ostream &os) const {
    os << "Position: x-> " << body.GetX() << "y-> " << body.GetY() << '\n';
}

void swap(Object &o1, Object &o2) {
    using std::swap;
    swap(o1.body, o2.body);
}

Object::Object(const Object& other) = default;

Object::~Object() = default;



