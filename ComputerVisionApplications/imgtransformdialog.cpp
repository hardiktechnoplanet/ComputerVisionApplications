#include "imgtransformdialog.h"
#include "ui_imgtransformdialog.h"

ImgTransformDialog::ImgTransformDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImgTransformDialog)
{
    ui->setupUi(this);
}

ImgTransformDialog::~ImgTransformDialog()
{
    delete ui;
}
