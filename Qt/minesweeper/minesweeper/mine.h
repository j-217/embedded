#ifndef MINE_H
#define MINE_H

#include <QObject>
#include <QPushButton>
#include "point.h"

class Mine : public QPushButton
{
    Q_OBJECT
public:
    Mine(Point position, QWidget *parent);
    ~Mine();

    void set_mine(bool flg) {_has_mine = flg;}
    void set_flag(bool flg) {_has_flag = flg;}
    void set_opened(bool flg) {_is_opened = flg;}

    Point get_position() {return _position;}
    bool get_has_mine() {return _has_mine;}
    bool get_has_flag() {return _has_flag;}
    bool get_opened() {return _is_opened;}

signals:
    void sig_send_position(Point _position);
    void sig_right_click(Point _position);

private:
    Point _position;
    bool _has_mine;
    bool _has_flag;
    bool _is_opened;
};

#endif // MINE_H
