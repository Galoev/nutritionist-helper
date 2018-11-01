#ifndef PRODUCTEDIT_H
#define PRODUCTEDIT_H

#include <QWidget>

namespace Ui {
class ProductEdit;
}

class ProductEdit : public QWidget
{
    Q_OBJECT

public:
    explicit ProductEdit(QWidget *parent = nullptr);
    ~ProductEdit();

private:
    Ui::ProductEdit *ui;
};

#endif // PRODUCTEDIT_H
