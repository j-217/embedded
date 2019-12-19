#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SIZE 100

int main(int argc, char const *argv[])
{
    if(argc != 3){
        printf("Usage: %s <Src Filename> <Dest Filename>\n", argv[0]);
        return -1;
    }

    int fs = -1,
        fd = -1;
    fs = open(argv[1], O_RDONLY|O_EXCL, 0666);
    fd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0666);

    if(fs == -1 || fd == -1){
        perror("OPEN FILE");
        return -1;
    }
    char buf[SIZE] = {'\0'};
    int read_num = -1;

    while(1){
        memset(buf, '\0', SIZE);
        read_num = read(fs, buf, SIZE);
        if(read_num == 0){
            break;
        }
        write(fd, buf, read_num);
    }

    close(fs);
    close(fd);

    return 0;
}
