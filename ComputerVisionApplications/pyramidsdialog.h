#ifndef PYRAMIDSDIALOG_H
#define PYRAMIDSDIALOG_H

#include <QDialog>

namespace Ui {
class pyramidsDialog;
}

class pyramidsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit pyramidsDialog(QWidget *parent = 0);
    ~pyramidsDialog();

signals:
    //gaussian,laplacian
    void pyramidSignal(bool,bool,int);
private slots:
    void on_gaussian_pushButton_clicked();

    void on_laplacian_pushButton_clicked();

private:
    Ui::pyramidsDialog *ui;
    int pyrLevel;
};

#endif // PYRAMIDSDIALOG_H
