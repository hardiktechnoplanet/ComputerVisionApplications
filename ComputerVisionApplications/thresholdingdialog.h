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
    //signal,thresholding value
    void thresholdingSignal(bool,int);
    //signal,block size, constant value
    void AdpthresholdingSignal(bool,int,int);

private slots:
    void on_thrsholdng_pushButton_clicked();

    void on_ADPthrsholdng_pushButton_clicked();

private:
    Ui::thresholdingDialog *ui;
    int thrshldVal, blockSize, constVal;
};

#endif // THRESHOLDINGDIALOG_H
