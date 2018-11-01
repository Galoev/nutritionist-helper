#ifndef ACTIVITYSEACH_H
#define ACTIVITYSEACH_H

#include <QWidget>

namespace Ui {
class ActivitySeach;
}

class ActivitySeach : public QWidget
{
    Q_OBJECT

public:
    explicit ActivitySeach(QWidget *parent = nullptr);
    ~ActivitySeach();

private:
    Ui::ActivitySeach *ui;
};

#endif // ACTIVITYSEACH_H
