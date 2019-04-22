#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include "opencv2/opencv.hpp"
#include <QMessageBox>
#include <QCloseEvent>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_inputImage_pushButton_clicked();

    //commonly used functions
    bool save_outputImg();
    void writeAndDispImg(QString fn);

    //filtering
    void img_filtering();
    void on_actionGaussian_triggered();
    void on_actionBlurr_triggered();
    void on_actionBilateral_triggered();
    void on_actionBox_triggered();
    void on_action2D_Filter_triggered();
    void on_actionEdge_Detection_triggered();
    void on_actionLaplacian_triggered();
    void on_actionScharr_triggered();
    void on_actionSobel_triggered();

    //filtering using the push button
    void on_filtering_pushButton_clicked();
    void on_gauFilter_flag(bool);
    //thresholding
    void on_thresholdingSignal(bool);
    void on_AdpthresholdingSignal(bool);
    void imgThreshold();

    void on_thresholding_pushButton_clicked();

    //morphology
    void on_morphology_pushButton_clicked();
    void on_dilationSignal(bool);
    void on_erosionSignal(bool);
    void on_openSignal(bool);
    void on_closeSignal(bool);
    void on_gradientSignal(bool);
    void on_tophatSignal(bool);
    void imgMorphology();

    //template matching
    void on_templateMatchingSignal(bool,bool,QString);
    void on_templateMat_pushButton_clicked();
    void imgtemplateMatching();

    //multiple template matching
    void on_mulTemplatemat_pushButton_clicked();
    void imgMulTemplateMatching();

    //feature detector
    void on_fDetection_pushButton_clicked();
    //AGAST algo
    void on_AGASTSignal(bool,int,bool,int);
    void imgAGASTfetDetector();

private:
    Ui::MainWindow *ui;

    //for saving output file
    QString FileName;

    //filter flags
    bool gaussianFilter_flag;
    bool blurrFilter_flag;
    bool biltrlFilter_flag;
    bool boxFilter_flag;
    bool twoDFilter_flag;
    bool edgeDetFilter_flag;
    bool lapFilter_flag;
    bool scharrFilter_flag;
    bool sobelFilter_flag;

    //push button filter flags
    bool mbGauFilter_flag;
    //thresholding
    bool thresholding_flag;
    bool Adpthresholding_flag;
    //morphology
    bool erosion_flag;
    bool dilation_flag;
    bool open_flag;
    bool close_flag;
    bool gradient_flag;
    bool tophat_flag;
    //template matching
    bool templateMatching_flag;
    QString templateImg;
    //multiple template matching
    bool multemplateMatching_flag;
    //feature detector
    //AGAST
    bool AGAST_flag, maxSup;
    int threshld, algo_type;

protected:
    //to prompt the user when they want to close
    //the program
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
