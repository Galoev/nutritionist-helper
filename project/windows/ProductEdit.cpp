#include "productedit.h"
#include "ui_Product_edit.h"

#include <QRegExpValidator>

ProductEdit::ProductEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductEdit)
{
    ui->setupUi(this);

    ui->lineEdit_productName->setValidator(new QRegExpValidator(QRegExp("[\\w]+")));
    ui->lineEdit_numProtein->setValidator(new QIntValidator(0, 1000));
    ui->lineEdit_numFats->setValidator(new QIntValidator(0, 1000));
    ui->lineEdit_numCarbohydrates->setValidator(new QIntValidator(0, 1000));
    ui->lineEdit_numKcal->setValidator(new QIntValidator(0, 10000));

    connect(ui->pushButton_save, SIGNAL(pressed()), SLOT(onPushButtonSave()));
    connect(ui->pushButton_cancel, SIGNAL(pressed()), SLOT(onPushButtonCancel()));
}

ProductEdit::~ProductEdit()
{
    delete ui;
}
