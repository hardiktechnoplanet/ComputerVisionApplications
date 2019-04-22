#ifndef TEMPLATEMATCHINGDIALOG_H
#define TEMPLATEMATCHINGDIALOG_H

#include <QDialog>

namespace Ui {
class templateMatchingDialog;
}

class templateMatchingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit templateMatchingDialog(QWidget *parent = 0);
    ~templateMatchingDialog();

signals:
    //first "bool" is true if the single template matching
    //button is pressed and second "bool" is true if multiple
    //template matching button is pressed
    void templateMatchingSignal(bool,bool,QString);

private slots:

    void on_template_pushButton_clicked();

    void on_mulTempMat_pushButton_clicked();

    void on_singleTempMat_pushButton_clicked();

private:
    Ui::templateMatchingDialog *ui;
    QString templateStr;
};

#endif // TEMPLATEMATCHINGDIALOG_H
