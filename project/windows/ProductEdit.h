#pragma once
#include <QWidget>
#include "entities/product.h"

namespace Ui {
class ProductEdit;
}

class ProductEdit : public QWidget
{
    Q_OBJECT

public:
    explicit ProductEdit(QWidget *parent = nullptr);
    ~ProductEdit();

    void setInformation(const ProductEntity& );
    ProductEntity product() const;

signals:
    void formNewProductReady();
    void formEditedProductReady();

private slots:
    void onPushButtonSave();
    void onPushButtonCancel();

private:
    Ui::ProductEdit *ui;
    ProductEntity _product;
    bool _isEditingMod = false;
};
