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

void filtersDialog::on_median_pushButton_clicked()
{
    emit medianFilterSignal(true);
}

void filtersDialog::on_bilateral_pushButton_clicked()
{
    emit bilateralFilterSignal(true);
}

void filtersDialog::on_box_pushButton_clicked()
{
    emit boxFilterSignal(true);
}

void filtersDialog::on_twoD_pushButton_clicked()
{
    emit twoDFilterSignal(true);
}

void filtersDialog::on_edge_pushButton_clicked()
{
    emit edgeFilterSignal(true);
}

void filtersDialog::on_laplacian_pushButton_clicked()
{
    emit laplacianFilterSignal(true);
}
