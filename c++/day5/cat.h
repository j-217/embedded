#pragma once
#include "pet.h"

class Cat: public Pet {
public:
    Cat(const string name = "Tom");
    virtual ~Cat();
    void eating();
    void saying();
    void be_cute();
};