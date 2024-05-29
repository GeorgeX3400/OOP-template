//
// Created by ASUS-ROG on 16.04.2024.
//

#include "Statistics.h"

Statistics::Statistics() {
    kills = 0;
    coinsCollected = 0;
    highscore = 0;
}


void Statistics::AddKill() {kills++;}

void Statistics::InitScore() { kills = 0; coinsCollected = 0;}

void Statistics::AddCoin() {coinsCollected++;}

void Statistics::UpdateHighscore() {highscore = std::max(highscore, kills + 10 * coinsCollected);}


void Statistics::draw() {
    raylib::DrawText("Coins: " + std::to_string(coinsCollected), 120, 10, 30, GOLD);
    raylib::DrawText("Kills: " + std::to_string(kills), 10, 10, 30, GREEN);

    raylib::DrawText("Highscore: " + std::to_string(highscore), 10, 55, 20, YELLOW);
}

int Statistics::GetHighscore() {return highscore;}

int Statistics::kills = 0;
int Statistics::coinsCollected = 0;
int Statistics::highscore = 0;