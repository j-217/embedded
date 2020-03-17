#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    if(argc != 2){
        printf("INFO: Need a pid\n");
        return -1;
    }
    int pid = atoi(argv[1]);

    kill(pid, SIGUSR2);

    return 0;
}
