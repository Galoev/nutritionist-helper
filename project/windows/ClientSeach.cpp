#include "ClientSeach.h"
#include <QDebug>

ClientSearch::ClientSearch(QWidget *wgt)
    :QWidget(wgt)
{
    _ui.setupUi(this);

    connect(_ui.pushButton_seach, SIGNAL(pressed()), SLOT(onPushButtonSeach()));
    connect(_ui.tableWidget_clients, SIGNAL(pressed(QModelIndex)), SLOT(onSelectClient(QModelIndex)));
}

void ClientSearch::setInformation(const QVector<Client> &clients)
{
    _clients = clients;

    _ui.tableWidget_clients->setRowCount(_clients.size());

    for(int iRow = 0; iRow < _clients.size(); ++iRow) {
        QStringList strColumns;
        strColumns << _clients[iRow].surname(),
        strColumns << _clients[iRow].name();
        strColumns << _clients[iRow].patronymic();

        for(int iCol = 0; iCol < strColumns.size(); ++iCol) {
            _ui.tableWidget_clients->setItem(iRow, iCol, new QTableWidgetItem(strColumns[iCol]));
        }
    }
    this->repaint();
}

Client ClientSearch::selectedClient() const
{
    return _selectedClient;
}

void ClientSearch::onPushButtonSeach()
{
    QString seach = _ui.lineEdit_clientName->text();
    emit seachLineReady(seach);
}

void ClientSearch::onSelectClient(const QModelIndex &index)
{
    int selectedClient = index.row();
    if (selectedClient >= _clients.size() && selectedClient < 0){
        qDebug() << "Error: ClientSearch::onSelectClient(const QModelIndex &)"
                 << "Not correct client vector index";
    }
    _selectedClient = _clients[selectedClient];
    emit selectedForShow();
}
