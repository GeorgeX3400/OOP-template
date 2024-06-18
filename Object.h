//
// Created by ASUS-ROG on 18.04.2024.
//

#ifndef OOP_OBJECT_H
#define OOP_OBJECT_H
#include <raylib-cpp.hpp>
#include <iostream>
class Object {
    protected:
        raylib::Rectangle body;

    public:
        raylib::Rectangle virtual GetBody() const;
        raylib::Vector2 virtual GetPosition();
        virtual void SetPosition(raylib::Vector2 pos);
        virtual void Draw() = 0;

        Object();
        Object(raylib::Rectangle r);
        Object(const Object& other);
        Object& operator=(const Object& other) = default;
        friend std::ostream& operator<<(std::ostream &os, const Object &o);
        virtual void afisare(std::ostream &os) const;
        friend void swap(Object& o1, Object& o2);
        virtual ~Object();
};


#endif //OOP_OBJECT_H
