#include "line.h"

Line::Line(int pt_a_x, int pt_a_y, int pt_b_x, int pt_b_y)
    :_pt_a{new Point(pt_a_x, pt_a_y)},
     _pt_b{new Point(pt_b_x, pt_b_y)}
{
#if TEST
    cout << "Line init" << endl;                 // log for testing
#endif
}

Line::~Line(){
#if TEST
    cout << "Line destructed" << endl;           // log for testing
    cout << this->_pt_a << endl;             
    cout << this->_pt_b << endl;
#endif
    delete this->_pt_a;
    this->_pt_a = nullptr;
    delete this->_pt_b;
    this->_pt_b = nullptr;
}

void Line::set_a(int x, int y){
    this->_pt_a->set_x(x);
    this->_pt_a->set_y(y);
}

void Line::set_b(int x, int y){
    this->_pt_b->set_x(x);
    this->_pt_b->set_y(y);
}

void Line::desc_line(){
    printf("A line from (%d, %d) to (%d, %d)\n", 
        this->_pt_a->get_x(), this->_pt_a->get_y(),
        this->_pt_b->get_x(), this->_pt_b->get_y()
    );
}

Line & Line::operator=(const Line & src){
    if(this == &src){
        return *this;
    }
    delete this->_pt_a;
    delete this->_pt_b;

    this->_pt_a = new Point(src._pt_a->get_x(), src._pt_a->get_y());
    this->_pt_b = new Point(src._pt_b->get_x(), src._pt_b->get_y());

    return *this;
}