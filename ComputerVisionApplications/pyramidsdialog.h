#ifndef PYRAMIDSDIALOG_H
#define PYRAMIDSDIALOG_H

#include <QDialog>

namespace Ui {
class pyramidsDialog;
}

class pyramidsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit pyramidsDialog(QWidget *parent = 0);
    ~pyramidsDialog();

private:
    Ui::pyramidsDialog *ui;
};

#endif // PYRAMIDSDIALOG_H
