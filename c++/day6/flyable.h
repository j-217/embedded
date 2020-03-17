#pragma once
#include <iostream>

class Flyable {
public:
    virtual ~Flyable() { std::cout << "[LOG]Flyable destruct" << std::endl; };
    virtual void do_sth() = 0;
protected:
    virtual void take_off() = 0;
    virtual void land() = 0; 
};