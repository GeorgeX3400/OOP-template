//
// Created by ASUS-ROG on 15.06.2024.
//

#ifndef OOP_WALLBUILDER_H
#define OOP_WALLBUILDER_H
#include "Wall.h"

class WallBuilder {
private:
    Wall wall;
public:
    WallBuilder() = default;
    WallBuilder& width(float w);
    WallBuilder& height(float h);
    WallBuilder& x(float xx);
    WallBuilder& y(float yy);
    Wall build();
};


#endif //OOP_WALLBUILDER_H
