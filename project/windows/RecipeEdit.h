#pragma once
#include <QWidget>
#include "entities/recipe.h"
#include "entities/product.h"
#include "windows/ProductSeach.h"

namespace Ui {
class RecipeEdit;
}

class RecipeEdit : public QWidget
{
    Q_OBJECT

public:
    explicit RecipeEdit(QWidget *parent = nullptr);
    ~RecipeEdit();

    void setInformation(const RecipeEntity& );
    RecipeEntity recipe() const;
    void setProducts(const QVector<ProductEntity>& );

signals:
    void formNewRecipeReady();
    void formEditedRecipeReady();
    void seachLineProductReady(const QString& );
    void seachLineProteinReady(const int from, const int to);
    void seachLineFatsReady(const int from, const int to);
    void seachLineCarbohydratesReady(const int from, const int to);

private slots:
    void onPushButtonSave();
    void onPushButtonCancel();
    void onPushButtonAddIngredient();
    void onPushButtoDeleteIngredient();
    void onPushButtonAddDescription();
    void onPushButtonDeleteDescription();

private:
    Ui::RecipeEdit *ui;
    RecipeEntity _recipe;
    bool _isEditingMod = false;

    ProductSeach* _productSeach;
};
