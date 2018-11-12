#include "activityinfo.h"
#include "ui_Activity_info.h"

ActivityInfo::ActivityInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActivityInfo)
{
    ui->setupUi(this);
}

ActivityInfo::~ActivityInfo()
{
    delete ui;
}
