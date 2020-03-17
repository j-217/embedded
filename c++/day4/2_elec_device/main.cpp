#include "cellphone.hpp"
#include "pc.hpp"

int main()
{
    Cellphone my_cell;
    my_cell.desc();
    my_cell.call();
    my_cell.gaming();   

    PC my_pc;
    my_pc.desc();
    my_pc.coding();
    my_pc.gaming(); 
    
    return 0;
}
