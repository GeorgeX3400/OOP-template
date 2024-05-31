//
// Created by ASUS-ROG on 16.04.2024.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H
#include <raylib-cpp.hpp>
#include "Statistics.h"
#include "Player.h"
#include "Gun.h"
#include "Enemy.h"
#include "Wall.h"
#include "Coin.h"
#include "OutOfBoundsException.h"

class Game {
    //variables used in the gameplay:
    raylib::Vector2 startPosition{};
    std::vector<Object*> walls;
    Statistics statistics;
    Player* player;
    Gun gun;
    Enemy* enemy;
    std::vector<raylib::Vector2> spawnPoints;
    std::vector<raylib::Vector2> coinSpawnPoints;
    //variables used in the start menu:
    raylib::Rectangle startButton;
    bool started;
    Object* coin;

    //member functions:

private:
    void initGame();
    void run();
    void runStartWindow();
    void runLoserWindow();
public:
    Game();
    Game(const Game& other) = default;

    void main();
};


#endif //OOP_GAME_H
