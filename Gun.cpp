//
// Created by ASUS-ROG on 15.04.2024.
//

#include "Gun.h"

std::vector<Bullet> &Gun::GetBullets() {return bullets;}

std::ostream &operator<<(std::ostream &os, const Gun &p) {
    os << "Gun goes brrr (" << p.bullets.size() << " bullets flying)\n";
    return os;
}

void Gun::handleShooting(raylib::Vector2 origin) {
    if (IsMouseButtonPressed(0)){
        bullets.push_back(Bullet(origin, raylib::Vector2(GetMouseX(), GetMouseY())));
    }
}
