#ifndef ACTIVITYINFO_H
#define ACTIVITYINFO_H

#include <QWidget>

namespace Ui {
class ActivityInfo;
}

class ActivityInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ActivityInfo(QWidget *parent = nullptr);
    ~ActivityInfo();

signals:
    void editActivityButtonPressed();

private:
    Ui::ActivityInfo *ui;
};

#endif // ACTIVITYINFO_H
