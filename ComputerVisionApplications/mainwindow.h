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
    void on_bilateralFilterSignal(bool);
    void on_boxFilterSignal(bool);
    void on_medianFilterSignal(bool);
    void on_twoDFilterSignal(bool);
    void on_edgeFilterSignal(bool);
    void on_laplacianFilterSignal(bool);

    //border
    void on_borderSignal(bool,bool,bool,bool,bool);
    void img_border();

    //smoothing
    //flag,blue,median,gaussian,bilateral
    void on_smoothingSignal(bool,bool,bool,bool,bool);
    void img_smoothing();

    //edge detection
    void on_edgeDetSignal(bool,bool,bool);
    void img_edgeDetection();

    //general image transform
    void on_imgTransformSignal(bool,QString,int,bool);
    void img_transform();

    //hough transform
    void on_houghTransform(bool,bool,bool,bool);
    void on_thresholdChange(int);
    void on_LineLenChange(int);
    void on_LineGapChange(int);
    void on_minDistChange(int);
    void img_hougthTransform();

    //image segmentation
    void on_segmentation(bool,bool,bool);
    void img_segmentation();

    //pyramids
    //gaussian,laplacian,pyramid level
    void on_pyramidSignal(bool,bool,int);
    void img_pyramids();

    //thresholding
    void on_thresholdingSignal(bool,int);
    void on_AdpthresholdingSignal(bool,int,int);
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
    void imgFetDetector();
    //AGAST algo
    void on_AGASTSignal(bool,int,bool,int);
    //BRISK algo
    void on_BRISKSignal(bool,int,int,int);

    //extraction and matching
    void on_emd_pushButton_clicked();
    void on_extractAndMatchSignal(bool,int,double,int,int,int,int);
    void imgExtractAndMatch();

    void on_smoothing_pushButton_clicked();

    void on_pyramid_pushButton_clicked();

    void on_edgeDet_pushButton_clicked();

    void on_contour_pushButton_clicked();

    void on_border_pushButton_clicked();

    void on_edgeDet_pushButton_2_clicked();

    void on_imgTransform_pushButton_clicked();

    void on_hough_pushButton_clicked();

    void on_segment_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    //for saving output file
    QString FileName;

    //border flags
    bool constBorderFlag, wrapBorderFlag;
    bool refBorderFlag, ref101BorderFlag;
    bool repBorderFlag;
    //filter flags
    bool gaussianFilter_flag;
    bool blurrFilter_flag;
    bool medianFilter_flag;
    bool boxFilter_flag;
    bool twoDFilter_flag;
    bool edgeDetFilter_flag;
    bool lapFilter_flag;
    bool biltrlFilter_flag;
    bool scharrFilter_flag;
    bool sobelFilter_flag;

    //smoothing flags
    bool blurrSmooth_flag; bool medSmooth_flag;
    bool gaussSmooth_flag; bool bilatSmooth_flag;

    //edge detection flags
    bool scharr_flag, sobel_flag, laplacian_flag;

    //general image transform
    bool inpaint_flag, hist_flag;
    QString maskStr; int inpaintMethod;
    //hough transform
    bool lineStd_flag,lineProgressive_flag,mhtLine_flag,circleHough_flag;
    int houghThreshold,lineLen,lineGap,minDistance;
    //image segmentation
    bool watershed_flag, grabcut_flag,meanshift_flag;
    //pyramids flags
    bool gauPyr_flag; bool lapPyr_flag; int pyramidLvl;

    //push button filter flags
    bool mbGauFilter_flag;
    //thresholding
    bool thresholding_flag;bool Adpthresholding_flag;
    int thrshldVal, blocksizeVal, constvarVal;
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
    //BRISK
    bool BRISK_flag;
    int BRISK_thrshld,BRISK_octaves,BRISK_pattern;

    //extract and match
    bool extractAndMatch_flag;
    int desType,octave_no,octave_layr,diffusvty,descriptor_matcher;
    double emThreshold;

protected:
    //to prompt the user when they want to close
    //the program
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
