#include "featuredetectordialog.h"
#include "ui_featuredetectordialog.h"

featureDetectorDialog::featureDetectorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::featureDetectorDialog)
{
    ui->setupUi(this);

    //add algo types to the combo box
    ui->type_comboBox->addItems(QStringList()
                                 << "AGAST_5_8"
                                 << "AGAST_7_12d"
                                 << "AGAST_7_12s"
                                 << "OAST_9_16");
}

featureDetectorDialog::~featureDetectorDialog()
{
    delete ui;
}

void featureDetectorDialog::on_ok_pushButton_clicked()
{
    emit AGAST_signal(true,ui->threshold_spinBox->value(),
                      ui->suppression_checkBox->isChecked(),
                      ui->type_comboBox->currentIndex());
    //close the dialog
    featureDetectorDialog::close();
}
