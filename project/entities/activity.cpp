#include "activity.h"

ActivityEntity::ActivityEntity()
    :m_id(-1)
    ,m_type("Unknown")
    ,m_kkm(0)
{
}

ActivityEntity::ActivityEntity(int id, QString type, float kkm)
    :m_id(id)
    ,m_type(type)
    ,m_kkm(kkm)
{
}

QString ActivityEntity::type() const
{
    return m_type;
}

void ActivityEntity::setType(const QString &name)
{
    m_type = name;
}

float ActivityEntity::kkm() const
{
    return m_kkm;
}

void ActivityEntity::setKKM(const float kkm)
{
    m_kkm = kkm;
}

int ActivityEntity::id() const
{
    return m_id;
}

void ActivityEntity::setId(int id)
{
    m_id = id;
}
