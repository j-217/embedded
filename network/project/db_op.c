/*
 * @Description: operations of database, only use in server.c
 * @version: 1.0.0
 * @Author: ru_j
 * @Date: 2019-12-31 14:15:18
 * @LastEditors  : ru_j
 * @LastEditTime : 2020-01-01 19:42:01
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

// int print_tbl_res(serv_data *p_srv_data)
// {
//     if(p_srv_data == NULL){
//         printf("[ERROR] Get Table Invalid Parameters\n");
//         return ERROR_S;
//     }
//     if(p_srv_data->i_row == 0){
//         printf("[INFO] Nothing to print for\n");
//         return FALSE_S;
//     }
    
//     for(int i = 0; i < p_srv_data->i_row; i++){
//         printf("------------------[%2d]----------------------------\n", i+1);
//         printf("TITLE: %s\n", p_srv_data->blogs[i].title);
//         printf("AUTHOR: %s\tPUBLISH TIME: %s\n", p_srv_data->blogs[i].author, p_srv_data->blogs[i].p_time);
//         printf("CONTENT:\n\t%s\n", p_srv_data->blogs[i].content);
//         printf("--------------------------------------------------\n");
//     }

//     return TRUE_S;
// }

// int handle_login(sqlite3 *p_db, clt_data *n_clt_data, serv_data **pp_n_srv_data)
// {
//     if(p_db == NULL || n_clt_data == NULL || pp_n_srv_data == NULL){
//         printf("[ERROR] Handle Login Invalid Parameters\n");
//         return ERROR_S;
//     }

//     char sql[255] = {0};
//     bzero(sql, 255);
//     sprintf(sql, "select * from user_t where username=\'%s\';", n_clt_data->username);

//     int res = get_table(p_db, sql, &((*pp_n_srv_data)->tbl_res), &((*pp_n_srv_data)->i_row), &((*pp_n_srv_data)->i_col), (*pp_n_srv_data)->err_msgs);
//     if(res == ERROR_S){
//         return ERROR_S;
//     }

//     if((*pp_n_srv_data)->i_row == 0){                                            // check if username exist
//         strcpy((*pp_n_srv_data)->err_msgs, "[INFO] Need Signup");
//         (*pp_n_srv_data)->status = NEED_SIGNUP;
//         printf("%s\n", (*pp_n_srv_data)->err_msgs);

//         return TRUE_S;
//     }else if((*pp_n_srv_data)->i_row == 1                                        // check username and password
//           && strcmp((*pp_n_srv_data)->tbl_res[5], n_clt_data->password) == 0
//     ){
        
//         strcpy((*pp_n_srv_data)->err_msgs, "[INFO] Login Succeed");
//         strcpy((*pp_n_srv_data)->username, n_clt_data->username);
//         (*pp_n_srv_data)->status = LOGIN_OK;

//         printf("%s\n", (*pp_n_srv_data)->err_msgs);

//         return TRUE_S;
//     }else{                                                                       // wrong password
//         strcpy((*pp_n_srv_data)->err_msgs, "[INFO] Wrong Password");
//         (*pp_n_srv_data)->status = WR_PASSWD;
//         printf("%s\n", (*pp_n_srv_data)->err_msgs);

//         return TRUE_S;
//     }

//     return TRUE_S;
// }

// int handle_signup(sqlite3 *p_db, clt_data *n_clt_data, serv_data **pp_n_srv_data)
// {
//     if(p_db == NULL || n_clt_data == NULL || pp_n_srv_data== NULL){
//         printf("[ERROR] Handle Login Invalid Parameters\n");
//         return ERROR_S;
//     }
    
//     char sql[255] = {0};
//     bzero(sql, 255);
//     sprintf(sql, "select * from user_t where username=\'%s\';", n_clt_data->username);

//     int res = get_table(p_db, sql, &((*pp_n_srv_data)->tbl_res), &((*pp_n_srv_data)->i_row), &((*pp_n_srv_data)->i_col), (*pp_n_srv_data)->err_msgs);
//     if(res == ERROR_S){
//         return ERROR_S;
//     }

//     if((*pp_n_srv_data)->i_row == 1){
//         strcpy((*pp_n_srv_data)->err_msgs, "[INFO] This username is already taken, try another one");
//         (*pp_n_srv_data)->status = SIGNUP_FAILED;
//         return FALSE_S;
//     }

//     bzero(sql, 255);
//     sprintf(sql, "insert into user_t (username, password) values (\'%s\', \'%s\');", n_clt_data->username, n_clt_data->password);
//     res = exec_db(p_db, sql, (*pp_n_srv_data)->err_msgs);
//     if(res == ERROR_S){
//         return ERROR_S;
//     }
//     (*pp_n_srv_data)->status = SIGNUP_OK;
//     strcpy((*pp_n_srv_data)->err_msgs, "[INFO] Signup Succeed\n");

//     return TRUE_S;
// }

// int handle_publish(sqlite3 *p_db, clt_data *n_clt_data, serv_data **pp_n_srv_data)
// {
//     if(p_db == NULL || n_clt_data == NULL || pp_n_srv_data== NULL){
//         printf("[ERROR] Handle Login Invalid Parameters\n");
//         return ERROR_S;
//     }
//     char sql[2000] = {0};
//     bzero(sql, 2000);
//     time_t now = time(NULL);

//     sprintf(sql, "insert into blog_t (title, author, content, p_time) values('%s', '%s', '%s', %ld);", 
//             n_clt_data->title,
//             n_clt_data->username,
//             n_clt_data->content,
//             now
//     );

//     int res = exec_db(p_db, sql, (*pp_n_srv_data)->err_msgs);
//     if(res == ERROR_S){
//         return ERROR_S;
//     }
//     (*pp_n_srv_data)->status = PUB_OK;
//     strcpy((*pp_n_srv_data)->err_msgs, "[INFO] Pulished A New Blog\n");

//     return TRUE_S;
// }

// int handle_show(sqlite3 *p_db, clt_data *n_clt_data, serv_data **pp_n_srv_data, int range_flag)
// {
//     if(p_db == NULL || n_clt_data == NULL || pp_n_srv_data== NULL){
//         printf("[ERROR] Handle Login Invalid Parameters\n");
//         return ERROR_S;
//     }

//     char sql[200] = {0};
//     bzero(sql, 200);
//     if(range_flag == SH_ALL_FLG){
//         sprintf(sql, "select * from blog_t order by p_time desc limit 10;");
//     }else if(range_flag == SH_MINE_FLG){
//         sprintf(sql, "select * from blog_t where author='%s' order by p_time desc limit 10;", n_clt_data->username);
//     }

//     int res = get_table(p_db, sql, &((*pp_n_srv_data)->tbl_res), &((*pp_n_srv_data)->i_row), &((*pp_n_srv_data)->i_col), (*pp_n_srv_data)->err_msgs);
//     if(res == ERROR_S){
//         return ERROR_S;
//     }

//     for (int i = 1; i <= (*pp_n_srv_data)->i_row; i++)                                      // first line is head, content in 1~n, first column is id
//     {
//         strcpy((*pp_n_srv_data)->blogs[i-1].title, (*pp_n_srv_data)->tbl_res[i * (*pp_n_srv_data)->i_col + 1]);
//         strcpy((*pp_n_srv_data)->blogs[i-1].author, (*pp_n_srv_data)->tbl_res[i * (*pp_n_srv_data)->i_col + 2]);
//         strcpy((*pp_n_srv_data)->blogs[i-1].content, (*pp_n_srv_data)->tbl_res[i * (*pp_n_srv_data)->i_col + 3]);
//         strcpy((*pp_n_srv_data)->blogs[i-1].p_time, (*pp_n_srv_data)->tbl_res[i * (*pp_n_srv_data)->i_col + 4]);
//     }

//     (*pp_n_srv_data)->status = SHOW_OK;
//     strcpy((*pp_n_srv_data)->err_msgs, "[INFO] Display Blogs\n");

//     return TRUE_S;
// }