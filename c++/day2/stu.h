#pragma once

#include <iostream>
#include <string>

using namespace std;

class Student{
    protected:
        string _name;
        unsigned int _age;
        int _credit;

    public:
        Student(string name, unsigned int age);         // structor
        ~Student();                                     // destructor
        void show_infos();
        void learning();
        void sleeping();
        void eating();
};