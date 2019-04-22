#include "thresholdingdialog.h"
#include "ui_thresholdingdialog.h"

thresholdingDialog::thresholdingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::thresholdingDialog)
{
    ui->setupUi(this);

    //message on hover
    ui->thrsholdng_pushButton->setToolTip("one global value as a "
                                          "threshold");
    ui->ADPthrsholdng_pushButton->setToolTip("different threshold "
                                             "for a pixel based on "
                                             "a small region around it");
}

thresholdingDialog::~thresholdingDialog()
{
    delete ui;
}

void thresholdingDialog::on_thrsholdng_pushButton_clicked()
{
    emit thresholdingSignal(true);
}

void thresholdingDialog::on_pushButton_clicked()
{
    emit AdpthresholdingSignal(true);
}
