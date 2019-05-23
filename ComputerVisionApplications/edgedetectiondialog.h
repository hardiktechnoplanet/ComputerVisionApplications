#ifndef EDGEDETECTIONDIALOG_H
#define EDGEDETECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class edgeDetectionDialog;
}

class edgeDetectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit edgeDetectionDialog(QWidget *parent = 0);
    ~edgeDetectionDialog();

signals:
    void edgeDetSignal(bool,bool,bool);

private slots:
    void on_edgeDetOK_pushButton_clicked();

private:
    Ui::edgeDetectionDialog *ui;
};

#endif // EDGEDETECTIONDIALOG_H
