#ifndef RECIPESEACH_H
#define RECIPESEACH_H

#include <QWidget>
#include "entities/recipe.h"

namespace Ui {
class RecipeSeach;
}

class RecipeSeach : public QWidget
{
    Q_OBJECT

public:
    explicit RecipeSeach(QWidget *parent = nullptr);
    ~RecipeSeach();

    void paintEvent(QPaintEvent *event) override;

    void setInformation(const QVector<RecipeEntity>&);
    RecipeEntity selectedRecipe() const;
    void hideInformationIfExists(const RecipeEntity &recipe);
    void updateInformationIfExist(RecipeEntity & );

signals:
    void seachLineRecipeReady(const QString& );
    void seachLineProteinReady(const int from, const int to);
    void seachLineFatsReady(const int from, const int to);
    void seachLineCarbohydratesReady(const int from, const int to);
    void selectedForShow();
    void requireUpdateAllInform();

private slots:
    void onPushButtonSeach();
    void onRecipeNameSeachType();
    void onPFCSeachType();
    void onSelectRecipe(const QModelIndex& );

private:
    Ui::RecipeSeach *ui;
    QVector<RecipeEntity> _recipes;
    RecipeEntity _selectedRecipe;

};

#endif // RECIPESEACH_H
