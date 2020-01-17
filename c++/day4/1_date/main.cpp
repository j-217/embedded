#include "date.h"

int main()
{
    Date now;
    show_date(now);    

    Date set_date(2011, 11, 2);
    show_date(set_date);

    return 0;
}
