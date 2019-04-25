#ifndef FILTERSDIALOG_H
#define FILTERSDIALOG_H

#include <QDialog>

namespace Ui {
class filtersDialog;
}

class filtersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit filtersDialog(QWidget *parent = 0);
    ~filtersDialog();

signals:
    void gauFilter_flag(bool);
    void medianFilterSignal(bool);
    void bilateralFilterSignal(bool);
    void boxFilterSignal(bool);
    void twoDFilterSignal(bool);
    void edgeFilterSignal(bool);
    void laplacianFilterSignal(bool);

private slots:
    void on_gaussian_pushButton_clicked();

    void on_median_pushButton_clicked();

    void on_bilateral_pushButton_clicked();

    void on_box_pushButton_clicked();

    void on_twoD_pushButton_clicked();

    void on_edge_pushButton_clicked();

    void on_laplacian_pushButton_clicked();

private:
    Ui::filtersDialog *ui;
};

#endif // FILTERSDIALOG_H
