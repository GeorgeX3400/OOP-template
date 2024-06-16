//
// Created by ASUS-ROG on 16.06.2024.
//

#include "CoinFactory.h"


Coin CoinFactory::bronzeCoin() {
    return Coin(8, raylib::Color::Brown(), 1);
}

Coin CoinFactory::silverCoin() {
    return Coin(12, raylib::Color::Gray(), 5);
}

Coin CoinFactory::goldenCoin() {
    return Coin(16, raylib::Color::Gold(), 10);
}


