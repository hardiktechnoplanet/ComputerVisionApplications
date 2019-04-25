#include "extrctandmtchdialog.h"
#include "ui_extrctandmtchdialog.h"

extrctAndMtchDialog::extrctAndMtchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::extrctAndMtchDialog)
{
    ui->setupUi(this);

    ui->desType_comboBox->addItems(QStringList()
                                 << "DESCRIPTOR_KAZE_UPRIGHT"
                                 << "DESCRIPTOR_KAZE"
                                 << "DESCRIPTOR_MLDB_UPRIGHT");
    ui->diffusivty_comboBox->addItems(QStringList()
                                 << "DIFF_PM_G1"
                                 << "DIFF_PM_G2"
                                 << "DIFF_WEICKERT"
                                 << "DIFF_CHARBONNIER");
    ui->matcher_comboBox->addItems(QStringList()
                               << "FLANNBASED"
                               << "BRUTEFORCE"
                               << "BRUTEFORCE_L1"
                               << "BRUTEFORCE_HAMMING"
                               << "BRUTEFORCE_HAMMINGLUT"
                               << "BRUTEFORCE_SL2");

}

extrctAndMtchDialog::~extrctAndMtchDialog()
{
    delete ui;
}

void extrctAndMtchDialog::on_ok_pushButton_clicked()
{
    emit extractAndMatchSignal(true,ui->desType_comboBox->currentIndex()+2,
                               ui->thrshld_spinBox->value(),ui->octvs_spinBox->value(),
                               ui->octvsLayers_spinBox->value(),
                               ui->diffusivty_comboBox->currentIndex(),
                               ui->matcher_comboBox->currentIndex()+1);
    //close dialog box
    extrctAndMtchDialog::close();
}
