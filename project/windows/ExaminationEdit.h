#include "ui_Examination_edit.h"
#include "entities/examination.h"

class ExaminationEdit : public QWidget {
    Q_OBJECT
public:
    ExaminationEdit(QWidget* wgt = 0);

    void setInformation(const Client& , bool isFullExamination);
    void setInformation(const Examination& );
    Examination examination() const;

signals:
    void formReady();
    void formNewExaminationReady();
    void formEditedExaminationReady();

private slots:
    void onNextPage();
    void onPrevPage();
    void onSaveForm();

    void onPushButtonCalculate_65();
    void onPushButtonCalculate_69_77();
    void onComboBoxChanged_87(int index);

private:
    void setPage(int index);
    void setupValidators();

    Ui::form_examinationEdit _ui;
    Examination _examination;
    QChar m_gender;
    bool m_isEditingMod;
};
