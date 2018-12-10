#include "RecipeSeach.h"
#include "ui_Recipe_seach.h"
#include <QDebug>
#include <QVector>
#include <QString>

RecipeSeach::RecipeSeach(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeSeach)
{
    ui->setupUi(this);
    ui->lineEdit_recipeName->setValidator(new QRegExpValidator(QRegExp("[A-Z/a-z/а-я/A-Я\\s]{1,}\[A-Z/a-z/а-я/A-Я\\s]{1,}")));

    connect(ui->pushButton_search, SIGNAL(pressed()), SLOT(onPushButtonSeach()));
    connect(ui->pushButton_searchAll, SIGNAL(pressed()), SIGNAL(requireUpdateAllInform()));
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

    for (int iRow = 0; iRow < _recipes.size(); ++iRow) {
        QVector<QString> itemValues = {
            _recipes[iRow].name(),
            QLocale::system().toString(_recipes[iRow].proteins()),
            QLocale::system().toString(_recipes[iRow].fats()),
            QLocale::system().toString(_recipes[iRow].carbohydrates()),
            QLocale::system().toString(_recipes[iRow].kkal())
        };
        for(int i = 0; i < itemValues.size(); ++i){
            QTableWidgetItem* item = new QTableWidgetItem(itemValues[i]);
            ui->tableWidget_recipe->setItem(iRow, i, item);
        }
    }
    this->repaint();
}

RecipeEntity RecipeSeach::selectedRecipe() const
{
    return _selectedRecipe;
}

void RecipeSeach::hideInformationIfExists(const RecipeEntity &recipe)
{
    for(const auto &tmp : _recipes){
        if (tmp.id() == recipe.id()){
            for(int i = 0; ui->tableWidget_recipe->rowCount(); ++i){
                if (tmp.name() == ui->tableWidget_recipe->item(i, 0)->text()){
                    ui->tableWidget_recipe->removeRow(i);
                    return;
                }
            }
        }
    }
}

void RecipeSeach::updateInformationIfExist(RecipeEntity &recipe)
{
    for(const auto &tmp : _recipes){
        if (tmp.id() == recipe.id()){
            for(int i = 0; ui->tableWidget_recipe->rowCount(); ++i){
                if (tmp.name() == ui->tableWidget_recipe->item(i, 0)->text()){
                    ui->tableWidget_recipe->item(i, 0)->setText(recipe.name());
                    ui->tableWidget_recipe->item(i, 0)->setText(QLocale::system().toString(recipe.proteins()));
                    ui->tableWidget_recipe->item(i, 0)->setText(QLocale::system().toString(recipe.fats()));
                    ui->tableWidget_recipe->item(i, 0)->setText(QLocale::system().toString(recipe.carbohydrates()));
                    ui->tableWidget_recipe->item(i, 0)->setText(QLocale::system().toString(recipe.kkal()));
                    return;
                }
            }
        }
    }
}
void RecipeSeach::onPushButtonSeach()
{
    int from = 0;
    int to = 0;
    if (ui->radioButton_productSearch->isChecked()) {
        QString seach = ui->lineEdit_recipeName->text();
        if (!seach.isEmpty()) {
            emit seachLineRecipeReady(seach);
        }
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


void RecipeSeach::paintEvent(QPaintEvent *event)
{
    auto width = ui->tableWidget_recipe->width();
    ui->tableWidget_recipe->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_recipe->setColumnWidth(0, width * 8/12-10);
    ui->tableWidget_recipe->setColumnWidth(1, width * 1/12-10);
    ui->tableWidget_recipe->setColumnWidth(2, width * 1/12-10);
    ui->tableWidget_recipe->setColumnWidth(3, width * 1/12-10);
    ui->tableWidget_recipe->setColumnWidth(4, width * 1/12-10);

    QWidget::paintEvent(event);
}
