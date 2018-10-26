#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->action_about, SIGNAL(triggered(bool)), SLOT(on_about()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_about()
{
    QMessageBox::about(this, "О программе", QString("Версия программы %1.").arg(APP_VERSION));
}
