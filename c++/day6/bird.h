#pragma once
#include "flyable.h"

class Bird: public Flyable {
public:
    Bird(std::string species = "sparrow");
    virtual ~Bird();
    virtual void do_sth() override;

protected:
    std::string _species;
    void forage();
    virtual void take_off() override;
    virtual void land() override;
};