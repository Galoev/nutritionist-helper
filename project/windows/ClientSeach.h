#include "ui_Client_search.h"
#include "entities/client.h"

class ClientSearch : public QWidget {
    Q_OBJECT
public:
    ClientSearch(QWidget* wgt = 0);

    void setInformation(const QVector<Client>& );
    Client selectedClient() const;
    void hideInformationIfExists(const Client &activity);
    void updateInformationIfExist(Client & );

    void paintEvent(QPaintEvent *event) override;

signals:
    void seachLineReady(const QString& );
    void selectedForShow();
    void requireUpdateAllInform();

private slots:
    void onPushButtonSeach();
    void onSelectClient(const QModelIndex& );

private:
    Ui::form_clientsSearch _ui;
    QVector<Client> _clients;
    Client _selectedClient;
};
