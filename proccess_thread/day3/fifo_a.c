#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define SIZE 20

int main(int argc, char const *argv[])
{
    if(    (mkfifo("fifo_1", 0666) == -1 && errno != EEXIST)
        || (mkfifo("fifo_2", 0666) == -1 && errno != EEXIST)
    ){
        perror("Make FIFO");
        return -1;
    }
    printf("a opened fifo\n");

    int fdw = open("fifo_1", O_WRONLY);
    if(fdw == -1){
        perror("Open Write File");
        return -1;
    }
    printf("a write\n");

    int fdr = open("fifo_2", O_RDONLY);
    if(fdw == -1){
        perror("Open Read File");
        return -1;
    }
    printf("a running...\n");

    char buf[SIZE] = {'\0'};

    while(1){
        // write to fifo
        memset(buf, '\0', SIZE);
        printf("a >> b: ");
        fgets(buf, SIZE, stdin);
        if(strcmp(buf, "quit\n") == 0){
            printf("Quit\n");
            exit(0);
        }
        write(fdw, buf, SIZE); 

        // read from fifo
        memset(buf, '\0', SIZE);
        read(fdr, buf, SIZE);
        printf("a << b: ");
        fputs(buf, stdout);
    }

    close(fdw);
    close(fdr);

    return 0;
}
