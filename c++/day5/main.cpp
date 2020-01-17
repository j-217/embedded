#include <iostream>
#include "dog.h"
#include "cat.h"

using namespace std;

int main()
{
    Dog my_dog("WangCai");          // create dog instance
    my_dog.guard();

    Pet* my_pet = &my_dog;          // use a pointer of base class
    my_pet->eating();
    my_pet->saying();

    cout << "--------------" << endl;

    Cat my_cat;                     // create cat instance
    my_cat.be_cute();

    my_pet = &my_cat;
    my_pet->eating();
    my_pet->saying();

    return 0;
}
