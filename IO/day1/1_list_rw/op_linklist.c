#include "linklist.h"

int main(int argc, char const *argv[])
{
    // 生成链表
    linknode *lk_list = (linknode *)malloc(sizeof(linknode));
    if(lk_list == NULL){
        printf("ERROR: MEMORY IS FULL\n");
        return ERROR_S;
    }

    data_type new_data = 0;
    while(1){
        printf("INPUT A NUMBER(-1 EXIT): ");
        scanf("%d", &new_data);
        while(getchar() != '\n')
            continue;

        if(new_data == -1){
            break;
        }

        insert_link(lk_list, -1, new_data);
    }

    printf("ORIGINAL LINKLIST: ");
    get_link(lk_list);

    // 读取链表数据存入文件
    save_linklist(lk_list, argv[1]);
    // 读取文件内容头插法插入链表
    load_linklist(lk_list, argv[1]);

    printf("MODIFIED LINKLIST: ");
    get_link(lk_list);

    return 0;
}
