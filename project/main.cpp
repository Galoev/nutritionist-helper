#include <QApplication>
#include <QDebug>
#include "databasemodule.h"
#include <QFileDialog>
#include <QStandardPaths>
#include "MDIProgram.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // qDebug() << "Run";
    // bool isOk;
    //DatabaseModule db;

    // //Client client(10, "Luc2", "Koko", "Blob", QDate(1999, 9, 10), 'm', 20, "79992343344");
    // //qDebug() << db.changeClientInformation(client);

    // QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    // QString fileName = QFileDialog::getOpenFileName(nullptr, "Импорт файла базы данных", path, "Файл базы данных (*.sqlite);;All Files (*)");
    // if (!fileName.isEmpty()) {
    //     db.importDB(fileName);
    // }

    // fileName = QFileDialog::getSaveFileName(nullptr, "Экспорт файла базы данных", path, "Файл базы данных (*.sqlite);;All Files (*)");
    // if (!fileName.isEmpty()) {
    //     db.exportDB(fileName);
    // }

    MainWindow* program = new MainWindow;
    //program->setAttribute(Qt::WA_DeleteOnClose, true);
    program->show();

    return a.exec();
}
