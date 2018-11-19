#ifndef ACTIVITYINFO_H
#define ACTIVITYINFO_H

#include <QWidget>
#include "entities/activity.h"

namespace Ui {
class ActivityInfo;
}

class ActivityInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ActivityInfo(QWidget *parent = nullptr);
    ~ActivityInfo();

    void setInformation(const ActivityEntity & );
    ActivityEntity activity() const;

signals:
    void editActivityButtonPressed();

private:
    Ui::ActivityInfo *ui;
    ActivityEntity _activity;

};

#endif // ACTIVITYINFO_H
