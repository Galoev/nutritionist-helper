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

    return a.exec();
}
