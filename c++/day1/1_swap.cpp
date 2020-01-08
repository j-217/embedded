#include <iostream>

using namespace std;

void swap(int &r_a, int &r_b)
{
    int temp = r_a;
    r_a = r_b;
    r_b = temp;

    return ;
}

int main(void)
{
    int n1 = 100,
        n2 = 50;

    cout << "before swap -> n1: " << n1 << ", " << "n2: " << n2 << endl;
    swap(n1, n2);
    cout << "after swap -> n1: " << n1 << ", " << "n2: " << n2 << endl; 

    return 0;
}
