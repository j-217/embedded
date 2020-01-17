#pragma once

class Pet {
protected:
    std::string _name;
public:
    Pet(const std::string name = "my_pet");
    virtual ~Pet();
    virtual void eating();
    virtual void saying();
};