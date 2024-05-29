//
// Created by ASUS-ROG on 16.04.2024.
//

#ifndef OOP_STATISTICS_H
#define OOP_STATISTICS_H
#include <raylib-cpp.hpp>
#include <iostream>

class Statistics {
    static int kills;
    static int highscore;
    static int coinsCollected;

public:
    Statistics();
    static void AddCoin();
    static void AddKill();
    static void InitScore();
    static void UpdateHighscore();
    static void draw();
    static int GetHighscore();
};


#endif //OOP_STATISTICS_H
