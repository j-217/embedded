#include "device.hpp"

class PC : public Device
{
    protected:
        string _type_graphic_card;
    public:
        PC(string owner = "Jerry", string brand = "Lenovo", string color = "grey", string t_grph_crd = "GT740M");
        void gaming();
        void coding();
        void desc();
};

PC::PC(string owner, string brand, string color, string t_grph_crd)
    :Device{owner, brand, color}, _type_graphic_card{t_grph_crd}
{

}

void PC::gaming()
{
    printf("%s playing game in his %s %s PC\n", 
        this->_owner.c_str(),
        this->_color.c_str(),
        this->_brand.c_str()
    );
}

void PC::coding()
{
    printf("%s workding hard with his %s %s PC, for his graphic card %s is a piece of crap\n", 
        this->_owner.c_str(),
        this->_color.c_str(),
        this->_brand.c_str(),
        this->_type_graphic_card.c_str()
    );
}

void PC::desc()
{
    cout << "-----Infos-----" << endl;
    cout << "Owner:\t" << this->_owner << endl;
    cout << "Brand:\t" << this->_brand << endl;
    cout << "Color:\t" << this->_color << endl;
    cout << "Graphic Card:\t" << this->_type_graphic_card << endl;
}