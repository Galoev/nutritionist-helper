#include "ActivityCalculation.h"
#include "ui_Activity_calculation.h"

ActivityCalculation::ActivityCalculation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActivityCalculation)
{
    ui->setupUi(this);
}

ActivityCalculation::~ActivityCalculation()
{
    delete ui;
}

void ActivityCalculation::paintEvent(QPaintEvent *event)
{
    const int borderOffset = 1;
    const int coefColumn[2] = { 3/4 - borderOffset
                              , 1/4 - borderOffset };

    auto activitiesWidth = ui->activitiesTable->width();
    ui->activitiesTable->setColumnWidth(0, activitiesWidth * coefColumn[0]);
    ui->activitiesTable->setColumnWidth(1, activitiesWidth * coefColumn[1]);
    auto productsWidth = ui->activitiesTable->width();
    ui->productsTable->setColumnWidth(0, productsWidth * coefColumn[0]);
    ui->productsTable->setColumnWidth(1, productsWidth * coefColumn[1]);

    QWidget::paintEvent(event);
}
