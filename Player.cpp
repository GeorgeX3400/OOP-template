//
// Created by ASUS-ROG on 15.04.2024.
//
#include <iostream>
#include "Player.h"
#include "OutOfBoundsException.h"

Player::Player() : MovableObject(raylib::Rectangle(500, 300, 20, 20)),
                   alive{true}{
    std::cout << "Constructor Player\n";
    if(body.GetX() < 20 || body.GetY() < 20 || body.GetX() > 700 || body.GetY() > 1080){
        throw OutOfBoundsException("Player is out of the map.");
    }

}

Player::Player(const Player &other) : MovableObject(other),
                                       alive{other.alive}{
    std::cout << "Constr de copiere Player" << '\n';
}

Player::~Player() {
    std::cout << "Destructor Player" << '\n';
}

Player &Player::operator=(const Player &other) {
    MovableObject::operator=(other);
    alive = other.alive;
    std::cout << "op= Player\n";
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Player &p) {
    os << "Position: x-> " << p.body.GetX() << "y-> " << p.body.GetY() << '\n';
    os << "Collisions:\n" << "up-> " << ((p.hasCollided[0]) ? "true\n" : "false\n");
    os << "down-> " << ((p.hasCollided[1]) ? "true\n" : "false\n");
    os << "left-> " << ((p.hasCollided[2]) ? "true\n" : "false\n");
    os << "right-> " << ((p.hasCollided[3]) ? "true\n" : "false\n");
    return os;
}



void Player::InitializeCollision() { hasCollided = {false, false, false, false}; }

void Player::SetCollision(raylib::Rectangle rec) {
    hasCollided[0] = hasCollided[0] || rec.CheckCollision(up);
    hasCollided[1] = hasCollided[1] || rec.CheckCollision(down);
    hasCollided[2] = hasCollided[2] || rec.CheckCollision(left);
    hasCollided[3] = hasCollided[3] || rec.CheckCollision(right);
}


bool Player::GetAlive() const {return alive;}

void Player::SetAlive(bool val) {alive = val;}

void Player::handleMovement() {
    float offsetX = 0, offsetY = 0;
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && !hasCollided[0])
        offsetY -= 0.5f;
    if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && !hasCollided[1])
        offsetY += 0.5f;
    if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && !hasCollided[2])
        offsetX -= 0.5f;
    if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && !hasCollided[3])
        offsetX += 0.5f;
    raylib::Vector2 offset{offsetX, offsetY};

    up.SetPosition(body.GetPosition() + raylib::Vector2(0, -2.5f));
    down.SetPosition(body.GetPosition() + raylib::Vector2(0, 21.5f));
    left.SetPosition(body.GetPosition() + raylib::Vector2(-2, 0));
    right.SetPosition(body.GetPosition() + raylib::Vector2(21, 0));
    if (offsetX && offsetY)
        offset *= 0.8f;
    offset *= 3;
    body.SetPosition(body.GetPosition() + offset);
    body.Draw({0, 0}, 0, GREEN);
}

void Player::Draw() {}

Object *Player::clone() const {
    return new Player(*this);
}
