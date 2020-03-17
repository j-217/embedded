#ifndef __MY_FTP_H
#define __MY_FTP_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 100

typedef struct {
    size_t i_len;
    char i_text[BUF_SIZE];
}info;

#endif