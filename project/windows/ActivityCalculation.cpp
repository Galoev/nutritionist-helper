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
