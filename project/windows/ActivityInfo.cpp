#include "ActivityInfo.h"
#include "ui_Activity_info.h"

ActivityInfo::ActivityInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActivityInfo)
{
    ui->setupUi(this);
    connect(ui->pushButton_activityEdit, SIGNAL(pressed()), SIGNAL(editActivityButtonPressed()));
}

void ActivityInfo::setInformation(const ActivityEntity &a)
{
    _activity = a;

    ui->label_activityName->setText(a.type());
    ui->label_kcal->setText(QLocale::system().toString(a.kkm()));

    this->repaint();
}

ActivityEntity ActivityInfo::activity() const
{
    return _activity;
}

ActivityInfo::~ActivityInfo()
{
    delete ui;
}
