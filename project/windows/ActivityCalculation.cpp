#include "ActivityCalculation.h"
#include "ui_Activity_calculation.h"


#include <QPalette>
#include <QTableWidget>
#include <QDebug>
#include <QString>

ActivityCalculation::ActivityCalculation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActivityCalculation)
{
    ui->setupUi(this);

    //connect(ui->activitiesTable, SIGNAL(itemChanged(QTableWidgetItem*)), SLOT(calculateActivity()));
    //connect(ui->productsTable, SIGNAL(itemChanged(QTableWidgetItem*)), SLOT(calculateActivity()));

    ui->lineEdit_weight->setValidator(new QIntValidator(1,999));

    connect(ui->activitiesTable, SIGNAL(cellChanged(int, int)), SLOT(calculateActivity(int, int)));
    connect(ui->productsTable, SIGNAL(cellChanged(int, int)), SLOT(calculateActivity(int, int)));

    connect(ui->pushButton_setWeight, SIGNAL(pressed()), SLOT(calculateActivity()));

    connect(ui->addSelectedActivity, SIGNAL(clicked(bool)), SLOT(onPushButtonAddActivity()));
    connect(ui->addSelectedProduct, SIGNAL(clicked(bool)), SLOT(onPushButtonAddProduct()));
    connect(ui->deleteActivity, SIGNAL(pressed()), SLOT(onPushButtonDeleteActivity()));
    connect(ui->deleteProduct, SIGNAL(pressed()), SLOT(onPushButtonDeleteProduct()));

    connect(ui->productSearch, SIGNAL(seachLineProductReady(QString)),          SIGNAL(productSearchLineReady(QString)));
    connect(ui->productSearch, SIGNAL(seachLineProteinReady(int,int)),          SIGNAL(productSearchProteinReady(int,int)));
    connect(ui->productSearch, SIGNAL(seachLineFatsReady(int,int)),             SIGNAL(productSearchFatsReady(int,int)));
    connect(ui->productSearch, SIGNAL(seachLineCarbohydratesReady(int,int)),    SIGNAL(productSearchCarbohydratesReady(int,int)));
    connect(ui->productSearch, SIGNAL(requireUpdateAllInform()),                SIGNAL(productRequireUpdateAllInform()));
    connect(ui->productSearch, &ProductSeach::selectedForShow, [this](){
        this->ui->addSelectedProduct->setEnabled(true);
        this->ui->deleteProduct->setEnabled(true);
    });

    connect(ui->ativitySearch, SIGNAL(seachLineActivityReady(QString)),         SIGNAL(activitySeachLineActivityReady(QString)));
    connect(ui->ativitySearch, SIGNAL(seachLineKcalReady(int,int)),             SIGNAL(activitySeachLineKcalReady(int,int)));
    connect(ui->ativitySearch, SIGNAL(requireUpdateAllInform()),                SIGNAL(activityRequireUpdateAllInform()));
    connect(ui->ativitySearch, &ActivitySeach::selectedForShow, [this](){
        this->ui->addSelectedActivity->setEnabled(true);
        this->ui->deleteActivity->setEnabled(true);
    });
}

ActivityCalculation::~ActivityCalculation()
{
    delete ui;
}

void ActivityCalculation::paintEvent(QPaintEvent *event)
{
    auto activitiesWidth = ui->activitiesTable->width();
    ui->activitiesTable->setColumnWidth(0, activitiesWidth * 3/7 - 1);
    ui->activitiesTable->setColumnWidth(1, activitiesWidth * 1/7 - 1);
    ui->activitiesTable->setColumnWidth(2, activitiesWidth * 1/7 - 1);
    ui->activitiesTable->setColumnWidth(3, activitiesWidth * 1/7 - 1);
    auto productsWidth = ui->activitiesTable->width();
    ui->productsTable->setColumnWidth(0, productsWidth * 3/7 - 1);
    ui->productsTable->setColumnWidth(1, productsWidth * 1/7 - 1);
    ui->productsTable->setColumnWidth(2, productsWidth * 1/7 - 1);
    ui->productsTable->setColumnWidth(3, productsWidth * 1/7 - 1);

    auto addActivityEnabled = ui->ativitySearch->selectedActivity().id() != -1;
    auto addProductEnabled = ui->productSearch->selectedProduct().id() != -1;

    ui->addSelectedActivity->setEnabled(addActivityEnabled);
    ui->addSelectedProduct->setEnabled(addProductEnabled);

    QWidget::paintEvent(event);
}

void ActivityCalculation::setSearcingProducts(const QVector<ProductEntity> &products)
{
    ui->productSearch->setInformation(products);
}

void ActivityCalculation::setSearcingActivities(const QVector<ActivityEntity> &activities)
{
    ui->ativitySearch->setInformation(activities);
}

void ActivityCalculation::removeSelectedRow(QTableWidget *table)
{
    if (table->selectedItems().isEmpty()) return ;

    auto selectionModel = table->selectionModel();
    auto selectedRow = selectionModel->selectedRows().first().row();
    table->removeRow(selectedRow);
    table->clearSelection();
    calculateActivity(0,0);
}

void ActivityCalculation::calculateActivity(int row, int column)
{
    if (column == 3) return;

    auto getSumKcalColumnOfTable = [](QTableWidget* table, float coef=1) {
        const auto kcalColumn(1), minColumn(2), totalColumn(3);
        const auto rowCount = table->rowCount();
        float sum(0);
        for (int i = 0; i < rowCount; ++i) {
            auto kcalItem = table->item(i, kcalColumn);
            auto minItem = table->item(i, minColumn);
            if (kcalItem != nullptr && minItem != nullptr) {
                auto totalKcal = kcalItem->text().toFloat() * minItem->text().toFloat() * coef;
                qDebug() << table->item(i, totalColumn) << totalColumn;
                table->setItem(i, totalColumn, new QTableWidgetItem(QString::number(totalKcal)));
                sum += totalKcal;
            }

        }
        return sum;
    };

    auto weight = ui->lineEdit_weight->text().toFloat();
    auto sumActivitiesKcal = getSumKcalColumnOfTable(ui->activitiesTable, weight);
    auto sumProductsKcal = getSumKcalColumnOfTable(ui->productsTable, 0.01);
    auto resCcal = sumProductsKcal - sumActivitiesKcal;

    QString kcalSign;
    QColor kcalColor;
    if (sumActivitiesKcal > sumProductsKcal){
        kcalSign = ">";
        kcalColor = Qt::green;
    } else if (sumActivitiesKcal < sumProductsKcal){
        kcalSign = "<";
        kcalColor = Qt::red;
    } else {
        kcalSign = "=";
        kcalColor = Qt::blue;
    }
    auto kcalPalette = QApplication::palette();
    kcalPalette.setBrush(QPalette::WindowText, kcalColor);
    ui->calculationSign->setText(kcalSign);
    ui->resKcal->setText(QString::number(resCcal));
    ui->calculationSign->setPalette(kcalPalette);
    ui->resKcal->setPalette(kcalPalette);
}

void ActivityCalculation::onPushButtonAddProduct()
{
    auto product = ui->productSearch->selectedProduct();
    pushRowFormStringList(ui->productsTable, {
                              product.name(),
                              QString::number(product.kilocalories())
                          });
}

void ActivityCalculation::onPushButtonAddActivity()
{
    auto activity = ui->ativitySearch->selectedActivity();
    pushRowFormStringList(ui->activitiesTable, {
                              activity.type(),
                              QString::number(activity.kkm())
                          });
}

void ActivityCalculation::onPushButtonDeleteProduct()
{

    removeSelectedRow(ui->productsTable);
}

void ActivityCalculation::onPushButtonDeleteActivity()
{
    removeSelectedRow(ui->activitiesTable);
}

void ActivityCalculation::pushRowFormStringList(QTableWidget *table, const QStringList &list)
{
    qDebug() << "test";
    auto rowN = table->rowCount();
    table->insertRow(rowN);

    for (auto column = 0; column < list.size(); ++column) {
        table->setItem(rowN, column, new QTableWidgetItem(list.at(column)));
        //table->item(rowN, column)->setFlags(Qt::ItemIsEnabled);

    }
    table->setItem(rowN, table->columnCount()-1, new QTableWidgetItem(""));

    QModelIndex index = table->model()->index(rowN, list.size());
    table->edit(index);
    //table->item(rowN, list.size())->setFlags(Qt::ItemIsEnabled);
}
