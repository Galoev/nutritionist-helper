#include "activityedit.h"
#include "ui_Activity_edit.h"

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
