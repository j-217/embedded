/*
 * @Author: Ru_j
 * @Date: 2020-02-15 17:46:08
 * @LastEditors  : Ru_j
 * @LastEditTime : 2020-02-15 17:57:35
 * @Description:
 * @        1. DLINK
 * @            a.定义链表类Link
 * @            b.私有内部结构体Node{T data, Node* pNext, Node* pFront}
 * @            c.私有成员指针pHead  pTail
 * @            d.公有函数add(T data)向尾部添加元素
 * @            e.公有函数重载[] 返回 指定位置的数据,并可以通过[]修改对应位置的数据
 * @            f.公有函数erase(index)删除index位置的元素
 * @            g.公有函数erase(int start, T data)从start位置开始查找删除链表中data的元素
 * @            h.公有函数size()返回链表的长度
 * @        2. MANAGE_SYS
 * @            a.Employee类:
 * @                    成员变量(私有): 编号id、姓名name、性别gender、出生日期birthday、职位position和基本工资basicSalary, 出生日期使用自定义的Date（日期）类;
 * @                    公有函数计算工资virtual float getSalary();
 * @            b.Date类:
 * @                    成员变量：年year、月month、日date
 * @                    成员函数：SetYear(int year)、SetMonth(int month)、SetDay(int day)、GetYear()、GetMonth()、GetDay()等多个构造函数;
 * @                    由Employee类派生销售员工Salasman类，Salasman类包含两个新数据成员：销售额sales和提成比例commrate。
 * @                    由Salasman类派生出销售经理Salamanager类。Salasmanager类包含新数据成员：职务工资jobSalary。
 * @            c.月工资计算办法：
 * @                    一般员工月薪=基本工资 销售员工月薪=基本工资+销售额*提成率
 * @                    销售经理月薪=基本工资+职务工资+销售额*提成率
 * @            d.基本功能如下，需将以下功能转化为不同的成员函数：
 * @                    各类人员信息的录入（包括基本工资等）；
 * @                    各类人员信息的显示（包括月工资）；name 工资
 * @                    用对象数组保存已输入的人员对象；
 * @                    可以修改人员的基本信息，如：姓名、职位等；
 * @                    可以通过编号或姓名进行人员查询。
 */
#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

#if DLINK
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
#endif

#if MANAGE_SYS
class Date {
friend ostream &operator<<(ostream &os, const Date &d);
private:
    uint _year;
    uint _month;
    uint _day;
public:
    Date() {
        time_t now = time(nullptr);
        tm *p_tm = localtime(&now);
        _year = p_tm->tm_year + 1900;
        _month = p_tm->tm_mon + 1;
        _day = p_tm->tm_mday;
    }
    Date(const uint &year, const uint &month, const uint &day)
        :_year(year), _month(month), _day(day) {}
    ~Date() = default;

    void set_year(const uint &year) { _year = year; }
    const uint &get_year() const {return _year;}

    void set_month(const uint &month) { _month = month; }
    const uint &get_month() const {return _month;}

    void set_day(const uint &day) { _day = day; }
    const uint &get_day() const {return _day;}
};
ostream &operator<<(ostream &os, const Date &d) {
    os << setw(4) << setfill('0') << d._year << "/";
    os << setw(2) << setfill('0') << d._month << "/";
    os << setw(2) << setfill('0') << d._day;
    return os;
}

class Employee {
private:
    static uint auto_id;
protected:
    bool _gender;
    uint _id;
    float _base_salary;
    string _name;
    string _position;
    Date _birthday;
    virtual float get_salary() const { return _base_salary; }
public:
    Employee(const string &name, const uint &year, const uint &month, const uint &day,
        const bool &gender = true, const float &base_salary = 2000.0f, const string &position = "A")
            :_gender(gender), _base_salary(base_salary), _name(name),
            _position(position), _birthday(year, month, day)
        {
            _id = ++auto_id;
            _position = "Common-" + position;
        }
    Employee(const string &name, const bool &gender = true, const float &base_salary = 2000.0f, const string &position = "A")
            :_gender(gender), _base_salary(base_salary), _name(name),
            _position(position), _birthday()
        {
            _id = ++auto_id;
            _position = "Common-" + position;
        }
    ~Employee() = default;

    virtual void show_info() const {
        cout << "-----------------------" << endl;
        cout << "ID:\t\t" << setw(6) << setfill('0') << _id << endl;
        cout << "Name:\t\t" << _name << endl;
        cout << "Gender:\t\t" << (_gender ? "Male" : "Female") << endl;
        cout << "Birth:\t\t" << _birthday << endl;
        cout << "Position:\t" << _position << endl;
        cout << "Salary:\t\t" << get_salary() << endl;
        cout << "-----------------------" << endl;
    }

    // getter
    const string &get_name() const { return _name; }
    const uint &get_id() const { return _id; }

    // setter
    void set_name(const string &new_name) { _name = new_name; }
    void set_gender(const bool &new_gender) { _gender = new_gender; }
    void set_base_salary(const float &new_b_sal) { _base_salary = new_b_sal; }
    void set_position(const string &new_pos) {
        _position.replace(_position.find('-') + 1, new_pos.size(), new_pos);
    }
    void set_birthday(const uint &year, const uint &month, const uint &day) {
        _birthday.set_year(year);
        _birthday.set_month(month);
        _birthday.set_day(day);
    }

    Employee *find(uint id) {
        if (id == _id)
            return this;
        return nullptr;
    }

    Employee *find(string name) {
        if (name == _name)
            return this;
        return nullptr;
    }
};
uint Employee::auto_id = 0;

class Salesman: public Employee {
protected:
    float _sales;
    float _rate;
    float get_salary() const {
        return _base_salary + _sales * _rate;
    }
public:
    Salesman(const string &name, const uint &year, const uint &month, const uint &day,
        const bool &gender = true, const float &sales = 300000.0f, const float &rate = 0.008f,
        const float &base_salary = 1500.0f, const string &position = "A")
        :Employee(name, year, month, day, gender, base_salary, position),
        _sales(sales), _rate(rate) {
            _position = "Salesman-" + position;
        }
    ~Salesman() = default;
    void set_sales(const float &sales, const float &rate) {
        _sales = sales;
        _rate = rate;
    }
};

class Salesmanager:public Salesman {
protected:
    float _job_salary;
    float get_salary() const {
        return _base_salary + _job_salary + _sales * _rate;
    }
public:
    Salesmanager(const string &name, const uint &year, const uint &month, const uint &day,
        const bool &gender = true, const float &sales = 3000000.0f, const float &rate = 0.003f,
        const float &base_salary = 3000.0f, const float &job_salary = 1000.0f, const string &position = "A")
        :Salesman(name, year, month, day, gender, sales, rate, base_salary, position),
        _job_salary(job_salary) {
            _position = "Sales Manage-" + position;
        }
    ~Salesmanager() = default;
    void set_job_salary(const float &new_j_sal) { _job_salary = new_j_sal; }
};
#endif

int main() {
#if DLINK
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
#endif

#if MANAGE_SYS
    vector<Employee *> employees;

    employees.push_back(new Salesmanager("One", 1980, 7, 7));                   // set data
    employees.push_back(new Salesman("Two", 1992, 10, 11));
    employees.push_back(new Employee("Three", 1995, 3, 3));
    employees.push_back(new Employee("Four"));

    employees[2]->set_name("Change_Three");                                     // change employee data
    employees[2]->set_position("C");
    employees[2]->set_birthday(1998, 11, 11);

    dynamic_cast<Salesman *>(employees[1])->set_sales(444444.4f, 1.0f);         // change salesman data
    employees[1]->show_info();

    for (const auto &item: employees) {                                         // use find
        Employee *ret = nullptr;
        if((ret = item->find("Three")) != nullptr) {
            ret->show_info();
        }
    }

    for (auto &item: employees) {                                               // free memonry & clear vector
        delete item;
        item = nullptr;
    }
    employees.clear();
#endif

    return 0;
}