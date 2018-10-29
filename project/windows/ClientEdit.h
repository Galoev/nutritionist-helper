#include "ui_Client_edit.h"
#include "client.h"

class ClientEdit : public QWidget {
    Q_OBJECT
public:
    ClientEdit(QWidget* wgt = 0);

    void setInformation(const Client& );
    Client client() const;

signals:
    void formNewClientReady();   // emitted when Client information is ready
    void formEditedClientReady();

private slots:
    void onPushButtonSave();
    void onPushButtonCancel();

private:
    Ui::form_clientEdit _ui;
    Client _client;
    bool _isEditingMod = false;
};
