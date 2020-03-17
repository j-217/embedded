#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <ctime>

using namespace std;

inline void get_time()
{
    time_t now = time(NULL);

    tm *new_time = localtime(&now);

    cout << setw(2) << setfill('0') << new_time->tm_hour
         << ":" << setw(2) << setfill('0') << new_time->tm_min
         << ":" << setw(2) << setfill('0') << new_time->tm_sec
         << endl;

    return ;
}

int main(int argc, char const *argv[])
{
    while(1){
        get_time();
        sleep(1);
    }
    
    return 0;
}
