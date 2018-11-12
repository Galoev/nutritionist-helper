#include "recipeedit.h"
#include "ui_Recipe_edit.h"

#include <QRegExpValidator>

RecipeEdit::RecipeEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeEdit)
{
    ui->setupUi(this);

    connect(ui->pushButton_save, SIGNAL(pressed()), SLOT(onPushButtonSave()));
    connect(ui->pushButton_cancel, SIGNAL(pressed()), SLOT(onPushButtonCancel()));
}

RecipeEdit::~RecipeEdit()
{
    delete ui;
}
