#include "RecipeEdit.h"
#include "ui_Recipe_edit.h"
#include <QVBoxLayout>
#include <QRegExpValidator>
#include <QDebug>
#include <QMessageBox>

#include "../widgets/AttachPhotoWidget.h"

RecipeEdit::RecipeEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeEdit)
{
    ui->setupUi(this);
    ui->lineEdit_recipeName->setValidator(new QRegExpValidator(QRegExp("[A-Z/a-z/а-я/A-Я]{1,}\[A-Z/a-z/а-я/A-Я\\s]{1,}")));
    //ui->tableWidget_ingredientList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->pushButton_save, SIGNAL(pressed()), SLOT(onPushButtonSave()));
    connect(ui->pushButton_cancel, SIGNAL(pressed()), SLOT(onPushButtonCancel()));
    connect(ui->pushButton_addIngredient, SIGNAL(pressed()), SLOT(onPushButtonAddIngredient()));
    connect(ui->pushButton_deleteIngredient, SIGNAL(pressed()), SLOT(onPushButtoDeleteIngredient()));
    connect(ui->pushButton_addDescription, SIGNAL(pressed()), SLOT(onPushButtonAddDescription()));
    connect(ui->pushButton_deleteDescription, SIGNAL(pressed()), SLOT(onPushButtonDeleteDescription()));

    connect(ui->frame_product_search, SIGNAL(seachLineProductReady(QString)),          SIGNAL(productSearchLineReady(QString)));
    connect(ui->frame_product_search, SIGNAL(seachLineProteinReady(int,int)),          SIGNAL(productSearchProteinReady(int,int)));
    connect(ui->frame_product_search, SIGNAL(seachLineFatsReady(int,int)),             SIGNAL(productSearchFatsReady(int,int)));
    connect(ui->frame_product_search, SIGNAL(seachLineCarbohydratesReady(int,int)),    SIGNAL(productSearchCarbohydratesReady(int,int)));
    connect(ui->frame_product_search, SIGNAL(selectedForShow()),                       SIGNAL(productSelectedForShow()));
    connect(ui->frame_product_search, SIGNAL(requireUpdateAllInform()),                SIGNAL(productRequireUpdateAllInform()));
 }

void RecipeEdit::setInformation(const RecipeEntity &r)
{
    _isEditingMod = true;
    _recipe = r;
    ui->lineEdit_recipeName->setText(r.name());

    for(const auto& wProduct : _recipe.products()){
        const auto& product = wProduct.product();
        const QString name = product.name();
        const QString amound = QLocale::system().toString(wProduct.amound());
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
    qDebug() << _recipe.id();
    ui->widget_image->loadImage("recipes",QString::number(_recipe.id()) + ".png");

    this->repaint();
}


void RecipeEdit::setSearchedProducts(const QVector<ProductEntity> &products)
{
    ui->frame_product_search->setInformation(products);
}

void RecipeEdit::saveImage(QString imageName)
{
    ui->widget_image->saveImage("recipes",imageName + "png");
}

void RecipeEdit::paintEvent(QPaintEvent *event)
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
    ui->frame_product_search->selectedProduct();
    if (ui->frame_product_search->getCurrentRow() >= 0)
    {
        ProductEntity product = ui->frame_product_search->selectedProduct();
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

        ui->tableWidget_ingredientList->item(productRow, 0)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget_ingredientList->item(productRow, 2)->setFlags(Qt::ItemIsEnabled);

        QModelIndex index = ui->tableWidget_ingredientList->model()->index(productRow, 1);
        ui->tableWidget_ingredientList->edit(index);
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

    QModelIndex index = ui->tableWidget_recipeDescription->model()->index(descriptionRow, 0);
    ui->tableWidget_recipeDescription->edit(index);

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
