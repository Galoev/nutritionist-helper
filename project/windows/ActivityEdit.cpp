#include "activityedit.h"
#include "ui_activityedit.h"

ActivityEdit::ActivityEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActivityEdit)
{
    ui->setupUi(this);
}

ActivityEdit::~ActivityEdit()
{
    delete ui;
}
