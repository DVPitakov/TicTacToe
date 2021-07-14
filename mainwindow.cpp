#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "view/startdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->widget, SIGNAL(finished(Board::Side)), SLOT(onFinished(Board::Side)));

    StartDialog* sDialog = new StartDialog();
    sDialog->exec();

    xIsBot_ = sDialog->xIsBot();
    yIsBot_ = sDialog->yIsBot();

    delete sDialog;

    ui->widget->start(xIsBot_, yIsBot_);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onFinished(Board::Side winner)
{
    if(winner == Board::X)
        xWins_++;
    if(winner == Board::Y)
        yWins_++;

    ui->label->setText(QString("X wins: %1").arg(QString::number(xWins_)));
    ui->label_2->setText(QString("Y wins: %1").arg(QString::number(yWins_)));

    ui->widget->start(xIsBot_, yIsBot_);
}
