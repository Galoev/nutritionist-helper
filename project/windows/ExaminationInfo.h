#include "ui_Examination_info.h"
#include "entities/examination.h"

class ExaminationInfo : public QWidget {
    Q_OBJECT
public:
    ExaminationInfo(QWidget* wgt = 0);

    void setInformation(const Examination & );
    Examination examination() const;

signals:
    void deleteExamination();
    void editExaminationButtonPressed();
    void printExamination(bool ifFull);    

private slots:
    void onDeleteExamination();
    void onEditExamination();
    void onPrintFullExamination();
    void onPrintHalfExamination();

private:
    Ui::form_examinationInfo _ui;
    Examination _examination;
};
