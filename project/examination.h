#pragma once
#include <QMap>
#include <QString>
#include <QDate>
#include <QVector>
#include <QPair>
#include "client.h"

class FormField {
public:
    enum Type { String, Date, UShort, Float, ComboB };
    FormField(QString name, Type type, QString interpretation
        , bool isMayBeEmpty = false);
    FormField() = default;

    QString name() const;
    QString value() const;
    Type type() const;
    bool isMayBeEmpty() const;
    QString interpretation() const;

    void setValue(const QString &value);

private:
    bool _notInit = true;
    QString _name;
    QString _value;
    Type _type;
    QString _interpretation;
    bool _isMayBeEmpty;
};

class Examination {
public:

    Examination();

    int id() const;
    Client client() const;
    bool isFullExamination() const;
    QDateTime date() const;
    FormField field(QString fieldName);
    QVector<FormField> fields();

    void setId(int id);
    void setClient(Client client);
    void setIsFullExamination(bool isFullExamination);
    void setDate(const QDateTime &date);
    void setFieldValue(QString fieldName, QString value);

private:
    void initFields();

    QVector<FormField> _fields;
    int _id;
    Client _client;
    bool _isFullExamination;
    QDateTime _date;
};
