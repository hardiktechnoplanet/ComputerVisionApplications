#include "templatematchingdialog.h"
#include "ui_templatematchingdialog.h"
#include <QFileDialog>

templateMatchingDialog::templateMatchingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::templateMatchingDialog)
{
    ui->setupUi(this);
}

templateMatchingDialog::~templateMatchingDialog()
{
    delete ui;
}


void templateMatchingDialog::on_template_pushButton_clicked()
{
    QFile file;
    QString fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"),tr("C:/"),
                                            tr("Image Files (*.png *.jpg *.bmp)"));
    file.setFileName(fileName);
    if (file.exists())
    {
       //after opening the image, write its path to the "inputLineEdit"
       ui->template_lineEdit->setText(fileName);

       QPixmap img = QPixmap(fileName);
       if (!img.isNull())
       {
          delete ui->template_graphicsView->scene();
          ui->template_graphicsView->setScene(new QGraphicsScene(ui->template_graphicsView));
          ui->template_graphicsView->scene()->addPixmap(img);
       }
       //put the image path to the QString to send it to mainwindow.cpp
       //in mainwindow.cpp file this path will be used by imread function
       //to read the template image
       templateStr=ui->template_lineEdit->text();

    }
}
//if single template matching
void templateMatchingDialog::on_singleTempMat_pushButton_clicked()
{
    emit templateMatchingSignal(true,false,templateStr);
    //close the dialog box to see the main gui
    templateMatchingDialog::close();
}
//if multiple template matching
void templateMatchingDialog::on_mulTempMat_pushButton_clicked()
{
    emit templateMatchingSignal(false,true,templateStr);
    //close the dialog box to see the main gui
    templateMatchingDialog::close();
}
