#ifndef PRODUCTSEACH_H
#define PRODUCTSEACH_H

#include <QWidget>

namespace Ui {
class ProductSeach;
}

class ProductSeach : public QWidget
{
    Q_OBJECT

public:
    explicit ProductSeach(QWidget *parent = nullptr);
    ~ProductSeach();

private:
    Ui::ProductSeach *ui;
};

#endif // PRODUCTSEACH_H
