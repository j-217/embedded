/*
 * @Description: function use in server.c
 * @version: 1.0.0
 * @Author: ru_j
 * @Date: 2020-01-01 20:13:22
 * @LastEditors  : ru_j
 * @LastEditTime : 2020-01-01 20:17:09
 */
#include "my_srv.h"

int handle_login(sqlite3 *p_db, clt_data *n_clt_data, serv_data **pp_n_srv_data)
{
    if(p_db == NULL || n_clt_data == NULL || pp_n_srv_data == NULL){
        printf("[ERROR] Handle Login Invalid Parameters\n");
        return ERROR_S;
    }

    char sql[255] = {0};
    bzero(sql, 255);
    sprintf(sql, "select * from user_t where username=\'%s\';", n_clt_data->username);

    int res = get_table(p_db, sql, &((*pp_n_srv_data)->tbl_res), &((*pp_n_srv_data)->i_row), &((*pp_n_srv_data)->i_col), (*pp_n_srv_data)->err_msgs);
    if(res == ERROR_S){
        return ERROR_S;
    }

    if((*pp_n_srv_data)->i_row == 0){                                            // check if username exist
        strcpy((*pp_n_srv_data)->err_msgs, "[INFO] Need Signup");
        (*pp_n_srv_data)->status = NEED_SIGNUP;
        printf("%s\n", (*pp_n_srv_data)->err_msgs);

        return TRUE_S;
    }else if((*pp_n_srv_data)->i_row == 1                                        // check username and password
          && strcmp((*pp_n_srv_data)->tbl_res[5], n_clt_data->password) == 0
    ){
        
        strcpy((*pp_n_srv_data)->err_msgs, "[INFO] Login Succeed");
        strcpy((*pp_n_srv_data)->username, n_clt_data->username);
        (*pp_n_srv_data)->status = LOGIN_OK;

        printf("%s\n", (*pp_n_srv_data)->err_msgs);

        return TRUE_S;
    }else{                                                                       // wrong password
        strcpy((*pp_n_srv_data)->err_msgs, "[INFO] Wrong Password");
        (*pp_n_srv_data)->status = WR_PASSWD;
        printf("%s\n", (*pp_n_srv_data)->err_msgs);

        return TRUE_S;
    }

    return TRUE_S;
}

int handle_signup(sqlite3 *p_db, clt_data *n_clt_data, serv_data **pp_n_srv_data)
{
    if(p_db == NULL || n_clt_data == NULL || pp_n_srv_data== NULL){
        printf("[ERROR] Handle Login Invalid Parameters\n");
        return ERROR_S;
    }
    
    char sql[255] = {0};
    bzero(sql, 255);
    sprintf(sql, "select * from user_t where username=\'%s\';", n_clt_data->username);

    int res = get_table(p_db, sql, &((*pp_n_srv_data)->tbl_res), &((*pp_n_srv_data)->i_row), &((*pp_n_srv_data)->i_col), (*pp_n_srv_data)->err_msgs);
    if(res == ERROR_S){
        return ERROR_S;
    }

    if((*pp_n_srv_data)->i_row == 1){
        strcpy((*pp_n_srv_data)->err_msgs, "[INFO] This username is already taken, try another one");
        (*pp_n_srv_data)->status = SIGNUP_FAILED;
        return FALSE_S;
    }

    bzero(sql, 255);
    sprintf(sql, "insert into user_t (username, password) values (\'%s\', \'%s\');", n_clt_data->username, n_clt_data->password);
    res = exec_db(p_db, sql, (*pp_n_srv_data)->err_msgs);
    if(res == ERROR_S){
        return ERROR_S;
    }
    (*pp_n_srv_data)->status = SIGNUP_OK;
    strcpy((*pp_n_srv_data)->err_msgs, "[INFO] Signup Succeed\n");

    return TRUE_S;
}

int handle_publish(sqlite3 *p_db, clt_data *n_clt_data, serv_data **pp_n_srv_data)
{
    if(p_db == NULL || n_clt_data == NULL || pp_n_srv_data== NULL){
        printf("[ERROR] Handle Login Invalid Parameters\n");
        return ERROR_S;
    }
    char sql[2000] = {0};
    bzero(sql, 2000);
    time_t now = time(NULL);

    sprintf(sql, "insert into blog_t (title, author, content, p_time) values('%s', '%s', '%s', %ld);", 
            n_clt_data->title,
            n_clt_data->username,
            n_clt_data->content,
            now
    );

    int res = exec_db(p_db, sql, (*pp_n_srv_data)->err_msgs);
    if(res == ERROR_S){
        return ERROR_S;
    }
    (*pp_n_srv_data)->status = PUB_OK;
    strcpy((*pp_n_srv_data)->err_msgs, "[INFO] Pulished A New Blog\n");

    return TRUE_S;
}

int handle_show(sqlite3 *p_db, clt_data *n_clt_data, serv_data **pp_n_srv_data, int range_flag)
{
    if(p_db == NULL || n_clt_data == NULL || pp_n_srv_data== NULL){
        printf("[ERROR] Handle Login Invalid Parameters\n");
        return ERROR_S;
    }

    char sql[200] = {0};
    bzero(sql, 200);
    if(range_flag == SH_ALL_FLG){
        sprintf(sql, "select * from blog_t order by p_time desc limit 10;");
    }else if(range_flag == SH_MINE_FLG){
        sprintf(sql, "select * from blog_t where author='%s' order by p_time desc limit 10;", n_clt_data->username);
    }

    int res = get_table(p_db, sql, &((*pp_n_srv_data)->tbl_res), &((*pp_n_srv_data)->i_row), &((*pp_n_srv_data)->i_col), (*pp_n_srv_data)->err_msgs);
    if(res == ERROR_S){
        return ERROR_S;
    }

    for (int i = 1; i <= (*pp_n_srv_data)->i_row; i++)                                      // first line is head, content in 1~n, first column is id
    {
        strcpy((*pp_n_srv_data)->blogs[i-1].title, (*pp_n_srv_data)->tbl_res[i * (*pp_n_srv_data)->i_col + 1]);
        strcpy((*pp_n_srv_data)->blogs[i-1].author, (*pp_n_srv_data)->tbl_res[i * (*pp_n_srv_data)->i_col + 2]);
        strcpy((*pp_n_srv_data)->blogs[i-1].content, (*pp_n_srv_data)->tbl_res[i * (*pp_n_srv_data)->i_col + 3]);
        strcpy((*pp_n_srv_data)->blogs[i-1].p_time, (*pp_n_srv_data)->tbl_res[i * (*pp_n_srv_data)->i_col + 4]);
    }

    (*pp_n_srv_data)->status = SHOW_OK;
    strcpy((*pp_n_srv_data)->err_msgs, "[INFO] Display Blogs\n");

    return TRUE_S;
}