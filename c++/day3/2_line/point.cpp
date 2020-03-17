#include "point.h"

Point::Point(int x, int y)
    :_x{x}, _y{y}
{
#if TEST
    // cout << "Point init" << endl;
#endif
}

Point::~Point(){
#if TEST
   // cout << "Point destructed" << endl; 
#endif
}

void Point::set_x(int x = 0){
    this->_x = x;
}

int Point::get_x(){
    return this->_x;
}

void Point::set_y(int y = 0){
    this->_y = y;
}

int Point::get_y(){
    return this->_y;
}