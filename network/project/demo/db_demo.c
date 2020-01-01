#include <stdio.h>
#include <sqlite3.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // init db
    sqlite3 *p_db;
    int res = sqlite3_open("my_db.db", &p_db);
    if(res != SQLITE_OK){
        printf("DB open failed\n");
        sqlite3_close(p_db);
        return -1;
    }

    // create tables
    char *p_sql = "create table if not exists user_t(\
                    id integer primary key,\
                    username varchar[100] unique not null,\
                    password varchar[100] not null\
                    );";

    char *db_errs = NULL;
    res = sqlite3_exec(p_db, p_sql, 0, 0, &db_errs);
    if(res != SQLITE_OK){
        printf("[ERROR] %s\n", db_errs);
        sqlite3_free(db_errs);
        return -1;
    }
    
    // insert
#if 0
    p_sql = "insert into user_t (username, password)\
            values('test', 'test');";

    res = sqlite3_exec(p_db, p_sql, 0, 0, &db_errs);
    char *e_user = "UNIQUE constraint failed: user_t.username";
    if(strcmp(db_errs, e_user) == 0){
        printf("Already have it\n");
    }else if(res != SQLITE_OK){
        printf("[ERROR] %s\n", db_errs);
        sqlite3_free(db_errs);
        return -1;
    }
#endif
    // select
#if 0
    p_sql = "select * from user_t;";
    res = sqlite3_exec(p_db, p_sql, 0, 0, &db_errs);
    if(res != SQLITE_OK){
        printf("[ERROR] %s\n", db_errs);
        sqlite3_free(db_errs);
        return -1;
    }
#endif

    p_sql = "select * from blog_t;";
    char **pp_sel_result = {0};
    int i_row = 0;
    int i_col = 0;
    res = sqlite3_get_table(p_db, p_sql, &pp_sel_result, &i_row, &i_col, &db_errs);
    if(res != SQLITE_OK){
        printf("[ERROR] %s\n", db_errs);
        return -1;
    }
    printf("%s %d %d\n", pp_sel_result[5], i_row, i_col);
    if(strcmp(pp_sel_result[3], "1") == 0){
        printf("aaa\n");
    }

#if 1    
    printf("%d %d\n", i_row, i_col);                                    // test pp_sel_result
    printf("%s \n", pp_sel_result[0]);
    printf("%s \n", pp_sel_result[6]);

    if (NULL != pp_sel_result)
    {
        int i = 0;
        for (; i <= i_row; i++)                                         // first line is head, 1~n is content
        {
            int j = 0;
            for (; j < i_col; j++)
            {
                if (NULL != pp_sel_result[i * i_col + j])
                {
                    printf("%s\t\t",pp_sel_result[i * i_col + j]);
                }
                
            }
            printf("\n");
        }
    }
#endif

    sqlite3_free(db_errs);

    sqlite3_close(p_db);

    return 0;
}
