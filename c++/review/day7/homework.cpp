/*
 * @Author: Ru_j
 * @Date: 2020-02-11 17:33:56
 * @LastEditors  : Ru_j
 * @LastEditTime : 2020-02-11 18:26:39
 */
#include <iostream>
#include <cstring>

using namespace std;

class Book {
private:
    char *_title;
    char *_author;
public:
    Book();
    Book(const char *title, const char *author);
    ~Book();
    void show();
};

Book::Book(): _title(nullptr), _author(nullptr) {               // do nothing

}

Book::Book(const char *title, const char *author) {
    if (title == nullptr || author == nullptr) {
        return ;
    }

    this->_title = new char[strlen(title) + 1]();               // allocate memory space and initialize
    this->_author = new char[strlen(author) + 1]();

    strcpy(_title, title);
    strcpy(_author, author);
}

Book::~Book() {
    if (_title == nullptr || _author == nullptr) {
        return ;
    }

    delete[] _title;
    delete[] _author;
}

void Book::show() {
    if (_title == nullptr || _author == nullptr) {
        return ;
    }

    cout << "Title: " << _title << "\t";
    cout << "Author: " << _author << endl;
}

int main() {
    Book b1("C++ Primer", "Stanley B. Lippman");
    Book b2("The Annotated STL Sources", "Hou Jie");
    Book b3("The C Programming Language", "Dennis M. Ritchie");

    b1.show();
    b2.show();
    b3.show();

    return 0;
}