#include "dog.h"
#include <iostream>

using std::cout;
using std::endl;

Dog::Dog(const string name)
    :Pet{name}
{
#if _LOG
    cout << "Dog init" << endl;
#endif
}

Dog::~Dog()
{
#if _LOG
    cout << "Dog destruct" << endl;
#endif
}

void Dog::guard()
{
    cout << "My dog " << this->_name << " is guarding the house" << endl;
}

void Dog::eating()
{
    cout << this->_name << " is eating a bone" << endl;
}

void Dog::saying()
{
    cout << this->_name << " is barking" << endl;
}