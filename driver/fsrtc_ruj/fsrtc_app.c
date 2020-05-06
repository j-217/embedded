#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "fsrtc.h"

int main() {
    int fd;
    struct rtc_time tm;

    fd = open("/dev/rtc", O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    tm.tm_sec = 0x56;
    tm.tm_min = 0x59;
    tm.tm_hour = 0x17;
    tm.tm_day = 0x5;
    tm.tm_mon = 0x5;
    tm.tm_year = 0x020;

    ioctl(fd, FSRTC_SET, &tm);

    while (1) {
        memset(&tm, 0, sizeof(tm));
        ioctl(fd, FSRTC_GET, &tm);
        printf("20%x-%x-%x ", tm.tm_year, tm.tm_mon, tm.tm_day);
        printf("%02x:%02x:%02x\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
        sleep(1);
    }

    close(fd);

    return 0;
}