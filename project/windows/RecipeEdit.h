#ifndef RECIPEEDIT_H
#define RECIPEEDIT_H

#include <QWidget>

namespace Ui {
class RecipeEdit;
}

class RecipeEdit : public QWidget
{
    Q_OBJECT

public:
    explicit RecipeEdit(QWidget *parent = nullptr);
    ~RecipeEdit();

private:
    Ui::RecipeEdit *ui;
};

#endif // RECIPEEDIT_H
