#include <QApplication>
#include <QDebug>
#include "databasemodule.h"
#include <QFileDialog>
#include <QStandardPaths>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "Run";
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

//    auto products = db.products();
//    for (auto product : products){
//        QString s = QString("id:%1, name:%2, p:%3, f:%4, c:%5, kkal:%6 - \"%7\"")
//                .arg(product.id())
//                .arg(product.name())
//                .arg(product.proteins())
//                .arg(product.fats())
//                .arg(product.carbohydrates())
//                .arg(product.kilocalories())
//                .arg(product.description());
//        qDebug() << s;
//    }

//    auto activities = db.activities();
//    if(activities.isEmpty())
//        qDebug() << "EmptyActivities";

//    for(auto act : activities){
//        QString s = QString("id:%1, type:%2 = \"%3\"")
//                .arg(act.id())
//                .arg(act.type())
//                .arg(act.kkm());
//        qDebug() << s;
//    }

    auto recipes = db.recipes();
    if(recipes.isEmpty())
        qDebug() << "EmptyRecipes";

    for(const RecipeEntity& resipe: recipes) {
        QStringList products;
        for (WeightedProduct product : resipe.products()) {
            products << QString("\tid:%1 - %2 (%3) [%4]")
                    .arg(product.product().id())
                    .arg(product.product().name())
                    .arg(product.amound())
                    .arg(product.units() == WeightedProduct::GRAMM ? "gr" : "ml");
        }
        QStringList cookiePoints;
        for(int i = 0; i < resipe.cookingPoints().size(); ++i) {
            cookiePoints << QString("\t%1: %2")
                            .arg(i)
                            .arg(resipe.cookingPoints().at(i));
        }
        qDebug() << QString("id:%1, name:%2")
                    .arg(resipe.id())
                    .arg(resipe.name());
        qDebug() << "\tingradients\n" << products;
        qDebug() << "\tCoociePoints\n" << cookiePoints;
    }

    if(db.hasUnwatchedWorkError()){
        qDebug() << "----hasError----";
        qDebug() << db.unwatchedWorkError();

    }
    return a.exec();
}
