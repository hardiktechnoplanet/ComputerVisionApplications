#ifndef IMGSEGMENTATIONDIALOG_H
#define IMGSEGMENTATIONDIALOG_H

#include <QDialog>

namespace Ui {
class imgSegmentationDialog;
}

class imgSegmentationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit imgSegmentationDialog(QWidget *parent = 0);
    ~imgSegmentationDialog();

signals:
    //wastershed, Grabcuts,Mean-shift segmentation
    void segmentation(bool,bool,bool);

private slots:
    void on_watershed_radioButton_clicked();

private:
    Ui::imgSegmentationDialog *ui;
};

#endif // IMGSEGMENTATIONDIALOG_H
