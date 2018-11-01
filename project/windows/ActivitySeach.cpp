#include "activityseach.h"
#include "ui_activityseach.h"

ActivitySeach::ActivitySeach(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActivitySeach)
{
    ui->setupUi(this);
}

ActivitySeach::~ActivitySeach()
{
    delete ui;
}
