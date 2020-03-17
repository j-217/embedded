#include "clk.h"

int main(void)
{
    Clock my_clock;

    while(1){
        my_clock.show_now();
        
#ifdef __linux__
        sleep(1);
        system("clear");
        cout << "OS: Linux" << endl;
#elif _WIN32
        Sleep(1000);
        system("cls");
        cout << "OS: Windows" << endl;
#endif
    }

    return 0;
}
