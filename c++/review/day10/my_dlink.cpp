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
    };
    Node *_p_head,
         *_p_tail;
public:
    DLink();
    ~DLink();
    T &operator[](size_t pos);
    DLink &operator=(const DLink &ohter);
    void add(const T &data);
    T erase(size_t pos);
    T erase(size_t pos, const T &data);
    size_t dl_size() const;
    void show() const;
    void destory();
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
    if (_p_head != nullptr && _p_tail != nullptr) {
        this->destory();
    }
}

template <typename T>
T &DLink<T>::operator[](size_t pos) {
    if (pos >= this->dl_size()) {
        throw out_of_range("");
    }

    Node *tmp = _p_head->_p_next;
    while (pos) {
        tmp = tmp->_p_next;
        --pos;
    }

    return tmp->_data;
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
        tmp = tmp->_p_next;
    }

    return cnt;
}

template <typename T>
void DLink<T>::show() const {
    if (dl_size() == 0) {
        return ;
    }
    Node *tmp = _p_head->_p_next;
    while (tmp->_p_next != nullptr) {
        if (tmp != _p_head->_p_next) {
            cout << "->";
        }
        cout << tmp->_data;
        tmp = tmp->_p_next;
    }
    cout << endl;
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

template <typename T>
T DLink<T>::erase(size_t pos, const T &data) {
    if (pos >= this->dl_size()) {
        throw out_of_range("");
    }

    Node *del = _p_head->_p_next;
    while (pos != 0) {
        del = del->_p_next;
        --pos;
    }

    while (del->_p_next != nullptr) {
        if (del->_data == data) {
            erase(0);
        }
        del = del->_p_next;
    }

    throw "Not Found";
}

template <typename T>
void DLink<T>::destory() {
    Node *del = _p_head->_p_next;
    while (del->_p_next != nullptr) {
        _p_head->_p_next = del->_p_next;
        delete del;
        del = _p_head->_p_next;
    }
    delete _p_head;
    _p_head = nullptr;
    delete _p_tail;
    _p_tail = nullptr;
};

int main() {
    DLink<int> my_dl;

    for (int i = 5; i <= 30; i += 5) {                      // add data
        my_dl.add(i);
    }
    my_dl.show();
    try {
        cout << my_dl.erase(0) << endl;                     // erase data in position
        cout << my_dl.erase(2, 50) << endl;                 // erase data from a position
    } catch (const char *e) {
        cout << e << endl;
    }
    my_dl.show();

    cout << my_dl[3] << endl;                               // test operator[]
    my_dl[3] = 100;
    cout << my_dl[3] << endl;

    return 0;
}