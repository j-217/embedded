#include "my_ls.h"

int handle_file_mode(mode_t f_mode, char (*res)[]){
    // 处理文件类型
    switch (f_mode&__S_IFMT)
    {
    case __S_IFSOCK:
        (*res)[0] = 's';
        break;
    case __S_IFLNK:
        (*res)[0] = 'l';
        break;
    case __S_IFREG:
        (*res)[0] = '-';
        break;
    case __S_IFBLK:
        (*res)[0] = 'b';
        break;
    case __S_IFDIR:
        (*res)[0] = 'd';
        break;
    case __S_IFCHR:
        (*res)[0] = 'c';
        break;
    case __S_IFIFO:
        (*res)[0] = 'p';
        break;
    default:
        break;
    }

    // 处理文件权限, 按位或1, 获取当前位置的结果, 为1表示有效, mod(3)后获取当前位置的权限内容
    char arr[3] = "xwr";
    for(int i = 1; i<10; i++){
       if(f_mode&(1<<(i-1))){
           (*res)[10-i] = arr[(i-1)%3];
       }else{
           (*res)[10-i] = '-';
       }
    }

    return 0;
}

int print_line(struct dirent * dd, const char *root_path){
    if(dd == NULL){
        printf("ERROR: INVALID PARAMETER\n");
        return -1;
    }

    struct stat buf;
    char full_file_name[SIZE] = {'\0'};
    if(strcmp(dd->d_name, ".") == 0 || strcmp(dd->d_name, "..") == 0){
        strcpy(full_file_name, dd->d_name);
    }else{
        strcpy(full_file_name, root_path);
        strcat(full_file_name, dd->d_name);
    }

    if(stat(full_file_name, &buf) < 0){
        return -1;
    }

    // 处理时间
    time_t m_time = buf.st_mtime;
    struct tm * m_tm = localtime(&m_time);

    // 处理文件类型和权限, 0: 文件类型, 1-9: 文件权限, 10: 字符串结束标识符
    char file_mode[11] = {'\0'};
    handle_file_mode(buf.st_mode, &file_mode);

    // 处理月份
    char *mon[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    // 打印信息
    printf("%s", file_mode);
    printf("%5ld", buf.st_nlink);
    printf("%8ld  ", buf.st_size);
    printf("%s %2d %02d:%02d  ", mon[m_tm->tm_mon], m_tm->tm_mday, m_tm->tm_hour, m_tm->tm_min);
    printf("%s\n", dd->d_name);

    return 0;
}

int print_lines(DIR *dirp, const char *root_path)
{
    if (dirp == NULL){
        printf("ERROR: INVALID PARAMETER\n");
        return -1;
    }

    while (1){
        struct dirent *dd = NULL;
        dd = readdir(dirp);

        if (dd == NULL){
            break;
        }

        // 打印内容
        print_line(dd, root_path);
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    if (argc != 2){
        printf("Uasge: %s <filename>\n", argv[0]);
        return -1;
    }

    DIR *pDir = NULL;
    pDir = opendir(argv[1]);
    if (pDir == NULL){
        perror("OPEN ERROR");
        return -1;
    }

    // 保存根路径地址
    // char root_path[SIZE] = {'\0'};
    // strcpy(root_path, argv[1]);    

    print_lines(pDir, argv[1]);
 
    return 0;
}
