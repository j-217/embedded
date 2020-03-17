/*
 * @Author: Ru_j
 * @Date: 2020-02-07 17:11:07
 * @LastEditors  : Ru_j
 * @LastEditTime : 2020-02-07 18:45:27
 * @Description:
 * @        1. MY_DOG 定义Dog类，有成员变量name，有成员函数setName起名，sleep睡觉，eat吃饭
 * @        2. MY_STACK 自定义一个类实现栈结构，有出栈（pop）和入栈（push）功能，（top）获得栈顶元素，栈空间可自行增长
 */
#include <iostream>
#include <string>

using namespace std;

#if MY_DOG
class Dog {
private:
    string _name;
public:
    Dog(string name = "WangWang");
    ~Dog() = default;
    void set_name(string name);
    void sleep();
    void eat();
};

Dog::Dog(string name)
    :_name{name} {}

void Dog::set_name(string name) {
    this->_name = name;
    return ;
}

void Dog::sleep() {
    cout << this->_name << " is sleeping" << endl;
    return ;
}

void Dog::eat() {
    cout << this->_name << " is eating" << endl;
    return ;
}
#endif

#if MY_STACK
template <typename T>
class Stack {
private:
    size_t _size;
    size_t _top;
    T *_arr;
    bool _is_empty();
    bool _is_full();
    void _extend_arr();
public:
    Stack();
    ~Stack();
    void push(T new_data);
    T pop();
    T top();
};

template <typename T>
Stack<T>::Stack() {
    _size = 10;
    _top = 0;
    _arr = new T[_size]();
}

template <typename T>
Stack<T>::~Stack() {
    delete[] _arr;
    _arr = nullptr;
}

template <typename T>
bool Stack<T>::_is_empty() {
    return _top == 0;
}

template <typename T>
bool Stack<T>::_is_full() {
    return _top == _size - 1;
}

template <typename T>
void Stack<T>::_extend_arr() {
    T *new_arr = new T[_size * 2]();
    for (int i = 0; i < _size; ++i) {
        new_arr[i] = _arr[i];
    }

    delete[] _arr;
    _arr = new_arr;
    _size *= 2;
    return ;
}

template <typename T>
void Stack<T>::push(T new_data) {
    if (this->_is_full()) {
        this->_extend_arr();
    }

    _arr[_top] = new_data;
    ++_top;
    return ;
}

template <typename T>
T Stack<T>::pop() {
    if (this->_is_empty()) {
        string e_msg = "ERROR: This stack is empty";
        throw e_msg;
    }

    return _arr[--_top];
}

template <typename T>
T Stack<T>::top() {
    if (this->_is_empty()) {
        string e_msg = "ERROR: This stack is empty";
        throw e_msg;
    }

    return _arr[_top - 1];
}

#endif

int main() {
#if MY_DOG
    Dog *my_dog = new Dog;
    my_dog->set_name("Big-Yellow");
    my_dog->eat();
    my_dog->sleep();

    delete my_dog;
    my_dog = nullptr;
#endif

#if MY_STACK
    string arr[5] = {"one", "two", "three", "four", "five"};
    Stack<string> my_stack;

    try {                                                           // test empty top
        cout << "Top of stack is: " << my_stack.top() << endl;
    } catch (string e) {
        cout << e << endl;
    }

    for (int i = 0; i < sizeof(arr) / sizeof(string); ++i) {
        my_stack.push(arr[i]);
    }

    try {
        cout << "Top of stack is: " << my_stack.top() << endl;
    } catch (string e) {
        cout << e << endl;
    }

    try {                                                           // test pop data when stack is empty
        for (int i = 0; i < 10; ++i) {
            cout << my_stack.pop() << endl;
        }
    } catch (string e) {
        cout << e << endl;
    }
#endif

    return 0;
}