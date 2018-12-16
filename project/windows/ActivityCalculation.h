#pragma once
#include <QWidget>
#include "entities/product.h"
#include "entities/activity.h"

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

    void setSearcingProducts(const QVector<ProductEntity>& );
    void setSearcingActivities(const QVector<ActivityEntity>& );

private:
    void removeSelectedRow(QTableWidget*);

signals:
    void productSearchLineReady(const QString& );
    void productSearchProteinReady(const int from, const int to);
    void productSearchFatsReady(const int from, const int to);
    void productSearchCarbohydratesReady(const int from, const int to);
    void productRequireUpdateAllInform();

    void activitySeachLineActivityReady(const QString& );
    void activitySeachLineKcalReady(const int from, const int to);
    void activityRequireUpdateAllInform();


private slots:
    void calculateActivity(int row, int column);
    void onPushButtonAddProduct();
    void onPushButtonAddActivity();
    void onPushButtonDeleteProduct();
    void onPushButtonDeleteActivity();

private:
    void pushRowFormStringList(QTableWidget* , const QStringList & );

private:
    Ui::ActivityCalculation *ui;
};
