#include "device.hpp"

class Cellphone : public Device
{
    protected:
        size_t _fee;
    public:
        Cellphone(string owner = "Tom", string brand = "Apple", string color = "black", size_t fee = 38);
        void call();
        void gaming();
        void desc();
};

Cellphone::Cellphone(string owner, string brand, string color, size_t fee)
    :Device{owner, brand, color}, _fee{fee}
{

}

void Cellphone::call()
{
    printf("%s calling his friedns with a %s %s cellphone, he paid %d for this every month\n", 
        this->_owner.c_str(),
        this->_color.c_str(),
        this->_brand.c_str(),
        this->_fee
    );
}

void Cellphone::gaming()
{
    printf("%s playing game in a %s %s cellphone\n", 
        this->_owner.c_str(),
        this->_color.c_str(),
        this->_brand.c_str()
    );
}

void Cellphone::desc()
{
    cout << "-----Infos-----" << endl;
    cout << "Owner:\t" << this->_owner << endl;
    cout << "Brand:\t" << this->_brand << endl;
    cout << "Color:\t" << this->_color << endl;
    cout << "Fee:\t" << this->_fee << endl;
}