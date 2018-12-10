#include "ClientSeach.h"
#include <QDebug>

ClientSearch::ClientSearch(QWidget *wgt)
    :QWidget(wgt)
{
    _ui.setupUi(this);

    connect(_ui.pushButton_seach, SIGNAL(pressed()), SLOT(onPushButtonSeach()));
    connect(_ui.pushButton_searchAll, SIGNAL(pressed()), SIGNAL(requireUpdateAllInform()));
    connect(_ui.tableWidget_clients, SIGNAL(pressed(QModelIndex)), SLOT(onSelectClient(QModelIndex)));
}

void ClientSearch::setInformation(const QVector<Client> &clients)
{
    _clients = clients;

    _ui.tableWidget_clients->setRowCount(_clients.size());

    for(int iRow = 0; iRow < _clients.size(); ++iRow) {
        QStringList strColumns;
        strColumns << _clients[iRow].surname();
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

void ClientSearch::hideInformationIfExists(const Client &client)
{
    for(const auto &tmp : _clients){
        if (tmp.id() == client.id()){
            for(int i = 0; _ui.tableWidget_clients->rowCount(); ++i){
                if (tmp.surname()    == _ui.tableWidget_clients->item(i, 0)->text() &&
                    tmp.name()       == _ui.tableWidget_clients->item(i, 1)->text() &&
                    tmp.patronymic() == _ui.tableWidget_clients->item(i, 2)->text()){
                    _ui.tableWidget_clients->removeRow(i);
                    return;
                }
            }
        }
    }
}

void ClientSearch::updateInformationIfExist(Client &client)
{
    for(const auto &tmp : _clients){
        if (tmp.id() == client.id()){
            for(int i = 0; _ui.tableWidget_clients->rowCount(); ++i){
                if (tmp.surname()    == _ui.tableWidget_clients->item(i, 0)->text() &&
                    tmp.name()       == _ui.tableWidget_clients->item(i, 1)->text() &&
                    tmp.patronymic() == _ui.tableWidget_clients->item(i, 2)->text()){
                    _ui.tableWidget_clients->item(i, 0)->setText(client.surname());
                    _ui.tableWidget_clients->item(i, 1)->setText(client.name());
                    _ui.tableWidget_clients->item(i, 2)->setText(client.patronymic());
                    return;
                }
            }
        }
    }
}

void ClientSearch::paintEvent(QPaintEvent *event)
{
    auto width = _ui.tableWidget_clients->width();
    _ui.tableWidget_clients->horizontalHeader()->setStretchLastSection(true);
    _ui.tableWidget_clients->setColumnWidth(0, width / 3 - 10);
    _ui.tableWidget_clients->setColumnWidth(1, width / 3 - 10);
    _ui.tableWidget_clients->setColumnWidth(2, width / 3 - 10);

    QWidget::paintEvent(event);
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
