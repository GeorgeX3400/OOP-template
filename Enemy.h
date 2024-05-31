//
// Created by ASUS-ROG on 15.04.2024.
//

#ifndef OOP_ENEMY_H
#define OOP_ENEMY_H
#include <raylib-cpp.hpp>
#include <iostream>
#include "MovableObject.h"
class Enemy : public MovableObject {

    float speed;
    raylib::Vector2 direction;
    raylib::Vector2 target;
    float currentNuance; //


private:
    void CalculateAndNormalizeDirection();
    int lerp(raylib::Vector2 target);
    //lerp - short for "interpolation":
    //calculates the brightness of the enemy body
    // depending on how close it is to the player

public:
    Enemy() {}
    Enemy(float x, float y);
    friend std::ostream& operator<<(std::ostream& os, const Enemy& e);
    void SetTarget(raylib::Vector2 t);
    float GetSpeed();
    void SetSpeed(float val);
    void InitializeCollision();
    void SetCollision(const raylib::Rectangle &rec);
    void handleMovement() override;
    void Draw() override;
    [[maybe_unused]]Object* clone() const override;

};


#endif //OOP_ENEMY_H
