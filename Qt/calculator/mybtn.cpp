#include "mybtn.h"

myBtn::myBtn(QString txt,myBtn::FLG flg, QWidget *parent, int x, int y, int w, int h)
    :QPushButton(parent), _txt(txt), _flg(flg)
{
    this->setText(txt);
    this->setGeometry(x, y, w, h);
    this->setStyleSheet(QString("QPushButton{font-family: Adobe Gothic Std B;"
                                "font-size: 20px;"
                                "font-weight: 700}"));
    connect(this, &QPushButton::clicked, this, [=](){
        emit sig_snd_txt(_txt, _flg);
    });
}
