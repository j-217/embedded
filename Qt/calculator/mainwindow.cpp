#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _show_str = "0";
    _buf_str = "0";
    _flg_pos_neg = true;
    _flg_pnt = false;
    _flg_input_new = false;
    _last_opt = myBtn::EQL;

    setFixedSize(441, 305);
    setWindowTitle("Calculator");

    ui->lcdNumber->setDigitCount(20);
    ui->lcdNumber->display(_show_str);
    ui->lcdNumber->setSmallDecimalPoint(true);

/*-----ROW 1-----*/
    myBtn *btn = new myBtn("7", myBtn::NUM, ui->widget_main, 9, 9);
    connect(btn, &myBtn::sig_snd_txt, this, &MainWindow::slot_recv_sig);
    btn = new myBtn("8", myBtn::NUM, ui->widget_main, 90, 9);
    connect(btn, &myBtn::sig_snd_txt, this, &MainWindow::slot_recv_sig);
    btn = new myBtn("9", myBtn::NUM, ui->widget_main, 171, 9);
    connect(btn, &myBtn::sig_snd_txt, this, &MainWindow::slot_recv_sig);
    btn = new myBtn("÷", myBtn::DIV, ui->widget_main, 255, 9);
    connect(btn, &myBtn::sig_snd_txt, this, &MainWindow::slot_recv_sig);
    btn = new myBtn("AC", myBtn::CLR, ui->widget_main, 339, 9);
    connect(btn, &myBtn::sig_snd_txt, this, &MainWindow::slot_recv_sig);

/*-----ROW 2-----*/
    btn = new myBtn("4", myBtn::NUM, ui->widget_main, 9, 57);
    connect(btn, &myBtn::sig_snd_txt, this, &MainWindow::slot_recv_sig);
    btn = new myBtn("5", myBtn::NUM, ui->widget_main, 90, 57);
    connect(btn, &myBtn::sig_snd_txt, this, &MainWindow::slot_recv_sig);
    btn = new myBtn("6", myBtn::NUM, ui->widget_main, 171, 57);
    connect(btn, &myBtn::sig_snd_txt, this, &MainWindow::slot_recv_sig);
    btn = new myBtn("×", myBtn::MUL, ui->widget_main, 255, 57);
    connect(btn, &myBtn::sig_snd_txt, this, &MainWindow::slot_recv_sig);
    btn = new myBtn("<", myBtn::BCK, ui->widget_main, 339, 57);
    connect(btn, &myBtn::sig_snd_txt, this, &MainWindow::slot_recv_sig);

/*-----ROW 3-----*/
    btn = new myBtn("1", myBtn::NUM, ui->widget_main, 9, 105);
    connect(btn, &myBtn::sig_snd_txt, this, &MainWindow::slot_recv_sig);
    btn = new myBtn("2", myBtn::NUM, ui->widget_main, 90, 105);
    connect(btn, &myBtn::sig_snd_txt, this, &MainWindow::slot_recv_sig);
    btn = new myBtn("3", myBtn::NUM, ui->widget_main, 171, 105);
    connect(btn, &myBtn::sig_snd_txt, this, &MainWindow::slot_recv_sig);
    btn = new myBtn("-", myBtn::SUB, ui->widget_main, 255, 105);
    connect(btn, &myBtn::sig_snd_txt, this, &MainWindow::slot_recv_sig);
    btn = new myBtn("%", myBtn::MOD, ui->widget_main, 339, 105);
    connect(btn, &myBtn::sig_snd_txt, this, &MainWindow::slot_recv_sig);

/*-----ROW 4-----*/
    btn = new myBtn("±", myBtn::POS_NEG, ui->widget_main, 9, 153);
    connect(btn, &myBtn::sig_snd_txt, this, &MainWindow::slot_recv_sig);
    btn = new myBtn("0", myBtn::NUM, ui->widget_main, 90, 153);
    connect(btn, &myBtn::sig_snd_txt, this, &MainWindow::slot_recv_sig);
    btn = new myBtn(".", myBtn::PNT, ui->widget_main, 171, 153);
    connect(btn, &myBtn::sig_snd_txt, this, &MainWindow::slot_recv_sig);
    btn = new myBtn("+", myBtn::PLS, ui->widget_main, 255, 153);
    connect(btn, &myBtn::sig_snd_txt, this, &MainWindow::slot_recv_sig);
    btn = new myBtn("=", myBtn::EQL, ui->widget_main, 339, 153);
    connect(btn, &myBtn::sig_snd_txt, this, &MainWindow::slot_recv_sig);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_recv_sig(QString txt, myBtn::FLG flg)
{
    switch (flg) {
    case myBtn::CLR:
        set_clear();
        break;
    case myBtn::BCK:
        set_backspace();
        break;
    case myBtn::NUM:
        set_show_str(txt);
        break;
    case myBtn::POS_NEG:
        set_pos_neg();
        break;
    case myBtn::PNT:
        set_point();
        break;
    case myBtn::EQL:
        set_equal();
        break;
    case myBtn::PLS:
    case myBtn::SUB:
    case myBtn::MUL:
    case myBtn::DIV:
    case myBtn::MOD:
        set_operator(flg);
        break;
//  switch covers all enumeration value in
//    default:
//        break;
    }
}

void MainWindow::lcd_display(QString str)
{
    if (_show_str.count() > 20)
        _show_str.resize(20);

    ui->lcdNumber->display(str);
}

void MainWindow::set_clear()
{
    _show_str = "0";
    _buf_str = "0";
    _flg_pos_neg = true;
    _flg_pnt = false;
    _flg_input_new = false;
    _last_opt = myBtn::EQL;
    lcd_display(_show_str);
}

void MainWindow::set_show_str(QString str)
{
    if (_flg_input_new) {
        _show_str = str;
        _flg_input_new = false;
        lcd_display(_show_str);

        return ;
    }

    if (_show_str == "0" || _show_str == "-0") {
        if (str == "0")
            return ;
        if (str != '.')
            _show_str = "";             // remove "0"
    }

    _show_str += str;
    _flg_input_new = false;
    lcd_display(_show_str);
}

void MainWindow::set_backspace()
{
    if (_flg_input_new)                // never backspace a return value
        return ;

    if (_show_str.toDouble() == 0.0 || _show_str.count() == 1) {
        _show_str = "0";
    } else {
        if (_show_str.endsWith("."))
            _flg_pnt = false;
        _show_str.remove(-1, 1);
    }

    lcd_display(_show_str);
}

void MainWindow::set_pos_neg()
{
    if (_flg_input_new)
        return ;

    (_flg_pos_neg = !_flg_pos_neg) ? _show_str.remove(0, 1)
                                   : _show_str.prepend("-");
    lcd_display(_show_str);
}

void MainWindow::set_point()
{
    if (_flg_input_new) {
        _show_str = "0.";
        _flg_input_new = false;
        lcd_display(_show_str);
        return ;
    }

    if (!_flg_pnt) {
        _show_str += ".";
        _flg_pnt = true;
    }
}

void MainWindow::set_equal()
{
    if (_show_str == "Error")
        _show_str = "0";

    switch (_last_opt) {
    case myBtn::PLS:
        _buf_str = QString::number(_buf_str.toDouble() + _show_str.toDouble());
        break;
    case myBtn::SUB:
        _buf_str = QString::number(_buf_str.toDouble() - _show_str.toDouble());
        break;
    case myBtn::MUL:
        _buf_str = QString::number(_buf_str.toDouble() * _show_str.toDouble());
        break;
    case myBtn::DIV:
        if (_show_str.toDouble() == 0.0) {
            _buf_str = QString("Error");
        } else {
            _buf_str = QString::number(_buf_str.toDouble() / _show_str.toDouble());
        }
        break;
    case myBtn::MOD:
        if (_buf_str.count(".") == 1 || _show_str.count(".") == 1) {
            _buf_str = QString("Error");
        } else {
            _buf_str = QString::number(_buf_str.toLongLong() % _show_str.toLongLong());
        }
        break;
    default:
        _buf_str = _show_str;    
        qDebug() << _buf_str;
        break;
    }

    _show_str = _buf_str;
    _last_opt = myBtn::EQL;
    _flg_pos_neg = true;
    _flg_pnt = false;
    _flg_input_new = true;
    lcd_display(_show_str);
}

void MainWindow::set_operator(myBtn::FLG flg)
{
    set_equal();
    _last_opt = flg;
}
