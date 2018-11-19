#include "RecipeSeach.h"
#include "ui_Recipe_seach.h"
#include <QDebug>

RecipeSeach::RecipeSeach(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeSeach)
{
    ui->setupUi(this);

    connect(ui->pushButton_search, SIGNAL(pressed()), SLOT(onPushButtonSeach()));
    connect(ui->radioButton_productSearch, SIGNAL(pressed()), SLOT(onRecipeNameSeachType()));
    connect(ui->radioButton_proteinSearch, SIGNAL(pressed()), SLOT(onPFCSeachType()));
    connect(ui->radioButton_fatsSearch, SIGNAL(pressed()), SLOT(onPFCSeachType()));
    connect(ui->radioButton_carbohydratesSearch, SIGNAL(pressed()), SLOT(onPFCSeachType()));
    connect(ui->tableWidget_recipe, SIGNAL(pressed(QModelIndex)), SLOT(onSelectRecipe(QModelIndex)));
}

void RecipeSeach::setInformation(const QVector<RecipeEntity> &recipes)
{
    _recipes = recipes;

    ui->tableWidget_recipe->setRowCount(_recipes.size());

    for (int iRow = 0; iRow < _recipes.size(); ++iRow)
    {
        ui->tableWidget_recipe->setItem(iRow, 0, new QTableWidgetItem(_recipes[iRow].name()));
        ui->tableWidget_recipe->setItem(iRow, 1, new QTableWidgetItem("-1"));
        ui->tableWidget_recipe->setItem(iRow, 2, new QTableWidgetItem("-1"));
        ui->tableWidget_recipe->setItem(iRow, 3, new QTableWidgetItem("-1"));
        ui->tableWidget_recipe->setItem(iRow, 4, new QTableWidgetItem("-1"));
    }

    this->repaint();
}

RecipeEntity RecipeSeach::selectedRecipe() const
{
    return _selectedRecipe;
}

void RecipeSeach::onPushButtonSeach()
{
    int from = 0;
    int to = 0;
    if (ui->radioButton_productSearch->isChecked()) {
        QString seach = ui->lineEdit_recipeName->text();
        if (!seach.isEmpty()) {
            emit seachLineRecipeReady(seach);
        } else if (ui->radioButton_proteinSearch->isChecked()) {
            from = ui->spinBox_From->value();
            to = ui->spinBox_To->value();
            emit seachLineProteinReady(from, to);
        } else if (ui->radioButton_fatsSearch->isChecked()) {
            from = ui->spinBox_From->value();
            to = ui->spinBox_To->value();
            emit seachLineFatsReady(from, to);
        } else if (ui->radioButton_carbohydratesSearch->isChecked()) {
            from = ui->spinBox_From->value();
            to = ui->spinBox_To->value();
            emit seachLineCarbohydratesReady(from, to);
        }
    }
}

void RecipeSeach::onRecipeNameSeachType()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void RecipeSeach::onPFCSeachType()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void RecipeSeach::onSelectRecipe(const QModelIndex &index)
{
    int selectedRecipe = index.row();
    if (selectedRecipe >= _recipes.size() && selectedRecipe < 0)
    {
        qDebug() << "Error: ProductSeach::onSelectProduct(const QModelIndex &)"
                 << "Not correct client vector index";
    }
    _selectedRecipe = _recipes[selectedRecipe];
    emit selectedForShow();
}

RecipeSeach::~RecipeSeach()
{
    delete ui;
}
