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
                 , unsigned proteins
                 , unsigned fats
                 , unsigned carbohydrates
                 , unsigned kilocalories
                 , UnitsType units);

    int id() const;
    QString name() const;
    QString description() const;
    unsigned proteins() const;
    unsigned fats() const;
    unsigned carbohydrates() const;
    unsigned kilocalories() const;
    UnitsType units() const;

    void setId(const int &id);


private:
    int m_id;
    QString m_name;
    QString m_description;
    unsigned m_proteins;
    unsigned m_fats;
    unsigned m_carbohydrates;
    unsigned m_kilocalories;
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
