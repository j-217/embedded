/*
 * @Author: Ru_j
 * @Date: 2020-02-12 17:19:31
 * @LastEditors  : Ru_j
 * @LastEditTime : 2020-02-12 19:46:10
 * @Description:
 * @        1. STUDENT_TEACHER:
 * @            a.有个学生类student 包括私有成员：姓名 成绩; student 构造函数对成员赋值
 * @            b.设计一个友元类teacher
 * @            c.teacher类中包含私有成员数组 student s[5] 构造函数对数组元素赋值
 * @            d.teacher类对学生数组进行排序 公有成员函数 sort() 降序
 * @            e.teacher类输出成绩对应等级 >=90 优 80-89 良 70-79中 60-69及格 <60不及格 公有函数show()
 * @        2. TRIANGLE: 设计一个三角形类Triange 包含三角形三条边长的私有数据成员 另有一个重载运算符'+'  以实现求两个三角形周长之和  注意：两个三角形对象相加
 * @        3. STUDENT: 设计一个学生类 包括姓名和三门成绩(C++ C linux) 利用重载运算符'+=' 将所有学生成绩的和汇总到一个学生对象中
 * @        4. RTIME: 在Time类中设计如下
 * @            a. 私有成员h m s
 * @            b. 重载后缀++ 让时间变成下一秒
 * @            c. show函数显示时间
 */
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

#if STUDENT_TEACHER
class Teacher;
class Student {
friend class Teacher;
private:
    string _name;
    size_t _score;
public:
    Student(string name, size_t score) {
        if (score > 100 || name == "") {
            throw "ERROR: Invalid arguments";
        }

        _name = name;
        _score = score;
    }
    ~Student() = default;
};

class Teacher {
private:
    vector<Student> _students;
    string get_grade(const Student &stu) {
        if (stu._score >= 90) {
            return "A";
        } else if (stu._score >= 80) {
            return "B";
        } else if (stu._score >= 70) {
            return "C";
        } else if (stu._score >= 60) {
            return "D";
        } else {
            return "E";
        }
    }
public:
    Teacher(Student *arr, size_t size) {
        for (int i = 0; i < size; ++i) {
            _students.push_back(arr[i]);
        }
    }
    ~Teacher() = default;
    void resort() {
        vector<Student>::iterator max_index;
        for (vector<Student>::iterator it1 = _students.begin(); it1 != _students.end(); ++it1) {
            max_index = it1;
            for (vector<Student>::iterator it2 = it1 + 1; it2 != _students.end(); ++it2) {
                if (it2->_score > max_index->_score) {
                    max_index = it2;
                }
            }
            if (max_index != it1) {
                swap(*max_index, *it1);
            }
        }
    }
    void show() {
        for (auto &item: _students) {
            cout << "name: " << item._name << "\t";
            cout << "score: " << item._score << "\t";
            cout << "grade: " << get_grade(item) << endl;
        }
    }
};
#endif

#if STUDENT
class Student {
private:
    string _name;
    size_t _score_c;
    size_t _score_cpp;
    size_t _score_linux;
public:
    Student(string name, size_t s_c, size_t s_cpp, size_t s_linux)
        :_name(name), _score_c(s_c), _score_cpp(s_cpp), _score_linux(s_linux) {}
    ~Student() = default;
    Student &operator+=(const Student &other) {
        _score_c += other._score_c;
        _score_cpp += other._score_cpp;
        _score_linux += other._score_linux;
        return *this;
    }
    void show() {
        cout << "name: " << _name << endl;
        cout << "C: " << _score_c << "\t";
        cout << "C++: " << _score_cpp << "\t";
        cout << "Linux: " << _score_linux << endl;
    }
};
#endif

#if TRIANGLE
class Triangle {
private:
    size_t _line_1,
           _line_2,
           _line_3;
public:
    Triangle(size_t line_1, size_t line_2, size_t line_3) {
        if (line_1 + line_2 <= line_3
            || line_1 + line_3 <= line_2
            || line_2 + line_3 <= line_1
        ) {
            throw "ERROR: Invalid arguments";
        }
        _line_1 = line_1;
        _line_2 = line_2;
        _line_3 = line_3;
    }
    ~Triangle() = default;

    size_t operator+(const Triangle &other) {
        return _line_1 + _line_2 + _line_3 + other._line_1 + other._line_2 + other._line_3;
    }
};
#endif

#if RTIME
class RTime {
private:
    size_t _h,
           _m,
           _s;
public:
    RTime(const size_t &h = 0, const size_t &m = 0, const size_t &s = 0) {
        if (h >= 24 || m >= 60 || s >= 60) {
            throw "ERROR: Invalid arguments";
        }
        _h = h;
        _m = m;
        _s = s;
    }
    ~RTime() = default;
    void show() {
        cout << setw(2) << setfill('0') << _h << ":";
        cout << setw(2) << setfill('0') << _m << ":";
        cout << setw(2) << setfill('0') << _s << endl;
    }
    void operator++(int) {
        (++_s < 60) ? : (_s %= 60, ++_m, _m < 60) ? : (_m %= 60, ++_h, _h < 24) ? : (_h %= 24);
    }
};
#endif

int main() {
#if STUDENT_TEACHER
    const size_t size = 5;                          // array size;
    try {
        Student students[size] = {
            Student("one", 50),
            Student("two", 90),
            Student("three", 70),
            Student("four", 20),
            Student("five", 100)
        };

        Teacher my_teacher(students, size);
        cout << "----- before sort -----" << endl;
        my_teacher.show();
        my_teacher.resort();
        cout << "----- after sort -----" << endl;
        my_teacher.show();
    } catch (const char *e) {
        cout << e << endl;
    }
#endif

#if TRIANGLE
    try {
        Triangle tri_1(3, 4, 10);
        Triangle tri_2(10, 15, 20);
        cout << "sum of perimeter: " << tri_1 + tri_2 << endl;
    } catch (const char *e) {
        cout << e << endl;
    }
#endif

#if STUDENT
    Student stu_1("one", 10, 10, 10);
    Student stu_2("two", 20, 20, 20);
    Student stu_3("three", 30, 30, 30);
    cout << "----- before sum -----" << endl;
    stu_1.show();
    stu_1 += (stu_2 += stu_3);
    cout << "----- after sum -----" << endl;
    stu_1.show();
#endif

#if RTIME
    RTime my_time(23, 59, 59);
    my_time.show();
    my_time++;
    my_time.show();
#endif

    return 0;
}