/*
 * @Description: common function
 * @version: 1.0.0
 * @Author: ru_j
 * @Date: 2020-01-01 20:15:55
 * @LastEditors  : ru_j
 * @LastEditTime : 2020-01-02 11:22:41
 */
#include "comm.h"

int print_tbl_res(serv_data *p_srv_data)
{
    if(p_srv_data == NULL){
        printf("[ERROR] Get Table Invalid Parameters\n");
        return ERROR_S;
    }
    if(p_srv_data->i_row == 0){
        printf("[INFO] Nothing to print for\n");
        return FALSE_S;
    }
    
    char n_tm[30];
    
    for(int i = 0; i < p_srv_data->i_row; i++){
        format_time(p_srv_data->blogs[i].p_time, n_tm, 30);

        printf("------------------[%02d]----------------------------\n", i+1);
        printf("TITLE: %s\n", p_srv_data->blogs[i].title);
        printf("AUTHOR: %s\tPUBLISH TIME: %s\n", p_srv_data->blogs[i].author, n_tm);
        printf("CONTENT:\n\t%s\n", p_srv_data->blogs[i].content);
        printf("--------------------------------------------------\n");
    }

    return TRUE_S;
}

int format_time(char *tm_str, char n_tm[], int size)
{
    if(tm_str == NULL || n_tm == NULL){
        printf("[ERROR] Format Time Invalid Parameter\n");
        return ERROR_S;
    }
    bzero(n_tm, size);
    time_t l_tm = atol(tm_str);
    struct tm *p_ntm = localtime(&l_tm);
    sprintf(n_tm, "%4d-%02d-%02d %02d:%02d:%02d",
            p_ntm->tm_year + 1900,
            p_ntm->tm_mon + 1,
            p_ntm->tm_mday,
            p_ntm->tm_hour,
            p_ntm->tm_min,
            p_ntm->tm_sec
    );

    return TRUE_S;
}