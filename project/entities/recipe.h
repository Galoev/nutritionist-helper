#pragma once
#include <QString>
#include <QStringList>
#include <QVector>

#include "product.h"

class RecipeEntity
{
public:
    RecipeEntity();
    RecipeEntity(int id, QString name, QVector<WeightedProduct> products, QStringList cookingPoints);

    int id() const;
    QString name() const;
    QVector<WeightedProduct> products() const;
    QStringList cookingPoints() const;

    void setId(int id);

private:
    int                       m_id;
    QString                   m_name;
    QVector<WeightedProduct>  m_products;
    QStringList               m_cookingPoints;
};
