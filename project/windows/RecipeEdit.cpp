#include "recipeedit.h"
#include "ui_recipeedit.h"

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
