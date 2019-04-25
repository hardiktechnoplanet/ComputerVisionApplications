#ifndef SMOOTHDIALOG_H
#define SMOOTHDIALOG_H

#include <QDialog>

namespace Ui {
class smoothDialog;
}

class smoothDialog : public QDialog
{
    Q_OBJECT

public:
    explicit smoothDialog(QWidget *parent = 0);
    ~smoothDialog();

private:
    Ui::smoothDialog *ui;
};

#endif // SMOOTHDIALOG_H
