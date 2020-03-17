/*
 * @Description: client functions head file
 * @version: 1.0.0
 * @Author: ru_j
 * @Date: 2020-01-01 19:45:45
 * @LastEditors  : ru_j
 * @LastEditTime : 2020-01-01 20:18:12
 */
#ifndef __MY_CLT_H
#define __MY_CLT_H

#include "comm.h"

/*-----Client Functions-------------------------*/

/**
 * @name: clt_send_recv
 * @msg: packaged client send and receive function
 * @param: 1. int skt_fd: socket file discription;
 *         2. clt_data *p_clt_data: pointer of client data structure;
 *         3. serv_data *p_srv_data: pointer of server data structure;
 * @return: result of function running
 */
extern int clt_send_recv(int skt_fd, clt_data *p_clt_data, serv_data *p_srv_data);

#endif