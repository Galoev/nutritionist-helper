#include "ExaminationInfo.h"

ExaminationInfo::ExaminationInfo(QWidget *wgt)
    :QWidget(wgt)
{
    _ui.setupUi(this);

    connect(_ui.pushButton_examinationDelete, SIGNAL(pressed()), SLOT(onDeleteExamination()));
    connect(_ui.pushButton_examinationEdit, SIGNAL(pressed()), SLOT(onEditExamination()));
    connect(_ui.pushButton_examinationFullExport, SIGNAL(pressed()), SLOT(onPrintFullExamination()));
    connect(_ui.pushButton_examinationHalfExport, SIGNAL(pressed()), SLOT(onPrintHalfExamination()));
}

void ExaminationInfo::setInformation(const Examination &e)
{
    _examination = e;

    /// Activates or deactivates the output of a full report,
    /// depending on the type (full/half) of examination
    _ui.pushButton_examinationFullExport->setEnabled(_examination.isFullExamination());

    Client client = _examination.client();
    _ui.label_clientSurname->setText(client.surname());
    _ui.label_clientName->setText(client.name());
    _ui.label_clientPatronymic->setText(client.patronymic());
    _ui.label_clientAgeYear->setText(QString("%1 (%2)")
                                     .arg(client.age())
                                     .arg(client.birthDate().year())
                                     );

    _ui.label_examinationType->setText(_examination.isFullExamination() ? tr("Прием") : tr("Консультация"));
    _ui.label__examinationDateTime->setText(_examination.date().toString());

    this->repaint();
}

Examination ExaminationInfo::examination() const
{
    return _examination;
}

void ExaminationInfo::onDeleteExamination()
{
    emit deleteExamination();
    this->close();
}

void ExaminationInfo::onEditExamination()
{
    // TODO: Add functionality
}

void ExaminationInfo::onPrintFullExamination()
{
    emit printExamination(true);
}

void ExaminationInfo::onPrintHalfExamination()
{
    emit printExamination(false);
}
