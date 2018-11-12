#ifndef PRODUCTINFO_H
#define PRODUCTINFO_H

#include <QWidget>

namespace Ui {
class ProductInfo;
}

class ProductInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ProductInfo(QWidget *parent = nullptr);
    ~ProductInfo();

private:
    Ui::ProductInfo *ui;
};

#endif // PRODUCTINFO_H
