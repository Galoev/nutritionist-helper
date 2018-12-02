#include "RecipeInfo.h"
#include "ui_Recipe_info.h"

RecipeInfo::RecipeInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeInfo)
{
    ui->setupUi(this);
    ui->tableWidget_ingredientList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_ingredientList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_recipeDescription->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_recipeDescription->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->pushButton_recipeEdit, SIGNAL(pressed()), SIGNAL(editRecipeButtonPressed()));
}

void RecipeInfo::setInformation(const RecipeEntity &r)
{
    _recipe = r;
    QVector<WeightedProduct> products = _recipe.getPoducts();
    ui->label_recipeName->setText(_recipe.name());
    ui->tableWidget_ingredientList->setRowCount(products.size());

    for (int iRow = 0; iRow < products.size(); ++iRow) {
        ui->tableWidget_ingredientList->setItem(iRow, 0, new QTableWidgetItem(products.at(iRow).product().name()));
        ui->tableWidget_ingredientList->setItem(iRow, 1, new QTableWidgetItem(QString::number(products.at(iRow).amound())));
    }

    auto proteins = QString::number(_recipe.proteins());
    ui->label_numProtein->setText(proteins);
    auto fats = QString::number(_recipe.fats());
    ui->label_numFats->setText(fats);
    auto carbohydrates = QString::number(_recipe.carbohydrates());
    ui->label_numCarbohydrates->setText(carbohydrates);
    auto kcal = QString::number(_recipe.kkal());
    ui->label_numKcal->setText(kcal);

    QStringList cookingPoints = _recipe.getCookingPoints();
    ui->tableWidget_recipeDescription->setRowCount(cookingPoints.size());

    for (int iRow = 0; iRow < cookingPoints.size(); ++iRow) {
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
