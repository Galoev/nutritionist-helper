#ifndef ACTIVITYCALCULATION_H
#define ACTIVITYCALCULATION_H

#include <QWidget>

namespace Ui {
class ActivityCalculation;
}

class ActivityCalculation : public QWidget
{
    Q_OBJECT

public:
    explicit ActivityCalculation(QWidget *parent = nullptr);
    ~ActivityCalculation();

private:
    Ui::ActivityCalculation *ui;
};

#endif // ACTIVITYCALCULATION_H
