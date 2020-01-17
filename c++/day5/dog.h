#pragma once
#include "pet.h"

class Dog: public Pet {
public:
    Dog(const string name = "PiPi");
    virtual ~Dog();
    void eating();
    void saying();
    void guard();
};