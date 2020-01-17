#pragma once
#include "comm.h"
#include "coordinate.h"

class Shape {
public:
    Shape(int org_x = GAME_BG::BG_ORIGIN_X + 11, int org_y = GAME_BG::BG_ORIGIN_Y + 2);
    virtual ~Shape() = default;
    virtual void get_arr(Coordinate (&arr)[4]);                             // get shape array
    virtual void set_rotate_stat();                                         // set rotate stat
    virtual void reset_rotate_stat();                                       // if rotate failed, recover _rotate_stat

    virtual void set_origin(int new_x, int new_y);                          // set shape original point
    virtual void set_shape() = 0;                                           // set shape pattern
protected:
    Coordinate _arr[4];                                                     // pattern include four points
    stat_t _rotate_stat;                                                    // pattern rotate status
    stat_t _rotate_stat_backup;                                             // backup pattern rotat status for rotate failed
};