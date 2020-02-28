#include "mine.h"
#include <QDebug>

Mine::Mine(Point position, QWidget *parent)
    : QPushButton(parent), _position(position)
{
    _has_mine = false;
    _has_flag = false;
    _is_opened = false;

    this->setContextMenuPolicy(Qt::CustomContextMenu);              // 开启右键菜单使能

    connect(this, &QPushButton::clicked, [=](){                     // 左键点击
        emit sig_send_position(_position);
    });

    connect(this, &QPushButton::customContextMenuRequested, [=](){      // 右键点击
        emit sig_right_click(_position);
    });
}

Mine::~Mine()
{

}

