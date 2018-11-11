#include "recipeseach.h"
#include "ui_Recipe_seach.h"

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
