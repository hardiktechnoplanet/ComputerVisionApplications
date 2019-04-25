#include "smoothdialog.h"
#include "ui_smoothdialog.h"

smoothDialog::smoothDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::smoothDialog)
{
    ui->setupUi(this);

    //add the smoothing operators to the menu
    ui->smooth_comboBox->addItems(QStringList()
                                  << "Blur"
                                  << "Median"
                                  << "Gaussian"
                                  << "Bilateral");
}

smoothDialog::~smoothDialog()
{
    delete ui;
}

void smoothDialog::on_smoothOk_pushButton_clicked()
{
    int curnt_indx=ui->smooth_comboBox->currentIndex();
    if(curnt_indx==0)
    {
        emit smoothingSignal(true,true,false,false,false);
    }
    else if(curnt_indx==1)
    {
        emit smoothingSignal(true,false,true,false,false);
    }
    else if(curnt_indx==2)
    {
        emit smoothingSignal(true,false,false,true,false);
    }
    else if(curnt_indx==3)
    {
        emit smoothingSignal(true,false,false,false,true);
    }
    smoothDialog::close();
}
