#include "ClientInfo.h"

ClientInfo::ClientInfo(QWidget *wgt)
    : QWidget(wgt)
{
    _ui.setupUi(this);

    connect(_ui.pushButton_addExaminationFull, SIGNAL(pressed()), SIGNAL(newExaminationFullButtonPressed()));
    connect(_ui.pushButton_addExaminationHalf, SIGNAL(pressed()), SIGNAL(newExaminationHalfButtonPressed()));
    connect(_ui.pushButton_clientEdit, SIGNAL(pressed()), SIGNAL(editClientButtonPressed()));
    connect(_ui.tableWidget_examinations, SIGNAL(pressed(QModelIndex)), SLOT(onSelectExamination(QModelIndex)));
}

void ClientInfo::setInformation(const Client &client, const QVector<Examination> &examinations)
{
    _client = client;
    _examinations = examinations;
    
    _ui.label_clientSurname->setText(_client.surname());
    _ui.label_clientName->setText(_client.name());
    _ui.label_clientPatronymic->setText(_client.patronymic());
    _ui.label_clientAgeYear->setText(QString("%1 (%2)")
                                     .arg(_client.age())
                                     .arg(_client.birthDate().year())
                                     );

    _ui.tableWidget_examinations->setRowCount(_examinations.size());

    for(int iRow = 0; iRow < _examinations.size(); ++iRow){
        QString columnStr1 = _examinations[iRow].date().toString();
        QString columnStr2 = _examinations[iRow].isFullExamination() ? tr("Прием") : tr("Консультация");
        _ui.tableWidget_examinations->setItem(iRow, 0, new QTableWidgetItem(columnStr1));
        _ui.tableWidget_examinations->setItem(iRow, 1, new QTableWidgetItem(columnStr2));
    }

    this->repaint();
}

void ClientInfo::onSelectExamination(const QModelIndex &index)
{
    int selectedExam = index.row();
    _selectedExm = _examinations[selectedExam];
    emit examinationSelectedForShow();
}

Client ClientInfo::client() const
{
    return _client;
}

Examination ClientInfo::selectedExamination() const
{
    return _selectedExm;
}
