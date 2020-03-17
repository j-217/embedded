#pragma once

#include <iostream>

using namespace std;

class Date {
    private:
        int _year,
            _month,
            _day;

    public:
        Date();
        Date(int year, int month, int day);
        ~Date();
        friend void show_date(Date & date);
};