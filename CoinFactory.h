//
// Created by ASUS-ROG on 16.06.2024.
//

#ifndef OOP_COINFACTORY_H
#define OOP_COINFACTORY_H
#include "Coin.h"

class CoinFactory {

public:
    static Coin bronzeCoin();
    static Coin silverCoin();
    static Coin goldenCoin();
};


#endif //OOP_COINFACTORY_H
