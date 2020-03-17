#include <iostream>
#include "bird.h"
#include "plane.h"

using namespace std;

int main()
{
    Bird my_bird;
    Plane my_plane;

    Flyable * p = &my_bird;
    p->do_sth();

    cout << "--------------------" << endl;

    p = &my_plane;
    p->do_sth();

    return 0;
}
