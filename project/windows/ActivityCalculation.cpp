#include "ActivityCalculation.h"
#include "ui_Activity_calculation.h"
#include <QPalette>
#include <QTableWidget>
#include <QDebug>

ActivityCalculation::ActivityCalculation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActivityCalculation)
{
    ui->setupUi(this);


    connect(ui->activitiesTable, SIGNAL(itemChanged(QTableWidgetItem*)), SLOT(calculateActivity()));
    connect(ui->deleteActivity, SIGNAL(pressed()), SLOT(onPushButtonDeleteActivity()));
    connect(ui->productsTable, SIGNAL(itemChanged(QTableWidgetItem*)), SLOT(calculateActivity()));
    connect(ui->deleteProduct, SIGNAL(pressed()), SLOT(onPushButtonDeleteProduct()));
}

ActivityCalculation::~ActivityCalculation()
{
    delete ui;
}

void ActivityCalculation::paintEvent(QPaintEvent *event)
{
    auto activitiesWidth = ui->activitiesTable->width();
    ui->activitiesTable->setColumnWidth(0, activitiesWidth * 3/4 - 1);
    ui->activitiesTable->setColumnWidth(1, activitiesWidth * 1/4 - 1);
    auto productsWidth = ui->activitiesTable->width();
    ui->productsTable->setColumnWidth(0, productsWidth * 3/4 - 1);
    ui->productsTable->setColumnWidth(1, productsWidth * 1/4 - 1);

    auto deleteActivityEnabled = !ui->activitiesTable->selectionModel()->selectedRows().isEmpty();
    ui->deleteActivity->setEnabled(deleteActivityEnabled);
    auto deleteProductEnabled = !ui->productsTable->selectionModel()->selectedRows().isEmpty();
    ui->deleteProduct->setEnabled(deleteProductEnabled);

    QWidget::paintEvent(event);
}

void ActivityCalculation::removeSelectedRow(QTableWidget *table)
{
    auto selectedIndexes = table->selectionModel()->selectedRows();
    auto selectedRow = selectedIndexes.first().row();
    table->removeRow(selectedRow);
    table->clearSelection();
}

void ActivityCalculation::calculateActivity()
{
    auto getSumKcalColumnOfTable = [](QTableWidget* table) {
        const auto selectedColumn = 1;
        const auto rowCount = table->rowCount();
        float sum(0);
        for (int i = 0; i < rowCount; ++i) {
            auto item = table->item(i, selectedColumn);
            if (item) { sum += item->text().toFloat(); }
        }
        return sum;
    };

    auto sumActivitiesKcal = getSumKcalColumnOfTable(ui->activitiesTable);
    auto sumProductsKcal = getSumKcalColumnOfTable(ui->productsTable);
    auto resCcal = sumActivitiesKcal - sumProductsKcal;

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

}

void ActivityCalculation::onPushButtonAddActivity()
{

}

void ActivityCalculation::onPushButtonDeleteProduct()
{
    removeSelectedRow(ui->productsTable);
}

void ActivityCalculation::onPushButtonDeleteActivity()
{
    removeSelectedRow(ui->activitiesTable);
}
