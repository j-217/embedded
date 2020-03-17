#include "shape.h"

Shape::Shape(int org_x, int org_y) {                                // set origin position
    this->_arr[0].set_x(org_x);
    this->_arr[0].set_y(org_y);
    this->_rotate_stat = 0;
    this->_rotate_stat_backup = 0;
}

void Shape::set_origin(int new_x, int new_y) {
    this->_arr[0].set_x(new_x);
    this->_arr[0].set_y(new_y);
}

void Shape::get_arr(Coordinate (&arr)[4]) {
    for (int i = 0; i < 4; i++) {
        arr[i].set_x(this->_arr[i].get_x());
        arr[i].set_y(this->_arr[i].get_y());
    }
}

void Shape::set_rotate_stat() {
    this->_rotate_stat_backup = this->_rotate_stat;
    this->_rotate_stat++;
}

void Shape::reset_rotate_stat () {
    this->_rotate_stat = this->_rotate_stat_backup;
}