/*
 * @Author: Ru_j
 * @Date: 2020-02-06 16:02:49
 * @LastEditors  : Ru_j
 * @LastEditTime : 2020-02-06 20:35:41
 * @Description:
 * @        1. MY_SWAP 使用引用类型交换两个变量的值
 * @        2. MY_STUDENTS input_data, 输入学生姓名，学号自增不重复; 将信息加入“数据库”中
 * @                       search_data, 输入学生姓名，从“数据库”查找相应信息，学生姓名可重复
 */
#include <iostream>
#include <string>
#include <map>

using namespace std;

#if MY_SWAP
template<typename T>
void my_swap(T& x, T& y) {
    T tmp = x;
    x = y;
    y = tmp;

    return ;
}
#endif

#if MY_STUDENTS
void input_data(map<size_t, string> *students) {
    if (students == nullptr) {
        return ;
    }

    size_t stu_id = distance(students->begin(), students->end());
    string stu_name = "";

    while (true) {
        cout << "Input student's NAME (quit for exit): ";
        cin >> stu_name;
        if (stu_name == "quit") {
            break;
        }

        ++stu_id;
        students->insert(make_pair(stu_id, stu_name));
    }

    return ;
}

void search_data(map<size_t, string> *students) {
    if (students == nullptr) {
        return ;
    }

    string stu_name = "";
    bool flg_found = false;

    while (true) {
        cout << "Input a NAME that you want to find out (quit for exit): ";
        cin >> stu_name;
        if (stu_name == "quit") {
            break;
        }

        for (map<size_t, string>::iterator it = students->begin(); it != students->end(); ++it) {
            if (it->second == stu_name) {
                cout << "ID: " << it->first << " ";
                cout << "NAME: " << it->second << endl;

                flg_found = true;
            }
        }
        if (!flg_found) {
            cout << "NOT FOUND" << endl;
        }

        flg_found = false;
    }

    return ;
}
#endif

int main() {
#if MY_SWAP
    int num_1 = 5,
        num_2 = 10;
    my_swap<int>(num_1, num_2);

    cout << "num_1: " << num_1 << " ";
    cout << "num_2: " << num_2 << endl;
#endif

#if MY_STUDENTS
    map<size_t, string> *students = new map<size_t, string>;

    input_data(students);
    search_data(students);

    delete students;
#endif
    return 0;
}