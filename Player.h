//
// Created by ASUS-ROG on 15.04.2024.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H
#include <raylib-cpp.hpp>
#include <iostream>
#include "MovableObject.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

class Player : public MovableObject
{

    bool alive;

public:
    Player();

    Player(const Player& other);
    ~Player();
    Player& operator=(const Player& other);
    //operator <<:
    friend std::ostream& operator<<(std::ostream& os, const Player& p);

    void InitializeCollision();
    void SetCollision(raylib::Rectangle rec);
    bool GetAlive() const;
    void SetAlive(bool val);
    void handleMovement() override;
    void Draw() override;
};
//left to check the position setter (and remove one of them)

#endif //OOP_PLAYER_H
