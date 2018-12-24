#include "RecipeInfo.h"
#include "ui_Recipe_info.h"

#include <QPrinter>
#include <QPaintDevice>
#include <QPrintPreviewDialog>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextTable>

RecipeInfo::RecipeInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeInfo)
{
    ui->setupUi(this);
    ui->tableWidget_ingredientList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_ingredientList->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_recipeDescription->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_recipeDescription->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->widget_image->setEnable(false);
    ui->widget_image->resizeEvent(nullptr);

    connect(ui->pushButton_recipeEdit, SIGNAL(pressed()), SIGNAL(editRecipeButtonPressed()));
    connect(ui->pushButton_delete, SIGNAL(pressed()), SIGNAL(deleteRecipeButtonPressed()));
    connect(ui->pushButton_print, SIGNAL(pressed()), SLOT(onPrintButtonPressed()));
}

void RecipeInfo::setInformation(const RecipeEntity &r)
{
    _recipe = r;
    QVector<WeightedProduct> products = _recipe.getPoducts();
    ui->label_recipeName->setText(_recipe.name());
    ui->tableWidget_ingredientList->setRowCount(products.size());

    for (int iRow = 0; iRow < products.size(); ++iRow) {
        ui->tableWidget_ingredientList->setItem(iRow, 0, new QTableWidgetItem(products.at(iRow).product().name()));
        ui->tableWidget_ingredientList->setItem(iRow, 1, new QTableWidgetItem(QLocale::system().toString(products.at(iRow).amound())));
        ui->tableWidget_ingredientList->setItem(iRow, 2, new QTableWidgetItem(products.at(iRow).product().units() == ProductEntity::GRAMM ? "гр" : products.at(iRow).product().units() == ProductEntity::MILLILITER ? "мл" : "???"));
    }

    auto proteins = QLocale::system().toString(_recipe.proteins());
    ui->label_numProtein->setText(proteins);
    auto fats = QLocale::system().toString(_recipe.fats());
    ui->label_numFats->setText(fats);
    auto carbohydrates = QLocale::system().toString(_recipe.carbohydrates());
    ui->label_numCarbohydrates->setText(carbohydrates);
    auto kcal = QLocale::system().toString(_recipe.kkal());
    ui->label_numKcal->setText(kcal);

    QStringList cookingPoints = _recipe.getCookingPoints();
    ui->tableWidget_recipeDescription->setRowCount(cookingPoints.size());

    for (int iRow = 0; iRow < cookingPoints.size(); ++iRow) {
        ui->tableWidget_recipeDescription->setItem(iRow, 0, new QTableWidgetItem(cookingPoints.at(iRow)));
    }
    ui->widget_image->loadImage("recipes",QString::number(_recipe.id()) + ".png");

    this->repaint();
}

RecipeEntity RecipeInfo::recipe() const
{
    return _recipe;
}

void RecipeInfo::paintEvent(QPaintEvent *event)
{
    auto width = ui->tableWidget_ingredientList->width();
    ui->tableWidget_ingredientList->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_ingredientList->setColumnWidth(0, width * 10/15-10);
    ui->tableWidget_ingredientList->setColumnWidth(1, width * 4/15-10);
    ui->tableWidget_ingredientList->setColumnWidth(2, width * 1/15-10);

    ui->tableWidget_recipeDescription->resizeRowsToContents();
    auto width2 = ui->tableWidget_recipeDescription->width();
    ui->tableWidget_recipeDescription->setColumnWidth(0, width2 * 8/12-10);
    QWidget::paintEvent(event);
}

void RecipeInfo::onPrintButtonPressed()
{
    QString resipeName = "Рецепт: " + ui->label_recipeName->text();

    QPrinter* _printer;


    _printer = new QPrinter(QPrinter::HighResolution);
    _printer->setOrientation(QPrinter::Portrait);
    _printer->setPageMargins(QMarginsF(10, 10, 10, 10), QPageLayout::Millimeter);
    _printer->setPaperSize(QPrinter::A4);
    _printer->setDocName(resipeName);

    QPrintPreviewDialog* dialog = new QPrintPreviewDialog(_printer, this);
    dialog->setWindowFlags(Qt::Window);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setWindowTitle(resipeName);
    connect(dialog, SIGNAL(paintRequested(QPrinter*)), SLOT(printRequest(QPrinter*)));
    dialog->exec();
}

void RecipeInfo::printRequest(QPrinter *printer)
{
    QTextCursor cursor;
    QTextDocument document;
    document.setDefaultFont(QFont("Times New Roman"));
    cursor = QTextCursor(&document);

    auto drawTitle = [&cursor](QString s){
        QTextCharFormat boldWeight;
        boldWeight.setFontWeight(QFont::Bold);
        QTextBlockFormat centerAlignment;
        centerAlignment.setAlignment(Qt::AlignCenter);

        cursor.setBlockFormat(centerAlignment);
        cursor.insertText(s, boldWeight);
        cursor.insertBlock();
        cursor.insertBlock();
    };

    auto drawTableHeader = [&cursor](QImage img, float kcal, float proteins, float fats, float carb){
       // QTextTableFormat tableFormat;
        QTextTable *table = cursor.insertTable(1, 2);


        QTextTableCell cell = table->cellAt(0,0);
        QTextCursor cellCursor = cell.firstCursorPosition();
        cellCursor.insertImage(img.scaled(280,280));

        cell = table->cellAt(0,1);
        cellCursor = cell.firstCursorPosition();
        cellCursor.insertText("ЭНЕРГЕТИЧЕСКАЯ ЦЕННОСТЬ");
        cellCursor.insertBlock();
        cellCursor.insertBlock();
        QTextTable *subTable = cellCursor.insertTable(4,1);

        QTextTableCell subCell = subTable->cellAt(0,0);
        QTextCursor subCellCursor = subCell.firstCursorPosition();
        subCellCursor.insertText("КАЛОРИЙНОСТЬ");
        subCellCursor.insertBlock();
        subCellCursor.insertText(QString::number(kcal));
        subCellCursor.insertBlock();
        subCellCursor.insertText("ккал");
        subCellCursor.movePosition(QTextCursor::NextCell);
        subCellCursor.insertText("БЕЛКИ");
        subCellCursor.insertBlock();
        subCellCursor.insertText(QString::number(kcal));
        subCellCursor.insertBlock();
        subCellCursor.insertText("грамм");
        subCellCursor.movePosition(QTextCursor::NextCell);
        subCellCursor.insertText("ЖИРЫ");
        subCellCursor.insertBlock();
        subCellCursor.insertText(QString::number(fats));
        subCellCursor.insertBlock();
        subCellCursor.insertText("грамм");
        subCellCursor.movePosition(QTextCursor::NextCell);
        subCellCursor.insertText("УГЛЕВОДЫ");
        subCellCursor.insertBlock();
        subCellCursor.insertText(QString::number(carb));
        subCellCursor.insertBlock();
        subCellCursor.insertText("грамм");

        //cellCursor.insertText("* КАЛОРИЙНОСТЬ РАССЧИТАНА ДЛЯ СЫРЫХ ПРОДУКТОВ");
        cursor.movePosition(QTextCursor::End);
    };

    auto drawTableIngredients = [&cursor](const RecipeEntity &recipe){
        cursor.insertBlock();
        cursor.insertBlock();
        cursor.insertText("ИНГРЕДИЕНТЫ");
        cursor.insertBlock();

        int rows = recipe.products().size();
        QTextTable *table = cursor.insertTable(rows, 3);
        for (auto product : recipe.products()){
            cursor.insertText(product.product().name());
            cursor.movePosition(QTextCursor::NextCell);
            cursor.insertText(QString::number(product.amound()));
            cursor.movePosition(QTextCursor::NextCell);
            cursor.insertText(product.product().units() == ProductEntity::GRAMM ? "гр" : product.product().units() == ProductEntity::MILLILITER ? "мл" : "???");
            cursor.movePosition(QTextCursor::NextCell);
        }
        cursor.movePosition(QTextCursor::End);
    };

    auto drawTableCookingpoint = [&cursor](const RecipeEntity &recipe){
        cursor.insertBlock();
        cursor.insertBlock();
        cursor.insertText("ИНСТРУКЦИЯ ПРИГОТОВЛЕНИЯ");
        cursor.insertBlock();

        int rows = recipe.cookingPoints().size();
        QTextTable *table = cursor.insertTable(rows, 2);
        for (int i = 0; i < rows; ++ i){
            cursor.insertText(QString::number(i+1));
            cursor.movePosition(QTextCursor::NextCell);
            cursor.insertText(recipe.cookingPoints().at(i));
            cursor.movePosition(QTextCursor::NextCell);
        }
        cursor.movePosition(QTextCursor::End);
    };

    drawTitle(ui->label_recipeName->text());
    drawTableHeader(ui->widget_image->image(), _recipe.kkal(), _recipe.proteins(), _recipe.fats(), _recipe.carbohydrates());
    drawTableIngredients(_recipe);
    drawTableCookingpoint(_recipe);

    document.print(printer);
}

RecipeInfo::~RecipeInfo()
{
    delete ui;
}
