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
    ui->lineEdit_recipeName->setValidator(new QRegExpValidator(QRegExp("[A-Z/a-z/а-я/A-Я]{1,}\[A-Z/a-z/а-я/A-Я\\s]{1,}")));
    //ui->tableWidget_ingredientList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->pushButton_save, SIGNAL(pressed()), SLOT(onPushButtonSave()));
    connect(ui->pushButton_cancel, SIGNAL(pressed()), SLOT(onPushButtonCancel()));
    connect(ui->pushButton_addIngredient, SIGNAL(pressed()), SLOT(onPushButtonAddIngredient()));
    connect(ui->pushButton_deleteIngredient, SIGNAL(pressed()), SLOT(onPushButtoDeleteIngredient()));
    connect(ui->pushButton_addDescription, SIGNAL(pressed()), SLOT(onPushButtonAddDescription()));
    connect(ui->pushButton_deleteDescription, SIGNAL(pressed()), SLOT(onPushButtonDeleteDescription()));

    connect(_productSeach, SIGNAL(seachLineProductReady(QString)),          SIGNAL(productSearchLineReady(QString)));
    connect(_productSeach, SIGNAL(seachLineProteinReady(int,int)),          SIGNAL(productSearchProteinReady(int,int)));
    connect(_productSeach, SIGNAL(seachLineFatsReady(int,int)),             SIGNAL(productSearchFatsReady(int,int)));
    connect(_productSeach, SIGNAL(seachLineCarbohydratesReady(int,int)),    SIGNAL(productSearchCarbohydratesReady(int,int)));
    connect(_productSeach, SIGNAL(selectedForShow()),                       SIGNAL(productSelectedForShow()));
 }

void RecipeEdit::setInformation(const RecipeEntity &r)
{
    _isEditingMod = true;
    _recipe = r;
    ui->lineEdit_recipeName->setText(r.name());

    for(const auto& wProduct : _recipe.products()){
        const auto& product = wProduct.product();
        const QString name = product.name();
        const QString amound = QString::number(wProduct.amound());
        const QString units = product.units() == ProductEntity::GRAMM      ? "гр"
                            : product.units() == ProductEntity::MILLILITER ? "мл"
                            : "???";
        const auto rowCount = ui->tableWidget_ingredientList->rowCount();
        ui->tableWidget_ingredientList->insertRow(rowCount);
        ui->tableWidget_ingredientList->setItem(rowCount, 0, new QTableWidgetItem(name));
        ui->tableWidget_ingredientList->setItem(rowCount, 1, new QTableWidgetItem(amound));
        ui->tableWidget_ingredientList->setItem(rowCount, 2, new QTableWidgetItem(units));
    }
    for(QString cookingPoint : _recipe.cookingPoints()){
        const int rowCount = ui->tableWidget_recipeDescription->rowCount();
        ui->tableWidget_recipeDescription->insertRow(rowCount);
        ui->tableWidget_recipeDescription->setItem(rowCount, 0, new QTableWidgetItem(cookingPoint));
    }

    this->repaint();
}


void RecipeEdit::setSearchedProducts(const QVector<ProductEntity> &products)
{
    _productSeach->setInformation(products);
}

void RecipeEdit::onPushButtonSave()
{
    QString errorLog;

    if (!ui->lineEdit_recipeName->hasAcceptableInput()) {
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

    QString recipeName = ui->lineEdit_recipeName->text();
    QVector<WeightedProduct> produsctsList = _recipe.getPoducts();
    QStringList cookingPoints;
    QTableWidgetItem item;
    int descriptionRows = ui->tableWidget_recipeDescription->rowCount();

    for(int i = 0; i<produsctsList.size(); i++){
        auto amound = ui->tableWidget_ingredientList->takeItem(i, 1)->text().toFloat();
        produsctsList[i].setAmound(amound);
    }
    for (int i = 0; i<descriptionRows; i++) {
        item = *ui->tableWidget_recipeDescription->takeItem(i, 0);
        cookingPoints.push_back(item.text());
    }
    _recipe = RecipeEntity(_recipe.id(), recipeName, produsctsList, cookingPoints);


    if (_isEditingMod) {
        emit formEditedRecipeReady();
    } else {
        emit formNewRecipeReady();
    }
}


void RecipeEdit::onPushButtonAddIngredient()
{
    _productSeach->selectedProduct();
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
        ui->tableWidget_ingredientList->setItem(productRow, 2, new QTableWidgetItem(product.units() == ProductEntity::GRAMM ? "гр"
                                                                                                                            : product.units() == ProductEntity::MILLILITER ? "мл"
                                                                                                                            : "???"));

        _recipe.addProduct(WeightedProduct(product, 0), productRow);

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

        //auto productName = ui->tableWidget_ingredientList->currentItem()->text();

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
