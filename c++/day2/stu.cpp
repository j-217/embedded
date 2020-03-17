#include "stu.h"

Student::Student(string name, unsigned int age)
    :_name(name), _age(age)
{
    _credit = 0;
}

Student::~Student(){
    cout << "[Destruct] " << _name << " finally he got " << _credit << " credit" << endl;
}

void Student::show_infos()
{
    cout << "-----Infomations-----" << endl;
    cout << "name:\t" << _name << endl;
    cout << "age:\t" << _age <<endl;
    cout << "credit:\t" << _credit << endl;
    cout << "---------------------" << endl;
    return ;
}

void Student::learning()
{
    _credit += 10;
    cout << _name << " wants nothing but learning, he get 10 credit increment." << endl;
}

void Student::sleeping()
{
    cout << _name << " got a nice sleeping." << endl;
}

void Student::eating()
{
    cout << _name << " ate a huge chinese burger, now he feel full." << endl;
}