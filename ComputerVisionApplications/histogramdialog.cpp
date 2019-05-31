#include "histogramdialog.h"
#include "ui_histogramdialog.h"

histogramDialog::histogramDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::histogramDialog)
{
    ui->setupUi(this);
}

histogramDialog::~histogramDialog()
{
    delete ui;
}

void histogramDialog::on_histogram_pushButton_clicked()
{
    emit histogram(true);
}
