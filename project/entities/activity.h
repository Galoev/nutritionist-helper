#pragma once
#include <QString>

class ActivityEntity
{
public:   
    ActivityEntity();
    ActivityEntity(int id, QString type, float kkm);

    int id() const;
    void setId(int id);

    QString type() const;
    void setType(const QString &type);

    float kkm() const;
    void setKKM(const float kkm);

private:
    int     m_id;
    QString m_type;
    float   m_kkm; // kkal per kg per minute
};

class ActivityController {
    //TODO: not emplemented

    //ActivityEntity + { Интервал } -> Расход энергии
};
