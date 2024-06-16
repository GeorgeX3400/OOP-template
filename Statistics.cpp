//
// Created by ASUS-ROG on 16.04.2024.
//

#include "Statistics.h"

Statistics::Statistics() {
    kills = 0;
    coinsCollected = 0;
    highscore = 0;
    score = 0;
}


void Statistics::AddKill() {kills++; score++;}

void Statistics::InitScore() { kills = 0; coinsCollected = 0; score = 0;}

void Statistics::AddCoin() {coinsCollected++;}

void Statistics::UpdateHighscore() {highscore = std::max(highscore, score);}

void Statistics::AddScore(int a) {score += a;}

void Statistics::draw() {
    raylib::DrawText("Coins: " + std::to_string(coinsCollected), 120, 10, 30, GOLD);
    raylib::DrawText("Kills: " + std::to_string(kills), 10, 10, 30, GREEN);
    raylib::DrawText("Score: " + std::to_string(score), 250, 10, 30, BLUE);
    raylib::DrawText("Highscore: " + std::to_string(highscore), 10, 55, 20, YELLOW);
}

int Statistics::GetHighscore() {return highscore;}

int Statistics::kills = 0;
int Statistics::coinsCollected = 0;
int Statistics::highscore = 0;
int Statistics::score = 0;


