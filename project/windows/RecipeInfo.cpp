#include "RecipeInfo.h"
#include "ui_Recipe_info.h"

RecipeInfo::RecipeInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeInfo)
{
    ui->setupUi(this);

    connect(ui->pushButton_recipeEdit, SIGNAL(pressed()), SIGNAL(editRecipeButtonPressed()));
}

void RecipeInfo::setInformation(const RecipeEntity &r)
{
    _recipe = r;
    QVector<WeightedProduct> products = _recipe.getPoducts();
    ui->label_recipeName->setText(_recipe.name());
    ui->tableWidget_ingredientList->setRowCount(products.size());

    int sumProtein = 0;
    int sumFats = 0;
    int sumCarbohydrates = 0;
    int sumKcal = 0;

    for (int iRow = 0; iRow < products.size(); ++iRow)
    {
        ui->tableWidget_ingredientList->setItem(iRow, 0, new QTableWidgetItem(products.at(iRow).product().name()));
        ui->tableWidget_ingredientList->setItem(iRow, 1, new QTableWidgetItem(products.at(iRow).amound()));
        sumProtein += products.at(iRow).product().proteins();
        sumFats += products.at(iRow).product().fats();
        sumCarbohydrates += products.at(iRow).product().carbohydrates();
        sumKcal += products.at(iRow).product().kilocalories();
    }

    ui->label_numProtein->setText(QString::number(sumProtein));
    ui->label_numFats->setText(QString::number(sumFats));
    ui->label_numCarbohydrates->setText(QString::number(sumCarbohydrates));
    ui->label_numKcal->setText(QString::number(sumKcal));

    QStringList cookingPoints = _recipe.getCookingPoints();

    for (int iRow = 0; iRow < cookingPoints.size(); ++iRow)
    {
        ui->tableWidget_recipeDescription->setItem(iRow, 0, new QTableWidgetItem(cookingPoints.at(iRow)));
    }

    this->repaint();
}

RecipeEntity RecipeInfo::recipe() const
{
    return _recipe;
}

RecipeInfo::~RecipeInfo()
{
    delete ui;
}
