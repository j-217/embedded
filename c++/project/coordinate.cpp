#include "coordinate.h"

Coordinate::Coordinate(int x, int y)
    :_x{x}, _y{y}
{}

int Coordinate::get_x() {
    return this->_x;
} 

int Coordinate::get_y() {
    return this->_y;
}

void Coordinate::set_x(int x) {
    this->_x = x;
}

void Coordinate::set_y(int y) {
    this->_y = y;
}