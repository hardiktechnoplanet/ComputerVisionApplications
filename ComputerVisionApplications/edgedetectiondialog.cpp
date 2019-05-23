#include "edgedetectiondialog.h"
#include "ui_edgedetectiondialog.h"

edgeDetectionDialog::edgeDetectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edgeDetectionDialog)
{
    ui->setupUi(this);
}

edgeDetectionDialog::~edgeDetectionDialog()
{
    delete ui;
}
