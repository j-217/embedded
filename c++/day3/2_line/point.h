#pragma once

#include <iostream>
using namespace std;

class Point {
    private:
        int _x,
            _y;
    
    public:
        Point(int x = 0, int y = 0);
        ~Point();
        void set_x(int x);
        int get_x();
        void set_y(int y);
        int get_y();
};