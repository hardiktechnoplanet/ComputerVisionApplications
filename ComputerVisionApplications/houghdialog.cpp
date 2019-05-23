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
