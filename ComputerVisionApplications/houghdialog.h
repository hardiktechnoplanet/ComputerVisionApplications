#ifndef HOUGHDIALOG_H
#define HOUGHDIALOG_H

#include <QDialog>

namespace Ui {
class houghDialog;
}

class houghDialog : public QDialog
{
    Q_OBJECT

public:
    explicit houghDialog(QWidget *parent = 0);
    ~houghDialog();

signals:
    //std line, progressive line, multiscale line,circle
    void houghTransform(bool,bool,bool,bool);
    void thresholdChange(int);
    //for progressive HT
    void LineLenChange(int);
    void LineGapChange(int);
    void minDistChange(int);

private slots:
    void on_standard_radioButton_clicked();

    void on_progressive_radioButton_clicked();

    void on_threshold_spinBox_valueChanged(int arg1);

    void on_lineGap_spinBox_valueChanged(int arg1);

    void on_lineLen_spinBox_valueChanged(int arg1);

    void on_multiscale_radioButton_clicked();

    void on_circle_radioButton_clicked();

    void on_minDist_spinBox_valueChanged(int arg1);

private:
    Ui::houghDialog *ui;
};

#endif // HOUGHDIALOG_H
