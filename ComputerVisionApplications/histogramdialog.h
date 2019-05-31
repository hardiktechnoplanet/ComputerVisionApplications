#ifndef HISTOGRAMDIALOG_H
#define HISTOGRAMDIALOG_H

#include <QDialog>

namespace Ui {
class histogramDialog;
}

class histogramDialog : public QDialog
{
    Q_OBJECT

public:
    explicit histogramDialog(QWidget *parent = 0);
    ~histogramDialog();

signals:
    void histogram(bool);

private slots:
    void on_histogram_pushButton_clicked();

private:
    Ui::histogramDialog *ui;
};

#endif // HISTOGRAMDIALOG_H
