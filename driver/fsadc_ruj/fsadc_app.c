#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "fsadc.h"

int main() {
    int fd;
    union chan_val cv;

    fd = open("/dev/fsadc", O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    while (1) {
        cv.chan = 3;
        ioctl(fd, FSADC_GET_VAL, &cv);
        printf("current voltage is: %.2f\n", cv.val * 1.8 / 4096.0);
        sleep(1);
    }

    return 0;
}