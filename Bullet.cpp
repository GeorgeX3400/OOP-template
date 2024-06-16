//
// Created by ASUS-ROG on 10.04.2024.
//

#include "Bullet.h"

Bullet::Bullet(raylib::Vector2 origin, raylib::Vector2 target) : MovableObject(raylib::Rectangle(origin, raylib::Vector2(10, 10))),
                                    direction{target - origin}{
    float distance = std::sqrt((target.GetX() - origin.GetX()) * (target.GetX() - origin.GetX()) +
                               (target.GetY() - origin.GetY()) * (target.GetY() - origin.GetY()));
    direction *= 1.0f / distance;
    spawnPosition = origin + direction * 25;
    body.SetPosition(spawnPosition);

}


std::ostream &operator<<(std::ostream &os, const Bullet &p) {
    os << "pew pew\n" << "Direction: x:" << p.direction.GetX() << "  y:" << p.direction.GetY();
    return os;
}

void Bullet::Draw() {}



void Bullet::handleMovement() {
    raylib::Vector2 position = body.GetPosition();
    position += direction * 5;
    body.SetPosition(position);
    body.Draw(Color{220, 220, 220, 250});
}


