#pragma once
#include <QVector>
#include <QString>
#include <QDate>
#include <QtSql/QSqlDatabase>

#include "client.h"
#include "examination.h"

class DatabaseModule
{
public:
    DatabaseModule();

    bool                    addExaminationAndSetID(Examination& );
    bool                    addClientAndSetID(Client & );

    bool                    changeClientInformation(const Client& );

    Client                  client(int id, bool &isOk) const;
    QVector<Client>         clients(const QString& snp) const;
    QVector<Client>         clients() const;
    Examination             examination(int id, bool &isOk, Client client = Client()) const;
    QVector<Examination>    examinations(Client client = Client()) const;
    QVector<Examination>    examinations(QDate from, QDate to) const;

    bool importDB(const QString& fileName);
    bool exportDB(const QString& fileName);

private:
    QSqlDatabase    _db;
    const QString   _DB_TYPE = "QSQLITE";
    //const QString   _DB_NAME = "../program/database/db.sqlite";  //INFO : For DEBUG
    const QString   _DB_NAME = "./database/db.sqlite";

    void initEmptyDB();
};
