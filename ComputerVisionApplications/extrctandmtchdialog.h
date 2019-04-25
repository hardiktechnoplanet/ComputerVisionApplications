#ifndef EXTRCTANDMTCHDIALOG_H
#define EXTRCTANDMTCHDIALOG_H

#include <QDialog>

namespace Ui {
class extrctAndMtchDialog;
}

class extrctAndMtchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit extrctAndMtchDialog(QWidget *parent = 0);
    ~extrctAndMtchDialog();
signals:
    //flag,descriptor type,threshold,octaves,octaves layers,
    //diffusivity,descriptor matcher
    void extractAndMatchSignal(bool,int,double,int,int,int,int);

private slots:
    void on_ok_pushButton_clicked();

private:
    Ui::extrctAndMtchDialog *ui;
};

#endif // EXTRCTANDMTCHDIALOG_H
