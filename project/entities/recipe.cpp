#include "recipe.h"
RecipeEntity::RecipeEntity()
    :m_id(-1)
    ,m_name("Unknown")
{
}

RecipeEntity::RecipeEntity(int id, QString name, QVector<WeightedProduct> products, QStringList cookingPoints)
    :m_id(id)
    ,m_name(name)
    ,m_products(products)
    ,m_cookingPoints(cookingPoints)
{
}

int RecipeEntity::id() const
{
    return m_id;
}

QString RecipeEntity::name() const
{
    return m_name;
}

QVector<WeightedProduct> RecipeEntity::products() const
{
    return m_products;
}

QStringList RecipeEntity::cookingPoints() const
{
    return m_cookingPoints;
}

float RecipeEntity::proteins()const
{
    float proteins(0.f);
    for (const auto& wp : m_products){
        proteins += wp.product().proteins() * wp.amound() * 0.01;
    }
    return proteins;
}

float RecipeEntity::fats()const
{
    float fats(0.f);
    for (const auto& wp : m_products){
        fats += wp.product().fats() * wp.amound() * 0.01;
    }
    return fats;
}

float RecipeEntity::carbohydrates()const
{
    float carbohydrates(0.f);
    for (const auto& wp : m_products){
        carbohydrates += wp.product().carbohydrates() * wp.amound() * 0.01;
    }
    return carbohydrates;
}

float RecipeEntity::kkal()const
{
    float kkal(0.f);
    for (const auto& wp : m_products){
        kkal += wp.product().kilocalories() * wp.amound() * 0.01;
    }
    return kkal;
}

void RecipeEntity::addProduct(WeightedProduct product, unsigned int index)
{
    m_products.insert(index, product);
}

void RecipeEntity::deleteProduct(unsigned int index)
{
    m_products.erase(m_products.begin() + index);
}

void RecipeEntity::addDescription(QString description, unsigned int index)
{
    m_cookingPoints.insert(index, description);
}

void RecipeEntity::deleteDescription(unsigned int index)
{
    m_cookingPoints.erase(m_cookingPoints.begin() + index);
}

QVector<WeightedProduct> RecipeEntity::getPoducts()
{
    return m_products;
}

QStringList RecipeEntity::getCookingPoints()
{
    return m_cookingPoints;
}

void RecipeEntity::setId(int id)
{
    m_id = id;
}
   
void RecipeEntity::setProducts(const QVector<WeightedProduct> &p)
{
    m_products = p;
}
