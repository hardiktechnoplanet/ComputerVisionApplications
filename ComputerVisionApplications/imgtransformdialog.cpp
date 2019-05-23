#include "imgtransformdialog.h"
#include "ui_imgtransformdialog.h"
#include "QFile"
#include "QFileDialog"

ImgTransformDialog::ImgTransformDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImgTransformDialog)
{
    ui->setupUi(this);
    //add the inpaint methods to the menu
    ui->inpaint_comboBox->addItems(QStringList()
                                   << "Navier-Stokes method"
                                   << "Telea's method");
    ui->ok_pushButton->setToolTip("repairs the damage image by taking color and"
                                  " texture at the border of the damaged area and"
                                  " propagating and mixing it inside the damaged area");
    ui->hist_pushButton->setToolTip("expands dynamic range of the image to increase"
                                    " its contrast");
}

ImgTransformDialog::~ImgTransformDialog()
{
    delete ui;
}

void ImgTransformDialog::on_inpaintMask_pushButton_clicked()
{
    QFile file;
    QString fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"),tr("C:/"),
                                            tr("Image Files (*.png *.jpg *.bmp)"));
    file.setFileName(fileName);
    if (file.exists())
    {
       //after opening the image, write its path to the "inputLineEdit"
       ui->inpaintMask_lineEdit->setText(fileName);

       QPixmap img = QPixmap(fileName);
       if (!img.isNull())
       {
          delete ui->inpaintMask_graphicsView->scene();
          ui->inpaintMask_graphicsView->setScene(new QGraphicsScene(ui->inpaintMask_graphicsView));
          ui->inpaintMask_graphicsView->scene()->addPixmap(img);
       }
       //put the image path to the QString to send it to mainwindow.cpp
       //in mainwindow.cpp file this path will be used by imread function
       //to read the template image
       inpaintMaskStr=ui->inpaintMask_lineEdit->text();

    }
}

void ImgTransformDialog::on_ok_pushButton_clicked()
{
    int curnt_indx=ui->inpaint_comboBox->currentIndex();
    emit imgTransformSignal(true,inpaintMaskStr,curnt_indx,false);
    ImgTransformDialog::close();
}

void ImgTransformDialog::on_hist_pushButton_clicked()
{
    emit imgTransformSignal(false,inpaintMaskStr,0,true);
}
