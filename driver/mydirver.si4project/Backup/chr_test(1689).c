#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	int fd;
	int value = 0;
	
	fd = open("/dev/chr2", O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	read(fd, &value, 4);
	write(fd, &value, 4);
	
	return 0;
}
