#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

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

int main() {
    vector<Employee *> employees;
    // set data
    employees.push_back(new Salesmanager("One", 1980, 7, 7));
    employees.push_back(new Salesman("Two", 1992, 10, 11));
    employees.push_back(new Employee("Three", 1995, 3, 3));
    employees.push_back(new Employee("Four"));

    // change employee data
    employees[2]->set_name("Change_Three");
    employees[2]->set_position("C");
    employees[2]->set_birthday(1998, 11, 11);

    // change salesman data
    dynamic_cast<Salesman *>(employees[1])->set_sales(444444.4f, 1.0f);
    employees[1]->show_info();

    // use find
    for (const auto &item: employees) {
        Employee *ret = nullptr;
        if((ret = item->find("Three")) != nullptr) {
            ret->show_info();
        }
    }

    // free memonry & clear vector
    for (auto &item: employees) {
        delete item;
        item = nullptr;
    }
    employees.clear();

    return 0;
}