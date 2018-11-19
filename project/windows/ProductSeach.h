#ifndef PRODUCTSEACH_H
#define PRODUCTSEACH_H

#include <QWidget>
#include <QVector>
#include "entities/product.h"

namespace Ui {
class ProductSeach;
}

class ProductSeach : public QWidget
{
    Q_OBJECT

public:
    explicit ProductSeach(QWidget *parent = nullptr);
    ~ProductSeach();

    void setInformation(const QVector<ProductEntity>& );
    ProductEntity selectedProduct() const;
    int getCurrentRow();

signals:
    void seachLineProductReady(const QString& );
    void seachLineProteinReady(const int from, const int to);
    void seachLineFatsReady(const int from, const int to);
    void seachLineCarbohydratesReady(const int from, const int to);
    void selectedForShow();

private slots:
    void onPushButtonSeach();
    void onProductNameSeachType();
    void onPFCSeachType();
    void onSelectProduct(const QModelIndex& );

private:
    Ui::ProductSeach *ui;
    QVector<ProductEntity> _products;
    ProductEntity _selectedProduct;
};

#endif // PRODUCTSEACH_H
