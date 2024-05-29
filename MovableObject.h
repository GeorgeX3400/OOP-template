//
// Created by ASUS-ROG on 18.04.2024.
//

#ifndef OOP_MOVABLEOBJECT_H
#define OOP_MOVABLEOBJECT_H
#include <raylib-cpp.hpp>
#include <iostream>
#include "Object.h"

class MovableObject : public Object {
protected:
    raylib::Rectangle up;
    raylib::Rectangle down;
    raylib::Rectangle left;
    raylib::Rectangle right; // "sensors" - help check collisions with walls
    std::vector<bool> hasCollided;
    virtual void handleMovement() = 0;
public:
    MovableObject() = default;
    explicit MovableObject(raylib::Rectangle r);
    MovableObject(const MovableObject& other);
    MovableObject& operator=(const MovableObject& other);
    ~MovableObject() override;
    void afisare(std::ostream &os) const override;;
};


#endif //OOP_MOVABLEOBJECT_H
