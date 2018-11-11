#include "productseach.h"
#include "ui_Product_seach.h"

ProductSeach::ProductSeach(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductSeach)
{
    ui->setupUi(this);
}

ProductSeach::~ProductSeach()
{
    delete ui;
}
