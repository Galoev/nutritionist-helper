#pragma once
#include <QString>

class ProductEntity
{
public:
    ProductEntity();
    ProductEntity(int id
                 , QString name
                 , QString description
                 , unsigned proteins
                 , unsigned fats
                 , unsigned carbohydrates
                 , unsigned kilocalories);

    void setId(const int &id);

    int id() const;
    QString name() const;
    QString description() const;
    unsigned proteins() const;
    unsigned fats() const;
    unsigned carbohydrates() const;
    unsigned kilocalories() const;

private:
    int m_id;
    QString m_name;
    QString m_description;
    unsigned m_proteins;
    unsigned m_fats;
    unsigned m_carbohydrates;
    unsigned m_kilocalories;
};

class WeightedProduct{
public:
    enum UnitsType { GRAMM,  MILLILITER };
    WeightedProduct() = default;
    WeightedProduct(const ProductEntity& product, int amound, UnitsType units);

public:
    ProductEntity product() const;
    int amound() const;
    UnitsType units() const;

private:
    ProductEntity m_product;
    int           m_amound;
    UnitsType     m_units;
};
