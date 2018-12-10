#include "ui_Examination_search.h"
#include "entities/examination.h"

class ExaminationSearch : public QWidget {
    Q_OBJECT
public:
    ExaminationSearch(QWidget* wgt = 0);

    void setInformation(const QVector<Examination>& );
    Examination selectedExamination() const;
    void hideInformationIfExists(const Examination &examination);
    void updateInformationIfExist(Examination & );

    void paintEvent(QPaintEvent *event) override;

signals:
    void seachLineDateReady(const QDate& from, const QDate& to);
    void seachLineClientReady(const QString& );
    void selectedForShow();
    void requireUpdateAllInform();

private slots:
    void onPushButtonSeach();
    void onDateSeachType();
    void onClientSeachType();
    void onSelectExamination(const QModelIndex& );

private:
    Ui::form_examinationSeach _ui;
    QVector<Examination> _examinations;
    Examination _selectedExamination;
};
