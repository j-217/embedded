#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>

int get_key(void)
{
    int fd = 0;
    struct input_event event;

    fd = open("/dev/input/event0", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    while (1) {
        if (read(fd, &event, sizeof(event)) == sizeof(event)) {
            if (event.type == EV_KEY && event.value == 1) {
                close(fd);
                return event.code;
            } else {
                continue;
            }
        } else {
            close(fd);
            fprintf(stderr, "fskey->read: read failed\n");
            return -1;
        }
    }
}

int main() {
    while (1) {
        printf("key value: %d\n", get_key());
    }

    return 0;
}