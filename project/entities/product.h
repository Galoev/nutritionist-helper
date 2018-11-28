#pragma once
#include <QString>

class ProductEntity
{
public:
    enum UnitsType { GRAMM,  MILLILITER, UNDEF };
    ProductEntity();
    ProductEntity(int id
                 , QString name
                 , QString description
                 , float proteins
                 , float fats
                 , float carbohydrates
                 , float kilocalories
                 , UnitsType units);

    int id() const;
    QString name() const;
    QString description() const;
    float proteins() const;
    float fats() const;
    float carbohydrates() const;
    float kilocalories() const;
    UnitsType units() const;

    void setId(const int &id);


private:
    int m_id;
    QString m_name;
    QString m_description;
    float m_proteins;
    float m_fats;
    float m_carbohydrates;
    float m_kilocalories;
    UnitsType m_units;
};

class WeightedProduct {
public:

    WeightedProduct() = default;
    WeightedProduct(ProductEntity product, int amound);

public:
    ProductEntity product() const;
    int amound() const;

private:
    ProductEntity m_product;
    int           m_amound;
};
