#include "productinfo.h"
#include "ui_productinfo.h"

ProductInfo::ProductInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductInfo)
{
    ui->setupUi(this);
}

ProductInfo::~ProductInfo()
{
    delete ui;
}
