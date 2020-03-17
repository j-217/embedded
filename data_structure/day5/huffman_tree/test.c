#include "huffman_tree.h"

int main(int argc, char const *argv[])
{
#if 0    
    // test find_leaves
    int min = -1,
        next_min = -1;

    tree_node t_1 = {10, NULL, NULL, NULL};
    tree_node t_2 = {3, &t_1, NULL, NULL};
    tree_node t_3 = {7, NULL, NULL, NULL};
    tree_node t_4 = {1, NULL, NULL, NULL};
    tree_node t_5 = {5, &t_3, NULL, NULL};

    tree_node *arr2[5] = {&t_1, &t_2, &t_3, &t_4, &t_5};

    find_leaves(arr2, 5, &min, &next_min);

    printf("wt: %d %d\n", arr2[min]->weight, arr2[next_min]->weight);

    t_4.parent = &t_2;
    t_3.parent = &t_1;

    find_leaves(arr2, 5, &min, &next_min);

    printf("wt: %d %d\n", arr2[min]->weight, arr2[next_min]->weight);
#endif
    tree_node *arr[N*2 - 1] = {NULL};

    init_tree_node(arr, N);

    // 打印数组
    // for(int i = 0; i<(N*2 - 1); i++){
    //     if(arr[i] != NULL)
    //         printf("%d ", arr[i]->weight);
    // }

    huffman_tree p_htree = (huffman_tree)malloc(sizeof(tree_node));

    create_huffman_tree(arr, N*2-1, &p_htree);

    printf("PRE ORDER: ");
    pre_order(p_htree);
    printf("\n");

    printf("IN ORDER: ");
    in_order(p_htree);
    printf("\n");

    printf("POST ORDER: ");
    post_order(p_htree);
    printf("\n");

    return 0;
}
