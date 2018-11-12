#include "recipeedit.h"
#include "ui_Recipe_edit.h"

#include <QRegExpValidator>

RecipeEdit::RecipeEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeEdit)
{
    ui->setupUi(this);

    ui->lineEdi_recipeName->setValidator(new QRegExpValidator(QRegExp("[\\w]")));

    connect(ui->pushButton_save, SIGNAL(pressed()), SLOT(onPushButtonSave()));
    connect(ui->pushButton_cancel, SIGNAL(pressed()), SLOT(onPushButtonCancel()));
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
        if (produsctsList.at(i).units() == WeightedProduct::GRAMM)
        {
            units = "гр";
        } else
        {
            units = "мл";
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

void RecipeEdit::onPushButtonSave()
{
    QString recipeName = ui->lineEdi_recipeName->text();
    QVector<WeightedProduct> produsctsList;
    QTableWidgetItem item;
    int tableRows = ui->tableWidget_ingredientList->rowCount();
    for (int i=0; i<tableRows; i++)
    {

        item = *ui->tableWidget_ingredientList->takeItem(i, 0);
        produsctsList.push_back(WeightedProduct());
    }
}

RecipeEdit::~RecipeEdit()
{
    delete ui;
}
