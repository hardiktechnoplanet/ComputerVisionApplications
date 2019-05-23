#include "borderdialog.h"
#include "ui_borderdialog.h"

borderDialog::borderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::borderDialog)
{
    ui->setupUi(this);

    ui->constant_pushButton->setToolTip("sets all the pixels in the border"
                                        "region to some fixed value");
    ui->wrap_pushButton->setToolTip("assign each pixel that is a distance n off the"
                                    "edge of the image the value of the pixel that"
                                    "is a distance n in from the opposite edge");
    ui->reflect_pushButton->setToolTip("assigns every pixel off the edge the same value"
                                       "as the pixel on that edge");
    ui->reflect101_pushButton->setToolTip("assign each pixel that is a distance n off the"
                                          "edge of the image the value of the pixel that"
                                          "is a distance n in from the same edge");
    ui->replicate_pushButton->setToolTip("assign each pixel that is a distance n off the"
                                         "edge of the image the value of the pixel that"
                                         "is a distance n+1 in from the same edge");
}

borderDialog::~borderDialog()
{
    delete ui;
}

void borderDialog::on_constant_pushButton_clicked()
{
    emit borderSignal(true,false,false,false,false);
}

void borderDialog::on_wrap_pushButton_clicked()
{
    emit borderSignal(false,true,false,false,false);
}

void borderDialog::on_replicate_pushButton_clicked()
{
    emit borderSignal(false,false,true,false,false);
}

void borderDialog::on_reflect_pushButton_clicked()
{
    emit borderSignal(false,false,false,true,false);;
}

void borderDialog::on_reflect101_pushButton_clicked()
{
    emit borderSignal(false,false,false,false,true);
}
