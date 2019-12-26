#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    // fork
    pid_t pid = -1;
    pid = fork();

    if(pid < 0){
        printf("Fork Error\n");
        exit(1);
    }

    if(pid > 0){
        printf("Parent Exit\n");
        exit(0);
    }

    if(pid == 0){
        sleep(1);
        printf("ppid: %d\n", getppid());
        // setsid
        setsid();

        // chdir
        chdir("/tmp");

        // umask
        umask(0);

        // closefd
        for(int i = 0; i<getdtablesize(); i++){
            close(i);
        }

        // do somethig
        sleep(30);
    }


    return 0;
}
