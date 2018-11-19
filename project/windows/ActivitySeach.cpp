#include "activityseach.h"
#include "ui_Activity_seach.h"
#include <QDebug>

ActivitySeach::ActivitySeach(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActivitySeach)
{
    ui->setupUi(this);

    connect(ui->pushButton_search, SIGNAL(pressed()), SLOT(onPushButtonSeach()));
    connect(ui->radioButton_activitySearch, SIGNAL(pressed()), SLOT(onActivitySeachType()));
    connect(ui->radioButton_kcalSearch, SIGNAL(pressed()), SLOT(onKcalSeachType()));
    connect(ui->tableWidget_activitys, SIGNAL(pressed(QModelIndex)), SLOT(onSelectActivity(QModelIndex)));
}

ActivityEntity ActivitySeach::selectedActivity() const
{
    return _selectedActivity;
}

void ActivitySeach::setInformation(const QVector<ActivityEntity> &activitys)
{
    _activitys = activitys;

    ui->tableWidget_activitys->setRowCount(_activitys.size());

    for (int iRow = 0; iRow < _activitys.size(); ++iRow)
    {
        ui->tableWidget_activitys->setItem(iRow, 0, new QTableWidgetItem(_activitys[iRow].type()));
        ui->tableWidget_activitys->setItem(iRow, 1, new QTableWidgetItem(QString::number(_activitys[iRow].kkm())));
    }

    this->repaint();
}

void ActivitySeach::onPushButtonSeach()
{
    if (ui->radioButton_activitySearch->isChecked()) {
        QString seach = ui->lineEdit_activityName->text();
        if (!seach.isEmpty()) {
            emit seachLineActivityReady(seach);
        }
    } else if (ui->radioButton_kcalSearch->isChecked()) {
        int from = ui->spinBox_calorieFrom->value();
        int to = ui->spinBox_calorieTo->value();
        emit seachLineKcalReady(from, to);
    }
}

void ActivitySeach::onActivitySeachType()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void ActivitySeach::onKcalSeachType()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void ActivitySeach::onSelectActivity(const QModelIndex &index)
{
    int selectedActivity = index.row();
    if (selectedActivity >= _activitys.size() && selectedActivity < 0) {
        qDebug() << "Error: ActivitySeach::onSelectActivity(const QModelIndex &index)"
                 << "Not correct client vector index";
    }
    _selectedActivity = _activitys[selectedActivity];
    emit selectedForShow();
}

ActivitySeach::~ActivitySeach()
{
    delete ui;
}
