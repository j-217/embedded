#include "game.h"
#include <iostream>
#include <cstring>
#include <random>
#include <ctime>

using namespace std;

void Game::test_arr() {
    goto_XY(50, 5);
    for (int row = 0; row < GAME_BG::BG_HEIGHT; row++) {
        for (int col = 0; col < GAME_BG::BG_WIDTH; col++) {
            printf("%d  ", this->_bg_arr[row][col]);
        }
        printf("\n");
    }
}

Game::Game() {
    memset(this->_bg_arr, 0, sizeof(this->_bg_arr));
    this->produce_shape();
}

void Game::draw_bg() {
    for (int row = 0; row < GAME_BG::BG_HEIGHT; row++) {
        for (int col = 0; col < GAME_BG::BG_WIDTH; col++) {
            if (row == 0 || row == GAME_BG::BG_HEIGHT - 1) {
                this->_bg_arr[row][col] = 2;
            }
            if (col == 0 || col == GAME_BG::BG_WIDTH - 1) {
                this->_bg_arr[row][col] = 2;
            }
        }
    }

    for (int row = 0; row < GAME_BG::BG_HEIGHT; row++) {
        for (int col = 0; col < GAME_BG::BG_WIDTH; col++) {
            if (this->_bg_arr[row][col] == 2) {
                goto_XY(col + GAME_BG::BG_ORIGIN_X, row + GAME_BG::BG_ORIGIN_Y);
                printf("*");
            }
        }
    }
    goto_XY(50, 1);
    cout << "---TETRIS---";
    goto_XY(50, 3);
    cout << "AUTHOR: " << "RU_J";

    goto_XY(50, 5);
    cout << "W: " << "ROTATE";
    goto_XY(50, 6);
    cout << "A: " << "TO_LEFT";
    goto_XY(50, 7);
    cout << "D: " << "TO_RIGHT";
    goto_XY(50, 8);
    cout << "S: " << "TO_BOTTOM";
    goto_XY(50, 9);
    cout << "Q: " << "QUIT";
}

void Game::draw_panel() {
    for (int row = 1; row < GAME_BG::BG_HEIGHT - 1; row++) {
        for (int col = 1; col < GAME_BG::BG_WIDTH - 1; col += 2) {
            if (this->_bg_arr[row][col] == 1) {
               goto_XY(col + GAME_BG::BG_ORIGIN_X, row + GAME_BG::BG_ORIGIN_Y);
               print_cube(); 
            }
        }
    }
}

void Game::draw_shape() {
    Coordinate arr[4];
    Coordinate (&r_arr)[4] = arr;

    this->_p_shape->get_arr(r_arr);

    for (int i = 0; i < 4; i++) {
        goto_XY(arr[i].get_x(), arr[i].get_y());
        print_cube();
    }
}

void Game::erase_shape() {
    Coordinate arr[4];
    Coordinate (&r_arr)[4] = arr;

    this->_p_shape->get_arr(r_arr);
    for (int i = 0; i < 4; i++) {
        this->_bg_arr[arr[i].get_y() - GAME_BG::BG_ORIGIN_Y][arr[i].get_x() - GAME_BG::BG_ORIGIN_X] = 0;
        goto_XY(arr[i].get_x(), arr[i].get_y());
        erase_cube();
    }
}

void Game::set_to_panel() {
    Coordinate arr[4];
    Coordinate (&r_arr)[4] = arr;

    _p_shape->get_arr(r_arr);
    for (int i = 0; i < 4; i++) {
        this->_bg_arr[arr[i].get_y() - GAME_BG::BG_ORIGIN_Y][arr[i].get_x() - GAME_BG::BG_ORIGIN_X] = 1;
        this->_bg_arr[arr[i].get_y() - GAME_BG::BG_ORIGIN_Y][arr[i].get_x() - GAME_BG::BG_ORIGIN_X + 1] = 1;
    }
}

void Game::clear_panel() {
    for (int row = 1; row < GAME_BG::BG_HEIGHT - 1; row++) {
        for (int col = 1; col < GAME_BG::BG_WIDTH - 1; col += 2) {
            this->_bg_arr[row][col] = 0;
            goto_XY(col + GAME_BG::BG_ORIGIN_X, row + GAME_BG::BG_ORIGIN_Y);
            erase_cube();
        }
    }
}

void Game::produce_shape() {
    time_t now = time(nullptr);                     // get random number mod 7
    srand(now);
    stat_t my_type = rand() % 7;

    this->_p_shape = nullptr;
    switch (my_type) {
        case PAT_TYP::PT_I:
            this->_p_shape = new I_PATTERN;
            break;
        case PAT_TYP::PT_O:
            this->_p_shape = new O_PATTERN;
            break;
        case PAT_TYP::PT_Z:
            this->_p_shape = new Z_PATTERN;
            break;
        case PAT_TYP::PT_ZZ:
            this->_p_shape = new ZZ_PATTERN;
            break;
        case PAT_TYP::PT_T:
            this->_p_shape = new T_PATTERN;
            break; 
        case PAT_TYP::PT_L:
            this->_p_shape = new L_PATTERN;
            break; 
        case PAT_TYP::PT_LL:
            this->_p_shape = new LL_PATTERN;
            break;
        default:
            break;
    }

    this->_p_shape->set_shape();

    if (this->gameover()) {
        this->_p_shape = nullptr;
        show_cursor();
        reset_kbhit();
        system("clear");

        exit(1);
    }

    return ;
}

void Game::move(MOV_DIR mov_dir) {
    if (!this->movable()) {
        return ;
    }

    this->erase_shape();

    Coordinate arr[4];
    Coordinate (&r_arr)[4] = arr;
    this->_p_shape->get_arr(r_arr);

    switch (mov_dir) {
        case MOV_DIR::TO_LT:
            for (int i = 0; i < 4; i++) {
                if (this->_bg_arr[arr[i].get_y() - GAME_BG::BG_ORIGIN_Y][arr[i].get_x() - 2 - GAME_BG::BG_ORIGIN_X] != 0 
                    || (arr[i].get_x() - 2) <= GAME_BG::BG_ORIGIN_X
                ) {
                    this->draw_shape();
                    return ;
                }
            }
            this->_p_shape->set_origin(arr[0].get_x() - 2, arr[0].get_y());
            this->_p_shape->set_shape();
            break;
        case MOV_DIR::TO_RT:
            for (int i = 0; i < 4; i++) {
                if (this->_bg_arr[arr[i].get_y() - GAME_BG::BG_ORIGIN_Y][arr[i].get_x() + 2 - GAME_BG::BG_ORIGIN_X] != 0
                    || (arr[i].get_x() + 2) >= (GAME_BG::BG_ORIGIN_X + GAME_BG::BG_WIDTH - 1)
                ) {
                    this->draw_shape();
                    return ;
                }
            }
            this->_p_shape->set_origin(arr[0].get_x() + 2, arr[0].get_y());
            this->_p_shape->set_shape();
            break;
        case MOV_DIR::TO_BTM:
            for (int i = 0; i < 4; i++) {
                if (this->_bg_arr[arr[i].get_y() + 1 - GAME_BG::BG_ORIGIN_Y][arr[i].get_x() - GAME_BG::BG_ORIGIN_X] != 0
                    || (arr[i].get_y() + 1) >= (GAME_BG::BG_HEIGHT + GAME_BG::BG_ORIGIN_Y - 1)
                ) {
                    this->draw_shape();
                    return ;
                }
            }
            this->_p_shape->set_origin(arr[0].get_x(), arr[0].get_y() + 1);
            this->_p_shape->set_shape();
            break;
        default:
            break;
    }

    this->draw_shape();
}

void Game::rotate() {
    if (!this->movable()) {
        return ;
    }
    this->erase_shape();

    this->_p_shape->set_rotate_stat();
    this->_p_shape->set_shape();

    Coordinate arr[4];
    Coordinate (&r_arr)[4] = arr;
    this->_p_shape->get_arr(r_arr);

    for (int i = 0; i < 4; i++) {
        if (this->_bg_arr[arr[i].get_y() - GAME_BG::BG_ORIGIN_Y][arr[i].get_x() - GAME_BG::BG_ORIGIN_X] != 0
            || arr[i].get_x() <= GAME_BG::BG_ORIGIN_X
            || arr[i].get_x() >= (GAME_BG::BG_ORIGIN_X + GAME_BG::BG_WIDTH - 1)
            || arr[i].get_y() >= (GAME_BG::BG_ORIGIN_Y + GAME_BG::BG_HEIGHT - 1)
        ) {
            this->_p_shape->reset_rotate_stat();
            this->_p_shape->set_shape();
            this->draw_shape();
            return ;
        }
    }
    this->draw_shape();
}

void Game::erase_panel() {
AGAIN:
    for (int row = GAME_BG::BG_HEIGHT - 2; row > 1; row-- ) {
        int col = 1;
        for (; col < GAME_BG::BG_WIDTH - 1; col += 2 ) {
            if (this->_bg_arr[row][col] == 0) {
                break;
            } 
        }

        if (col == GAME_BG::BG_WIDTH - 1) {
            int new_row = row;
            for (; new_row > 1; new_row--) {
                for(int new_col = 1; new_col < GAME_BG::BG_WIDTH - 1; new_col += 2) {
                    goto_XY(new_col + GAME_BG::BG_ORIGIN_X, new_row + GAME_BG::BG_ORIGIN_Y);
                    erase_cube();
                    this->_bg_arr[new_row][new_col] = this->_bg_arr[new_row - 1][new_col];
                }
            }
            goto AGAIN;
        }
    }
}

bool Game::movable() {
    Coordinate arr[4];
    Coordinate (&r_arr)[4] = arr;
    this->_p_shape->get_arr(r_arr);

    for (int i = 0; i < 4; i++) {
        if (this->_bg_arr[arr[i].get_y() + 1 - GAME_BG::BG_ORIGIN_Y][arr[i].get_x() - GAME_BG::BG_ORIGIN_X] != 0
            || (arr[i].get_y() + 1) >= (GAME_BG::BG_HEIGHT + GAME_BG::BG_ORIGIN_Y - 1)
        ) {
            this->set_to_panel();
            this->draw_panel();

            delete this->_p_shape;
            this->erase_panel();
            this->draw_panel();

            this->produce_shape(); 
            return false;
        }
    }

    return true;
}

void Game::run() {
    system("clear");

    hide_cursor();
    
    this->draw_bg();
    this->draw_shape();

/*----------keyboard set-------------*/

    set_kbhit();
    char c = 0;
    while((c = getchar()) != 113) {

        if (c == 'w') {
            this->rotate();
        }
        if (c == 'a') {
            this->move(MOV_DIR::TO_LT);
        }
        if (c == 'd') {
            this->move(MOV_DIR::TO_RT);
        }
        if (c == 's') {
            this->move(MOV_DIR::TO_BTM);
        }
    }
    
    show_cursor();
    reset_kbhit();
    system("clear");
/*----------keyboard reset----------*/
}

bool Game::gameover() {
    Coordinate arr[4];
    Coordinate (&r_arr)[4] = arr;
    this->_p_shape->get_arr(r_arr);

    for (int i = 0; i < 4; i++) {
        if (this->_bg_arr[arr[i].get_y() - GAME_BG::BG_ORIGIN_Y][arr[i].get_x() - GAME_BG::BG_ORIGIN_X] != 0) {
            this->clear_panel();
            goto_XY(GAME_BG::BG_ORIGIN_X + 8, GAME_BG::BG_ORIGIN_Y + 5);
            printf("GAME OVER");
            getchar();
            return true;
        }
    }

    return false;
}