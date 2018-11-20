#include "ProductInfo.h"
#include "ui_Product_info.h"

ProductInfo::ProductInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductInfo)
{
    ui->setupUi(this);

    connect(ui->pushButton_productEdit, SIGNAL(pressed()), SIGNAL(editProductButtonPressed()));
}

void ProductInfo::setInformation(const ProductEntity &p)
{
    _product = p;

    ui->label_productName->setText(p.name());
    ui->label_numProtein->setText(QString::number(p.proteins()));
    ui->label_numFats->setText(QString::number(p.fats()));
    ui->label_numCarbohydrates->setText(QString::number(p.carbohydrates()));
    ui->label_numKcal->setText(QString::number(p.kilocalories()));
    ui->textBrowser_description->setText(p.description());

    this->repaint();
}

ProductEntity ProductInfo::product() const
{
    return _product;
}

ProductInfo::~ProductInfo()
{
    delete ui;
}
