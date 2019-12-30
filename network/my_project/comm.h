#ifndef __COMM_H
#define __COMM_H

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 56789
#define EPOLL_EVS_SIZE 100
#define BUF_SIZE 100 

enum status {
    ERROR_S = -1,
    FALSE_S,
    TRUE_S
};

#endif