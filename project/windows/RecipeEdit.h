#include <QWidget>
#include "entities/recipe.h"

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

signals:
    void formNewRecipeReady();
    void formEditedRecipeReady();

private slots:
    void onPushButtonSave();
    void onPushButtonCancel();

private:
    Ui::RecipeEdit *ui;
    RecipeEntity _recipe;
    bool _isEditingMod = false;
};

#endif // RECIPEEDIT_H
