#include "recipeinfo.h"
#include "ui_recipeinfo.h"

RecipeInfo::RecipeInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeInfo)
{
    ui->setupUi(this);
}

RecipeInfo::~RecipeInfo()
{
    delete ui;
}
