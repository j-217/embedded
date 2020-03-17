#ifndef MYBTN_H
#define MYBTN_H

#include <QPushButton>
#include <QString>

class myBtn : public QPushButton
{
    Q_OBJECT
public:
    enum FLG {
        NUM,
        PLS,
        SUB,
        MUL,
        DIV,
        MOD,
        EQL,
        BCK,                    // backspace
        CLR,                    // clear
        POS_NEG,                // positive or negative
        PNT                     // point
    };
    explicit myBtn(QString txt, myBtn::FLG flg, QWidget *parent = nullptr,
                   int x = 0, int y = 0,
                   int w = 75, int h = 42);

signals:
    void sig_snd_txt(QString txt, myBtn::FLG flg);

public slots:

private:
    QString _txt;
    myBtn::FLG _flg;
};

#endif // MYBTN_H
