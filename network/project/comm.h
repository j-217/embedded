/*
 * @Description: common head file
 * @version: 1.0.0
 * @Author: ru_j
 * @Date: 2019-12-31 11:12:12
 * @LastEditors  : ru_j
 * @LastEditTime : 2020-01-01 20:56:37
 */
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
#include <strings.h>
#include <stdlib.h>
#include <sqlite3.h>

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 56789
#define EPOLL_EVS_SIZE 100
#define TITLE_SIZE 100
#define CONTENT_SIZE 1000
#define COMM_SIZE 100                           // username, password, error_messages

enum status {
    ERROR_S = -1,
    FALSE_S,
    TRUE_S,

    SH_ALL_FLG = 10,
    SH_MINE_FLG,

    LOGIN_OK = 100,
    NEED_SIGNUP,
    WR_PASSWD,
    SIGNUP_OK,
    SIGNUP_FAILED,

    PUB_OK = 200,
    PUB_FAILED,
    SHOW_OK,
    SHOW_FAILED
};

typedef struct {
    int opt;
    int log_flag;
    char username[COMM_SIZE];
    char password[COMM_SIZE];
    char title[TITLE_SIZE];
    char content[CONTENT_SIZE];
}clt_data;

typedef struct {
    char p_time[20];
    char title[TITLE_SIZE];
    char author[COMM_SIZE];
    char content[CONTENT_SIZE];
}blog;

typedef struct {
    char **tbl_res;
    int i_row;
    int i_col;
    int status;
    char username[COMM_SIZE];
    char err_msgs[COMM_SIZE];
    blog blogs[10];
}serv_data;

/**
 * @name: print_tbl_res
 * @msg: print result of table to the screen
 * @param: serv_data *p_srv_data: pointer of server data stucture
 * @return: result of function running
 */
extern int print_tbl_res(serv_data *p_srv_data);

/**
 * @name: format_time
 * @msg: print result of table to the screen
 * @param: 1. char *tm_str: time_t strings;
 *         2. char n_tm[]: pass out formated time strings;
 *         3. int size: size of array n_tm;
 * @return: result of function running
 */
extern int format_time(char *tm_str, char n_tm[], int size);

#endif