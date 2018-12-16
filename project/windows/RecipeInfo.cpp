#include "RecipeInfo.h"
#include "ui_Recipe_info.h"

RecipeInfo::RecipeInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeInfo)
{
    ui->setupUi(this);
    ui->tableWidget_ingredientList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_ingredientList->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_recipeDescription->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_recipeDescription->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    connect(ui->pushButton_recipeEdit, SIGNAL(pressed()), SIGNAL(editRecipeButtonPressed()));
    connect(ui->pushButton_delete, SIGNAL(pressed()), SIGNAL(deleteRecipeButtonPressed()));
}

void RecipeInfo::setInformation(const RecipeEntity &r)
{
    _recipe = r;
    QVector<WeightedProduct> products = _recipe.getPoducts();
    ui->label_recipeName->setText(_recipe.name());
    ui->tableWidget_ingredientList->setRowCount(products.size());

    for (int iRow = 0; iRow < products.size(); ++iRow) {
        ui->tableWidget_ingredientList->setItem(iRow, 0, new QTableWidgetItem(products.at(iRow).product().name()));
        ui->tableWidget_ingredientList->setItem(iRow, 1, new QTableWidgetItem(QLocale::system().toString(products.at(iRow).amound())));
        ui->tableWidget_ingredientList->setItem(iRow, 2, new QTableWidgetItem(products.at(iRow).product().units() == ProductEntity::GRAMM ? "гр" : products.at(iRow).product().units() == ProductEntity::MILLILITER ? "мл" : "???"));
    }

    auto proteins = QLocale::system().toString(_recipe.proteins());
    ui->label_numProtein->setText(proteins);
    auto fats = QLocale::system().toString(_recipe.fats());
    ui->label_numFats->setText(fats);
    auto carbohydrates = QLocale::system().toString(_recipe.carbohydrates());
    ui->label_numCarbohydrates->setText(carbohydrates);
    auto kcal = QLocale::system().toString(_recipe.kkal());
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

void RecipeInfo::paintEvent(QPaintEvent *event)
{
    auto width = ui->tableWidget_ingredientList->width();
    ui->tableWidget_ingredientList->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_ingredientList->setColumnWidth(0, width * 8/12-10);
    ui->tableWidget_ingredientList->setColumnWidth(1, width * 3/12-10);
    ui->tableWidget_ingredientList->setColumnWidth(2, width * 1/12-10);

    ui->tableWidget_recipeDescription->resizeRowsToContents();
    auto width2 = ui->tableWidget_recipeDescription->width();
    ui->tableWidget_recipeDescription->setColumnWidth(0, width2 * 8/12-10);
    QWidget::paintEvent(event);
}

RecipeInfo::~RecipeInfo()
{
    delete ui;
}
