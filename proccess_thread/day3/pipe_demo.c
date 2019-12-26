#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 10

int main(int argc, char const *argv[])
{
    int fd[2] = {0};

    if(pipe(fd) == -1){
        return -1;
    }

    pid_t pid = -1;

    pid = fork();

    if(pid == -1){
        return -1;
    }
    
    char buf[SIZE] = {'\0'};
    if(pid == 0){
        printf("writing...\n");
        strcpy(buf, "testing");
        write(fd[1], buf, SIZE);
        close(fd[1]);
        exit(1);

    }else{
        printf("reading...\n");
        sleep(1);
        read(fd[0], buf, SIZE);
        printf("read: %s\n", buf);
        close(fd[0]);
        wait(NULL);
        exit(0);
    }

    return 0;
}
