#ifndef ACTIVITYEDIT_H
#define ACTIVITYEDIT_H

#include <QWidget>

namespace Ui {
class ActivityEdit;
}

class ActivityEdit : public QWidget
{
    Q_OBJECT

public:
    explicit ActivityEdit(QWidget *parent = nullptr);
    ~ActivityEdit();

private:
    Ui::ActivityEdit *ui;
};

#endif // ACTIVITYEDIT_H
