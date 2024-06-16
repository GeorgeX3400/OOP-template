//
// Created by ASUS-ROG on 15.06.2024.
//

#include "WallBuilder.h"

WallBuilder& WallBuilder::width(float w) {
    wall.body.SetWidth(w);
    return *this;
}

WallBuilder& WallBuilder::height(float h) {
    wall.body.SetHeight(h);
    return *this;
}

WallBuilder& WallBuilder::x(float xx) {
    wall.body.SetX(xx);
    return *this;
}
WallBuilder& WallBuilder::y(float yy) {
    wall.body.SetY(yy);
    return *this;
}
Wall WallBuilder::build() {
    return wall;
}

