#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    printf("\033[47;37m  \033[0m\n");

    printf("\033[%d;%dH", 2, 1);

    printf("\033[8m");
    return 0;
}
