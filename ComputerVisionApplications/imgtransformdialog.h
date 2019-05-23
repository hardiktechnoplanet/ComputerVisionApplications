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

private:
    Ui::ImgTransformDialog *ui;
};

#endif // IMGTRANSFORMDIALOG_H
