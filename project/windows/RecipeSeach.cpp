#include "recipeseach.h"
#include "ui_recipeseach.h"

RecipeSeach::RecipeSeach(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeSeach)
{
    ui->setupUi(this);
}

RecipeSeach::~RecipeSeach()
{
    delete ui;
}
