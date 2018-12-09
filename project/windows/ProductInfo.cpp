#include "ProductInfo.h"
#include "ui_Product_info.h"
#include <QDebug>

ProductInfo::ProductInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductInfo)
{
    ui->setupUi(this);

    connect(ui->pushButton_productEdit, SIGNAL(pressed()), SIGNAL(editProductButtonPressed()));
    connect(ui->pushButton_delete, SIGNAL(pressed()), SIGNAL(deleteProductButtonPressed()));
}

void ProductInfo::setInformation(const ProductEntity &p)
{
    _product = p;

    ui->label_productName->setText(p.name());
    ui->label_numProtein->setText(QLocale::system().toString(p.proteins()));
    ui->label_numFats->setText(QLocale::system().toString(p.fats()));
    ui->label_numCarbohydrates->setText(QLocale::system().toString(p.carbohydrates()));
    ui->label_numKcal->setText(QLocale::system().toString(p.kilocalories()));
    ui->label_unitsType->setText(p.units() == ProductEntity::GRAMM ? "гр" : p.units() == ProductEntity::MILLILITER ? "мл" : "???");
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
