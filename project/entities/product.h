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

    int id() const;
    void setId(const int &id);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    unsigned proteins() const;
    void setProteins(const unsigned &proteins);

    unsigned fats() const;
    void setFats(const unsigned &fats);

    unsigned carbohydrates() const;
    void setCarbohydrates(const unsigned &carbohydrates);

    unsigned kilocalories() const;
    void setKilocalories(const unsigned &kilocalories);

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
    enum UnitsType { GRAMM,  MILLILITER, NONE };
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
