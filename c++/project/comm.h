#pragma once

using stat_t = unsigned int;

enum GAME_BG {                              // backgroun origin and size
    BG_ORIGIN_X = 10,
    BG_ORIGIN_Y = 1,

    BG_WIDTH = 26,                          // 2*12 + 2
    BG_HEIGHT = 22                          // 20 + 2
};

enum PAT_TYP {                              // pattern types
    PT_I = 0,
    PT_O,
    PT_T,
    PT_L,
    PT_LL,
    PT_Z,
    PT_ZZ
};

enum MOV_DIR {                              // move direction
    TO_LT = 1,
    TO_RT = 2,
    TO_BTM = 4
};

void goto_XY(int x, int y);                 // locate cursor to X.Y

void hide_cursor();                         // hide cursor in linux

void show_cursor();                         // show cursor in linux

void set_kbhit();                           // set catch keyboard input without enter key

void reset_kbhit();                         // close kbhit

void print_cube();                          // print white cube

void erase_cube();                          // erase cube

