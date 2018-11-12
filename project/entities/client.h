#pragma once
#include <QString>
#include <QDate>

class Client {
public:
    Client() = default;
    Client(int id, QString name, QString surname, QString patronymic,
           QDate birthDate, QChar gender, short age, QString telNumber
           );

    int id() const;
    QString name() const;
    QString surname() const;
    QString patronymic() const;
    QDate birthDate() const;
    QChar gender() const;
    short age() const;
    QString telNumber() const;

    bool isInit() const;

    void setId(int id);

private:
    int _id = -1;
    QString _name;
    QString _surname;
    QString _patronymic;
    QDate _birthDate;
    QChar _gender;
    short _age;
    QString _telNumber;

    bool _isInit = false;
};
