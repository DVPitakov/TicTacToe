#include "startdialog.h"
#include "ui_startdialog.h"

StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);
}

StartDialog::~StartDialog()
{
    delete ui;
}

bool StartDialog::xIsBot() const
{
    ui->checkBox->isChecked();
}

bool StartDialog::yIsBot() const
{
    ui->checkBox_2->isChecked();
}
