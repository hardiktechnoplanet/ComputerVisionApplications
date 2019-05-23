#ifndef IMGTRANSFORMDIALOG_H
#define IMGTRANSFORMDIALOG_H

#include <QDialog>

namespace Ui {
class ImgTransformDialog;
}

class ImgTransformDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImgTransformDialog(QWidget *parent = 0);
    ~ImgTransformDialog();

signals:
    //inpaint, inpaint mask, inpaint method, histogram equalization
    void imgTransformSignal(bool,QString,int,bool);

private slots:
    void on_inpaintMask_pushButton_clicked();

    void on_ok_pushButton_clicked();

    void on_hist_pushButton_clicked();

private:
    Ui::ImgTransformDialog *ui;
    QString inpaintMaskStr;
};

#endif // IMGTRANSFORMDIALOG_H
