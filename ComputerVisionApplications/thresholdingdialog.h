#ifndef THRESHOLDINGDIALOG_H
#define THRESHOLDINGDIALOG_H

#include <QDialog>

namespace Ui {
class thresholdingDialog;
}

class thresholdingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit thresholdingDialog(QWidget *parent = 0);
    ~thresholdingDialog();

signals:
    void thresholdingSignal(bool);
    void AdpthresholdingSignal(bool);

private slots:
    void on_thrsholdng_pushButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::thresholdingDialog *ui;
};

#endif // THRESHOLDINGDIALOG_H
