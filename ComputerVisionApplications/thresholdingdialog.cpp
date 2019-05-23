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
    thrshldVal=0; blockSize=3; constVal=0;
}

thresholdingDialog::~thresholdingDialog()
{
    delete ui;
}

void thresholdingDialog::on_thrsholdng_pushButton_clicked()
{
    thrshldVal=ui->threshold_spinBox->value();
    emit thresholdingSignal(true,thrshldVal);
}

void thresholdingDialog::on_ADPthrsholdng_pushButton_clicked()
{
    blockSize=ui->blockSize_spinBox->value();
    constVal=ui->const_spinBox->value();
    emit AdpthresholdingSignal(true,blockSize,constVal);
}
