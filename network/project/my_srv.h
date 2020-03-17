/*
 * @Description: server functions head file
 * @version: 1.0.0
 * @Author: ru_j
 * @Date: 2020-01-01 20:01:20
 * @LastEditors  : ru_j
 * @LastEditTime : 2020-01-01 20:17:29
 */
#ifndef __MY_SRV_H
#define __MY_SRV_H

#include "comm.h"
#include "db_op.h"

/*-----Server Functions-------------------------*/

/**
 * @name: handle_login
 * @msg: handle login request
 * @param: 1. sqlite3 *p_db: pointer of database structure;
 *         2. clt_data *n_clt_data: pointer of client data structure;
 *         3. serv_data **pp_n_srv_data: address of pointer of server data structure;
 * @return: result of function running
 */
extern int handle_login(sqlite3 *p_db, clt_data *n_clt_data, serv_data **pp_n_srv_data);

/**
 * @name: handle_signup
 * @msg: handle signup new user request
 * @param: 1. sqlite3 *p_db: pointer of database structure;
 *         2. clt_data *n_clt_data: pointer of client data structure;
 *         3. serv_data **pp_n_srv_data: address of pointer of server data structure;
 * @return: result of function running
 */
extern int handle_signup(sqlite3 *p_db, clt_data *n_clt_data, serv_data **pp_n_srv_data);

/**
 * @name: handle_publish
 * @msg: handle publish new blog request
 * @param: 1. sqlite3 *p_db: pointer of database structure;
 *         2. clt_data *n_clt_data: pointer of client data structure;
 *         3. serv_data **pp_n_srv_data: address of pointer of server data structure;
 * @return: result of function running
 */
extern int handle_publish(sqlite3 *p_db, clt_data *n_clt_data, serv_data **pp_n_srv_data);

/**
 * @name: handle_show
 * @msg: handle display the blogs request (default list 10)
 * @param: 1. sqlite3 *p_db: pointer of database structure;
 *         2. clt_data *n_clt_data: pointer of client data structure;
 *         3. serv_data **pp_n_srv_data: address of pointer of server data structure;
 *         4. int range_flag: choose show range;
 * @return: result of function running
 */
extern int handle_show(sqlite3 *p_db, clt_data *n_clt_data, serv_data **pp_n_srv_data, int range_flag);

#endif