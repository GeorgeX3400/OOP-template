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
#include "WallBuilder.h"
#include "CoinFactory.h"
class Game {
    //variables used in the gameplay:
    std::vector<Wall> walls;
    Statistics statistics;
    Player player;
    Gun gun;
    Enemy enemy;
    std::vector<raylib::Vector2> spawnPoints;
    std::vector<raylib::Vector2> coinSpawnPoints;
    //variables used in the start menu:
    raylib::Rectangle startButton;
    bool started;
    Coin coin;
    WallBuilder wallBuilder;
    //member functions:

private:
    void initGame();
    void run();
    void runStartWindow();
    void runLoserWindow();
public:
    Game();
    Game(const Game& other) = default;
    Game& operator=(const Game& other) = delete;
    void main();
};


#endif //OOP_GAME_H
