#include <iostream>

using namespace std;

template <typename T>
class DLink {
private:
    class Node {
    public:
        T _data;
        Node *_p_prev,
             *_p_next;
        Node(T data = 0)
            :_data(data), _p_prev(nullptr), _p_next(nullptr){}
        ~Node() = default;
        Node *operator++() {
            _data = _p_next->_data;
            _p_prev = _p_next->_p_prev;
            _p_next = _p_next->_p_next;
            return this;
        }
        // Node *operator++() {
        //     this = this->_p_next;
        //     return this;
        // }
        Node &operator++(int) {
            Node tmp = this;
            this = this->_p_next;
            return tmp;
        }
    };
    Node *_p_head,
         *_p_tail;
public:
    DLink();
    ~DLink();
    T operator[](const size_t &pos);
    DLink &operator=(const DLink &ohter);
    void add(const T &data);
    T erase(size_t pos);
    T erase(size_t pos, const T &data);
    size_t dl_size() const;
    void show() const;
};

template <typename T>
DLink<T>::DLink() {
    _p_head = new Node;
    _p_tail = new Node;
    _p_head->_p_next = _p_tail;
    _p_tail->_p_prev = _p_head;
}

template <typename T>
DLink<T>::~DLink() {

}

template <typename T>
void DLink<T>::add(const T &data) {
    Node *new_node = new Node(data);
    new_node->_p_next = _p_tail;
    new_node->_p_prev = _p_tail->_p_prev;
    new_node->_p_prev->_p_next = new_node;
    _p_tail->_p_prev = new_node;
}

template <typename T>
size_t DLink<T>::dl_size() const {
    size_t cnt = 0;
    DLink<T>::Node *tmp = _p_head->_p_next;
    while (tmp->_p_next != nullptr) {
        ++cnt;
        // tmp = tmp->_p_next;
        tmp->operator++();
        // ++tmp;
    }

    return cnt;
}

template <typename T>
void DLink<T>::show() const {
    Node *tmp = _p_head->_p_next;
    while (tmp->_p_next != nullptr) {
        cout << tmp->_data << endl;
        tmp = tmp->_p_next;
    }
}

template <typename T>
T DLink<T>::erase(size_t pos) {
    if (pos >= this->dl_size()) {
        throw out_of_range("");
    }

    Node *del = _p_head->_p_next;
    while (pos != 0) {
        del = del->_p_next;
        --pos;
    }

    Node *tmp = del->_p_prev;
    tmp->_p_next = del->_p_next;
    del->_p_next->_p_prev = tmp;
    T data = del->_data;
    delete del;

    return data;
}

int main() {
    DLink<int> my_dl;
    my_dl.add(5);
    my_dl.add(10);
    my_dl.add(15);
    my_dl.show();
    // cout << my_dl.erase(2) << endl;
    // my_dl.show();
    cout << my_dl.dl_size() << endl;

    return 0;
}