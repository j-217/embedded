#pragma once

#include "point.h"

class Line {
    private:
        Point *_pt_a,
              *_pt_b;

    public:
        Line(int pt_a_x = 0, int pt_a_y = 0, int pt_b_x = 0, int pt_b_y = 0);
        ~Line();
        Line & operator=(const Line & src);
        void set_a(int x, int y);
        void set_b(int x, int y);
        void desc_line();
};