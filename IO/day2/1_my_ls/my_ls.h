#ifndef __MY_LS_H
#define __MY_LS_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define SIZE 1000

/**
 * @name: handle_file_mode
 * @msg: 处理文件类型和权限
 * @param: 1. mode_t f_mode struc stat->st_mode 结构体, 
 *         2. char (*res)[] 传出参数: 处理后的文件类型和权限字符串 下标说明: 0: 文件类型, 1-9: 文件权限, 10: 字符串结束标识符
 * @return: 函数调用结果 -1 错误 0 成功
 */
int handle_file_mode(mode_t f_mode, char (*res)[]);

/**
 * @name: print_line
 * @msg: 打印一行文件信息,包含文件类型/权限, 连接数量, 文件大小, 最后修改日期, 文件名称
 * @param: 1. struct dirent *dd 文件信息指针, 2. const char *root_path 查看的文件的根路径
 * @return: 函数调用结果 -1 错误 0 成功
 */
int print_line(struct dirent *dd, const char *root_path);

/**
 * @name: print_lines
 * @msg: 打印多行文件信息
 * @param: 1. DIR *dirp 文件目录信息指针, 2. const char *root_path 查看的文件的根路径
 * @return: 函数调用结果 -1 错误 0 成功
 */
int print_lines(DIR *dirp, const char *root_path);


#endif