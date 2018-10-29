#include "Client.h"

Client::Client(int id, QString name, QString surname, QString patronymic,
               QDate birthDate, QChar gender, short age, QString telNumber)
    :_id(id)
    ,_name(name)
    ,_surname(surname)
    ,_patronymic(patronymic)
    ,_birthDate(birthDate)
    ,_gender(gender)
    ,_age(age)
    ,_telNumber(telNumber)
    ,_isInit(true)
{
}

int Client::id() const
{
    return _id;
}

QString Client::name() const
{
    return _name;
}

QString Client::surname() const
{
    return _surname;
}


QString Client::patronymic() const
{
    return _patronymic;
}

QDate Client::birthDate() const
{
    return _birthDate;
}

QChar Client::gender() const
{
    return _gender;
}

short Client::age() const
{
    return _age;
}

QString Client::telNumber() const
{
    return _telNumber;
}

void Client::setId(int id)
{
    _id = id;
}

bool Client::isInit() const
{
    return _isInit;
}
