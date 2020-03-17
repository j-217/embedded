#include "bird.h"
#include <iostream>
#include <string>

using namespace std;

Bird::Bird(string species)
    :_species{species}
{
    cout << "[LOG]Bird init" << endl;
}

Bird::~Bird() { cout << "[LOG]Bird destruct" << endl; }

void Bird::take_off(){
    printf("A %s is taking off\n", this->_species.c_str());
}

void Bird::land(){
    printf("A %s land on a tree\n", this->_species.c_str());
}

void Bird::do_sth(){
    this->take_off();
    this->forage();
    this->land();
}

void Bird::forage(){
    printf("A %s forage for food\n", this->_species.c_str());
}

