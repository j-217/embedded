#include "mainwindow.h"
#include <QDebug>
#include <iostream>
using std::cout;
using std::endl;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(36*G_COL, 36*G_ROW);
    _my_widget = nullptr;
    _count_opened = 0;

    init_map();
}

MainWindow::~MainWindow()
{
}

void MainWindow::slot_handle_mine_click(Point position)
{
    if (_map[position.get_y()][position.get_x()]->get_has_mine()) {
        _map[position.get_y()][position.get_x()]->setIcon(QIcon("://images/bomber.png"));
        _map[position.get_y()][position.get_x()]->setIconSize(QSize(36, 36));
        _map[position.get_y()][position.get_x()]->set_opened(true);

        check_win(position);
        return ;
    }

    open(position);
}

void MainWindow::slot_handle_mine_rclick(Point position)
{
    if (!_map[position.get_y()][position.get_x()]->get_has_flag() &&
         !_map[position.get_y()][position.get_x()]->get_opened())
    {
        _map[position.get_y()][position.get_x()]->set_flag(true);
        _map[position.get_y()][position.get_x()]->setIcon(QIcon("://images/know.png"));
        _map[position.get_y()][position.get_x()]->setIconSize(QSize(36, 36));
    }
    else if (_map[position.get_y()][position.get_x()]->get_has_flag() &&
            !_map[position.get_y()][position.get_x()]->get_opened())
    {
        _map[position.get_y()][position.get_x()]->set_flag(false);
        _map[position.get_y()][position.get_x()]->setIcon(QIcon());
    }
}

void MainWindow::init_map()
{
    if (_my_widget != nullptr) {
        return ;
    }
    _my_widget = new QWidget(this);
    QGridLayout *_layout = new QGridLayout(_my_widget);
    for (int row = 0; row < G_ROW; ++row) {
        for (int col = 0; col < G_COL; ++col) {
            Mine *mine = new Mine(Point(col, row), this);
            mine->setFixedSize(36, 36);
            _layout->addWidget(mine, row, col, 1, 1);
            _map[row][col] = mine;
            connect(mine, &Mine::sig_send_position,
                    this, &MainWindow::slot_handle_mine_click);

            connect(mine, &Mine::sig_right_click,
                    this, &MainWindow::slot_handle_mine_rclick);
        }
    }
    _layout->setGeometry(QRect(0, 0, 36*G_COL, 36*G_ROW));
    _layout->setSpacing(0);
    _layout->setMargin(0);
    _my_widget->setLayout(_layout);
    setCentralWidget(_my_widget);

    set_mine_map();
    get_mine_map();
}

void MainWindow::set_mine_map()
{
    int ran_row = 0;
    int ran_col = 0;
    int count = G_MINE;

    while (count) {
        ran_row = QRandomGenerator::global()->bounded(0, 10);
        ran_col = QRandomGenerator::global()->bounded(0, 10);
        if (!_map[ran_row][ran_col]->get_has_mine()) {
            _map[ran_row][ran_col]->set_mine(true);
            --count;
        }
    }
}

void MainWindow::get_mine_map()
{
    for(int r = 0; r < 10; ++r) {
        for (int c = 0; c < 10; ++c) {
            cout << _map[r][c]->get_has_mine() << " ";
        }
        cout << endl;
    }
}

void MainWindow::open(Point position)
{
    if (_map[position.get_y()][position.get_x()]->get_opened()) {
        return ;
    }

    int count = find_around(position);
    QString path = QString("://images/%1.png").arg(count);

    _map[position.get_y()][position.get_x()]->setIcon(QIcon(path));
    _map[position.get_y()][position.get_x()]->setIconSize(QSize(36, 36));
    _map[position.get_y()][position.get_x()]->set_opened(true);
    ++_count_opened;

    qDebug() << _count_opened;

    if (count == 0) {
        int x_start = position.get_x() == 0 ?
                    0 : (position.get_x() - 1);
        int x_end = position.get_x() == (G_COL - 1) ?
                    (G_COL - 1) : (position.get_x() + 1);
        int y_start = position.get_y() == 0 ?
                    0 : (position.get_y() - 1);
        int y_end = position.get_y() == (G_ROW - 1) ?
                    (G_ROW - 1) : (position.get_y() + 1);

        for (int row = y_start; row <= y_end; ++row) {
            for (int col = x_start; col <= x_end; ++col) {
                if ((row == position.get_y() && col == position.get_x()) ||
                    _map[row][col]->get_opened())
                    continue;
                open(Point(col, row));                          // 如果为0，递归展开周围8个格子
            }
        }
    }

    check_win(position);
}

int MainWindow::find_around(Point position)
{
    int count = 0;
    int x_start = position.get_x() == 0 ?
                0 : (position.get_x() - 1);
    int x_end = position.get_x() == (G_COL - 1) ?
                (G_COL - 1) : (position.get_x() + 1);
    int y_start = position.get_y() == 0 ?
                0 : (position.get_y() - 1);
    int y_end = position.get_y() == (G_ROW - 1) ?
                (G_ROW - 1) : (position.get_y() + 1);

    for (int row = y_start; row <= y_end; ++row) {
        for (int col = x_start; col <= x_end; ++col) {
            if (row == position.get_y() && col == position.get_x())
                continue;
            if (_map[row][col]->get_has_mine())
                ++count;
        }
    }

    return count;
}

bool MainWindow::check_win(Point position)
{
    if (_map[position.get_y()][position.get_x()]->get_has_mine()) {
        for (int row = 0; row < G_ROW; ++row) {
            for (int col = 0; col < G_COL; ++col) {
                if (_map[row][col]->get_has_mine()) {
                    _map[row][col]->setIcon(QIcon("://images/bomber.png"));
                    _map[row][col]->setIconSize(QSize(36, 36));
                }
            }
        }

        QMessageBox::StandardButton res = QMessageBox::information(this, "提示", "GAME OVER",
                                               QMessageBox::Retry | QMessageBox::Close,
                                               QMessageBox::Retry);
        switch (res) {
        case QMessageBox::Retry:
            _my_widget->deleteLater();
            _my_widget = nullptr;
            init_map();
            break;
        case QMessageBox::Close:
            this->close();
            break;
        default:
            break;
        }

        return false;
    }
    else if (_count_opened == (G_ROW * G_COL - G_MINE)) {
        QMessageBox *res = new QMessageBox(QMessageBox::NoIcon, "提示", "YOU WIN", QMessageBox::Retry, this);
        res->exec();
        if (res->clickedButton()->text() == "Retry") {
            _my_widget->deleteLater();
            _my_widget = nullptr;
            init_map();
        }
        return true;
    }

    return false;
}

