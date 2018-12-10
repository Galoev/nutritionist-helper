#include <QApplication>
#include "databasemodule.h"
#include <QFileDialog>
#include <QStandardPaths>
#include "MDIProgram.h"
#include "windows/ActivityCalculation.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DatabaseModule db;

    MainWindow mw;
    mw.show();

    return a.exec();
}
