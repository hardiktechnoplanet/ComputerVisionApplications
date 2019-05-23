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

signals:
    void borderSignal(bool,bool,bool,bool,bool);

private slots:
    void on_constant_pushButton_clicked();

    void on_wrap_pushButton_clicked();

    void on_replicate_pushButton_clicked();

    void on_reflect_pushButton_clicked();

    void on_reflect101_pushButton_clicked();

private:
    Ui::borderDialog *ui;
};

#endif // BORDERDIALOG_H
