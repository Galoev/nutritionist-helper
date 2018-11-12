#ifndef RECIPESEACH_H
#define RECIPESEACH_H

#include <QWidget>

namespace Ui {
class RecipeSeach;
}

class RecipeSeach : public QWidget
{
    Q_OBJECT

public:
    explicit RecipeSeach(QWidget *parent = nullptr);
    ~RecipeSeach();

private:
    Ui::RecipeSeach *ui;
};

#endif // RECIPESEACH_H
