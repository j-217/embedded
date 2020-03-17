#include "linklist.h"

int save_linklist(linknode *p_head, const char *pathname){
    if(p_head == NULL || pathname == NULL){
        printf("ERROR: INVALID PARAMETER\n");
        return ERROR_S;
    }

    // 判断是否为空链表
    if(p_head->next == NULL){
        printf("INFO: EMPTY LINKLIST\n");
        return FALSE_S;
    }
    // 移动到首结点开始保存
    p_head = p_head->next;

    FILE *fw = NULL;
    fw = fopen(pathname, "w");
    if(fw == NULL){
        perror("FILE OPEN");
        return ERROR_S;
    }

    while(p_head != NULL){
        int data = p_head->data;
        fputc(data, fw);
        p_head = p_head->next;
    }

    fclose(fw);

    printf("SAVED IN %s\n", pathname);

    return TRUE_S;
}

int load_linklist(linknode *p_head, const char *pathname){
    if(p_head == NULL || pathname == NULL){
        printf("ERROR: INVALID PARAMETER\n");
        return ERROR_S;
    }

    FILE *fr = NULL;
    fr = fopen(pathname, "r");
    if(fr == NULL){
        perror("FILE OPEN");
        return ERROR_S;
    }

    while(1){
        int data = fgetc(fr);

        if(feof(fr)){
            break;
        }

        // 头插法重新插入链表
        insert_link(p_head, 0, data);
    }

    fclose(fr);

    printf("LOADED FROM %s\n", pathname);

    return TRUE_S;
}