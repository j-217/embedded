/*
 * @Description: 
 * @version: 1.0.0
 * @Author: ru_jin
 * @Date: 2019-12-11 18:24:55
 * @LastEditors: ru_jin
 * @LastEditTime: 2019-12-12 20:34:25
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
    
    printf("---Test insert in order--------------\n");
    linknode *p_seql_1 = create_link();
    linknode **p_p_1 = &p_seql_1;

    // test negative
    insert_in_order(p_seql_1, -13);
    insert_in_order(p_seql_1, -15);
    insert_in_order(p_seql_1, -11);
    insert_in_order(p_seql_1, -17);

    insert_in_order(p_seql_1, 0);
    insert_in_order(p_seql_1, 15);
    insert_in_order(p_seql_1, 11);
    insert_in_order(p_seql_1, 17);

    get_link(p_seql_1);
    destory_link(p_p_1);
    printf("-------------------------------------\n\n");

    printf("---Test merge two linklist-----------\n");
    linknode *p_seql_2 = create_link();

    insert_in_order(p_seql_2, 2);
    insert_in_order(p_seql_2, 5);
    insert_in_order(p_seql_2, 7);
    printf("LINK 1: ");
    get_link(p_seql_2);

    linknode *p_seql_3 = create_link();
    insert_in_order(p_seql_3, 1);
    insert_in_order(p_seql_3, 3);
    insert_in_order(p_seql_3, 7);
    insert_in_order(p_seql_3, 4);
    insert_in_order(p_seql_3, 8);
    insert_in_order(p_seql_3, 10);
    printf("LINK 2: ");
    get_link(p_seql_3);

    linknode *p_m_res = merge_link(p_seql_2, p_seql_3);
    get_link(p_m_res);
    printf("-------------------------------------\n\n");
    
    printf("---Test destory linklist-------------\n");
    destory_link(p_p);
    printf("LINKLIST HAS BEEN RELEASED: %d\n", p == NULL);
    printf("-------------------------------------\n\n");

    return 0;
}
