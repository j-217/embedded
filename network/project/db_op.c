/*
 * @Description: operations of database, only use in server.c
 * @version: 1.0.0
 * @Author: ru_j
 * @Date: 2019-12-31 14:15:18
 * @LastEditors  : ru_j
 * @LastEditTime : 2020-01-02 08:52:26
 */
#include "db_op.h"

int init_db(sqlite3 **p_db)
{
    // init database
    int res = sqlite3_open(DB_NAME, p_db);
    if(res != SQLITE_OK){
        printf("[ERROR] DB open failed\n");
        sqlite3_close(*p_db);
        return ERROR_S;
    }
    // create tables
    char *sql = "create table if not exists user_t(\
                    id integer primary key,\
                    username varchar[100] unique not null,\
                    password varchar[100] not null\
                   );";

    char *db_errs = NULL;
    res = sqlite3_exec(*p_db, sql, 0, 0, &db_errs);
    if(res != SQLITE_OK){
        printf("[ERROR] %s\n", db_errs);
        sqlite3_free(db_errs);
        return ERROR_S;
    }

    sql = "create table if not exists blog_t(\
                id integer primary key,\
                title varchar[100] not null,\
                author varchar[100] not null,\
                content varchar[1000] not null,\
                p_time bigint not null\
            );";
    res = sqlite3_exec(*p_db, sql, 0, 0, &db_errs);
    if(res != SQLITE_OK){
        printf("[ERROR] %s\n", db_errs);
        sqlite3_free(db_errs);
        return ERROR_S;
    }

    // create user admin
    sql = "insert into user_t (username, password) values ('admin', 'admin');";
    res = sqlite3_exec(*p_db, sql, 0, 0, &db_errs);

    char *e_user = "UNIQUE constraint failed: user_t.username";
    if(strcmp(db_errs, e_user) == 0){
        printf("[INFO] Already Have Administrator\n");
    }else if(res != SQLITE_OK){
        printf("[ERROR] %s\n", db_errs);
        sqlite3_free(db_errs);
        return ERROR_S;
    }else{
        printf("[INFO] Create Administrator Successded\n");
    }
    
    // free resource
    sqlite3_free(db_errs);

    printf("[INFO] Create Database %s Succeeded\n", DB_NAME);
    return TRUE_S;
}

int close_db(sqlite3 *p_db)
{
    if(p_db == NULL){
        printf("[INFO] DB Already Closed\n");
        return TRUE_S;
    }
    int res = sqlite3_close(p_db);
    if(res != SQLITE_OK){
        printf("[ERROR] DB Close Failed\n");
        return FALSE_S;
    }

    printf("[INFO] DB Closed\n");
    return TRUE_S;
}

int exec_db(sqlite3 *p_db, char *sql, char *err_msgs)
{
    if(p_db == NULL || sql == NULL){
        printf("[ERROR] Exec Invalid Parameters\n");
        return ERROR_S;
    }

    int res = sqlite3_exec(p_db, sql, 0, 0, &err_msgs);
    if(res != SQLITE_OK){
        printf("[ERROR] %s\n", err_msgs);
        return ERROR_S;
    }

    sqlite3_free(err_msgs);

    printf("[INFO] DB Exec Succeeded\n");

    return TRUE_S;
}

int get_table(sqlite3 *p_db, char *sql, char ***p_tbl_res, int *i_row, int *i_col, char *err_msgs)
{
    if(p_db == NULL || sql == NULL || p_tbl_res == NULL || i_row == NULL || i_col == NULL){
        printf("[ERROR] Get Table Invalid Parameters\n");
        return ERROR_S;
    }

    int res = sqlite3_get_table(p_db, sql, p_tbl_res, i_row, i_col, &err_msgs);
    if(res != SQLITE_OK){
        printf("[ERROR] %s\n", err_msgs);
        return ERROR_S;
    }

    printf("[INFO] Get Table Succeeded\n");
    return TRUE_S;    
}