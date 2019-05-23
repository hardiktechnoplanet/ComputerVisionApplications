#include <QFileDialog>
#include <QWheelEvent>
#include <QDebug>
#include <QPushButton>
#include <vector>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filtersdialog.h" //filters header file
#include "thresholdingdialog.h" //thresholding header file
#include "morphologydialog.h" //morphology header file
#include "templatematchingdialog.h" //template matching header file
#include "featuredetectordialog.h" //feature detector header file
#include "extrctandmtchdialog.h" //extractor and matching header file
#include "smoothdialog.h" //smoothing operator header file
#include "pyramidsdialog.h"
#include "borderdialog.h"
#include "edgedetectiondialog.h"
#include "imgtransformdialog.h"
#include "houghdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //background image
    //set the background JADAK image
    QPixmap bkgnd("C:/ComputerVision/Images/images2.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    //stylesheet
    qApp->setStyleSheet("QPushButton {background-color:white;"
                        ""
                        "border-style:outset;"
                        "border-width:2px;"
                        "border-radius:10px;"
                        "border-color:beige;"
                        "font:bold 10px;"
                        "min-width: 5em;"
                        "padding: 6px}"
                        "QPushButton:hover {background-color:rgb(224,225,0)}"
                        "QPushButton:pressed {background-color:rgb(224,225,0)}");
    //qApp->setStyleSheet("QPushButton:hover {background-color: rgb(224, 0, 200)}");

        /*background-color: red;
    border-style: outset;
    border-width: 2px;
    border-radius: 10px;
    border-color: beige;
    font: bold 14px;
    min-width: 10em;
    padding: 6px;*/

    //qApp->setStyleSheet("QPushButton { background-color: yellow }");

    //pushbutton filter flags
    mbGauFilter_flag=false;

    //border flag
    constBorderFlag=false; repBorderFlag=false;wrapBorderFlag=false;
    refBorderFlag=false; ref101BorderFlag=false;
    ui->border_pushButton->setToolTip("creates virtual pixels outside"
                                      "of the image at the borders");
    //filter flags
    gaussianFilter_flag=false;
    blurrFilter_flag=false;
    biltrlFilter_flag=false;
    boxFilter_flag=false;
    twoDFilter_flag=false;
    edgeDetFilter_flag=false;
    lapFilter_flag=false;
    scharrFilter_flag=false;
    sobelFilter_flag=false;
    //smoothing flag
    blurrSmooth_flag=false; gaussSmooth_flag=false;
    bilatSmooth_flag=false, medSmooth_flag=false;
    ui->smoothing_pushButton->setToolTip("reduce noise"
                                      " or camera artifacts");
    //edge detection
    scharr_flag=false; laplacian_flag=false; sobel_flag=false;
    ui->edgeDet_pushButton->setToolTip("derivative computation or"
                                       "edge detection");
    //image transform
    inpaint_flag=false; hist_flag=false;
    ui->imgTransform_pushButton->setToolTip("general image transformation like"
                                            " inpainting and Histogram Equalization");

    //hough transform
    lineStd_flag=false; lineProgressive_flag=false; circleHough_flag=false;
    mhtLine_flag=false;
    ui->hough_pushButton->setToolTip("detects lines, circles, or other simple"
                                     "forms in an image");

    //pyramids
    gauPyr_flag=false; lapPyr_flag=false;
    ui->pyramid_pushButton->setToolTip("downsample or upsample the input"
                                       " image");
    //thresholding
    thresholding_flag=false; Adpthresholding_flag=false;
    ui->thresholding_pushButton->setToolTip("keep all the pixles in the image that"
                                            "are above or below some particular value");
    thrshldVal=0; blocksizeVal=3;constvarVal=0;
    //morphology
    erosion_flag=false;
    dilation_flag=false;
    open_flag=false;
    close_flag=false,
    gradient_flag=false;
    tophat_flag=false;
    ui->morphology_pushButton->setToolTip("remove noise,isolates"
                                          "individual elements,"
                                          "and join disprate elements"
                                          "in an image");
    //template matching
    templateMatching_flag=false;
    //feature detector
    AGAST_flag=false; BRISK_flag=false;
    //extract and matching
    extractAndMatch_flag=false;
    //edge detection
    ui->edgeDet_pushButton->setToolTip("canny edge detector");
}

MainWindow::~MainWindow()
{
    gaussianFilter_flag=false;
    blurrFilter_flag=false;
    delete ui;
}

//to open the input image
void MainWindow::on_inputImage_pushButton_clicked()
{
    QFile file;
    QString fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"),tr("C:/"),
                                            tr("Image Files (*.png *.jpg *.bmp)"));
    file.setFileName(fileName);
    if (file.exists())
    {
       //after opening the image, write its path to the "inputLineEdit"
       ui->input_lineEdit->setText(fileName);

       QPixmap img = QPixmap(fileName);
       if (!img.isNull())
       {
          delete ui->inputImage_graphicsView->scene();
          ui->inputImage_graphicsView->setScene(new QGraphicsScene(ui->inputImage_graphicsView));
          ui->inputImage_graphicsView->scene()->addPixmap(img);
       }
    }

}

/*//////////////////////////border extrapolation/////////////////////*/
void MainWindow::img_border()
{
    //to save the ouput img
    QString fileName=QFileDialog::getSaveFileName(this,
                                                  "Select Output Image",
                                                  QDir::currentPath(),
                                                  "*.jpg,*.png;;*.bmp");
    if(!fileName.isEmpty())
    {
        ui->output_lineEdit->setText(fileName);
        using namespace cv;
        Mat inpImg, outImg;

        //read the input image
        //OpenCv uses C++ std::string class and the QT uses QString class,
        //we need to convert the format.
        inpImg=imread(ui->input_lineEdit->text().toStdString());

        //select the padding size as 0.5% of the input image
        int top,bottom,left,right;
        top=(int) (0.5*inpImg.rows); bottom=top;
        left=(int) (0.5*inpImg.cols); right=left;

        //const border
        if(constBorderFlag)
        {
            /*src,dst,top side padding, bottom side padding,
             *left side padding, right side padding, border type,
             * val for const border*/
            copyMakeBorder(inpImg,outImg,top,bottom,left,right,BORDER_CONSTANT,45);
        }
        else if(repBorderFlag)
        {
            copyMakeBorder(inpImg,outImg,top,bottom,left,right,BORDER_REPLICATE);
        }
        else if(wrapBorderFlag)
        {
            copyMakeBorder(inpImg,outImg,top,bottom,left,right,BORDER_WRAP);
        }
        else if(refBorderFlag)
        {
            copyMakeBorder(inpImg,outImg,top,bottom,left,right,BORDER_REFLECT);
        }
        else if(ref101BorderFlag)
        {
            copyMakeBorder(inpImg,outImg,top,bottom,left,right,BORDER_REFLECT_101);
        }

        else if(gaussianFilter_flag || mbGauFilter_flag)
        {
            /*src,dst,ksize,sigmaX,sigmaY
             * sigmaX=Gaussian kernel standard deviation in
             * X direction.
             * sigmaY=Gaussian kernel standard deviation in
             * Y direction.
            */
            cv::GaussianBlur(inpImg,outImg,Size(5,5),1.25);
            gaussianFilter_flag=false;
        }
        //Median blurr filter
        else if(blurrFilter_flag)
        {
            //src,dst,ksize(kernel size)
            cv::medianBlur(inpImg,outImg,5);
            blurrFilter_flag=false;
        }
        //Bilateral filter
        else if(biltrlFilter_flag)
        {
            /*src,dst,ksize,sigmaSpace,maxsigmaColor,bordertype
             * ksize=kernel size
             * sigmaSpace=Larger value of the parameter means
             * that farther pixels will influence each other
             * maxsigmaColor= Larger value of the parameter means
             * that more dissimilar pixels will influence each other
            */
            cv::bilateralFilter(inpImg,outImg,15,200,200);
            biltrlFilter_flag=false;
        }
        //Box filter
        else if(boxFilter_flag)
        {
            Size * kernelSize=new Size(10,10);
            Point * pt=new Point(-1,-1);
            /*src,dst,depth,kernel size,anchor point, normalised*/
            //cv::boxFilter(inpImg,outImg,50,&size,&pt,true);
            boxFilter_flag=false;
        }
        //2D filter flag
        else if(twoDFilter_flag)
        {
            Matx33f f2dkernel (0, -1, 0,
                               -1, 5, -1,
                               0, -1, 0);
            int depth=-1;
            cv::filter2D(inpImg,outImg,depth,f2dkernel);
            twoDFilter_flag=false;
        }
        //edge detection
        else if(edgeDetFilter_flag)
        {
            Matx33f f2dkernel (0, +1.5, 0,
                               +1.5, -6, +1.5,
                               0, +1.5, 0);
            int depth=-1;
            cv::filter2D(inpImg,outImg,depth,f2dkernel);
            edgeDetFilter_flag=false;
        }
        //edge detection(img derivatives)->laplacian
        else if(lapFilter_flag)
        {
            int depth=-1;
            int kernelSize=3;
            double scale=1.0; double delta=0.0;
            cv::Laplacian(inpImg,outImg,depth,kernelSize,
                          scale,delta);
            lapFilter_flag=false;

        }
        //scharr filter
        else if(scharrFilter_flag)
        {
            int depth=-1;
            int dx=1; int dy=0;
            double scale=1.0; double delta=100.0;
            cv::Scharr(inpImg,outImg,depth,dx,dy,scale,delta);
            scharrFilter_flag=false;
        }
        //sobel filter
        else if(sobelFilter_flag)
        {
            int depth=-1;
            int dx=1; int dy=0;
            int kernelSize=3;
            double scale=5; double delta=220;
            cv::Sobel(inpImg,outImg,depth,dx,dy,kernelSize,
                          scale,delta);
            sobelFilter_flag=false;
        }

        //write the filtered image to the outImg
        imwrite(fileName.toStdString(),outImg);

        //display output img using opencv
        if(ui->displayImg_checkBox->isChecked())
        {
            imshow("Output Image",outImg);
        }

        //display output img using qt
        QPixmap img = QPixmap(fileName);
        if (!img.isNull())
        {
           delete ui->outputImage_graphicsView->scene();
           ui->outputImage_graphicsView->setScene(new QGraphicsScene(ui->outputImage_graphicsView));
           ui->outputImage_graphicsView->scene()->addPixmap(img);
        }
    }
}
/*//////////////////////////filtering/////////////////////////*/
void MainWindow::img_filtering()
{
    //to save the ouput img
    QString fileName=QFileDialog::getSaveFileName(this,
                                                  "Select Output Image",
                                                  QDir::currentPath(),
                                                  "*.jpg,*.png;;*.bmp");
    if(!fileName.isEmpty())
    {
        ui->output_lineEdit->setText(fileName);
        using namespace cv;
        Mat inpImg, outImg;

        //read the input image
        //OpenCv uses C++ std::string class and the QT uses QString class,
        //we need to convert the format.
        inpImg=imread(ui->input_lineEdit->text().toStdString());

        //Gaussian filter
        if(gaussianFilter_flag || mbGauFilter_flag)
        {
            /*src,dst,ksize,sigmaX,sigmaY
             * sigmaX=Gaussian kernel standard deviation in
             * X direction.
             * sigmaY=Gaussian kernel standard deviation in
             * Y direction.
            */
            cv::GaussianBlur(inpImg,outImg,Size(5,5),1.25);
            gaussianFilter_flag=false;
        }
        //Median blurr filter
        else if(blurrFilter_flag)
        {
            //src,dst,ksize(kernel size)
            cv::medianBlur(inpImg,outImg,5);
            blurrFilter_flag=false;
        }
        //Bilateral filter
        else if(biltrlFilter_flag)
        {
            /*src,dst,ksize,sigmaSpace,maxsigmaColor,bordertype
             * ksize=kernel size
             * sigmaSpace=Larger value of the parameter means
             * that farther pixels will influence each other
             * maxsigmaColor= Larger value of the parameter means
             * that more dissimilar pixels will influence each other
            */
            cv::bilateralFilter(inpImg,outImg,15,200,200);
            biltrlFilter_flag=false;
        }
        //Box filter
        else if(boxFilter_flag)
        {
            Size * kernelSize=new Size(10,10);
            Point * pt=new Point(-1,-1);
            /*src,dst,depth,kernel size,anchor point, normalised*/
            //cv::boxFilter(inpImg,outImg,50,&size,&pt,true);
            boxFilter_flag=false;
        }
        //2D filter flag
        else if(twoDFilter_flag)
        {
            Matx33f f2dkernel (0, -1, 0,
                               -1, 5, -1,
                               0, -1, 0);
            int depth=-1;
            cv::filter2D(inpImg,outImg,depth,f2dkernel);
            twoDFilter_flag=false;
        }
        //edge detection
        else if(edgeDetFilter_flag)
        {
            Matx33f f2dkernel (0, +1.5, 0,
                               +1.5, -6, +1.5,
                               0, +1.5, 0);
            int depth=-1;
            cv::filter2D(inpImg,outImg,depth,f2dkernel);
            edgeDetFilter_flag=false;
        }
        //edge detection(img derivatives)->laplacian
        else if(lapFilter_flag)
        {
            int depth=-1;
            int kernelSize=3;
            double scale=1.0; double delta=0.0;
            cv::Laplacian(inpImg,outImg,depth,kernelSize,
                          scale,delta);
            lapFilter_flag=false;

        }
        //scharr filter
        else if(scharrFilter_flag)
        {
            int depth=-1;
            int dx=1; int dy=0;
            double scale=1.0; double delta=100.0;
            cv::Scharr(inpImg,outImg,depth,dx,dy,scale,delta);
            scharrFilter_flag=false;
        }
        //sobel filter
        else if(sobelFilter_flag)
        {
            int depth=-1;
            int dx=1; int dy=0;
            int kernelSize=3;
            double scale=5; double delta=220;
            cv::Sobel(inpImg,outImg,depth,dx,dy,kernelSize,
                          scale,delta);
            sobelFilter_flag=false;
        }

        //write the filtered image to the outImg
        imwrite(fileName.toStdString(),outImg);

        //display output img using opencv
        if(ui->displayImg_checkBox->isChecked())
        {
            imshow("Output Image",outImg);
        }

        //display output img using qt
        QPixmap img = QPixmap(fileName);
        if (!img.isNull())
        {
           delete ui->outputImage_graphicsView->scene();
           ui->outputImage_graphicsView->setScene(new QGraphicsScene(ui->outputImage_graphicsView));
           ui->outputImage_graphicsView->scene()->addPixmap(img);
        }
    }

}
//smoothing
void MainWindow::img_smoothing()
{
    //to save the ouput img
    QString fileName=QFileDialog::getSaveFileName(this,
                                                  "Select Output Image",
                                                  QDir::currentPath(),
                                                  "*.jpg,*.png;;*.bmp");
    if(!fileName.isEmpty())
    {
        ui->output_lineEdit->setText(fileName);
        using namespace cv;
        Mat inpImg, outImg;

        //read the input image
        //OpenCv uses C++ std::string class and the QT uses QString class,
        //we need to convert the format.
        inpImg=imread(ui->input_lineEdit->text().toStdString());

        //Gaussian filter
        if(gaussSmooth_flag)
        {
            /*src,dst,ksize,sigmaX,sigmaY
             * sigmaX=Gaussian kernel standard deviation in
             * X direction.
             * sigmaY=Gaussian kernel standard deviation in
             * Y direction.
            */
            GaussianBlur(inpImg,outImg,Size(5,5),1.25);
            gaussSmooth_flag=false;
        }
        //Median blurr filter
        else if(medSmooth_flag)
        {
            //src,dst,ksize(kernel size)
            medianBlur(inpImg,outImg,5);
            medSmooth_flag=false;
        }
        //Bilateral filter
        else if(bilatSmooth_flag)
        {
            /*src,dst,ksize,sigmaSpace,maxsigmaColor,bordertype
             * ksize=kernel size
             * sigmaSpace=Larger value of the parameter means
             * that farther pixels will influence each other
             * maxsigmaColor= Larger value of the parameter means
             * that more dissimilar pixels will influence each other
            */
            bilateralFilter(inpImg,outImg,15,200,200);
            bilatSmooth_flag=false;
        }
        else if(blurrSmooth_flag)
        {
            blur(inpImg,outImg,Size(3,3),Point(-1,-1));
            blurrSmooth_flag=false;
        }
        //write the filtered image to the outImg
        imwrite(fileName.toStdString(),outImg);

        //display output img using opencv
        if(ui->displayImg_checkBox->isChecked())
        {
            imshow("Output Image",outImg);
        }

        //display output img using qt
        QPixmap img = QPixmap(fileName);
        if (!img.isNull())
        {
           delete ui->outputImage_graphicsView->scene();
           ui->outputImage_graphicsView->setScene(new QGraphicsScene(ui->outputImage_graphicsView));
           ui->outputImage_graphicsView->scene()->addPixmap(img);
        }
    }
}

//edge detection
void MainWindow::img_edgeDetection()
{
    //to save the ouput img
    QString fileName=QFileDialog::getSaveFileName(this,
                                                  "Select Output Image",
                                                  QDir::currentPath(),
                                                  "*.jpg,*.png;;*.bmp");
    if(!fileName.isEmpty())
    {
        ui->output_lineEdit->setText(fileName);
        using namespace cv;
        Mat inpImg, outImg;

        //read the input image
        //OpenCv uses C++ std::string class and the QT uses QString class,
        //we need to convert the format.
        inpImg=imread(ui->input_lineEdit->text().toStdString());

        //Sobel derivative
        if(sobel_flag)
        {
            /*src,dst,ddepth,xorder,yorder,ksize,scale,delta,border type
             * ddepth=pixel depth of output
             * xorder=order of corresponding derivative in x
             * yorder=order of corresponding derivative in y
             * ksize=kernel size, scale is assigned before assignment
             * de;ta os a[[;oed nefpre assignment
            */
            Sobel(inpImg,outImg,CV_16S,1,1,5,1,1,BORDER_DEFAULT);
            sobel_flag=false;
        }
        //Scharr filter
        else if(scharr_flag)
        {
            //src,dst,ddepth,xorder,yorder,scale,delta
            int depth=-1;
            int dx=1; int dy=0;
            double scale=1.0; double delta=100.0;
            Scharr(inpImg,outImg,depth,dx,dy,scale,delta);
            scharr_flag=false;
        }
        //laplacian
        else if(laplacian_flag)
        {
            /*src,dst,ddepth,ksize,scale,delta,border type*/
            Laplacian(inpImg,outImg,3,1,0, BORDER_DEFAULT);
            laplacian_flag=false;
        }

        //write the filtered image to the outImg
        imwrite(fileName.toStdString(),outImg);

        //display output img using opencv
        if(ui->displayImg_checkBox->isChecked())
        {
            imshow("Output Image",outImg);
        }

        //display output img using qt
        QPixmap img = QPixmap(fileName);
        if (!img.isNull())
        {
           delete ui->outputImage_graphicsView->scene();
           ui->outputImage_graphicsView->setScene(new QGraphicsScene(ui->outputImage_graphicsView));
           ui->outputImage_graphicsView->scene()->addPixmap(img);
        }
    }
}
/*//////////////////////////hough transformation/////////////////////////*/
void MainWindow::img_hougthTransform()
{
    //to save the ouput img
    QString fileName=QFileDialog::getSaveFileName(this,
                                                  "Select Output Image",
                                                  QDir::currentPath(),
                                                  "*.jpg,*.png;;*.bmp");
    if(!fileName.isEmpty())
    {
        ui->output_lineEdit->setText(fileName);
        using namespace cv;
        Mat inputImg,inpImg,outImg;
        //read the input image
        //OpenCv uses C++ std::string class and the QT uses QString class,
        //we need to convert the format.
        inpImg=imread(ui->input_lineEdit->text().toStdString());
        inputImg=inpImg.clone();

        //edge detection
        Mat dst, cdst,cdstP,cdstM,cdstC;
        if(inpImg.channels()>=3)
        {
            cvtColor(inpImg,inpImg,CV_BGR2GRAY);
        }

        Canny(inpImg, dst, 50, 200, 3);
        //imshow("hell",cdst);
        cvtColor(dst, cdst, CV_GRAY2BGR);
        //clone the image for the progressive and multiscale transforms
        cdstP=cdst.clone();
        cdstM=cdst.clone();
        cdstC=cdst.clone();

        //Standard hough line transform
        if(lineStd_flag)
        {
            //Nx1 2 channel array of floating point type
            std::vector<Vec2f> lines;
            /*src,dst,rho,theta,threshold,srn,stn
             * rho=set the resolution desired for the line (uint is pixel)
             * theta=set the resolution desired for the line(uint is radians)
             * srn, stn=used for multiscale hough transform (not for standard
             * hough transform)
            */
            HoughLines(dst,lines,1,CV_PI/180,houghThreshold,0,0);

            //draw the line
            for( size_t i = 0; i < lines.size(); i++ )
              {
                 float rho = lines[i][0], theta = lines[i][1];
                 Point pt1, pt2;
                 double a = cos(theta), b = sin(theta);
                 double x0 = a*rho, y0 = b*rho;
                 pt1.x = cvRound(x0 + 1000*(-b));
                 pt1.y = cvRound(y0 + 1000*(a));
                 pt2.x = cvRound(x0 - 1000*(-b));
                 pt2.y = cvRound(y0 - 1000*(a));
                 line( cdst, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
              }
            outImg=cdst;
            lineStd_flag=false;

        }
        else if(lineProgressive_flag)
        {
            // Probabilistic Line Transform
            std::vector<Vec4i> linesP; // will hold the results of the detection
            //last 2 parameters are min line length and maxlinegap
            HoughLinesP(dst, linesP, 1, CV_PI/180, houghThreshold,lineLen,lineGap );
            // Draw the lines
            for( size_t i = 0; i < linesP.size(); i++ )
            {
                Vec4i l = linesP[i];
                line( cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
            }
            outImg=cdstP;
            lineProgressive_flag=false;

        }
        else if(mhtLine_flag)
        {
            //Nx1 2 channel array of floating point type
            std::vector<Vec2f> lines;
            /*src,dst,rho,theta,threshold,srn,stn
             * rho=set the resolution desired for the line (uint is pixel)
             * theta=set the resolution desired for the line(uint is radians)
             * srn, stn=used for multiscale hough transform (not for standard
             * hough transform)
             * last 2 parameters are used for result refinement
            */
            HoughLines(dst,lines,1,CV_PI/180,houghThreshold,0.03,1);

            //draw the line
            for( size_t i = 0; i < lines.size(); i++ )
              {
                 float rho = lines[i][0], theta = lines[i][1];
                 Point pt1, pt2;
                 double a = cos(theta), b = sin(theta);
                 double x0 = a*rho, y0 = b*rho;
                 pt1.x = cvRound(x0 + 1000*(-b));
                 pt1.y = cvRound(y0 + 1000*(a));
                 pt2.x = cvRound(x0 - 1000*(-b));
                 pt2.y = cvRound(y0 - 1000*(a));
                 line( cdstM, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
              }
            outImg=cdstM;
            mhtLine_flag=false;
        }
        //hough circle transform
        else if(circleHough_flag)
        {
            Mat grayImg;
            //src=inpImg.clone();
            // if colored image -convert it to gray

            // Reduce the noise so we avoid false circle detection
            medianBlur(inpImg, grayImg, 5);
            //GaussianBlur( grayImg, grayImg, Size(9, 9), 2, 2 );

            std::vector<Vec3f> circles;

            // Apply the Hough Transform to find the circles
            HoughCircles( grayImg, circles, CV_HOUGH_GRADIENT, 2,
                          inputImg.cols/minDistance);

            // Draw the circles detected
            for( size_t i = 0; i < circles.size(); i++ )
            {
                Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
                int radius = cvRound(circles[i][2]);
                // circle center
                circle( inputImg, center, 3, Scalar(0,255,0), -1, 8, 0 );
                // circle outline
                circle( inputImg, center, radius, Scalar(0,0,255), 2, 8, 0 );
            }
            //imshow( "Hough Circle Transform Demo", src );
            outImg=inputImg;
            circleHough_flag=false;
        }

        //write the filtered image to the outImg
        imwrite(fileName.toStdString(),outImg);

        //display output img using opencv
        if(ui->displayImg_checkBox->isChecked())
        {
            imshow("Output Image",outImg);
        }

        //display output img using qt
        QPixmap img = QPixmap(fileName);
        if (!img.isNull())
        {
           delete ui->outputImage_graphicsView->scene();
           ui->outputImage_graphicsView->setScene(new QGraphicsScene(ui->outputImage_graphicsView));
           ui->outputImage_graphicsView->scene()->addPixmap(img);
        }

    }
}

//pyramids
void MainWindow::img_pyramids()
{
    if(true)
    {
        //ui->output_lineEdit->setText(fileName);
        using namespace cv;
        Mat inpImg, outImg;

        //read the input image
        //OpenCv uses C++ std::string class and the QT uses QString class,
        //we need to convert the format.
        inpImg=imread(ui->input_lineEdit->text().toStdString());

        for(int i=0;i<pyramidLvl;i++)
        {
            //Gaussian pyramid
            if(gauPyr_flag)
            {
                QString msg="level"+QString::number(i+1);
                //src,dst,size
                pyrDown(inpImg,outImg,Size(inpImg.cols/2,inpImg.rows/2));
                imshow(msg.toStdString(),outImg);
                //copy the outImg to inpImg so that we can process the next level
                outImg.copyTo(inpImg);
            }
            //Laplacian Pyramid
            else if(lapPyr_flag)
            {
                QString msg="level"+QString::number(i+1);
                //src,dst,size
                pyrUp(inpImg,outImg,Size(inpImg.cols*2,inpImg.rows*2));
                imshow(msg.toStdString(),outImg);
                //copy the outImg to inpImg so that we can process the next level
                outImg.copyTo(inpImg);
            }
        }
        gauPyr_flag=false;
        lapPyr_flag=false;
        inpImg=imread(ui->input_lineEdit->text().toStdString());
    }
}
//save output img
bool MainWindow::save_outputImg()
{
    QString FileName=QFileDialog::getSaveFileName(this,
                                                  "Select Output Image",
                                                  QDir::currentPath(),
                                                  "*.jpg,*.png;;*.bmp");
    if(!FileName.isEmpty())
        return true;
    return false;
}

//write the processed img to ouput img and display it.
void MainWindow::writeAndDispImg(QString fn)
{
    using namespace cv;
    Mat outImg;

    //write the filtered image to the outImg
    imwrite(fn.toStdString(),outImg);

    //display output img using opencv
    if(ui->displayImg_checkBox->isChecked())
    {
        imshow("Output Image",outImg);
    }

    //display output img using qt
    QPixmap img = QPixmap(fn);
    if (!img.isNull())
    {
       delete ui->outputImage_graphicsView->scene();
       ui->outputImage_graphicsView->setScene(new QGraphicsScene(ui->outputImage_graphicsView));
       ui->outputImage_graphicsView->scene()->addPixmap(img);
    }

}
//thresholding
void MainWindow::imgThreshold()
{
    //to save the ouput img
    QString fileName=QFileDialog::getSaveFileName(this,
                                                  "Select Output Image",
                                                  QDir::currentPath(),
                                                  "*.jpg,*.png;;*.bmp");
    //bool var=save_outputImg();

    if(!fileName.isEmpty())
    {
        ui->output_lineEdit->setText(fileName);
        using namespace cv;
        Mat inpImg, outImg;

        //read the input image
        //OpenCv uses C++ std::string class and the QT uses QString class,
        //we need to convert the format.
        inpImg=imread(ui->input_lineEdit->text().toStdString());

        if(thresholding_flag)
        {
            Mat grayScale, interMediate;
            /* convert the img to gray scale
             * src, dst, code*/
            cv::cvtColor(inpImg,grayScale,CV_BGR2GRAY);
            /*input,output,thrshld value, max thrshvalue, type*/
            cv::threshold(grayScale,interMediate,thrshldVal,255,THRESH_BINARY_INV);
            //convert img back to BGR color
            cv::cvtColor(interMediate,outImg,CV_GRAY2BGR);
            thresholding_flag=false;
        }
        //adaptive thresholding
        else if(Adpthresholding_flag)
        {
            Mat grayScale,interMediate;
            cv::cvtColor(inpImg,grayScale,CV_BGR2GRAY);
            /*input,output,max thrshvalue,adaptive method,threshold type
            block size, const*/
            cv::adaptiveThreshold(grayScale,interMediate,155,
                                  ADAPTIVE_THRESH_MEAN_C,
                                  THRESH_BINARY,blocksizeVal,constvarVal);
            cv::cvtColor(grayScale,outImg,CV_GRAY2BGR);
        }

        //write the filtered image to the outImg
        imwrite(fileName.toStdString(),outImg);

        //display output img using opencv
        if(ui->displayImg_checkBox->isChecked())
        {
            imshow("Output Image",outImg);
        }

        //display output img using qt
        QPixmap img = QPixmap(fileName);
        if (!img.isNull())
        {
           delete ui->outputImage_graphicsView->scene();
           ui->outputImage_graphicsView->setScene(new QGraphicsScene(ui->outputImage_graphicsView));
           ui->outputImage_graphicsView->scene()->addPixmap(img);
        }
        //writeAndDispImg(FileName);
    }
}

//general image transform
void MainWindow::img_transform()
{
    //to save the ouput img
    QString fileName=QFileDialog::getSaveFileName(this,
                                                  "Select Output Image",
                                                  QDir::currentPath(),
                                                  "*.jpg,*.png;;*.bmp");
    if(!fileName.isEmpty())
    {
        ui->output_lineEdit->setText(fileName);
        using namespace cv;
        Mat img, mask,maskGrayScale,dst;

        using namespace cv;
        img=imread(ui->input_lineEdit->text().toStdString());

        //inpainting
        if(inpaint_flag)
        {
            mask=imread(maskStr.toStdString());
            cvtColor(mask,maskGrayScale,CV_BGR2GRAY);

            //check if the images are read
            if(img.empty() || maskGrayScale.empty())
            {
                qDebug()<<"Error reading file(s)!";
            }
            //inpainting
            /*input image,mask image,output image, inpaint radius, flags
             *mask image: damaged area (same size as input image)
             *inpaint radius: range to consider around pixel
             *flags: select NS or TELEA*/
            if(inpaintMethod==0){
                inpaint(img,maskGrayScale,dst,3,INPAINT_NS);
            }
            else
            {
                inpaint(img,maskGrayScale,dst,3,INPAINT_TELEA);
            }
            inpaint_flag=false;
        }

        //histogram equalization
        else if(hist_flag)
        {
            //if image is colored
            if(img.channels()>=3)
            {
                Mat ycrcb;
                cvtColor(img,ycrcb,CV_BGR2YCrCb);
                std::vector<Mat> channels;
                split(ycrcb,channels);
                //Perform HE of the intensity plane Y
                equalizeHist(channels[0], channels[0]);
                merge(channels,ycrcb);
                cvtColor(ycrcb,dst,CV_YCrCb2BGR);
            }
            else
            {
                equalizeHist(img,dst);
            }
            hist_flag=false;
        }

        //write the filtered image to the outImg
        imwrite(fileName.toStdString(),dst);

        //display output img using opencv
        if(ui->displayImg_checkBox->isChecked())
        {
            imshow("Output_Image",dst);
        }

        //display output img using qt
        QPixmap img1 = QPixmap(fileName);
        if (!img1.isNull())
        {
           delete ui->outputImage_graphicsView->scene();
           ui->outputImage_graphicsView->setScene(new QGraphicsScene(ui->outputImage_graphicsView));
           ui->outputImage_graphicsView->scene()->addPixmap(img1);
        }

     }
}
//Image Morphology
void MainWindow::imgMorphology()
{
    //to save the ouput img
    QString fileName=QFileDialog::getSaveFileName(this,
                                                  "Select Output Image",
                                                  QDir::currentPath(),
                                                  "*.jpg,*.png;;*.bmp");
    //bool var=save_outputImg();

    if(!fileName.isEmpty())
    {
        ui->output_lineEdit->setText(fileName);
        using namespace cv;
        Mat inpImg, outImg;

        //read the input image
        //OpenCv uses C++ std::string class and the QT uses QString class,
        //we need to convert the format.
        inpImg=imread(ui->input_lineEdit->text().toStdString());

        //erosion
        if(erosion_flag)
        {
            erode(inpImg,outImg,Mat()); //Mat() is 3x3 kernel
            erosion_flag=false;
        }
        //dilation
        else if(dilation_flag)
        {
            dilate(inpImg,outImg,Mat());
            dilation_flag=false;
        }
        //opening
        else if(open_flag)
        {
            morphologyEx(inpImg,outImg,MORPH_OPEN,Mat());
        }
        //closing
        else if(close_flag)
        {
            morphologyEx(inpImg,outImg,MORPH_CLOSE,Mat());
        }
        //gradient
        else if(gradient_flag)
        {
            morphologyEx(inpImg,outImg,MORPH_GRADIENT,Mat());
        }
        //tophat
        else if(tophat_flag)
        {
            morphologyEx(inpImg,outImg,MORPH_TOPHAT,Mat());
        }
        //write the filtered image to the outImg
        imwrite(fileName.toStdString(),outImg);

        //display output img using opencv
        if(ui->displayImg_checkBox->isChecked())
        {
            imshow("Output Image",outImg);
        }

        //display output img using qt
        QPixmap img = QPixmap(fileName);
        if (!img.isNull())
        {
           delete ui->outputImage_graphicsView->scene();
           ui->outputImage_graphicsView->setScene(new QGraphicsScene(ui->outputImage_graphicsView));
           ui->outputImage_graphicsView->scene()->addPixmap(img);
        }
        //writeAndDispImg(FileName);
    }

}

//template matching
void MainWindow::imgtemplateMatching()
{
    //to save the ouput img
    QString fileName=QFileDialog::getSaveFileName(this,
                                                  "Select Output Image",
                                                  QDir::currentPath(),
                                                  "*.jpg,*.png;;*.bmp");
    if(!fileName.isEmpty())
    {
        ui->output_lineEdit->setText(fileName);
        using namespace cv;
        Mat img, temp1;

        //read the input image
        //OpenCv uses C++ std::string class and the QT uses QString class,
        //we need to convert the format.
        img=imread(ui->input_lineEdit->text().toStdString());
        temp1=imread(templateImg.toStdString());
        //create the empty result Mat according to the img and template size
        //it will contain the best location for out template match
        Mat result(img.rows-temp1.rows+1,img.cols-temp1.cols+1,CV_32FC1);
        //image,template to search,Mat to store the result,method
        matchTemplate(img,temp1,result,TM_CCORR_NORMED);
        //use minMaxLoc to draw the rectangle around the best match
        double minVal,maxVal;
        Point minLoc,maxLoc;
        minMaxLoc(result,&minVal,&maxVal,&minLoc,&maxLoc);
        rectangle(img,
                  Rect(maxLoc.x,maxLoc.y,temp1.cols,temp1.rows),
                  Scalar(0,0,255),
                  2);

        //write the filtered image to the outImg
        imwrite(fileName.toStdString(),img);

        //display output img using opencv
        if(ui->displayImg_checkBox->isChecked())
        {
            imshow("Output Image",img);
        }

        //display output img using qt
        QPixmap img1 = QPixmap(fileName);
        if (!img1.isNull())
        {
           delete ui->outputImage_graphicsView->scene();
           ui->outputImage_graphicsView->setScene(new QGraphicsScene(ui->outputImage_graphicsView));
           ui->outputImage_graphicsView->scene()->addPixmap(img1);
        }
    }
}

//multiple template matching
void MainWindow::imgMulTemplateMatching()
{
    //to save the ouput img
    QString fileName=QFileDialog::getSaveFileName(this,
                                                  "Select Output Image",
                                                  QDir::currentPath(),
                                                  "*.jpg,*.png;;*.bmp");
    if(!fileName.isEmpty())
    {
        ui->output_lineEdit->setText(fileName);
        using namespace cv;
        Mat img, temp1;

        using namespace cv;
        img=imread(ui->input_lineEdit->text().toStdString());
        temp1=imread(templateImg.toStdString());

        //check if the images are read
        if(img.empty() || temp1.empty())
        {
            qDebug()<<"Error reading file(s)!";
        }

        Mat gimg, gtemp1;
        //change to grayscale
        cvtColor(img, gimg, CV_BGR2GRAY);
        cvtColor(temp1, gtemp1, CV_BGR2GRAY);

        //apply the Canny filter
        const int canny_low = 110;
        Canny(gimg, gimg, canny_low, canny_low*3);
        Canny(gtemp1, gtemp1, canny_low, canny_low*3);

        imshow("image", gimg);
        imshow("template", gtemp1);

        //generate the result Mat according to the image and template size
        Mat res_32f(img.rows - temp1.rows + 1, img.cols - temp1.cols + 1, CV_32FC1);
        matchTemplate(gimg, gtemp1, res_32f, CV_TM_CCOEFF_NORMED);

        Mat res;
        res_32f.convertTo(res, CV_8U, 255.0);
        imshow("result", res);

        //force size to be odd
        int size = ((temp1.cols + temp1.rows) / 4) * 2 + 1;
        //thresholding
        adaptiveThreshold(res, res, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, size, -64);
        imshow("result_thresholding", res);

        while(1)
        {
            double minval, maxval;
            Point minloc, maxloc;
            //find the min and max location and draw the rectangle
            minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);

            //find all the matching templates
            if(maxval > 0)
            {
                rectangle(img, maxloc, Point(maxloc.x + temp1.cols, maxloc.y + temp1.rows), Scalar(0,255,0), 2);
                floodFill(res, maxloc, 0); //mark drawn blob
            }
            else
            {
                break;
            }
        }
        //write the filtered image to the outImg
        imwrite(fileName.toStdString(),img);

        //display output img using opencv
        if(ui->displayImg_checkBox->isChecked())
        {
            imshow("Output_Image",img);
        }

        //display output img using qt
        QPixmap img1 = QPixmap(fileName);
        if (!img1.isNull())
        {
           delete ui->outputImage_graphicsView->scene();
           ui->outputImage_graphicsView->setScene(new QGraphicsScene(ui->outputImage_graphicsView));
           ui->outputImage_graphicsView->scene()->addPixmap(img1);
        }

        imshow("final", img);
     }
}

//feature detector
//AGAST algo
void MainWindow::imgFetDetector()
{
    /*Adaptive and Genric accelerated segment test
     *useful in corner detection*/
    //to save the ouput img
    QString fileName=QFileDialog::getSaveFileName(this,
                                                  "Select Output Image",
                                                  QDir::currentPath(),
                                                  "*.jpg,*.png;;*.bmp");
    if(!fileName.isEmpty())
    {
        ui->output_lineEdit->setText(fileName);
        using namespace cv;
        using namespace std;
        Mat inpImg,inputImage, outputImage;

        using namespace cv;
        inputImage=imread(ui->input_lineEdit->text().toStdString());
        //check if the images are read
        if(inputImage.empty())
        {
            qDebug()<<"Error reading file(s)!";
        }
        //blurr filter to reduce unwanted keypoints
        //medianBlur(inpImg,inputImage,5);
        vector<KeyPoint> keypoints;

        if(AGAST_flag)
        {
            AGAST(inputImage,
                  keypoints,
                  threshld, //threshold value
                  maxSup, //maximum supression
                  algo_type); //algorithm type
            AGAST_flag=false;
        }
        else if(BRISK_flag)
        {
            Ptr<BRISK> brisk=
                    BRISK::create(BRISK_thrshld,
                                  BRISK_octaves,
                                  BRISK_pattern);
            BRISK_flag=false;
        }

        drawKeypoints(inputImage,keypoints,outputImage);
        //imshow("Output Image", outputImage);
        imwrite(fileName.toStdString(),outputImage);

        //display output img using opencv
        if(ui->displayImg_checkBox->isChecked())
        {
            imshow("Output_Image",outputImage);
        }

        //display output img using qt
        QPixmap img1 = QPixmap(fileName);
        if (!img1.isNull())
        {
           delete ui->outputImage_graphicsView->scene();
           ui->outputImage_graphicsView->setScene(new QGraphicsScene(ui->outputImage_graphicsView));
           ui->outputImage_graphicsView->scene()->addPixmap(img1);
        }
     }
}

//extract and match
void MainWindow::imgExtractAndMatch()
{
    //to save the ouput img
    QString fileName=QFileDialog::getSaveFileName(this,
                                                  "Select Output Image",
                                                  QDir::currentPath(),
                                                  "*.jpg,*.png;;*.bmp");
    cv::Mat outputImage;
    if(!fileName.isEmpty())
    {
        if(extractAndMatch_flag)
        {
            using namespace cv;
            using namespace std;
            ui->output_lineEdit->setText(fileName);
            using namespace cv;
            Mat img1, img2;
            vector<DMatch> matches;
            //extract keypoints from both the images
            img2=imread(ui->input_lineEdit->text().toStdString());
            img1=imread("C:/ComputerVision/Images/firstt2.jpg");

            //Step 1: AKAZE algo to detect keypoints
            Ptr<AKAZE> akaze=AKAZE::create();
            vector<KeyPoint> keypoints1,keypoints2;
            //set the algo parameters
            akaze->setDescriptorChannels(3);
            akaze->setDescriptorSize(0);
            akaze->setDescriptorType(desType);
            akaze->setDiffusivity(diffusvty);
            akaze->setNOctaves(octave_no);
            akaze->setNOctaveLayers(octave_layr);
            akaze->setThreshold(emThreshold);
            akaze->detect(img1,keypoints1);
            akaze->detect(img2,keypoints2);

            //Step 2: Extract the descriptors
            Mat descriptor1,descriptor2;
            akaze->compute(img1,keypoints1,descriptor1);
            akaze->compute(img2,keypoints2,descriptor2);

            //Step 3: Descriptor matching
            Ptr<DescriptorMatcher> descMather;
            descMather=DescriptorMatcher::create(descriptor_matcher);
                        //DescriptorMatcher::FLANNBASED);
            descMather->match(descriptor1, descriptor2, matches);

            // Find good matches (AKAZE)
            vector<DMatch> goodMatches;
            double matchThresh = 0.1;
            for(int i=0; i<descriptor1.rows; i++)
            {
                if(matches[i].distance < matchThresh)
                    goodMatches.push_back(matches[i]);
            }

            //Mat outputImage;
            drawMatches(img1,
                        keypoints1,
                        img2,
                        keypoints2,
                        goodMatches,
                        outputImage);

            vector<Point2f> goodP1, goodP2;
            for(size_t i=0; i<goodMatches.size(); i++)
            {
                goodP1.push_back(keypoints1[goodMatches[i].queryIdx].pt);
                goodP2.push_back(keypoints2[goodMatches[i].trainIdx].pt);
            }
            Mat homoChange = findHomography(goodP1, goodP2);

            vector<Point2f> corners1(4), corners2(4);
            corners1[0] = Point2f(0,0);
            corners1[1] = Point2f(img1.cols-1, 0);
            corners1[2] = Point2f(img1.cols-1, img1.rows-1);
            corners1[3] = Point2f(0, img1.rows-1);

            perspectiveTransform(corners1, corners2, homoChange);
            //img2.copyTo(outputImage);
            Point2f offset(img1.cols, 0);

            line(outputImage, corners2[0] + offset, corners2[1] + offset, Scalar::all(1), 2);
            line(outputImage, corners2[1] + offset, corners2[2] + offset, Scalar::all(1), 2);
            line(outputImage, corners2[2] + offset, corners2[3] + offset, Scalar::all(1), 2);
            line(outputImage, corners2[3] + offset, corners2[0] + offset, Scalar::all(1), 2);

            /*//call the match function
            vector<DMatch> matches;
            descMather->match(descriptors1,descriptors2,matches);

            Mat dispImg;
            drawMatches(img1,
                        keypoints1,
                        img2,
                        keypoints2,
                        matches,
                        dispImg,
                        Scalar(0,255,0),
                        Scalar::all(-1),
                        vector<char>(),
                        DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
            imshow("oo",dispImg);
            //filter out unwanted matching results
            vector<DMatch> goodMatches;
            double matchThresh=0.1;
            for(int i=0;i<descriptors1.rows;i++)
            {
                if(matches[i].distance<matchThresh)
                    goodMatches.push_back(matches[i]);
            }
            //use goodMatches to find the homography change
            vector<Point2f> goodP1,goodP2;
            for(int i=0;i<goodMatches.size();i++)
            {
                goodP1.push_back(keypoints1[goodMatches[i].queryIdx].pt);
                goodP2.push_back(keypoints2[goodMatches[i].trainIdx].pt);
            }
            Mat homoChange=findHomography(goodP1,goodP2);

            //apply perspective transform to the matched points using homography
            //change matrix
            vector<Point2f> corners1 (4), corners2 (4);
            corners1[0] = Point2f(0,0);
            corners1[1] = Point2f(img1.cols-1, 0);
            corners1[2] = Point2f(img1.cols-1, img1.rows-1);
            corners1[3] = Point2f(0, img1.rows-1);

            perspectiveTransform(corners1, corners2, homoChange);

            img2.copyTo(dispImg);

            //Point2f offset(img1.cols, 0);

            line(dispImg, corners2[0], corners2[1], Scalar::all(255), 2);
            line(dispImg, corners2[1], corners2[2], Scalar::all(255), 2);
            line(dispImg, corners2[2], corners2[3], Scalar::all(255), 2);
            line(dispImg, corners2[3], corners2[0], Scalar::all(255), 2);*/

            imshow("output image",outputImage);
            imwrite(fileName.toStdString(),outputImage);

            //display output img using opencv
            if(ui->displayImg_checkBox->isChecked())
            {
                imshow("Output_Image",outputImage);
            }

            //display output img using qt
            QPixmap img_out = QPixmap(fileName);
            if (!img_out.isNull())
            {
               delete ui->outputImage_graphicsView->scene();
               ui->outputImage_graphicsView->setScene(new QGraphicsScene(ui->outputImage_graphicsView));
               ui->outputImage_graphicsView->scene()->addPixmap(img_out);
            }
            extractAndMatch_flag=false;
        }
    }
}

/*////////////////////////////////////////////////////////*/
//Gaussian filter
void MainWindow::on_actionGaussian_triggered()
{
    gaussianFilter_flag=true;
    //call the filtering function
    img_filtering();
}

/*Blurr filter
 * takes median of all the pixels under kernel area and central element
 * is replaced with this median value. This is highly effective against
 * salt-and-pepper noise in the images.*/
void MainWindow::on_actionBlurr_triggered()
{
    blurrFilter_flag=true;
    //call the filtering function
    img_filtering();
}

/*Bilateral filter
 * It is highly effective in noise removal while keeping edges sharp.
 * But the operation is slower compared to other filters*/
void MainWindow::on_actionBilateral_triggered()
{
    biltrlFilter_flag=true;
    img_filtering();
}

/*Box filter*/
void MainWindow::on_actionBox_triggered()
{
    boxFilter_flag=true;
    img_filtering();
}

/*2D filter (image sharpening)*/
void MainWindow::on_action2D_Filter_triggered()
{
    twoDFilter_flag=true;
    img_filtering();
}

/*Edge detection*/
void MainWindow::on_actionEdge_Detection_triggered()
{
    edgeDetFilter_flag=true;
    img_filtering();
}

/*Edge detection (img derivatives)*/
//laplacian
void MainWindow::on_actionLaplacian_triggered()
{
    lapFilter_flag=true;
    img_filtering();
}
//Scharr filter
void MainWindow::on_actionScharr_triggered()
{
    scharrFilter_flag=true;
    img_filtering();
}
//Sobel filter
void MainWindow::on_actionSobel_triggered()
{
    sobelFilter_flag=true;
    img_filtering();
}

/*//////////////////////Close Event////////////////*/
//code to be executed when a window is closed
void MainWindow::closeEvent(QCloseEvent *event)
{
    int result=QMessageBox::warning(this,
                                    "Exit",
                                    "Are you sure you want to close this program?",
                                    QMessageBox::Yes,
                                    QMessageBox::No);
    if(result==QMessageBox::Yes)
    {
        //save the settings while closing the app
        //saveSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

/*///////////////////Push Button Filters//////////////////*/
//for signal coming from filtersDialog.cpp file
void MainWindow::on_gauFilter_flag(bool b)
{
    mbGauFilter_flag=b;
    img_filtering();
}
void MainWindow::on_bilateralFilterSignal(bool b)
{
    biltrlFilter_flag=b;
    img_filtering();
}
void MainWindow::on_boxFilterSignal(bool b)
{
    boxFilter_flag=b;
    img_filtering();
}
void MainWindow::on_edgeFilterSignal(bool b)
{
    edgeDetFilter_flag=b;
    img_filtering();
}
void MainWindow::on_laplacianFilterSignal(bool b)
{
    lapFilter_flag=b;
    img_filtering();
}
void MainWindow::on_medianFilterSignal(bool b)
{
    medianFilter_flag=b;
    img_filtering();
}
void MainWindow::on_twoDFilterSignal(bool b)
{
    twoDFilter_flag=b;
    img_filtering();
}
void MainWindow::on_filtering_pushButton_clicked()
{
    //model approach
    filtersDialog fd(this);

    //connection
    //connect the gauFilter_flag from filtersDialog.cpp file to here
    //when the button is pressed is pressed in filtersDialog then the
    //other thread in mainwindow.cpp file is notified to filter the image
    connect(&fd, &filtersDialog::gauFilter_flag,this,
            &MainWindow::on_gauFilter_flag);
    connect(&fd,&filtersDialog::medianFilterSignal,this,
            &MainWindow::on_medianFilterSignal);
    connect(&fd,&filtersDialog::twoDFilterSignal,this,
            &MainWindow::on_twoDFilterSignal);
    connect(&fd,&filtersDialog::laplacianFilterSignal,this,
            &MainWindow::on_laplacianFilterSignal);
    connect(&fd,&filtersDialog::boxFilterSignal,this,
            &MainWindow::on_boxFilterSignal);
    connect(&fd,&filtersDialog::edgeFilterSignal,this,
            &MainWindow::on_edgeFilterSignal);
    connect(&fd,&filtersDialog::bilateralFilterSignal,this,
            &MainWindow::on_bilateralFilterSignal);

    fd.setModal(true);
    fd.exec();
}
/*//////////////////Push Button Thresholding////////////////*/
//thresholding
void MainWindow::on_thresholdingSignal(bool b,int t)
{
    thresholding_flag=b;
    thrshldVal=t;
    imgThreshold();
}
void MainWindow::on_AdpthresholdingSignal(bool b,int bl,int c)
{
    Adpthresholding_flag=b;
    blocksizeVal=bl; constvarVal=c;
    imgThreshold();
}
void MainWindow::on_thresholding_pushButton_clicked()
{
    thresholdingDialog td(this);

    //connection
    //connect the thresholdingSignal from thresholdingDialog.cpp file to here
    //when the button is in thresholdingDialog is pressed then the
    //other thread in mainwindow.cpp file is notified to threshold the image
    connect (&td, &thresholdingDialog::thresholdingSignal, this,
             &MainWindow::on_thresholdingSignal);
    connect (&td,&thresholdingDialog::AdpthresholdingSignal,this,
             &MainWindow::on_AdpthresholdingSignal);
    td.setModal(true);
    td.exec();
}

/*//////////////////Push Button Morphology////////////////////*/
void MainWindow::on_erosionSignal(bool b)
{
    erosion_flag=b;
    imgMorphology();
}
void MainWindow::on_dilationSignal(bool b)
{
    dilation_flag=b;
    imgMorphology();
}
void MainWindow::on_openSignal(bool b)
{
    open_flag=b;
    imgMorphology();
}
void MainWindow::on_closeSignal(bool b)
{
    close_flag=b;
    imgMorphology();
}
void MainWindow::on_gradientSignal(bool b)
{
    gradient_flag=b;
    imgMorphology();
}
void MainWindow::on_tophatSignal(bool b)
{
    tophat_flag=b;
    imgMorphology();
}
void MainWindow::on_morphology_pushButton_clicked()
{
    morphologyDialog md(this);
    //connection
    //connect the erosionSignal from morphologyDialog.cpp file to here
    //when the button is in morphologyDialog is pressed then the
    //other thread in mainwindow.cpp file is notified to erode the image
    connect(&md,&morphologyDialog::erosionSignal,this,
            &MainWindow::on_erosionSignal);
    connect(&md,&morphologyDialog::dilationSignal,this,
            &MainWindow::on_dilationSignal);
    connect(&md,&morphologyDialog::openSignal,this,
            &MainWindow::on_openSignal);
    connect(&md,&morphologyDialog::closeSignal,this,
            &MainWindow::on_closeSignal);
    connect(&md,&morphologyDialog::gradientSignal,this,
            &MainWindow::on_gradientSignal);
    connect(&md,&morphologyDialog::tophatSignal,this,
            &MainWindow::on_tophatSignal);
    md.setModal(true);
    md.exec();
}

/*//////////////////Push Button Template Matching///////////*/
void MainWindow::on_templateMatchingSignal(bool b, bool mul_b,
                                           QString tmpltStr)
{
    //single template matching
    if(b==true)
    {
        templateMatching_flag=b;
        templateImg=tmpltStr;
        imgtemplateMatching();
    }
    //multiple template matching
    else if(mul_b==true)
    {
        multemplateMatching_flag=mul_b;
        templateImg=tmpltStr;
        imgMulTemplateMatching();
    }

}
void MainWindow::on_templateMat_pushButton_clicked()
{
    templateMatchingDialog tmd(this);
    connect(&tmd,&templateMatchingDialog::templateMatchingSignal,
            this,&MainWindow::on_templateMatchingSignal);
    tmd.setModal(true);
    tmd.exec();
}

/*//////////////////Push Button Multiple Template Matching///////////*/
void MainWindow::on_mulTemplatemat_pushButton_clicked()
{
    templateMatchingDialog mtmd(this);
    connect(&mtmd,&templateMatchingDialog::templateMatchingSignal,
            this,&MainWindow::on_templateMatchingSignal);
    mtmd.setModal(true);
    mtmd.exec();

}

/*//////////////////Push Button Feature Detection///////////*/
void MainWindow::on_AGASTSignal(bool b,int thrs,bool ifChecked,
                                int type)
{
    AGAST_flag=b;
    threshld=thrs;
    maxSup=ifChecked;
    algo_type=type;
    imgFetDetector();
}
void MainWindow::on_BRISKSignal(bool b, int t,int o, int p)
{
    BRISK_flag=b;
    BRISK_thrshld=t;
    BRISK_octaves=o;
    BRISK_pattern=p;
    imgFetDetector();
}
void MainWindow::on_fDetection_pushButton_clicked()
{
    featureDetectorDialog fdd(this);
    //connect AGAST_signal from featureDetectorDialog to mainwindow
    connect(&fdd,&featureDetectorDialog::AGAST_signal,this,
            &MainWindow::on_AGASTSignal);
    //connect BRISK_signal to here
    connect(&fdd,&featureDetectorDialog::BRISK_signal,this,
            &MainWindow::on_BRISKSignal);
    fdd.setModal(true);
    fdd.exec();
}

/*//////////////////Push Button Extraction & Matching///////////*/
void MainWindow::on_extractAndMatchSignal(bool b,int d,double t,int o,
                                          int ol,int diff,int desMatcher)
{
    extractAndMatch_flag=b;
    desType=d;
    emThreshold=t;
    octave_no=o;
    octave_layr=ol;
    diffusvty=diff;
    descriptor_matcher=desMatcher;
    imgExtractAndMatch();
}
void MainWindow::on_emd_pushButton_clicked()
{
    extrctAndMtchDialog emd(this);
    //connection
    connect(&emd,&extrctAndMtchDialog::extractAndMatchSignal,this,
            &MainWindow::on_extractAndMatchSignal);
    emd.setModal(true);
    emd.exec();
}

/*//////////////////Push Button Smoothing///////////*/
void MainWindow::on_smoothingSignal(bool b,bool bl,bool m,bool g,bool bil)
{
    blurrSmooth_flag=bl; medSmooth_flag=m;
    gaussSmooth_flag=g; bilatSmooth_flag=bil;
    img_smoothing();
}
void MainWindow::on_smoothing_pushButton_clicked()
{
    smoothDialog sd(this);
    //connection
    connect(&sd,&smoothDialog::smoothingSignal,this,
            &MainWindow::on_smoothingSignal);
    sd.setModal(true);
    sd.exec();
}
/*//////////////////Push Button Pyramids///////////*/
void MainWindow::on_pyramidSignal(bool g,bool l,int pl)
{
    gauPyr_flag=g; lapPyr_flag=l; pyramidLvl=pl;
    img_pyramids();
}
void MainWindow::on_pyramid_pushButton_clicked()
{
    pyramidsDialog pd(this);
    //connection
    connect(&pd,&pyramidsDialog::pyramidSignal,this,
            &MainWindow::on_pyramidSignal);
    pd.setModal(true);
    pd.exec();
}
/*/////////////Push Button Edge Detection//////////*/
void MainWindow::on_edgeDet_pushButton_clicked()
{
    //to save the ouput img
    QString fileName=QFileDialog::getSaveFileName(this,
                                                  "Save Output Image",
                                                  QDir::currentPath(),
                                                  "*.jpg,*.png;;*.bmp");
    //bool var=save_outputImg();

    if(!fileName.isEmpty())
    {
        ui->output_lineEdit->setText(fileName);
        using namespace cv;
        Mat inpImg, outImg;

        //read the input image
        //OpenCv uses C++ std::string class and the QT uses QString class,
        //we need to convert the format.
        inpImg=imread(ui->input_lineEdit->text().toStdString());
        //change the image to gray scale
        cvtColor(inpImg,outImg,CV_BGR2GRAY);
        //blur the image
        blur(outImg,outImg,Size(3,3));
        //canny operator
        int thrshld=0;
        Canny(outImg,outImg,thrshld,thrshld*3,3);

        //write the filtered image to the outImg
        imwrite(fileName.toStdString(),outImg);

        //display output img using opencv
        if(ui->displayImg_checkBox->isChecked())
        {
            imshow("Output Image",outImg);
        }

        //display output img using qt
        QPixmap img = QPixmap(fileName);
        if (!img.isNull())
        {
           delete ui->outputImage_graphicsView->scene();
           ui->outputImage_graphicsView->setScene(new QGraphicsScene(ui->outputImage_graphicsView));
           ui->outputImage_graphicsView->scene()->addPixmap(img);
        }
    }
}
/*/////////////Push Button Contours///////////////////////*/
void MainWindow::on_contour_pushButton_clicked()
{
    //to save the ouput img
    QString fileName=QFileDialog::getSaveFileName(this,
                                                  "Save Output Image",
                                                  QDir::currentPath(),
                                                  "*.jpg,*.png;;*.bmp");
    //bool var=save_outputImg();

    if(!fileName.isEmpty())
    {
        ui->output_lineEdit->setText(fileName);
        using namespace cv;
        using namespace std;
        Mat inpImg, outImg;

        //read the input image
        //OpenCv uses C++ std::string class and the QT uses QString class,
        //we need to convert the format.
        inpImg=imread(ui->input_lineEdit->text().toStdString());
        //change the image to gray scale
        cvtColor(inpImg,outImg,CV_BGR2GRAY);
        //blur the image
        blur(outImg,outImg,Size(3,3));
        //canny operator
        int thrshld=75;
        Canny(outImg,outImg,thrshld,thrshld*2,3);
        //find contour
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        findContours(outImg,contours,hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE,
                     Point(0,0));
        //Draw contours
        RNG rng(12345);
        Mat drawing = Mat::zeros(outImg.size(), CV_8UC3 );
        for( int i = 0; i< contours.size(); i++ )
         {
           Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
           drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
         }

        //write the filtered image to the outImg
        imwrite(fileName.toStdString(),drawing);

        //display output img using opencv
        if(ui->displayImg_checkBox->isChecked())
        {
            imshow("Output Image",drawing);
        }

        //display output img using qt
        QPixmap img = QPixmap(fileName);
        if (!img.isNull())
        {
           delete ui->outputImage_graphicsView->scene();
           ui->outputImage_graphicsView->setScene(new QGraphicsScene(ui->outputImage_graphicsView));
           ui->outputImage_graphicsView->scene()->addPixmap(img);
        }
    }
}
/*/////////////Push Button Border Extrapolation///////////////////////*/
void MainWindow::on_border_pushButton_clicked()
{
    borderDialog bd(this);
    //connection
    connect(&bd,&borderDialog::borderSignal,this,&MainWindow::
            on_borderSignal);
    bd.setModal(true);
    bd.exec();
}

void MainWindow::on_borderSignal(bool constant,bool wrap, bool rep, bool ref,
                                 bool ref101)
{
    constBorderFlag=constant; wrapBorderFlag=wrap; repBorderFlag=rep;
    refBorderFlag=ref; ref101BorderFlag=ref101;

    img_border();

}

/*/////////////Push Button Edge Detection///////////////////////*/
void MainWindow::on_edgeDet_pushButton_2_clicked()
{
    edgeDetectionDialog ed(this);
    //connection
    connect(&ed,&edgeDetectionDialog::edgeDetSignal,this,
            &MainWindow::on_edgeDetSignal);
    ed.setModal(true);
    ed.exec();
}

void MainWindow::on_edgeDetSignal(bool s, bool sc, bool l)
{
    sobel_flag=s; scharr_flag=sc, laplacian_flag=l;
    img_edgeDetection();
}

void MainWindow::on_imgTransform_pushButton_clicked()
{
    ImgTransformDialog itd(this);
    //connection
    connect(&itd,&ImgTransformDialog::imgTransformSignal,this,
            &MainWindow::on_imgTransformSignal);
    itd.setModal(true);
    itd.exec();
}
void MainWindow::on_imgTransformSignal(bool i,QString str,int m,bool h)
{
    inpaint_flag=i; hist_flag=h;
    maskStr=str;
    inpaintMethod=m;
    img_transform();
}

/*/////////////Hough Transform///////////////////////////*/
void MainWindow::on_hough_pushButton_clicked()
{
    houghDialog hd(this);
    //connection
    connect(&hd,&houghDialog::houghTransform,this,&MainWindow::on_houghTransform);
    connect(&hd,&houghDialog::thresholdChange,this,&MainWindow::on_thresholdChange);
    connect(&hd,&houghDialog::LineLenChange,this,&MainWindow::on_LineLenChange);
    connect(&hd,&houghDialog::LineGapChange,this,&MainWindow::on_LineGapChange);
    connect(&hd,&houghDialog::minDistChange,this,&MainWindow::on_minDistChange);
    hd.setModal(true);
    hd.exec();
}
void MainWindow::on_houghTransform(bool sl,bool pl, bool m,bool c)
{
    lineStd_flag=sl; lineProgressive_flag=pl; mhtLine_flag=m;
    circleHough_flag=c;
    img_hougthTransform();
}
void MainWindow::on_thresholdChange(int t)
{
    houghThreshold=t;
}
void MainWindow::on_LineLenChange(int l)
{
    lineLen=l;
}
void MainWindow::on_LineGapChange(int l)
{
    lineGap=l;
}
void MainWindow::on_minDistChange(int d)
{
    minDistance=d;
}
