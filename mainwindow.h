#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "logic/board.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    int xWins_{0};
    int yWins_{0};

    bool xIsBot_{false};
    bool yIsBot_{false};

private slots:
    void onFinished(Board::Side winner);

};

#endif // MAINWINDOW_H
