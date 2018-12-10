#ifndef RECIPEINFO_H
#define RECIPEINFO_H

#include <QWidget>
#include "entities/recipe.h"
#include "entities/product.h"

namespace Ui {
class RecipeInfo;
}

class RecipeInfo : public QWidget
{
    Q_OBJECT

public:
    explicit RecipeInfo(QWidget *parent = nullptr);
    ~RecipeInfo();

    void setInformation(const RecipeEntity& );
    RecipeEntity recipe() const;

signals:
    void editRecipeButtonPressed();
    void deleteRecipeButtonPressed();

private:
    Ui::RecipeInfo *ui;
    RecipeEntity _recipe;
};

#endif // RECIPEINFO_H
