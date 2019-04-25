#include "pyramidsdialog.h"
#include "ui_pyramidsdialog.h"

pyramidsDialog::pyramidsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pyramidsDialog)
{
    ui->setupUi(this);
}

pyramidsDialog::~pyramidsDialog()
{
    delete ui;
}
