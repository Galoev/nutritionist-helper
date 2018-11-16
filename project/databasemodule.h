#pragma once
#include <QVector>
#include <QString>
#include <QDate>
#include <QtSql/QSqlDatabase>

#include "entities/client.h"
#include "entities/examination.h"
#include "entities/product.h"
#include "entities/recipe.h"
#include "entities/activity.h"

class DatabaseModule
{
public:
    DatabaseModule();

    /* functions to work with Product entities */
    unsigned                addProduct(const ProductEntity&);
    ProductEntity           product(unsigned id);
    QVector<ProductEntity>  products();
    QVector<ProductEntity>  products(const QString& seachLine);
    QVector<ProductEntity>  products(QPair<int,int> interval, const char type); // type: {c, f, p, k}

    /* functions to work with Recipe entities */
    unsigned                addRecipe(const RecipeEntity&);
    RecipeEntity            recipe(unsigned id);
    QVector<RecipeEntity>   recipes();
    QVector<RecipeEntity>   recipes(const QString& seachLine);
    QVector<RecipeEntity>   recipes(QPair<int,int> interval, const char type); // type: {c, f, p, k}

    /* functions to work with Activity entities */
    unsigned                addActivity(const ActivityEntity&);
    ActivityEntity          activity(unsigned id);
    QVector<ActivityEntity> activities();
    QVector<ActivityEntity> activities(const QString& seachLine);
    QVector<ActivityEntity> activities(float kkm);                              // kkm - kkal/kg/min

    /* functions to work with Client entities */
    bool                    addClientAndSetID(Client & );                       //TODO: Need to be change as in the previous style
    Client                  client(int id, bool &isOk) const;
    QVector<Client>         clients(const QString& snp) const;
    QVector<Client>         clients() const;
    bool                    changeClientInformation(const Client& );

    /* functions to work with Examination entities */
    bool                    addExaminationAndSetID(Examination& );      //TODO: Need to be change as in the previous style
    Examination             examination(int id, bool &isOk, Client client = Client()) const;
    QVector<Examination>    examinations(Client client = Client()) const;
    QVector<Examination>    examinations(QDate from, QDate to) const;

    /* Specific database functions */
    bool importDB(const QString& fileName);
    bool exportDB(const QString& fileName);

    bool hasUnwatchedWorkError();           //Lets you know if there was an Unwatched Error at DataBase job time
    QStringList unwatchedWorkError();

private:
    QSqlDatabase    _db;
    const QString   _DB_TYPE = "QSQLITE";
    //const QString   _DB_NAME = "../program/database/db.sqlite";  //INFO : For DEBUG
    const QString   _DB_NAME = "./database/db.sqlite";
    QStringList     m_errorList;

    void initEmptyDB();
};
