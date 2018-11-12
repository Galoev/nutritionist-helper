#include "activityedit.h"
#include "ui_Activity_edit.h"

#include <QRegExpValidator>

ActivityEdit::ActivityEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActivityEdit)
{
    ui->setupUi(this);

    ui->lineEdit_activityName->setValidator(new QRegExpValidator(QRegExp("[\\w]+")));
    ui->lineEdit_calories->setValidator(new QIntValidator(0, 100000));

    connect(ui->pushButton_save, SIGNAL(pressed()), SLOT(onPushButtonSave()));
    connect(ui->pushButton_cancel, SIGNAL(pressed()), SLOT(onPushButtonCancel()));
}

ActivityEdit::~ActivityEdit()
{
    delete ui;
}
