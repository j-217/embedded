#pragma once

#include <iostream>
#include <ctime>
#include <iomanip>

#ifdef __linux__
    #include <unistd.h>
#elif _WIN32
    #include <windows.h>
#endif

using namespace std;

typedef enum clk_flags{
    CF_HOUR,
    CF_MIN,
    CF_SEC
}CLK_FLG;


class Clock {
    protected:
        int _hour,
            _min,
            _sec;
        void set_arg(int data, CLK_FLG type);
        int get_arg(CLK_FLG type);

    public:
        Clock(int hour = 0, int min = 0, int sec = 0);
        ~Clock();
        void show_now();
        
};
