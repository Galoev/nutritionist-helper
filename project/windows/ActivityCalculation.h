#pragma once
#include <QWidget>

class QTableWidget;

namespace Ui {
class ActivityCalculation;
}

class ActivityCalculation : public QWidget
{
    Q_OBJECT

public:
    explicit ActivityCalculation(QWidget *parent = nullptr);
    ~ActivityCalculation() override;

    void paintEvent(QPaintEvent *event) override;

private:
    void removeSelectedRow(QTableWidget*);

private slots:
    void calculateActivity();
    void onPushButtonAddProduct();
    void onPushButtonAddActivity();
    void onPushButtonDeleteProduct();
    void onPushButtonDeleteActivity();

private:
    Ui::ActivityCalculation *ui;
};
