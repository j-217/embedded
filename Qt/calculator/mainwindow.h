#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "mybtn.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slot_recv_sig(QString txt, myBtn::FLG flg);

private:
    Ui::MainWindow *ui;
    QString _show_str;
    QString _buf_str;
    bool _flg_pos_neg;               // true: pos, false: neg
    bool _flg_pnt;                   // true: have, false: no
    bool _flg_input_new;             // true: input new string is allowed
    myBtn::FLG _last_opt;            // last operator

    void lcd_display(QString str);
    void set_clear();
    void set_show_str(QString str);
    void set_backspace();
    void set_pos_neg();
    void set_point();
    void set_equal();
    void set_operator(myBtn::FLG flg);
};
#endif // MAINWINDOW_H
