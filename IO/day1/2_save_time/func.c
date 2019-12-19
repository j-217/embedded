/*
 * @Description: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-12-17 19:35:14
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-12-17 20:33:03
 */
#include "save_time.h"

int count_lines(FILE *fr){
    if(fr == NULL){
        printf("ERROR: INVALID PARAMETER\n");
        return ERROR_S;
    }
    // 移动光标至文件头
    fseek(fr, 0, SEEK_SET);
    int i = 1;
    char buf[BUFF_SIZE] = {'\0'};

    while(1){
        // 清空BUFFER
        memset(buf, '\0', BUFF_SIZE);

        fgets(buf, BUFF_SIZE, fr);
        if(feof(fr)){
            break;
        }

        if(buf[strlen(buf)-1] == '\n'){
            i++;
        }
    }

    return i;
}

int save_time(const char *pathname){
    if(pathname == NULL){
        printf("ERROR: INVALID PARAMETER\n");
        return ERROR_S;
    }

    FILE *p_f = fopen(pathname, "a+");
    if(p_f == NULL){
        perror("FILE OPEN");
        return ERROR_S;
    }

    printf("Saving...(TO EXIT, USE CTRL+C)\n");
    
    int i = count_lines(p_f);
    while(1){
        time_t now;
        struct tm *now_tm;
        time(&now);
        now_tm = localtime(&now);

        // 写入数据, 手动刷新buffer
        fprintf(p_f, "%d. %d-%02d-%02d %02d:%02d:%02d\n", i, 
                now_tm->tm_year + 1900, now_tm->tm_mon + 1, now_tm->tm_mday, 
                now_tm->tm_hour, now_tm->tm_min, now_tm->tm_sec);
        fflush(p_f);

        sleep(1);
        i++;
    }

    fclose(p_f);

    return TRUE_S;
}

int main(int argc, char const *argv[])
{
    if(argc != 2){
        printf("Usage: %s <filename>\n", argv[0]);
        return FALSE_S;
    }

    save_time(argv[1]);

    return 0;
}
