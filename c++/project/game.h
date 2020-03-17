#pragma once

#include "comm.h"
#include "shape.h"
#include "pattern.h"

class Game {
public:
    Game();
    void run();                                 // run game
    
private:
    void draw_bg();                             // draw background
    void produce_shape();                       // produce random pattern    
    void draw_shape();                          // draw pattern
    void erase_shape();                         // erase pattern
    void draw_panel();                          // draw fixed pattern of panel
    void erase_panel();                         // erase fixed pattern if this line if fulled
    void set_to_panel();                        // set pattern to panel
    void clear_panel();                         // reset panel
    void test_arr();                            // *[Removable]test_function print background array
    void move(MOV_DIR move_dir);                // move pattern
    void rotate();                              // rotate pattern
    bool movable();                             // check if pattern could move
    bool gameover();                            // gameover

    int _bg_arr[GAME_BG::BG_HEIGHT][GAME_BG::BG_WIDTH];             // background array
    Shape *_p_shape;                                                // pointer of base class of patterns            
};