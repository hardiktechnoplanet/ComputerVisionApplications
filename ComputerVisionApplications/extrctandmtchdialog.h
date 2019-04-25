#ifndef EXTRCTANDMTCHDIALOG_H
#define EXTRCTANDMTCHDIALOG_H

#include <QDialog>

namespace Ui {
class extrctAndMtchDialog;
}

class extrctAndMtchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit extrctAndMtchDialog(QWidget *parent = 0);
    ~extrctAndMtchDialog();

private:
    Ui::extrctAndMtchDialog *ui;
};

#endif // EXTRCTANDMTCHDIALOG_H
