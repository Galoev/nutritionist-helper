#include "ActivitySeach.h"
#include "ui_Activity_seach.h"

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
