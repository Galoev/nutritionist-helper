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
    float proteins() const;
    float fats() const;
    float carbohydrates() const;
    float kkal() const;
    QVector<WeightedProduct> getPoducts();
    QStringList getCookingPoints();

    void setId(int id);
    void setProducts(const QVector<WeightedProduct>& );

    void addProduct(WeightedProduct product, unsigned int index);
    void addDescription(QString description, unsigned int index);

    void deleteProduct(unsigned int index);
    void deleteDescription(unsigned int index);





private:
    int                       m_id;
    QString                   m_name;
    QVector<WeightedProduct>  m_products;
    QStringList               m_cookingPoints;
};
