#include "imgsegmentationdialog.h"
#include "ui_imgsegmentationdialog.h"

imgSegmentationDialog::imgSegmentationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::imgSegmentationDialog)
{
    ui->setupUi(this);
}

imgSegmentationDialog::~imgSegmentationDialog()
{
    delete ui;
}

void imgSegmentationDialog::on_watershed_radioButton_clicked()
{
    emit segmentation(true,false,false);
}
