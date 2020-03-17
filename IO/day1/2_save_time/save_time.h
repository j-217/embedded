#ifndef __SAVE_TIME_H__
#define __SAVE_TIME_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define BUFF_SIZE 50

enum status {
    ERROR_S = -1,
    FALSE_S,
    TRUE_S
};

/**
 * @name: count_lines
 * @msg: 计算文件的行数
 * @param: FILE *fr 文件指针 
 * @return: int 计算结果
 */
int count_lines(FILE *fr);

/**
 * @name: save_time
 * @msg: 每隔一秒记录一次当前日期保存到指定文件,格式为 lineNumber. yy-MM-dd HH:MM:SS
 * @param: const char *pathname
 * @return: 函数调用结果 status
 */
int save_time(const char *pathname);

#endif
