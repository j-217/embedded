/*
 * @Description: operations of database, only use in server.c
 * @version: 1.0.0
 * @Author: ru_j
 * @Date: 2019-12-31 14:08:39
 * @LastEditors  : ru_j
 * @LastEditTime : 2020-01-01 20:14:09
 */
#ifndef __DB_OP_H
#define __DB_OP_H

#include "comm.h"

#define DB_NAME "my_db.db"

/**
 * @name: init_db
 * @msg: initialize database, tables and create administritor
 * @param: sqlite3 **p_db: address of the pointer of database
 * @return: result of function running
 */
extern int init_db(sqlite3 **p_db);

/**
 * @name: close_db
 * @msg: close database
 * @param: sqlite3 *p_db: pointer of database
 * @return: result of function running
 */
extern int close_db(sqlite3 *p_db);

/**
 * @name: exec_db
 * @msg: execute sql in database
 * @param: 1. sqlite3 *p_db: pointer of database;
 *         2. char *sql: Structured Query Language;
 *         3. char *err_msgs: error messages
 * @return: result of function running
 */
extern int exec_db(sqlite3 *p_db, char *sql, char *err_msgs);

/**
 * @name: get_table
 * @msg: select from tables
 * @param: 1. sqlite3 *p_db: pointer of database;
 *         2. char *sql: Structured Query Language;
 *         3. char ***p_tbl_res: result of searching tables;
 *         4. int *i_row: row number of results;
 *         5. int *i_col: column number of results;
 *         3. char *err_msgs: error messages
 * @return: result of function running
 */
extern int get_table(sqlite3 *p_db, char *sql, char ***p_tbl_res, int *i_row, int *i_col, char *err_msgs);

#endif