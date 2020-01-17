#include "cat.h"
#include <iostream>

using std::cout;
using std::endl;

Cat::Cat(const string name)
    :Pet{name}
{
#if _LOG
    cout << "Cat init" << endl;
#endif
}

Cat::~Cat()
{
#if _LOG
    cout << "Cat destruct" << endl;
#endif
}

void Cat::be_cute()
{
    cout << "My cat " << this->_name << " is acting cute" << endl;
}

void Cat::eating()
{
    cout << this->_name << " is eating jelly" << endl;
}

void Cat::saying()
{
    cout << "Meow-Meow " << this->_name << " said that" << endl;
}