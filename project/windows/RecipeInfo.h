#ifndef RECIPEINFO_H
#define RECIPEINFO_H

#include <QWidget>

namespace Ui {
class RecipeInfo;
}

class RecipeInfo : public QWidget
{
    Q_OBJECT

public:
    explicit RecipeInfo(QWidget *parent = nullptr);
    ~RecipeInfo();

private:
    Ui::RecipeInfo *ui;
};

#endif // RECIPEINFO_H
