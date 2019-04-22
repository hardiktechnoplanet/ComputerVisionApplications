#include "morphologydialog.h"
#include "ui_morphologydialog.h"

morphologyDialog::morphologyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::morphologyDialog)
{
    ui->setupUi(this);

    ui->erosion_pushButton->setToolTip("isolates and shrunk the "
                                       "bright regions");
    ui->dilation_pushButton->setToolTip("expands and joins the"
                                        "bright regions");
    ui->open_pushButton->setToolTip("dilates an eroded image");
    ui->close_pushButton->setToolTip("erodes a dilated image");
    ui->gradient_pushButton->setToolTip("difference of an eroded"
                                        "and dilated version of the"
                                        "same image");
    ui->topHat_pushButton->setToolTip("difference between an image and"
                                      "its opening morph");
}

morphologyDialog::~morphologyDialog()
{
    delete ui;
}

void morphologyDialog::on_erosion_pushButton_clicked()
{
    emit erosionSignal(true);
}

void morphologyDialog::on_dilation_pushButton_clicked()
{
    emit dilationSignal(true);
}

void morphologyDialog::on_open_pushButton_clicked()
{
    emit openSignal(true);
}

void morphologyDialog::on_close_pushButton_clicked()
{
    emit closeSignal(true);
}

void morphologyDialog::on_gradient_pushButton_clicked()
{
    emit gradientSignal(true);
}

void morphologyDialog::on_topHat_pushButton_clicked()
{
    emit tophatSignal(true);
}
