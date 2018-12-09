#include "ui_Client_info.h"
#include "entities/examination.h"
#include "entities/client.h"

class ClientInfo : public QWidget {
    Q_OBJECT
public:
    ClientInfo(QWidget* wgt = 0);
    void setInformation(const Client &client, const QVector<Examination> &examinations);
    Client client() const;
    Examination selectedExamination() const;

signals:
    void newExaminationHalfButtonPressed();
    void newExaminationFullButtonPressed();
    void examinationSelectedForShow();
    void editClientButtonPressed();
    void deleteClientButtonPressed();

private slots:
    void onSelectExamination(const QModelIndex& );

private:
    Ui::form_clientInfo _ui;
    Client _client;
    QVector<Examination> _examinations;
    Examination _selectedExm;
};
