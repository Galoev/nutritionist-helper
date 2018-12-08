#pragma once
#include <QWidget>

namespace Ui {
class ActivityCalculation;
}

class ActivityCalculation : public QWidget
{
    Q_OBJECT

public:
    explicit ActivityCalculation(QWidget *parent = nullptr);
    ~ActivityCalculation() override;

    void paintEvent(QPaintEvent *event) override;

private:
    Ui::ActivityCalculation *ui;
};
