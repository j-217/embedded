#pragma once

class Coordinate {
public:
    Coordinate(int x = 0, int y = 0);
    int get_x();
    int get_y();
    void set_x(int x);
    void set_y(int y);
private:
    int _x,
        _y;
};