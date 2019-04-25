#ifndef FEATUREDETECTORDIALOG_H
#define FEATUREDETECTORDIALOG_H

#include <QDialog>

namespace Ui {
class featureDetectorDialog;
}

class featureDetectorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit featureDetectorDialog(QWidget *parent = 0);
    ~featureDetectorDialog();

signals:
    //send signal,threshold value,max-suppression true
    //or false, and algo type
    void AGAST_signal(bool,int,bool,int);
    //flag,threshold,octave,pattern scale
    void BRISK_signal(bool,int, int,int);

private slots:
    void on_ok_pushButton_clicked();

private:
    Ui::featureDetectorDialog *ui;
};

#endif // FEATUREDETECTORDIALOG_H
