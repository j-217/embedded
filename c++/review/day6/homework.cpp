/*
 * @Author: Ru_j
 * @Date: 2020-02-10 17:44:47
 * @LastEditors  : Ru_j
 * @LastEditTime : 2020-02-10 20:34:37
 * @Description:
 * @        1. MY_POKER 定义扑克类，私有属性color，point，创建54张牌存入数组中 (构造函数重载);
 * @        2. MY_LINKLIST 定义一个链表类，实现简单的增、删、改、查功能;
 */
#include <iostream>
#include <string>

using namespace std;

#if MY_POKER
const string g_poker_type[4] = {"S", "H", "C", "D"};                // S:spade, H:heart, C:club, D:diamond
const string g_poker_point[54] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

class Poker {
private:
    string _color;
    string _point;
public:
    Poker(string color, string point)
        :_color(color), _point(point)
        {}
    Poker() {
        _color = "";
        _point = "Joker";
    }
    ~Poker() {}
    void show_card() {
        if (_color != "") {
            cout << _color << "-" << _point << " ";
        } else {
            cout << _point << " ";
        }
    }
};
#endif

#if MY_LINKLIST
class Linklist {
private:
    class Node {
    public:
        int _data;
        Node *_p_next;

        Node(int data = 0, Node *p_next = nullptr)
            : _data(data), _p_next(p_next) {}
        ~Node() {};
    };
    Node *_p_head;
    size_t _size;
public:
    Linklist() {
        _p_head = new Node;
        _size = 0;
    }
    ~Linklist() {
        if (_p_head != nullptr) {
            this->destory_link();
        }
    }

    bool insert_data(int data, size_t pos = 0) {
        if (pos > _size) {
            return false;
        }

        Node *p_tmp = _p_head;
        Node *p_new = new Node(data);

        for (int i = 0; i < pos; ++i) {
            p_tmp = p_tmp->_p_next;
        }

        p_new->_p_next = p_tmp->_p_next;
        p_tmp->_p_next = p_new;
        ++_size;

        return true;
    }

    bool delete_data(int data) {
        if (_size == 0) {
            return false;
        }

        Node *p_tmp = _p_head->_p_next;
        Node *p_prev = _p_head;

        while (p_tmp != nullptr) {
            if (p_tmp->_data == data) {
                p_prev->_p_next = p_tmp->_p_next;
                delete p_tmp;
                --_size;
                return true;
            }
            p_prev = p_tmp;
            p_tmp = p_tmp->_p_next;
        }

        return false;
    }

    bool update_data(int data, size_t pos) {
        if (pos > _size) {
            return false;
        }

        Node *p_tmp = _p_head;

        for (int i = 0; i < pos; ++i) {
            p_tmp = p_tmp->_p_next;
        }

        p_tmp->_data = data;

        return true;
    }

    int search_data(int data) {
        if (_size == 0) {
            return -1;
        }

        Node *p_tmp = _p_head;
        int i = 0;
        while (p_tmp != nullptr) {
            if (p_tmp->_data == data) {
                return i;
            }

            p_tmp = p_tmp->_p_next;
            ++i;
        }

        return -1;
    }

    void destory_link() {
        Node *p_del = _p_head->_p_next;
        while (p_del != nullptr) {
            _p_head->_p_next = p_del->_p_next;
            delete p_del;
            p_del = _p_head->_p_next;
        }

        delete _p_head;
        _p_head = nullptr;
    }

    void show_link() {
        if (_p_head == nullptr) {
            return ;
        }

        Node *p_tmp = _p_head->_p_next;
        while (p_tmp != nullptr) {
            cout << p_tmp->_data << " ";
            p_tmp = p_tmp->_p_next;
        }
        cout << endl;
    }
};
#endif


int main() {
#if MY_POKER
    Poker my_cards[54];
    int i = 0;
    for (int t = 0; t < 4; ++t) {                   // input cards
        for (int p = 0; p < 13; ++p) {
            my_cards[i++] = Poker(g_poker_type[t], g_poker_point[p]);
        }
    }

    for (int i = 0; i < 54; ++i) {                  // display my_cards
        my_cards[i].show_card();

        if (i % 13 == 12 && i != 0 || i == 53) {
            cout << endl;
        }
    }
#endif

#if MY_LINKLIST
    Linklist my_link;
    for (int i = 1; i <= 5; ++i) {                  // insert data at the default position
        my_link.insert_data(i);
    }
    my_link.show_link();
    my_link.insert_data(10, 5);                     // insert data at the specified location
    my_link.show_link();
    my_link.delete_data(4);
    my_link.show_link();
    my_link.update_data(100, 5);
    my_link.show_link();
    my_link.destory_link();
    my_link.show_link();
#endif

    return 0;
}