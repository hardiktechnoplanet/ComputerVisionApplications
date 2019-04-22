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

private slots:
    void on_gaussian_pushButton_clicked();

private:
    Ui::filtersDialog *ui;
};

#endif // FILTERSDIALOG_H
