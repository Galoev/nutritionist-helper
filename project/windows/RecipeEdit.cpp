#include "recipeedit.h"
#include "ui_Recipe_edit.h"

RecipeEdit::RecipeEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeEdit)
{
    ui->setupUi(this);
}

RecipeEdit::~RecipeEdit()
{
    delete ui;
}
