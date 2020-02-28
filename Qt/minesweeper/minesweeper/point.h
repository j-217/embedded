#ifndef POINT_H
#define POINT_H


class Point
{
public:
    Point(int x, int y);
    ~Point();
    int get_x() {return _x;}
    int get_y() {return _y;}
private:
    int _x;
    int _y;
};

#endif // POINT_H
