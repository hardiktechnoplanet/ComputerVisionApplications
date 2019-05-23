#include "houghdialog.h"
#include "ui_houghdialog.h"

houghDialog::houghDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::houghDialog)
{
    ui->setupUi(this);
}

houghDialog::~houghDialog()
{
    delete ui;
}

void houghDialog::on_standard_radioButton_clicked()
{
    emit houghTransform(true,false,false,false);
}

void houghDialog::on_progressive_radioButton_clicked()
{
    emit houghTransform(false,true,false,false);
}

void houghDialog::on_threshold_spinBox_valueChanged(int arg1)
{
    emit thresholdChange(arg1);
}

void houghDialog::on_lineGap_spinBox_valueChanged(int arg1)
{
    emit LineLenChange(arg1);
}

void houghDialog::on_lineLen_spinBox_valueChanged(int arg1)
{
    emit LineGapChange(arg1);
}

void houghDialog::on_multiscale_radioButton_clicked()
{
    emit houghTransform(false,false,true,false);
}

void houghDialog::on_circle_radioButton_clicked()
{
    emit houghTransform(false,false,false,true);
}

void houghDialog::on_minDist_spinBox_valueChanged(int arg1)
{
    emit minDistChange(arg1);
}
