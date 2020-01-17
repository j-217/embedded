#include <iostream>
#include <random>
#include <ctime>

using namespace std;

int main(int argc, char const *argv[])
{
    time_t now = time(nullptr);
    srand(now);
    int a = rand();

    cout << a % 7 << endl;
    return 0;
}
