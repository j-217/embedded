#include "line.h"

int main(void)
{
    Line line_a(10, 15, 100, 150);
    Line line_b;
    line_b = line_a;

    cout << "-----original-----" << endl;
    cout << "line a: ";
    line_a.desc_line();    
    cout << "line b: ";
    line_b.desc_line(); 

    cout << "-----modify b-----" << endl;
    line_b.set_a(50, 60);
    line_b.set_b(20, 30);
    cout << "line a: ";
    line_a.desc_line();
    cout << "line b: ";
    line_b.desc_line(); 

    return 0;
}
