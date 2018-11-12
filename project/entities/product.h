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

    inline int id() const;
    inline void setId(const int &id);

    inline QString name() const;
    inline void setName(const QString &name);

    inline QString description() const;
    inline void setDescription(const QString &description);

    inline unsigned proteins() const;
    inline void setProteins(const unsigned &proteins);

    inline unsigned fats() const;
    inline void setFats(const unsigned &fats);

    inline unsigned carbohydrates() const;
    inline void setCarbohydrates(const unsigned &carbohydrates);

    inline unsigned kilocalories() const;
    inline void setKilocalories(const unsigned &kilocalories);

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
