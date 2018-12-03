#include "ProductEdit.h"
#include "ui_Product_edit.h"
#include <QMessageBox>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QDebug>

ProductEdit::ProductEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductEdit)
{
    ui->setupUi(this);

    ui->lineEdit_productName->setValidator(new QRegExpValidator(QRegExp("[A-Z/a-z/а-я/A-Я]{1,}\[A-Z/a-z/а-я/A-Я\\s]{1,}")));
    ui->lineEdit_numProtein->setValidator(new QDoubleValidator(0.0, 1000.0, 2));
    ui->lineEdit_numFats->setValidator(new QDoubleValidator(0.0, 1000.0, 2));
    ui->lineEdit_numCarbohydrates->setValidator(new QDoubleValidator(0.0, 1000.0, 2));
    ui->lineEdit_numKcal->setValidator(new QDoubleValidator(0.0, 10000.0, 2));

    connect(ui->pushButton_save, SIGNAL(pressed()), SLOT(onPushButtonSave()));
    connect(ui->pushButton_cancel, SIGNAL(pressed()), SLOT(onPushButtonCancel()));
}

void ProductEdit::setInformation(const ProductEntity &p)
{
    _isEditingMod = true;

    _product.setId(p.id());

    ui->lineEdit_productName->setText(p.name());
    ui->lineEdit_numProtein->setText(QString::number(p.proteins()));
    ui->lineEdit_numFats->setText(QString::number(p.fats()));
    ui->lineEdit_numCarbohydrates->setText(QString::number(p.carbohydrates()));
    ui->lineEdit_numKcal->setText(QString::number(p.kilocalories()));
    ui->textEdit_description->setText(p.description());
    ui->comboBox->setCurrentIndex(p.units() == ProductEntity::GRAMM ? 0 : 1);

    this->repaint();
}

void ProductEdit::onPushButtonSave()
{
    QString errorLog;

    if (!ui->lineEdit_productName->hasAcceptableInput()){
        errorLog += "Неправильный формат названия\n";
    }
    if (!ui->lineEdit_numProtein->hasAcceptableInput()){
        errorLog += "Неправильный формат белков\n";
    }
    if (!ui->lineEdit_numFats->hasAcceptableInput()){
        errorLog += "Неправильный формат жиров\n";
    }
    if (!ui->lineEdit_numCarbohydrates->hasAcceptableInput()){
        errorLog += "Неправильный формат углеводов\n";
    }
    if (!ui->lineEdit_numKcal->hasAcceptableInput()){
        errorLog += "Неправильный формат Ккал\n";
    }

    if (!errorLog.isEmpty()){
        QMessageBox::critical(this, "Ошибка заполнения\n", errorLog);
        return;
    }

    QString productName = ui->lineEdit_productName->text();
    float protein = QLocale::system().toDouble(ui->lineEdit_numProtein->text());
    float fats = QLocale::system().toDouble(ui->lineEdit_numFats->text());
    float carbohydrates = QLocale::system().toDouble(ui->lineEdit_numCarbohydrates->text());
    float kcal = QLocale::system().toDouble(ui->lineEdit_numKcal->text());
    QString description = ui->textEdit_description->toPlainText();

    _product = ProductEntity(_product.id()
                             , productName
                             , description
                             , protein
                             , fats
                             , carbohydrates
                             , kcal
                             , ui->comboBox->currentIndex() == 0 ? ProductEntity::GRAMM : ui->comboBox->currentIndex() == 1 ? ProductEntity::MILLILITER : ProductEntity::UNDEF); //WARNIND: TODO:

    if (_isEditingMod) {
        emit formEditedProductReady();
    } else {
        emit formNewProductReady();
    }

    this->close();
}

void ProductEdit::onPushButtonCancel()
{
    this->parent()->deleteLater();
}

ProductEntity ProductEdit::product() const
{
    return _product;
}

ProductEdit::~ProductEdit()
{
    delete ui;
}
