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
    //help
    ui->AGAST_label->setToolTip("Adaptive and Generic Accelerated"
                                "Segment Test");
    ui->BRISK_label->setToolTip("Binary Robust Invariant"
                                "Scalable Keypoints");
    //add the algo list to the combo box
    ui->selectAlgo_comboBox->addItems(QStringList()
                                      << "AGAST"
                                      << "BRISK");
}

featureDetectorDialog::~featureDetectorDialog()
{
    delete ui;
}

void featureDetectorDialog::on_ok_pushButton_clicked()
{
    //check which algo is selected to run
    int indx=ui->selectAlgo_comboBox->currentIndex();
    if(indx==0)
    {
        emit AGAST_signal(true,ui->threshold_spinBox->value(),
                          ui->suppression_checkBox->isChecked(),
                          ui->type_comboBox->currentIndex());
    }
    else if(indx==1)
    {
        emit BRISK_signal(true,ui->thrs_spinBox->value(),
                          ui->octaves_spinBox->value(),
                          ui->patterns_spinBox->value());
    }
    //close the dialog
    featureDetectorDialog::close();
}
