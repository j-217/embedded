#include "date.h"
#include <ctime>
#include <iomanip>

void show_date(Date & date)
{
    cout << "Date: " 
    << setw(2) << setfill('0') << date._month << "/"
    << setw(2) << setfill('0') << date._day << "/"
    << date._year << endl;
}

Date::Date()
{
    time_t now = time(nullptr);
    tm *today = localtime(&now);

    this->_year = today->tm_year + 1900;
    this->_month = today->tm_mon + 1;
    this->_day = today->tm_mday;
}

Date::Date(int year, int month, int day)
    :_year{year}, _month{month}, _day{day}
{
    if(month < 0 || month > 12 || day < 0 || day > 31){
        cout << "Invalid Arguments" << endl;
        exit(-1);
    }
}

Date::~Date(){}