#pragma once
#include <QString>
#include <QStringList>
#include <QVector>

#include "product.h"

class RecipeEntity
{
public:
    RecipeEntity() = default;
    RecipeEntity(int id, QString name, QVector<WeightedProduct> products, QStringList cookingPoints);

    int id() const;
    QString name() const;
    QVector<WeightedProduct> products() const;
    QStringList cookingPoints() const;
    void addProduct(WeightedProduct product, unsigned int index);
    void deleteProduct(unsigned int index);
    void addDescription(QString description, unsigned int index);
    void deleteDescription(unsigned int index);
    QVector<WeightedProduct> getPoducts();
    QStringList getCookingPoints();

private:
    int                       m_id;
    QString                   m_name;
    QVector<WeightedProduct>  m_products;
    QStringList               m_cookingPoints;
};
