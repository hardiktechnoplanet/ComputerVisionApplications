#ifndef MORPHOLOGYDIALOG_H
#define MORPHOLOGYDIALOG_H

#include <QDialog>

namespace Ui {
class morphologyDialog;
}

class morphologyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit morphologyDialog(QWidget *parent = 0);
    ~morphologyDialog();

signals:
    void erosionSignal(bool);
    void dilationSignal(bool);
    void openSignal(bool);
    void closeSignal(bool);
    void gradientSignal(bool);
    void tophatSignal(bool);

private slots:
    void on_erosion_pushButton_clicked();

    void on_dilation_pushButton_clicked();

    void on_open_pushButton_clicked();

    void on_close_pushButton_clicked();

    void on_gradient_pushButton_clicked();

    void on_topHat_pushButton_clicked();

private:
    Ui::morphologyDialog *ui;
};

#endif // MORPHOLOGYDIALOG_H
