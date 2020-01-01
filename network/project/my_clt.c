/*
 * @Description: function use in client.c 
 * @version: 1.0.0
 * @Author: ru_j
 * @Date: 2020-01-01 19:46:54
 * @LastEditors  : ru_j
 * @LastEditTime : 2020-01-01 20:31:48
 */
#include "my_clt.h"

int clt_send_recv(int skt_fd, clt_data *p_clt_data, serv_data *p_srv_data)
{
    // send
    int res = send(skt_fd, p_clt_data, sizeof(clt_data), 0);
    if(res == -1){
        perror("[ERROR] Client Send");
        exit(ERROR_S);
    }

    // recv
    bzero(p_srv_data, sizeof(serv_data));
    res = recv(skt_fd, p_srv_data, sizeof(serv_data), 0);
    if(res == -1){
        perror("[ERROR] Client Recv");
        exit(ERROR_S);
    }
    printf("%s\n", p_srv_data->err_msgs);

    return TRUE_S;
}