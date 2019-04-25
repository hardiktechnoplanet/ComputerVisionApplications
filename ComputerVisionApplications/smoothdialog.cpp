#include "smoothdialog.h"
#include "ui_smoothdialog.h"

smoothDialog::smoothDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::smoothDialog)
{
    ui->setupUi(this);
}

smoothDialog::~smoothDialog()
{
    delete ui;
}
