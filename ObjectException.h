//
// Created by ASUS-ROG on 27.05.2024.
//

#ifndef OOP_OBJECTEXCEPTION_H
#define OOP_OBJECTEXCEPTION_H
#include <stdexcept>
#include <iostream>


class ObjectException : public std::runtime_error {
protected:
    explicit ObjectException(const std::string& msg);
    ObjectException(const ObjectException& other);
    ObjectException& operator=(const ObjectException& other);

};


#endif //OOP_OBJECTEXCEPTION_H
