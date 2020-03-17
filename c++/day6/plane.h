#pragma once
#include "flyable.h"

class Plane: public Flyable {
public:
    Plane(std::string model = "Xian Y-20");
    ~Plane();
    virtual void do_sth() override;
protected:
    std::string _model;
    void carry();
    virtual void take_off() override;
    virtual void land() override;
};
