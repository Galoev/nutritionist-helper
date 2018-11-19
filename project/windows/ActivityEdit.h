#include <QWidget>
#include "entities/activity.h"

namespace Ui {
class ActivityEdit;
}

class ActivityEdit : public QWidget
{
    Q_OBJECT

public:
    explicit ActivityEdit(QWidget *parent = nullptr);
    ~ActivityEdit();

    void setInformation(const ActivityEntity& );
    ActivityEntity activity() const;

signals:
    void formNewActivityReady();
    void formEditedActivityReady();

private slots:
    void onPushButtonSave();
    void onPushButtonCancel();

private:
    Ui::ActivityEdit *ui;
    ActivityEntity _activity;
    bool _isEditingMod = false;
};

