#include "ActivitySeach.h"
#include "ui_Activity_seach.h"
#include <QDebug>

ActivitySeach::ActivitySeach(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActivitySeach)
{
    ui->setupUi(this);

    connect(ui->pushButton_search, SIGNAL(pressed()), SLOT(onPushButtonSeach()));
    connect(ui->pushButton_searchAll, SIGNAL(pressed()), SIGNAL(requireUpdateAllInform()));
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
        ui->tableWidget_activitys->setItem(iRow, 1, new QTableWidgetItem(QLocale::system().toString(_activitys[iRow].kkm())));
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

void ActivitySeach::paintEvent(QPaintEvent *event)
{
    auto width = ui->tableWidget_activitys->width();
    ui->tableWidget_activitys->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_activitys->setColumnWidth(0, width * 3/4-13);
    ui->tableWidget_activitys->setColumnWidth(1, width * 1/4-13);

    QWidget::paintEvent(event);
}

void ActivitySeach::hideInformationIfExists(ActivityEntity &activity)
{
    for(const auto &act : _activitys){
        if (act.id() == activity.id()){
            for(int i = 0; ui->tableWidget_activitys->rowCount(); ++i){
                if (act.type() == ui->tableWidget_activitys->item(i, 0)->text()){
                    ui->tableWidget_activitys->removeRow(i);
                    for(int j = 0; j < _activitys.size(); ++j){
                        if(_activitys[j].type() == activity.type()){
                            qDebug() << "ok";
                            _activitys.erase(_activitys.begin()+j);
                        }
                    }
                    return;
                }
            }
        }
    }
    this->repaint();
}

void ActivitySeach::updateInformationIfExist(ActivityEntity &activity)
{
    qDebug() << "ok";
    for(const auto &act : _activitys){
        if (act.id() == activity.id()){
            for(int i = 0; ui->tableWidget_activitys->rowCount(); ++i){
                if (act.type() == ui->tableWidget_activitys->item(i, 0)->text()){
                    ui->tableWidget_activitys->item(i, 0)->setText(activity.type());
                    ui->tableWidget_activitys->item(i, 1)->setText(QLocale::system().toString(activity.kkm()));
                    for(int j = 0; j < _activitys.size(); ++j){
                        if(_activitys[j].type() == activity.type()){
                           _activitys[j] = activity;
                        }
                    }
                    return;
                }
            }
        }
    }
    this->repaint();
}
