#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    printf("\033[%d;%dH", 5 + 2, 5);

    getchar();

    return 0;
}
