#ifndef BORDERDIALOG_H
#define BORDERDIALOG_H

#include <QDialog>

namespace Ui {
class borderDialog;
}

class borderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit borderDialog(QWidget *parent = 0);
    ~borderDialog();

private:
    Ui::borderDialog *ui;
};

#endif // BORDERDIALOG_H
