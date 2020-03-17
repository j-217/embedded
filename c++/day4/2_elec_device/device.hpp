#pragma once

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Device {
    protected:
        string _owner,
               _brand,
               _color;

    public:
        Device(string _owner = "XiaoMing", string brand = "cheap copy", string color = "white");
};

Device::Device(string owner, string brand, string color)
    :_owner{owner}, _brand{brand}, _color{color}
{

}