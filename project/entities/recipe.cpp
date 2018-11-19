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
void RecipeEntity::setId(int id)
{
    m_id = id;
}
