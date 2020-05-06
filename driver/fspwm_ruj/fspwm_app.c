#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "fspwm.h"

typedef struct {
	int freq;
	int delay;
}node;

#define DO 262
#define RE 295
#define MI 330
#define FA 349
#define SO 392
#define LA 440
#define SI 494

#define BEAT (60000000/120)

const node song[] = {
	{DO, BEAT/2},
	{RE, BEAT/2},
	{MI, BEAT/2},
	{FA, BEAT/2},
	{SO, BEAT/2},
	{LA, BEAT/2},
	{SI, BEAT/2},
};

int main()
{
	int fd;

	fd=open("/dev/fspwm",O_RDWR);
	if(fd<0) {
		perror("open");
		exit(1);
	}
	ioctl(fd,FSPWM_START);

	for (i = 0; i < sizeof(song)/sizeof(song[0]); ++i) {
		ioctl(fd, FSPWM_SET_FREQ, song[i].freq);
		usleep(song[i].delay);
	}

	ioctl(fd,FSPWM_STOP);
	close(fd);

	exit(0);
}