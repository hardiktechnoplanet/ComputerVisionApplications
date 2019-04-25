#include "pyramidsdialog.h"
#include "ui_pyramidsdialog.h"

pyramidsDialog::pyramidsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pyramidsDialog)
{
    ui->setupUi(this);
    pyrLevel=0;
}

pyramidsDialog::~pyramidsDialog()
{
    delete ui;
}

void pyramidsDialog::on_gaussian_pushButton_clicked()
{
    pyrLevel=ui->pyramid_spinBox->value();
    emit pyramidSignal(true,false,pyrLevel);
    pyramidsDialog::close();
}

void pyramidsDialog::on_laplacian_pushButton_clicked()
{
    pyrLevel=ui->pyramid_spinBox->value();
    emit pyramidSignal(false,true,pyrLevel);
    pyramidsDialog::close();
}
