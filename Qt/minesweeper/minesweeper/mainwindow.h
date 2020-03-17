#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mine.h"
#include <QGridLayout>
#include <QRandomGenerator>
#include <QMessageBox>

const static int G_ROW = 10;            // row of map
const static int G_COL = 10;            // column of map
const static int G_MINE = 10;           // number of mine

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slot_handle_mine_click(Point position);
    void slot_handle_mine_rclick(Point position);

private:
    Mine *_map[G_ROW][G_COL];
    QWidget *_my_widget;
    int _count_opened;              // count opened grid in the map

    void init_map();
    void set_mine_map();
    void get_mine_map();            // print map of mine to terminal
    void open(Point position);
    int find_around(Point position);
    bool check_win(Point position);
};
#endif // MAINWINDOW_H
