#include "ProductInfo.h"
#include "ui_Product_info.h"

ProductInfo::ProductInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductInfo)
{
    ui->setupUi(this);

    connect(ui->pushButton_productEdit, SIGNAL(pressed()), SIGNAL(editProductButtonPressed()));
}

ProductInfo::~ProductInfo()
{
    delete ui;
}
