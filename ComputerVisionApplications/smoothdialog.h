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

signals:
    //flag,blur,median,gaussian,bilateral
    void smoothingSignal(bool,bool,bool,bool,bool);

private slots:
    void on_smoothOk_pushButton_clicked();

private:
    Ui::smoothDialog *ui;
};

#endif // SMOOTHDIALOG_H
