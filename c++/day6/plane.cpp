#include "plane.h"
#include <iostream>
#include <string>

using namespace std;

Plane::Plane(string model)
    :_model{model}
{
    cout << "[LOG]Plane init" << endl;
}

Plane::~Plane() { cout << "[LOG]Plane destruct" << endl; }

void Plane::take_off(){
    printf("A %s is taking off\n", this->_model.c_str());
}

void Plane::land(){
    printf("A %s land on the airport\n", this->_model.c_str());
}

void Plane::do_sth(){
    this->take_off();
    this->carry();
    this->land();
}

void Plane::carry(){
    printf("A %s transported resources from xi'an to beijing\n", this->_model.c_str());
}