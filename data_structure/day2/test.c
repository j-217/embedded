/*
 * @Description: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-12-11 18:24:55
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-12-11 20:26:32
 */
#include "linklist.h"

int main(int argc, char const *argv[])
{
    linknode *p = create_link();
    linknode **p_p = &p;
    data_type test = 0;
    data_type *p_test = &test;

    printf("---Test delete void linklist--------\n");
    delete_data(p, 1, p_test);
    printf("------------------------------------\n\n");

    printf("---Test insert item into linklist---\n");
    insert_link(p, HEAD, 2);
    insert_link(p, 1, 3);
    insert_link(p, HEAD, 1);
    insert_link(p, TAIL, 4);
    get_link(p);
    printf("---Test insert in boundary-----------\n");
    insert_link(p, 4, 5);
    get_link(p);
    printf("---Test insert overflow--------------\n");
    insert_link(p, 10, 10);
    printf("-------------------------------------\n\n");

    printf("---Test reverse linklist-------------\n");
    reverse_link(p_p);
    get_link(p);
    printf("-------------------------------------\n\n");
    
    printf("---Test delete item from linklist----\n");
    // test delete in position
    delete_data(p, 2, p_test);
    get_link(p);  
    printf("DELETED ITEM: %d\n", test);
    // test delete from tail 
    delete_data(p, TAIL, p_test);
    get_link(p);
    printf("DELETED ITEM: %d\n", test);
    printf("---Test delete in boundary-----------\n");
    delete_data(p, 3, p_test);
    get_link(p);
    printf("---Test delete overflow--------------\n");
    delete_data(p, 5, p_test);
    printf("-------------------------------------\n\n");

    printf("---Test destory linklist-------------\n");
    destory_link(p_p);
    printf("LINKLIST HAS BEEN RELEASED: %d\n", p == NULL);
    printf("-------------------------------------\n\n");

    return 0;
}
