#include "edgedetectiondialog.h"
#include "ui_edgedetectiondialog.h"

edgeDetectionDialog::edgeDetectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edgeDetectionDialog)
{
    ui->setupUi(this);

    //add the edge detection methods to the menu
    ui->edgeDet_comboBox->addItems(QStringList()
                                  << "Sobel Derivative"
                                  << "Scharr Filter"
                                  << "Laplacian");
}

edgeDetectionDialog::~edgeDetectionDialog()
{
    delete ui;
}

void edgeDetectionDialog::on_edgeDetOK_pushButton_clicked()
{
    int curnt_indx=ui->edgeDet_comboBox->currentIndex();
    if(curnt_indx==0)
    {
        emit edgeDetSignal(true,false,false);
    }
    else if(curnt_indx==1)
    {
        emit edgeDetSignal(false,true,false);
    }
    else if(curnt_indx==2)
    {
        emit edgeDetSignal(false,false,true);
    }
    edgeDetectionDialog::close();
}
