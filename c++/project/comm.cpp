#include "comm.h"

#include <iostream>
#include <cstdio> 
#include <cstdlib>  
#include <unistd.h>  
#include <termios.h>

using namespace std;

static struct termios s_initial_settings;

void goto_XY(int x, int y) {                    
    printf("\033[%d;%dH", y + 1, x);
}

void hide_cursor() {
    printf("\33[?25l");
}

void show_cursor() {
    printf("\33[?25h");
}

void set_kbhit() {
    FILE *input;  
    FILE *output;  
    struct termios new_settings;  
    if (!isatty(fileno(stdout))) {  
        fprintf(stderr,"You are not a terminal, OK.\n");  
    }  
    input = fopen("/dev/tty", "r");  
    output = fopen("/dev/tty", "w");  
    if(!input || !output) {  
        fprintf(stderr, "Unable to open /dev/tty\n");  
        exit(1);  
    }  
    tcgetattr(fileno(input),&s_initial_settings);  
    new_settings = s_initial_settings;  
    new_settings.c_lflag &= ~ICANON;  
    new_settings.c_lflag &= ~ECHO;  
    new_settings.c_cc[VMIN] = 1;  
    new_settings.c_cc[VTIME] = 0;  
    new_settings.c_lflag &= ~ISIG;  
    if(tcsetattr(fileno(input), TCSANOW, &new_settings) != 0) {  
        fprintf(stderr,"could not set attributes\n");  
    }
}

void reset_kbhit() {
    FILE *input; 
    input = fopen("/dev/tty", "r");   
    tcsetattr(fileno(input),TCSANOW,&s_initial_settings); 
}

void print_cube() {
    printf("\033[47;37m  \033[0m");                         // white cube
}

void erase_cube() {                                         // erase cube
    printf("\033[8m  ");
}