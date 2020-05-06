#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "fsled.h"

int main() {
    int fd[4];
    int i;
    char filename[100];

    for (i = 0; i < 4; ++i) {
        sprintf(filename, "/dev/led%d", i+2);
        fd[i] = open(filename, O_RDWR);
        if (fd[i] < 0) {
            perror("open");
            exit(-1);
        }
    }

    i = 0;

    while (1) {
        ioctl(fd[i], FSLED_ON);
        usleep(500000);
        ioctl(fd[i], FSLED_OFF);
        usleep(500000);

        if (++i > 3)
            i = 0;
    }

    return 0;
}