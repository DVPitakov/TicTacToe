#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent = 0);
    ~StartDialog();

    bool xIsBot() const;
    bool yIsBot() const;
private:
    Ui::StartDialog *ui;

};

#endif // STARTDIALOG_H
