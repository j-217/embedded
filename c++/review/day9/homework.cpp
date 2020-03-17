/*
 * @Author: Ru_j
 * @Date: 2020-02-13 17:38:51
 * @LastEditors  : Ru_j
 * @LastEditTime : 2020-02-13 19:33:17
 */
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

#if ANIMAL
class Animal {
private:
    string _type;
    string _color;
    size_t _legs;
public:
    Animal() = default;
    Animal(string type, string color, size_t legs)
        :_type(type), _color(color), _legs(legs) {};
    ~Animal() = default;
    void set_type(string type) {
        _type = type;
    }
    string get_type() {
        return _type;
    }
    void set_color(string color) {
        _color = color;
    }
    string get_color() {
        return _color;
    }
    void set_legs(size_t legs) {
        _legs = legs;
    }
    size_t get_legs() {
        return _legs;
    }
    void eat() {
        cout << "a " << _color << " " << _type << " is eating" << endl;
    }
    void move() {
        cout << "a " << _color << " " << _type << " is roaming" << endl;
    }
};

class Sheep: public Animal {
public:
    Sheep(string type, string color, size_t legs)
        :Animal(type, color, legs) {}
    ~Sheep() = default;
    void call() {
        cout << get_type() <<" baa-baa" << endl;
    }
    void show() {
        cout << "a " << get_legs() << " legs " << get_color() << " " << get_type() << endl;
    }
};

class Tiger: public Animal {
public:
    Tiger(string type, string color, size_t legs)
        :Animal(type, color, legs) {}
    ~Tiger() = default;
    void run() {
        cout << get_type() << "is running" << endl;
    }
    void show() {
        cout << "a " << get_legs() << " legs " << get_color() << " " << get_type() << endl;
    }
};
#endif

#if COMPANY
class Developer {
protected:
    string _name;
public:
    Developer(string name): _name(name) {};
    ~Developer() = default;
    string get_name() {
        return _name;
    }
    virtual void develop() = 0;
};

class Master:public Developer {
public:
    Master(string name): Developer(name) {};
    ~Master() = default;
    void develop() override {
        cout << "Talk is cheap, show me the code." << ends;
    }
};

class Newbie: public Developer {
public:
    Newbie(string name): Developer(name) {};
    ~Newbie() = default;
    void develop() override {
        cout << "Say 'Hello World' in C, Cpp, Java, Python." << ends;
    }
};

class Company {
private:
    Developer *_employee;
public:
    Company(): _employee(nullptr) {};
    ~Company() {
        if (_employee != nullptr) {
            delete _employee;
            _employee = nullptr;
        }
    }
    Developer *recruit(string name = "new employee") {
        srand(time(nullptr));
        _employee = rand() % 2 ? dynamic_cast<Developer *>(new Master(name)) : dynamic_cast<Developer *>(new Newbie(name));
        return _employee;
    }
    void work(Developer *employee) {
        cout << employee->get_name() << ": ";
        employee->develop();
        cout << endl;
    }
};
#endif

int main() {
#if ANIMAL
    Sheep my_sheep("goat", "white", 4);
    my_sheep.show();
    my_sheep.call();
    my_sheep.eat();
    my_sheep.move();

    cout << "---------" << endl;
    Tiger my_tiger("manchurian tiger", "white", 4);
    my_tiger.show();
    my_tiger.run();
    my_sheep.eat();
    my_sheep.move();
#endif

#if COMPANY
    Company my_cmp;
    my_cmp.work(my_cmp.recruit("XiaoWang"));
#endif

    return 0;
}