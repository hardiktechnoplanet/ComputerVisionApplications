#include "extrctandmtchdialog.h"
#include "ui_extrctandmtchdialog.h"

extrctAndMtchDialog::extrctAndMtchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::extrctAndMtchDialog)
{
    ui->setupUi(this);
}

extrctAndMtchDialog::~extrctAndMtchDialog()
{
    delete ui;
}
