#include <QApplication>
#include "databasemodule.h"
#include <QFileDialog>
#include <QStandardPaths>
#include "MDIProgram.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DatabaseModule db;

    //    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    //    QString fileName = QFileDialog::getOpenFileName(nullptr, "Импорт файла базы данных", path, "Файл базы данных (*.sqlite);;All Files (*)");
    //    if (!fileName.isEmpty()) {
    //        db.importDB(fileName);
    //    }
    //    fileName = QFileDialog::getSaveFileName(nullptr, "Экспорт файла базы данных", path, "Файл базы данных (*.sqlite);;All Files (*)");
    //    if (!fileName.isEmpty()) {
    //        db.exportDB(fileName);
    //    }

    MainWindow mw;
    mw.show();

    //For debug RecipeInfo
    /*
    RecipeInfo r;
    QVector<WeightedProduct> products;
    products.push_back(WeightedProduct(ProductEntity(0, "Картошка1Картошка2Картошка3Картошка4", "Description", 10, 11, 12, 13, ProductEntity::GRAMM), 1000));
    QStringList cookingPoints;
    cookingPoints.push_back("Почистить картошку");
    cookingPoints.push_back("Нарезать картошку");
    cookingPoints.push_back("Пожарить картошку");
    RecipeEntity recipe(0, "Жаренная картошка", products, cookingPoints);
    r.setInformation(recipe);
    r.show();
    */
    return a.exec();
}
