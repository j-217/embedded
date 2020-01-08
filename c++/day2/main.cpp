#include "stu.h"

int main(void)
{
    Student stu1("Tom", 23);                            // assign memory in stack
    stu1.show_infos();
    stu1.learning();
    stu1.eating();
    stu1.sleeping();
    stu1.show_infos();

    Student *p_stu2 = new Student("laowang", 20);       // assign memory in heap
    p_stu2->show_infos();
    p_stu2->sleeping();
    p_stu2->sleeping();
    delete p_stu2;

    return 0;
}
