#ifndef ACTIVITYSEACH_H
#define ACTIVITYSEACH_H

#include <QWidget>
#include "entities/activity.h"

namespace Ui {
class ActivitySeach;
}

class ActivitySeach : public QWidget
{
    Q_OBJECT

public:
    explicit ActivitySeach(QWidget *parent = nullptr);
    ~ActivitySeach();

    void paintEvent(QPaintEvent *event) override;

    void hideInformationIfExists(ActivityEntity & );
    void updateInformationIfExist(ActivityEntity & );
    void setInformation(const QVector<ActivityEntity>& );
    ActivityEntity selectedActivity() const;

signals:
    void seachLineActivityReady(const QString& );
    void seachLineKcalReady(const int from, const int to);
    void selectedForShow();
    void requireUpdateAllInform();

private slots:
    void onPushButtonSeach();
    void onActivitySeachType();
    void onKcalSeachType();
    void onSelectActivity(const QModelIndex& );

private:
    Ui::ActivitySeach *ui;
    QVector<ActivityEntity> _activitys;
    ActivityEntity _selectedActivity;
};

#endif // ACTIVITYSEACH_H
