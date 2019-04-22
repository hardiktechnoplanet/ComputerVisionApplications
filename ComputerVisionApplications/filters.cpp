#include "filters.h"
#include "ui_filters.h"

filters::filters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::filters)
{
    ui->setupUi(this);
}

filters::~filters()
{
    delete ui;
}
