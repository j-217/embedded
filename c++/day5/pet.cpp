#include "pet.h"
#include <iostream>

using std::cout;
using std::endl;

Pet::Pet(const string name)
    :_name{name}
{
#if _LOG
    cout << "Pet init" << endl;
#endif
}

Pet::~Pet()
{
#if _LOG
    cout << "Pet destruct" << endl;
#endif
}

void Pet::eating()
{
    cout << this->_name << " is eating" << endl;
}

void Pet::saying()
{
    cout << this->_name << " is saying" << endl;
}