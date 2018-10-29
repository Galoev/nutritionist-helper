#include "ExaminationSearch.h"
#include <QDebug>
ExaminationSearch::ExaminationSearch(QWidget *wgt)
    :QWidget(wgt)
{
    _ui.setupUi(this);

    connect(_ui.pushButton_seach, SIGNAL(pressed()), SLOT(onPushButtonSeach()));
    connect(_ui.radioButton_clientSeach, SIGNAL(pressed()), SLOT(onClientSeachType()));
    connect(_ui.radioButton_dateSeach, SIGNAL(pressed()), SLOT(onDateSeachType()));
    connect(_ui.tableWidget_examinations, SIGNAL(pressed(QModelIndex)), SLOT(onSelectExamination(QModelIndex)));
}

Examination ExaminationSearch::selectedExamination() const
{
    return _selectedExamination;
}

void ExaminationSearch::setInformation(const QVector<Examination> &exms)
{
    _examinations = exms;

    _ui.tableWidget_examinations->setRowCount(_examinations.size());

    for(int iRow = 0; iRow < _examinations.size(); ++iRow) {
        QString name = QString("%1 %2. %3.")
                .arg(_examinations[iRow].client().surname())
                .arg(_examinations[iRow].client().name()[0])
                .arg(_examinations[iRow].client().patronymic()[0]);

        QStringList strColumns;
        strColumns << _examinations[iRow].date().date().toString()
                   << _examinations[iRow].date().time().toString()
                   << name
                   << (_examinations[iRow].isFullExamination() ? tr("Прием") : tr("Консультация"));

        for(int iCol = 0; iCol < strColumns.size(); ++iCol) {
            _ui.tableWidget_examinations->setItem(iRow, iCol, new QTableWidgetItem(strColumns[iCol]));
        }
    }

    this->repaint();
}

void ExaminationSearch::onPushButtonSeach()
{
    if(_ui.radioButton_clientSeach->isChecked()) {
        QString seach = _ui.lineEdit_clientName->text();
        if (!seach.isEmpty()) {
           emit seachLineClientReady(seach);
        }
    } else if (_ui.radioButton_dateSeach->isChecked()) {
        QDate from = _ui.dateEdit_examinationFrom->date();
        QDate to = _ui.dateEdit_examinationTo->date();
        emit seachLineDateReady(from, to);
    }
}

void ExaminationSearch::onDateSeachType()
{
    _ui.stackedWidget->setCurrentIndex(0);
}

void ExaminationSearch::onClientSeachType()
{
    _ui.stackedWidget->setCurrentIndex(1);
}

void ExaminationSearch::onSelectExamination(const QModelIndex &index)
{
    int selectedExm = index.row();
    if (selectedExm >= _examinations.size() && selectedExm < 0){
        qDebug() << "Error: ClientSearch::onSelectClient(const QModelIndex &)"
                 << "Not correct client vector index";
    }
    _selectedExamination = _examinations[selectedExm];
    emit selectedForShow();
}
