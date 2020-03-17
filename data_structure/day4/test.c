#include "bin_tree.h"

int main(int argc, char const *argv[])
{
    b_tree p = NULL;
    
    // 普通二叉树
    // init_b_tree(&p);

    // 有序二叉树
    init_order_b_tree(&p);

    printf("PRE ORDER: ");
    pre_order(p);
    printf("\n");


    printf("IN ORDER: ");
    in_order(p);
    printf("\n");

    printf("POST ORDER: ");
    post_order(p);
    printf("\n");

    printf("LEVEL ORDER: ");
    level_order(p);
    printf("\n");

    // 销毁
    destory_b_tree(&p);
    printf("%p\n", p);

    return 0;
}
