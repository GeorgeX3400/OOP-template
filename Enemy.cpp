//
// Created by ASUS-ROG on 15.04.2024.
//

#include "Enemy.h"

void Enemy::CalculateAndNormalizeDirection() {
    direction = target - body.GetPosition();
    float distance = std::sqrt((target.GetX() - body.GetX()) * (target.GetX() - body.GetX())
                               + (target.GetY() - body.GetY()) * (target.GetY() - body.GetY()));
    direction *= 1.0f / distance;
    if ((direction.GetY() < 0 && hasCollided[0]) || (direction.GetY() > 0 && hasCollided[1]))
        direction.SetY(0);
    if ((direction.GetX() < 0 && hasCollided[2]) || (direction.GetX() > 0 && hasCollided[3]))
        direction.SetX(0);
}

Enemy::Enemy() : MovableObject(raylib::Rectangle(25, 25, 20, 20)),
                                 speed{0.8f}, currentNuance{(float)10} {}

std::ostream &operator<<(std::ostream &os, const Enemy &e) {
    os << "Position: x-> " << e.body.GetX() << " y-> " << e.body.GetY() << '\n';
    os << "Target: x-> " << e.target.GetX() << " y-> " << e.target.GetY() << '\n';
    return os;
}



void Enemy::SetTarget(raylib::Vector2 t) { target = t; }

float Enemy::GetSpeed() {return speed;}

void Enemy::SetSpeed(float val) {speed = val;}

void Enemy::InitializeCollision() { for(int i = 0; i < 4; i++) hasCollided[i] = false; }

void Enemy::SetCollision(const raylib::Rectangle &rec) {
    hasCollided[0] = hasCollided[0] || up.CheckCollision(rec);
    hasCollided[1] = hasCollided[1] || down.CheckCollision(rec);
    hasCollided[2] = hasCollided[2] || left.CheckCollision(rec);
    hasCollided[3] = hasCollided[3] || right.CheckCollision(rec);
}

int Enemy::lerp(raylib::Vector2 tgt) {
    float lowerBoundNuance = 10, upperBoundNuance = 250;
    float lowerDistance = 80, upperDistance = 150;
    float distance = std::sqrt((body.GetX() - tgt.GetX()) * (body.GetX() - tgt.GetX())
            + (body.GetY() - tgt.GetY()) * (body.GetY() - tgt.GetY()));
    if(distance > upperDistance) return lowerBoundNuance;
    else if (distance < lowerDistance) return upperBoundNuance;
    else {
       float percentage = (distance - lowerDistance) / (upperDistance - lowerDistance);
       float result = upperBoundNuance - percentage * (upperBoundNuance - lowerBoundNuance);
       return (int)result;
    }
}

void Enemy::Draw() {}

void Enemy::handleMovement() {
    std:: cout << "target: " << target.GetX() << " " << target.GetY() << '\n';
    std::cout << "direction: " << direction.GetX() << " " << direction.GetY() << '\n';
    CalculateAndNormalizeDirection();
    raylib::Vector2 position = body.GetPosition() + direction * speed;
    body.SetPosition(position);
    up.SetPosition(body.GetPosition() + raylib::Vector2(0, -2.5f));
    down.SetPosition(body.GetPosition() + raylib::Vector2(0, 21.5f));
    left.SetPosition(body.GetPosition() + raylib::Vector2(-2, 0));
    right.SetPosition(body.GetPosition() + raylib::Vector2(21, 0));
    currentNuance = lerp(target);
    body.Draw({0, 0}, 0, raylib::Color(currentNuance, 5, 5));
}

Object *Enemy::clone() const {
    return new Enemy(*this);
}
