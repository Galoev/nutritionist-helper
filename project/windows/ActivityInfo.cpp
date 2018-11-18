#include "ActivityInfo.h"
#include "ui_Activity_info.h"

ActivityInfo::ActivityInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActivityInfo)
{
    ui->setupUi(this);
    connect(ui->pushButton_activityEdit, SIGNAL(pressed()), SIGNAL(editActivityButtonPressed()));
}

ActivityInfo::~ActivityInfo()
{
    delete ui;
}
