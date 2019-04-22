#ifndef FILTERS_H
#define FILTERS_H

#include <QDialog>

namespace Ui {
class filters;
}

class filters : public QDialog
{
    Q_OBJECT

public:
    explicit filters(QWidget *parent = 0);
    ~filters();

private:
    Ui::filters *ui;
};

#endif // FILTERS_H
