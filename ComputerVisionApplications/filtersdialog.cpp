#include "filtersdialog.h"
#include "ui_filtersdialog.h"
#include "mainwindow.h"

filtersDialog::filtersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::filtersDialog)
{
    ui->setupUi(this);
}

filtersDialog::~filtersDialog()
{
    delete ui;
}

void filtersDialog::on_gaussian_pushButton_clicked()
{
    emit gauFilter_flag(true);
}
