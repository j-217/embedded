#include "pattern.h"

/*---------------I_Pattern------------------------*/

I_PATTERN::I_PATTERN(int org_x, int org_y)
    :Shape{org_x, org_y}
{ }

void I_PATTERN::set_shape() {
    this->_rotate_stat %= 2;
    switch (this->_rotate_stat) {
    case 1:
        this->_arr[1].set_x(this->_arr[0].get_x() - 2);
        this->_arr[1].set_y(this->_arr[0].get_y());
        this->_arr[2].set_x(this->_arr[0].get_x() + 2);
        this->_arr[2].set_y(this->_arr[0].get_y());
        this->_arr[3].set_x(this->_arr[0].get_x() + 4);
        this->_arr[3].set_y(this->_arr[0].get_y());
        break;

    default:
        this->_arr[1].set_x(this->_arr[0].get_x());
        this->_arr[1].set_y(this->_arr[0].get_y() - 1);
        this->_arr[2].set_x(this->_arr[0].get_x());
        this->_arr[2].set_y(this->_arr[0].get_y() + 1); 
        this->_arr[3].set_x(this->_arr[0].get_x());
        this->_arr[3].set_y(this->_arr[0].get_y() + 2);
        break;
    }
}

/*---------------I_Pattern  end-------------------*/

/*---------------O_Pattern------------------------*/

O_PATTERN::O_PATTERN(int org_x, int org_y)
    :Shape{org_x, org_y}
{ }

void O_PATTERN::set_shape() {
    this->_arr[1].set_x(this->_arr[0].get_x() + 2);
    this->_arr[1].set_y(this->_arr[0].get_y());
    this->_arr[2].set_x(this->_arr[0].get_x());
    this->_arr[2].set_y(this->_arr[0].get_y() + 1);
    this->_arr[3].set_x(this->_arr[0].get_x() + 2);
    this->_arr[3].set_y(this->_arr[0].get_y() + 1);
}

/*---------------O_Pattern  end-------------------*/

/*---------------Z_Pattern------------------------*/

Z_PATTERN::Z_PATTERN(int org_x, int org_y)
    :Shape{org_x, org_y}
{ }

void Z_PATTERN::set_shape() {
    this->_rotate_stat %= 2;
    switch (this->_rotate_stat) {
    case 1:
        this->_arr[1].set_x(this->_arr[0].get_x() + 2);
        this->_arr[1].set_y(this->_arr[0].get_y());
        this->_arr[2].set_x(this->_arr[0].get_x() + 2);
        this->_arr[2].set_y(this->_arr[0].get_y() - 1);
        this->_arr[3].set_x(this->_arr[0].get_x());
        this->_arr[3].set_y(this->_arr[0].get_y() + 1);
        break;

    default:
        this->_arr[1].set_x(this->_arr[0].get_x());
        this->_arr[1].set_y(this->_arr[0].get_y() - 1);
        this->_arr[2].set_x(this->_arr[0].get_x() - 2);
        this->_arr[2].set_y(this->_arr[0].get_y() - 1); 
        this->_arr[3].set_x(this->_arr[0].get_x() + 2);
        this->_arr[3].set_y(this->_arr[0].get_y());
        break;
    }
}

/*---------------Z_Pattern  end-------------------*/

/*---------------ZZ_Pattern-----------------------*/

ZZ_PATTERN::ZZ_PATTERN(int org_x, int org_y)
    :Shape{org_x, org_y}
{ }

void ZZ_PATTERN::set_shape() {
    this->_rotate_stat %= 2;
    switch (this->_rotate_stat) {
    case 1:
        this->_arr[1].set_x(this->_arr[0].get_x() - 2);
        this->_arr[1].set_y(this->_arr[0].get_y());
        this->_arr[2].set_x(this->_arr[0].get_x() - 2);
        this->_arr[2].set_y(this->_arr[0].get_y() - 1);
        this->_arr[3].set_x(this->_arr[0].get_x());
        this->_arr[3].set_y(this->_arr[0].get_y() + 1);
        break;

    default:
        this->_arr[1].set_x(this->_arr[0].get_x());
        this->_arr[1].set_y(this->_arr[0].get_y() - 1);
        this->_arr[2].set_x(this->_arr[0].get_x() + 2);
        this->_arr[2].set_y(this->_arr[0].get_y() - 1); 
        this->_arr[3].set_x(this->_arr[0].get_x() - 2);
        this->_arr[3].set_y(this->_arr[0].get_y());
        break;
    }
}

/*---------------ZZ_Pattern  end------------------*/

/*---------------T_Pattern------------------------*/

T_PATTERN::T_PATTERN(int org_x, int org_y)
    :Shape{org_x, org_y}
{}

void T_PATTERN::set_shape() {
    this->_rotate_stat %= 4;
    switch (this->_rotate_stat) {
    case 1:
        this->_arr[1].set_x(this->_arr[0].get_x() + 2);
        this->_arr[1].set_y(this->_arr[0].get_y());
        this->_arr[2].set_x(this->_arr[0].get_x());
        this->_arr[2].set_y(this->_arr[0].get_y() - 1);
        this->_arr[3].set_x(this->_arr[0].get_x());
        this->_arr[3].set_y(this->_arr[0].get_y() + 1);
        break;
    case 2:
        this->_arr[1].set_x(this->_arr[0].get_x());
        this->_arr[1].set_y(this->_arr[0].get_y() + 1);
        this->_arr[2].set_x(this->_arr[0].get_x() + 2);
        this->_arr[2].set_y(this->_arr[0].get_y());
        this->_arr[3].set_x(this->_arr[0].get_x() - 2);
        this->_arr[3].set_y(this->_arr[0].get_y());
        break;
    case 3:
        this->_arr[1].set_x(this->_arr[0].get_x() - 2);
        this->_arr[1].set_y(this->_arr[0].get_y());
        this->_arr[2].set_x(this->_arr[0].get_x());
        this->_arr[2].set_y(this->_arr[0].get_y() + 1);
        this->_arr[3].set_x(this->_arr[0].get_x());
        this->_arr[3].set_y(this->_arr[0].get_y() - 1);
        break;
    default:
        this->_arr[1].set_x(this->_arr[0].get_x());
        this->_arr[1].set_y(this->_arr[0].get_y() - 1);
        this->_arr[2].set_x(this->_arr[0].get_x() - 2);
        this->_arr[2].set_y(this->_arr[0].get_y()); 
        this->_arr[3].set_x(this->_arr[0].get_x() + 2);
        this->_arr[3].set_y(this->_arr[0].get_y());
        break;
    }
}

/*---------------T_Pattern  end-------------------*/

/*---------------L_Pattern------------------------*/

L_PATTERN::L_PATTERN(int org_x, int org_y)
    :Shape{org_x, org_y}
{}

void L_PATTERN::set_shape() {
    this->_rotate_stat %= 4;
    switch (this->_rotate_stat) {
    case 1:
        this->_arr[1].set_x(this->_arr[0].get_x());
        this->_arr[1].set_y(this->_arr[0].get_y() + 1);
        this->_arr[2].set_x(this->_arr[0].get_x() + 2);
        this->_arr[2].set_y(this->_arr[0].get_y());
        this->_arr[3].set_x(this->_arr[0].get_x() + 4);
        this->_arr[3].set_y(this->_arr[0].get_y());
        break;
    case 2:
        this->_arr[1].set_x(this->_arr[0].get_x() - 2);
        this->_arr[1].set_y(this->_arr[0].get_y());
        this->_arr[2].set_x(this->_arr[0].get_x());
        this->_arr[2].set_y(this->_arr[0].get_y() + 1);
        this->_arr[3].set_x(this->_arr[0].get_x());
        this->_arr[3].set_y(this->_arr[0].get_y() + 2);
        break;
    case 3:
        this->_arr[1].set_x(this->_arr[0].get_x());
        this->_arr[1].set_y(this->_arr[0].get_y() - 1);
        this->_arr[2].set_x(this->_arr[0].get_x() - 2);
        this->_arr[2].set_y(this->_arr[0].get_y());
        this->_arr[3].set_x(this->_arr[0].get_x() - 4);
        this->_arr[3].set_y(this->_arr[0].get_y());
        break;
    default:
        this->_arr[1].set_x(this->_arr[0].get_x() + 2);
        this->_arr[1].set_y(this->_arr[0].get_y());
        this->_arr[2].set_x(this->_arr[0].get_x());
        this->_arr[2].set_y(this->_arr[0].get_y() - 1); 
        this->_arr[3].set_x(this->_arr[0].get_x());
        this->_arr[3].set_y(this->_arr[0].get_y() - 2);
        break;
    }
}

/*---------------L_Pattern  end-------------------*/

/*---------------LL_Pattern-----------------------*/

LL_PATTERN::LL_PATTERN(int org_x, int org_y)
    :Shape{org_x, org_y}
{}

void LL_PATTERN::set_shape() {
    this->_rotate_stat %= 4;
    switch (this->_rotate_stat) {
    case 1:
        this->_arr[1].set_x(this->_arr[0].get_x());
        this->_arr[1].set_y(this->_arr[0].get_y() - 1);
        this->_arr[2].set_x(this->_arr[0].get_x() + 2);
        this->_arr[2].set_y(this->_arr[0].get_y());
        this->_arr[3].set_x(this->_arr[0].get_x() + 4);
        this->_arr[3].set_y(this->_arr[0].get_y());
        break;
    case 2:
        this->_arr[1].set_x(this->_arr[0].get_x() + 2);
        this->_arr[1].set_y(this->_arr[0].get_y());
        this->_arr[2].set_x(this->_arr[0].get_x());
        this->_arr[2].set_y(this->_arr[0].get_y() + 1);
        this->_arr[3].set_x(this->_arr[0].get_x());
        this->_arr[3].set_y(this->_arr[0].get_y() + 2);
        break;
    case 3:
        this->_arr[1].set_x(this->_arr[0].get_x());
        this->_arr[1].set_y(this->_arr[0].get_y() + 1);
        this->_arr[2].set_x(this->_arr[0].get_x() - 2);
        this->_arr[2].set_y(this->_arr[0].get_y());
        this->_arr[3].set_x(this->_arr[0].get_x() - 4);
        this->_arr[3].set_y(this->_arr[0].get_y());
        break;
    default:
        this->_arr[1].set_x(this->_arr[0].get_x() - 2);
        this->_arr[1].set_y(this->_arr[0].get_y());
        this->_arr[2].set_x(this->_arr[0].get_x());
        this->_arr[2].set_y(this->_arr[0].get_y() - 1); 
        this->_arr[3].set_x(this->_arr[0].get_x());
        this->_arr[3].set_y(this->_arr[0].get_y() - 2);
        break;
    }
}

/*---------------LL_Pattern  end------------------*/