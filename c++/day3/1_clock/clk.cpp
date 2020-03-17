#include "clk.h"

Clock::Clock(int hour, int min, int sec)
    :_hour{hour}, _min{min}, _sec{sec}
{
    cout << "Clock init on 00:00:00" << endl;
}

Clock::~Clock(){
    cout << "Clock destructed" << endl;
}


void Clock::set_arg(int data, CLK_FLG type){
    switch (type)
    {
        case CF_HOUR:
            this->_hour = data;
            break;

        case CF_MIN:
            this->_min = data;
            break;
        
        case CF_SEC:
            this->_sec = data;
            break;
        
        default:
            break;
    }

    return ;
}

int Clock::get_arg(CLK_FLG type){
    int ret = 0;
    switch (type)
    {
        case CF_HOUR:
            ret = this->_hour;
            break;
        
        case CF_MIN:
            ret = this->_min;
            break;
        
        case CF_SEC:
            ret = this->_sec;
            break;
        
        default:
            break;
    }

    return ret;
}

void Clock::show_now(){
    time_t now = time(nullptr);
    tm * p_localtm = localtime(&now);

    this->set_arg(p_localtm->tm_hour, CF_HOUR);
    this->set_arg(p_localtm->tm_min, CF_MIN);
    this->set_arg(p_localtm->tm_sec, CF_SEC);

    cout << setw(2) << setfill('0') << this->get_arg(CF_HOUR)
    << ":" << setw(2) << setfill('0') << this->get_arg(CF_MIN)
    << ":" << setw(2) << setfill('0') << this->get_arg(CF_SEC)
    << endl;    
}