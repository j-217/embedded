#include "stack.h"

int main(int argc, char const *argv[])
{
    stack *p_s = init_stack();
    stack **p_ps = &p_s;
    data_type out_item = 0;
    data_type *p_item = &out_item;

    pop_stack(p_s, p_item);
    push_stack(p_s, 1);
    push_stack(p_s, 2);
    push_stack(p_s, 3);
    push_stack(p_s, 4);
    push_stack(p_s, 5);

    pop_stack(p_s, p_item);
    pop_stack(p_s, p_item);
    pop_stack(p_s, p_item);
    pop_stack(p_s, p_item);
    pop_stack(p_s, p_item);
    pop_stack(p_s, p_item);
    
    destory_stack(p_ps);
    printf("IS DESTORYED: %p\n", p_s);

    return 0;
}
