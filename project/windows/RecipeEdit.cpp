#include "RecipeEdit.h"
#include "ui_Recipe_edit.h"
#include <QVBoxLayout>
#include <QRegExpValidator>
#include <QDebug>
#include <QMessageBox>

RecipeEdit::RecipeEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeEdit)
{
    ui->setupUi(this);
    _productSeach = new ProductSeach(ui->widget_product_search);
    _productSeach->resize(457,200);
    ui->lineEdi_recipeName->setValidator(new QRegExpValidator(QRegExp("[A-Z/a-z/а-я/A-Я]{1,}\[A-Z/a-z/а-я/A-Я\\s]{1,}")));
    ui->tableWidget_ingredientList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->pushButton_save, SIGNAL(pressed()), SLOT(onPushButtonSave()));
    connect(ui->pushButton_cancel, SIGNAL(pressed()), SLOT(onPushButtonCancel()));
    connect(ui->pushButton_addIngredient, SIGNAL(pressed()), SLOT(onPushButtonAddIngredient()));
    connect(ui->pushButton_deleteIngredient, SIGNAL(pressed()), SLOT(onPushButtoDeleteIngredient()));
    connect(ui->pushButton_addDescription, SIGNAL(pressed()), SLOT(onPushButtonAddDescription()));
    connect(ui->pushButton_deleteDescription, SIGNAL(pressed()), SLOT(onPushButtonDeleteDescription()));
    connect(_productSeach, SIGNAL(seachLineProductReady(QString)), SIGNAL(seachLineProductReady(QString)));
    connect(_productSeach, SIGNAL(seachLineProteinReady(int,int)), SIGNAL(seachLineProteinReady(int,int)));
    connect(_productSeach, SIGNAL(seachLineFatsReady(int,int)), SIGNAL(seachLineFatsReady(int,int)));
    connect(_productSeach, SIGNAL(seachLineCarbohydratesReady(int,int)), SIGNAL(seachLineCarbohydratesReady(int,int)));
 }






void RecipeEdit::setInformation(const RecipeEntity &r)
{
    _isEditingMod = true;

    _recipe.setId(r.id());

    ui->lineEdi_recipeName->setText(r.name());
    QVector<WeightedProduct> produsctsList = r.products();
    for (int i = 0; i < produsctsList.size(); i++)
    {
        ui->tableWidget_ingredientList->insertRow(i);
        QTableWidgetItem item;
        item.setText(produsctsList.at(i).product().name());
        ui->tableWidget_ingredientList->setItem(i,0, &item);
        QString units = "";
        if (produsctsList.at(i).product().units() == ProductEntity::GRAMM)
        {
            units = "гр";
        } else if (produsctsList.at(i).product().units() == ProductEntity::MILLILITER)
        {
            units = "мл";
        } else
        {
            units = "NONE";
        }
        item.setText(QString::number(produsctsList.at(i).amound())+" "+units);
        ui->tableWidget_ingredientList->setItem(i, 1, &item);
    }
    QStringList cookingPointList = r.cookingPoints();
    for (int i = 0; i < cookingPointList.size(); i++)
    {
        ui->tableWidget_recipeDescription->insertRow(i);
        QTableWidgetItem item;
        item.setText(cookingPointList.takeAt(i));
        ui->tableWidget_recipeDescription->setItem(i, 0, &item);
    }

    this->repaint();
}


void RecipeEdit::setProducts(const QVector<ProductEntity> &products)
{
    _productSeach->setInformation(products);
}

void RecipeEdit::onPushButtonSave()
{
    QString errorLog;

    if (!ui->lineEdi_recipeName->hasAcceptableInput()) {
        errorLog += tr("Неправильное имя рецепта\n");
    }
    if (ui->tableWidget_ingredientList->rowCount() == 0) {
        errorLog += tr("Нет продуктов\n");
    }
    if (ui->tableWidget_recipeDescription->rowCount() == 0) {
        errorLog += tr("Описание рецепта пустое\n");
    }

    if (!errorLog.isEmpty()){
        QMessageBox::critical(this, "Ошибка заполнения", errorLog);
        return;
    }

    QString recipeName = ui->lineEdi_recipeName->text();
    QVector<WeightedProduct> produsctsList;
    QStringList cookingPoints;
    QTableWidgetItem item;
    int descriptionRows = ui->tableWidget_recipeDescription->rowCount();
    /*
    for (int i=0; i<tableRows; i++)
    {

        item = *ui->tableWidget_ingredientList->takeItem(i, 0);
        produsctsList.push_back(WeightedProduct());
    }*/
    for (int i = 0; i<descriptionRows; i++)
    {
        item = *ui->tableWidget_recipeDescription->takeItem(i, 0);
        cookingPoints.push_back(item.text());
    }
    _recipe = RecipeEntity(_recipe.id(), recipeName, _recipe.getPoducts(), cookingPoints);

    if (_isEditingMod) {
        emit formEditedRecipeReady();
    } else {
        emit formNewRecipeReady();
    }
}


void RecipeEdit::onPushButtonAddIngredient()
{
    if (!(_productSeach->getCurrentRow() < 0))
    {
        ProductEntity product = _productSeach->selectedProduct();
        int productRow = ui->tableWidget_ingredientList->currentRow();
        if (productRow < 0) {
            productRow = ui->tableWidget_ingredientList->rowCount();
        } else {
            productRow++;
        }
        ui->tableWidget_ingredientList->insertRow(productRow);
        ui->tableWidget_ingredientList->setItem(productRow, 0, new QTableWidgetItem(product.name()));
        ui->tableWidget_ingredientList->setItem(productRow, 1, new QTableWidgetItem("0"));
        _recipe.addProduct(WeightedProduct(product, -1), productRow);

    } else {
        qDebug()<<"Error: RecipeEdit::onPushButtonAddIngredient()"
               <<"Nothing selected";
    }
}

void RecipeEdit::onPushButtoDeleteIngredient()
{
    if (!(ui->tableWidget_ingredientList->currentRow() < 0))
    {
        int deletedProductRow = ui->tableWidget_ingredientList->currentRow();
        ui->tableWidget_ingredientList->removeRow(deletedProductRow);
        _recipe.deleteProduct(deletedProductRow);
    } else {
        qDebug()<<"RecipeEdit::onPushButtoDeleteIngredient()"
               <<"Nothing selected";
    }
}

void RecipeEdit::onPushButtonAddDescription()
{
    int descriptionRow = ui->tableWidget_recipeDescription->currentRow();
    if (!(descriptionRow < 0)) {
        descriptionRow = ui->tableWidget_recipeDescription->rowCount();
    } else {
        descriptionRow++;
    }
    ui->tableWidget_recipeDescription->insertRow(descriptionRow);
    ui->tableWidget_recipeDescription->setItem(descriptionRow, 0, new QTableWidgetItem("<Описание>"));
    _recipe.addDescription("<Описание>", descriptionRow);
}

void RecipeEdit::onPushButtonDeleteDescription()
{
    if (!(ui->tableWidget_recipeDescription->currentRow() < 0))
    {
        int deletedDescriptionRow = ui->tableWidget_recipeDescription->currentRow();
        ui->tableWidget_recipeDescription->removeRow(deletedDescriptionRow);
        _recipe.deleteDescription(deletedDescriptionRow);
    } else {
        qDebug()<<"RecipeEdit::onPushButtoDeleteIngredient()"
               <<"Nothing selected";
    }
}

void RecipeEdit::onPushButtonCancel()
{
    this->parent()->deleteLater();
}

RecipeEntity RecipeEdit::recipe() const
{
    return _recipe;
}

RecipeEdit::~RecipeEdit()
{
    delete ui;
}
