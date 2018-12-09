#ifndef PRODUCTINFO_H
#define PRODUCTINFO_H

#include <QWidget>
#include "entities/product.h"

namespace Ui {
class ProductInfo;
}

class ProductInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ProductInfo(QWidget *parent = nullptr);
    ~ProductInfo();

    void setInformation(const ProductEntity& );
    ProductEntity product() const;

signals:
    void editProductButtonPressed();
    void deleteProductButtonPressed();

private:
    Ui::ProductInfo *ui;
    ProductEntity _product;
};

#endif // PRODUCTINFO_H
