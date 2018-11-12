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

signals:
    void formNewActivityReady();   // emitted when Client information is ready
    void formEditedActivityReady();

private slots:
    void onPushButtonSave();
    void onPushButtonCancel();

private:
    Ui::ActivityEdit *ui;
};

#endif // ACTIVITYEDIT_H
