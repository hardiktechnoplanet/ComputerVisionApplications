#include "borderdialog.h"
#include "ui_borderdialog.h"

borderDialog::borderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::borderDialog)
{
    ui->setupUi(this);
}

borderDialog::~borderDialog()
{
    delete ui;
}
