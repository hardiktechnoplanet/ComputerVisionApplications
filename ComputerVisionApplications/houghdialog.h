#ifndef HOUGHDIALOG_H
#define HOUGHDIALOG_H

#include <QDialog>

namespace Ui {
class houghDialog;
}

class houghDialog : public QDialog
{
    Q_OBJECT

public:
    explicit houghDialog(QWidget *parent = 0);
    ~houghDialog();

private:
    Ui::houghDialog *ui;
};

#endif // HOUGHDIALOG_H
