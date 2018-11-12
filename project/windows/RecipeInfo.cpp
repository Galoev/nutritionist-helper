#include "recipeinfo.h"
#include "ui_Recipe_info.h"

RecipeInfo::RecipeInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeInfo)
{
    ui->setupUi(this);

    connect(ui->pushButton_recipeEdit, SIGNAL(pressed()), SIGNAL(editRecipeButtonPressed()));
}

RecipeInfo::~RecipeInfo()
{
    delete ui;
}
