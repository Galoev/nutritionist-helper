#include "ProductSeach.h"
#include "ui_Product_seach.h"
#include <QDebug>

ProductSeach::ProductSeach(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductSeach)
{
    ui->setupUi(this);

    connect(ui->pushButton_search, SIGNAL(pressed()), SLOT(onPushButtonSeach()));
    connect(ui->radioButton_productSearch, SIGNAL(pressed()), SLOT(onProductNameSeachType()));
    connect(ui->radioButton_proteinSearch, SIGNAL(pressed()), SLOT(onPFCSeachType()));
    connect(ui->radioButton_fatsSearch, SIGNAL(pressed()), SLOT(onPFCSeachType()));
    connect(ui->radioButton_carbohydratesSearch, SIGNAL(pressed()), SLOT(onPFCSeachType()));
    connect(ui->tableWidget_products, SIGNAL(pressed(QModelIndex)), SLOT(onSelectProduct(QModelIndex)));
}

ProductSeach::~ProductSeach()
{
    delete ui;
}

ProductEntity ProductSeach::selectedProduct() const
{
    return _selectedProduct;
}

void ProductSeach::setInformation(const QVector<ProductEntity> &products)
{
    _products = products;

    ui->tableWidget_products->setRowCount(_products.size());

    for(int iRow = 0; iRow < _products.size(); ++iRow) {
        QStringList strColumns;
        strColumns << _products[iRow].name()
                   << QLocale::system().toString(_products[iRow].proteins())
                   << QLocale::system().toString(_products[iRow].fats())
                   << QLocale::system().toString(_products[iRow].carbohydrates())
                   << QLocale::system().toString(_products[iRow].kilocalories());
        for(int iCol = 0; iCol < strColumns.size(); ++iCol) {
            ui->tableWidget_products->setItem(iRow, iCol, new QTableWidgetItem(strColumns[iCol]));
        }
    }

    this->repaint();
}

int ProductSeach::getCurrentRow()
{
    return ui->tableWidget_products->currentRow();
}

void ProductSeach::onPushButtonSeach()
{
    int from = 0;
    int to = 0;
    if (ui->radioButton_productSearch->isChecked()) {
        QString search = ui->lineEdit_productName->text();
        if (!search.isEmpty()) {
            emit seachLineProductReady(search);
        }
    } else if (ui->radioButton_proteinSearch->isChecked()) {
        from = ui->spinBox_From->value();
        to = ui->spinBox_To->value();
        emit seachLineProteinReady(from, to);
    } else if (ui->radioButton_fatsSearch->isChecked()) {
        from = ui->spinBox_From->value();
        to = ui->spinBox_To->value();
        emit seachLineFatsReady(from, to);
    } else if (ui->radioButton_carbohydratesSearch->isChecked()) {
        from = ui->spinBox_From->value();
        to = ui->spinBox_To->value();
        emit seachLineCarbohydratesReady(from, to);
    }
}

void ProductSeach::onProductNameSeachType()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void ProductSeach::onPFCSeachType()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void ProductSeach::onSelectProduct(const QModelIndex &index)
{
    int selectedProduct = index.row();
    if (selectedProduct >= _products.size() && selectedProduct < 0)
    {
        qDebug() << "Error: ProductSeach::onSelectProduct(const QModelIndex &)"
                 << "Not correct client vector index";
    }
    _selectedProduct = _products[selectedProduct];
    emit selectedForShow();
}



