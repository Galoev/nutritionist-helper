#include "ui_Client_search.h"
#include "client.h"

class ClientSearch : public QWidget {
    Q_OBJECT
public:
    ClientSearch(QWidget* wgt = 0);

    void setInformation(const QVector<Client>& );
    Client selectedClient() const;

signals:
    void seachLineReady(const QString& );
    void selectedForShow();

private slots:
    void onPushButtonSeach();
    void onSelectClient(const QModelIndex& );

private:
    Ui::form_clientsSearch _ui;
    QVector<Client> _clients;
    Client _selectedClient;
};
