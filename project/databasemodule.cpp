#include "databasemodule.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QFile>
#include <QDebug>
#include <QDir>

DatabaseModule::DatabaseModule()
{
    if (!QSqlDatabase::drivers().contains("QSQLITE")){
        qDebug() << "Error: " << Q_FUNC_INFO
                 << "Unable to load database. This program needs the SQLITE driver";
        return;
    }
    _db = QSqlDatabase::addDatabase(_DB_TYPE);

    if (!QFile::exists(_DB_NAME)){
        initEmptyDB();
    } else{
        _db.setDatabaseName(_DB_NAME);
    }

    if (!_db.open()) {
        qDebug() << "Error: " << Q_FUNC_INFO
                 << _db.lastError().text();
        QFile::remove(_DB_NAME);
        initEmptyDB();
    }
}

unsigned DatabaseModule::addProduct(const ProductEntity &pe)
{
    QSqlQuery q;
    q.prepare("INSERT INTO Products (name, description, proteins, fats, carbohydrates, kkal, units)"
              "VALUES( ?, ?, ?, ?, ?, ?, ?);");
    q.addBindValue(pe.name());
    q.addBindValue(pe.description());
    q.addBindValue(pe.proteins());
    q.addBindValue(pe.fats());
    q.addBindValue(pe.carbohydrates());
    q.addBindValue(pe.kilocalories());
    q.addBindValue(static_cast<int>(pe.units()));
    if(!q.exec()) {
        m_errorList << "Error: in " << Q_FUNC_INFO << q.lastError().text();
        return 0;
    }
    ///
    return q.lastInsertId().toUInt();
}

void DatabaseModule::deleteProduct(const ProductEntity &product)
{
    QSqlQuery q;
    q.prepare("DELETE FROM Products WHERE id=?");
    q.addBindValue(product.id());
    if(!q.exec()) {
        m_errorList << "Error: in " << Q_FUNC_INFO << q.lastError().text();
    }
}

ProductEntity DatabaseModule::product(unsigned id)
{
    QSqlQuery q;
    q.prepare("SELECT * FROM Products WHERE id=?");
    q.addBindValue(id);
    if(!q.exec()){
        m_errorList << "Error: in " << Q_FUNC_INFO << q.lastError().text();
        ProductEntity();
    }
    ///
    q.next();
    ///
    if(!q.isValid()){
        qDebug() << "Error:" << Q_FUNC_INFO
                 << "In DB has no Product with id:" + QString::number(id);
    }
    ///
    QString name =        q.value("name").toString();
    QString description = q.value("description").toString();
    float proteints =     q.value("proteins").toFloat();
    float fats =          q.value("fats").toFloat();
    float carbohydrates = q.value("carbohydrates").toFloat();
    float kkal =          q.value("kkal").toFloat();
    int units =           q.value("units").toInt();
    return ProductEntity(id, name, description
                         , proteints, fats, carbohydrates, kkal
                         , static_cast<ProductEntity::UnitsType>(units));
}

QVector<ProductEntity> DatabaseModule::products()
{
    QVector<ProductEntity> products;
    ///
    QSqlQuery q("SELECT id FROM Products");
    if(!q.exec()) {
        m_errorList << "Error: in " << Q_FUNC_INFO << q.lastError().text();
        return products;
    }
    while(q.next()) {
        auto prevErrorSize =  m_errorList.size();
        ProductEntity c = this->product(q.value("id").toInt());
        auto avterErrorSize = m_errorList.size();
        if(prevErrorSize == avterErrorSize) {
            products.push_back(c);
        }
    }
    return products;
}

QVector<ProductEntity> DatabaseModule::products(const QStringList &seachLine)
{
    QVector<ProductEntity> products;
    foreach (QString snp, seachLine) {
        QSqlQuery q(QString(" SELECT id FROM Products     "
                            " WHERE name LIKE '%%1%'       "
                            "    OR description LIKE '%%2%'"
                            ).arg(snp).arg(snp));
        if(!q.exec()){
            m_errorList << "Error:" << Q_FUNC_INFO << "Wrong condition" << q.lastError().text();
            return products;
        }

        while(q.next()) {
            auto prevErrorSize =  m_errorList.size();
            ProductEntity c = this->product(q.value("id").toInt());
            auto avterErrorSize = m_errorList.size();
            if(prevErrorSize == avterErrorSize) {
                products.push_back(c);
            }
        }
    }
    return products;
}

QVector<ProductEntity> DatabaseModule::products(QPair<float, float> interval, const char type)
{
    QVector<ProductEntity> products;
    ///
    QString stype, prefix = " WHERE %1 BETWEEN %2 AND %3";
    switch (type) {
    case 'c': { stype = "carbohydrates"; } break;
    case 'f': { stype = "fats"; } break;
    case 'p': { stype = "proteins"; } break;
    case 'k': { stype = "kkal"; } break;
    default: {
        stype = "";
        prefix = "";
    }
    }
    QSqlQuery q("SELECT id FROM Products"
                    "" + prefix.arg(stype).arg(interval.first).arg(interval.second));
    if(!q.exec()){
        m_errorList << "Error:" << Q_FUNC_INFO << "Wrong condition" << q.lastError().text();
        return products;
    }
    while(q.next()) {
        auto prevErrorSize =  m_errorList.size();
        ProductEntity c = this->product(q.value("id").toInt());
        auto avterErrorSize = m_errorList.size();
        if(prevErrorSize == avterErrorSize) {
            products.push_back(c);
        }
    }
    return products;
}

void DatabaseModule::changeProductInformation(const ProductEntity &newProduct)
{
    //call this for testing to exists product
    auto prevErrorSize =  m_errorList.size();
    product(newProduct.id());
    auto avterErrorSize = m_errorList.size();
    if(prevErrorSize != avterErrorSize) {
        m_errorList << "Error:" << Q_FUNC_INFO << " Error with searching product for update";
        return;
    }

    QSqlQuery q;
    q.prepare("UPDATE Products "
              "SET name = ?, description = ?, proteins = ?, fats = ?, carbohydrates = ?, kkal = ?, units = ? "
              "WHERE id = ?"
              );
    q.addBindValue(newProduct.name());
    q.addBindValue(newProduct.description());
    q.addBindValue(newProduct.proteins());
    q.addBindValue(newProduct.fats());
    q.addBindValue(newProduct.carbohydrates());
    q.addBindValue(newProduct.kilocalories());
    q.addBindValue(newProduct.units());
    q.addBindValue(newProduct.id());

    if(!q.exec()) {
        m_errorList << "Error:" << Q_FUNC_INFO <<  q.lastError().text();
        return;
    }
}

unsigned DatabaseModule::addRecipe(const RecipeEntity &re)
{
    ///
    QSqlQuery q;
    q.prepare("INSERT INTO Recipes (name, proteins, fats, carbohydrates, kcal )"
              "VALUES( ?, ?, ?, ?, ? );");
    q.addBindValue(re.name());
    q.addBindValue(re.proteins());
    q.addBindValue(re.fats());
    q.addBindValue(re.carbohydrates());
    q.addBindValue(re.kkal());
    if(!q.exec()) {
        qDebug() <<
        m_errorList << "Error: in " << Q_FUNC_INFO << "!q!" << q.lastError().text();
        return 0;
    }
    ///
    auto recipeID = q.lastInsertId().toUInt();
    ///
    insertIntoCookingPoints(recipeID, re.cookingPoints());
    insertIntoProductsInRecipes(recipeID, re.products());
    ///
    return recipeID;
}

void DatabaseModule::deleteRecipe(const RecipeEntity &recipe)
{
    QSqlQuery q;
    q.prepare("DELETE FROM Recipes WHERE id=?");
    q.addBindValue(recipe.id());
    if(!q.exec()) {
        m_errorList << "Error: in " << Q_FUNC_INFO << q.lastError().text();
    }
}

RecipeEntity DatabaseModule::recipe(unsigned recipeId)
{
    QSqlQuery q;
    q.prepare("SELECT id, name FROM Recipes WHERE id=?");
    q.addBindValue(recipeId);
    if(!q.exec()){
        m_errorList << "Error: in " << Q_FUNC_INFO << "!q!" << q.lastError().text();
        ProductEntity();
    }
    q.next();
    if(!q.isValid()){
        qDebug() << "Error:" << Q_FUNC_INFO
                 << "In DB has no Recipe with id:" + QString::number(recipeId);
    }
    QString recipeName = q.value("name").toString();
    ///
    /// Получение пордуктов для рецепта
    ///
    QSqlQuery q2;
    q2.prepare("SELECT Products.id, Products.units, ProductsInRecipes.amound"
                 "      FROM Products INNER JOIN ProductsInRecipes ON ProductsInRecipes.product_id = Products.id "
                 "                                                      AND ProductsInRecipes.recipe_id = ?");
    q2.addBindValue(recipeId);
    if(!q2.exec()){
        qDebug() << "Error: in " << Q_FUNC_INFO << "!q2!" << q2.lastError().text();
        m_errorList << "Error: in " << Q_FUNC_INFO << "!q2!" << q2.lastError().text();
    }
    QVector<WeightedProduct> weightedProducts;
    while(q2.next()){
        auto productId = q2.value("id").toUInt();

        WeightedProduct wproduct(this->product(productId) ,q2.value("amound").toFloat());
        weightedProducts.push_back(wproduct);
    }
    ///
    /// Получение пунктов приготовления
    ///
    QSqlQuery q3;
    q3.prepare("SELECT CookingPoints.description "
               "    FROM CookingPoints"
               "    WHERE CookingPoints.recipe_id = ?");
    q3.addBindValue(recipeId);
    QStringList coockingPoints;
    if(!q3.exec()){
        m_errorList << "Error: in " << Q_FUNC_INFO << "!q3!" << q3.lastError().text();
    }
    while(q3.next()) {
        coockingPoints << q3.value("description").toString();
    }

    return RecipeEntity(recipeId, recipeName, weightedProducts, coockingPoints);
}

QVector<RecipeEntity> DatabaseModule::recipes()
{
    QVector<RecipeEntity> recipe;
    ///
    QSqlQuery q("SELECT id FROM Recipes");
    if(!q.exec()) {
        m_errorList << "Error: in " << Q_FUNC_INFO << q.lastError().text();
        return recipe;
    }
    while(q.next()) {
        auto prevErrorSize =  m_errorList.size();
        RecipeEntity c = this->recipe(q.value("id").toInt());
        auto avterErrorSize = m_errorList.size();
        if(prevErrorSize == avterErrorSize) {
            recipe.push_back(c);
        }
    }
    return recipe;
}

QVector<RecipeEntity> DatabaseModule::recipes(const QStringList &seachLine)
{
    QVector<RecipeEntity> recipes;
    foreach (QString snp, seachLine) {
        QSqlQuery q(QString(" SELECT id FROM Recipes     "
                            " WHERE name LIKE '%%1%'       "
                            ).arg(snp));
        if(!q.exec()){
            m_errorList << "Error:" << Q_FUNC_INFO << "Wrong condition" << q.lastError().text();
            return recipes;
        }

        while(q.next()) {
            auto prevErrorSize =  m_errorList.size();
            RecipeEntity c = this->recipe(q.value("id").toInt());
            auto avterErrorSize = m_errorList.size();
            if(prevErrorSize == avterErrorSize) {
                recipes.push_back(c);
            }
        }
    }
    return recipes;
}

QVector<RecipeEntity> DatabaseModule::recipes(QPair<float, float> interval, const char type)
{
    QVector<RecipeEntity> recipes;
    ///
    QString stype, prefix = " WHERE %1 BETWEEN %2 AND %3";
    switch (type) {
    case 'c': { stype = "carbohydrates"; } break;
    case 'f': { stype = "fats"; } break;
    case 'p': { stype = "proteins"; } break;
    case 'k': { stype = "kkal"; } break;
    default: {
        stype = "";
        prefix = "";
    }
    }
    qDebug()<<stype<<interval<<"SELECT id FROM Recipes"
                               "" + prefix.arg(stype).arg(interval.first).arg(interval.second);

    QSqlQuery q("SELECT id FROM Recipes"
                "" + prefix.arg(stype).arg(interval.first).arg(interval.second));
    if(!q.exec()){
        m_errorList << "Error:" << Q_FUNC_INFO << "Wrong condition" << q.lastError().text();
        return recipes;
    }
    while(q.next()) {
        auto prevErrorSize =  m_errorList.size();
        RecipeEntity c = this->recipe(q.value("id").toInt());
        auto avterErrorSize = m_errorList.size();
        if(prevErrorSize == avterErrorSize) {
            recipes.push_back(c);
        }
    }

    return recipes;
}

void DatabaseModule::changeRecipeInformation(const RecipeEntity &newRecipe)
{
    for(auto p : newRecipe.products()) qDebug() << p.product().name();
    //call this for testing to exists product
    auto prevErrorSize =  m_errorList.size();
    recipe(newRecipe.id());
    auto avterErrorSize = m_errorList.size();
    if(prevErrorSize != avterErrorSize) {
        m_errorList << "Error:" << Q_FUNC_INFO << " Error with searching Recipe for update";
        return;
    }
    //QSqlQuery q("SELECT count(*) FROM Recipes WHERE id = ");

    //update RecipesTable
    QSqlQuery updRecipesQ;
    updRecipesQ.prepare(" UPDATE Recipes "
                        " SET name = ? "
                        " WHERE id = ? ");
    updRecipesQ.addBindValue(newRecipe.name());
    updRecipesQ.addBindValue(newRecipe.id());
    if(!updRecipesQ.exec()){
        m_errorList << "Error:" << Q_FUNC_INFO << updRecipesQ.lastError().text();
        return;
    }

    //update ProductsInRecipes table
    QSqlQuery dltProdInRecQ("DELETE FROM ProductsInRecipes WHERE recipe_id = " + QString::number(newRecipe.id()));
    if(!dltProdInRecQ.exec()){
        m_errorList << "Error:" << Q_FUNC_INFO << "DELETE ProductsInRecipes ERROR" << dltProdInRecQ.lastError().text();
        return;
    }
    if(!insertIntoProductsInRecipes(newRecipe.id(), newRecipe.products())) return;

    //update CookingPoints table
    QSqlQuery dltCookingQ("DELETE FROM CookingPoints WHERE recipe_id = " + QString::number(newRecipe.id()));
    if(!dltCookingQ.exec()){
        m_errorList << "Error:" << Q_FUNC_INFO << "DELETE CookingPoints ERROR" << dltCookingQ.lastError().text();
        return;
    }
    if(!insertIntoCookingPoints(newRecipe.id(), newRecipe.cookingPoints())) return;

}

unsigned DatabaseModule::addActivity(const ActivityEntity &ae)
{
    QSqlQuery q;
    q.prepare("INSERT INTO Activities (type, kkal_m_km)"
              "VALUES( ?, ? );");
    q.addBindValue(ae.type());
    q.addBindValue(ae.kkm());
    if(!q.exec()){
        m_errorList << "Error: in " << Q_FUNC_INFO << q.lastError().text();
        return 0;
    }
    ///
    return q.lastInsertId().toUInt();
}

void DatabaseModule::deleteActivity(const ActivityEntity &activity)
{
    QSqlQuery q;
    q.prepare("DELETE FROM Activities WHERE id=?");
    q.addBindValue(activity.id());
    if(!q.exec()) {
        m_errorList << "Error: in " << Q_FUNC_INFO << q.lastError().text();
    }
}

ActivityEntity DatabaseModule::activity(unsigned id)
{
    QSqlQuery q;
    q.prepare("SELECT * FROM Activities WHERE id=?");
    q.addBindValue(id);
    if(!q.exec()){
        m_errorList << "Error: in " << Q_FUNC_INFO << q.lastError().text();
        ActivityEntity();
    }
    ///
    q.next();
    ///
    if(!q.isValid()){
        qDebug() << "Error:" << Q_FUNC_INFO
                 << "In DB has no Activity with id:" + QString::number(id);
    }
    ///
    QString type = q.value("type").toString();
    float kkm =  q.value("kkal_m_km").toFloat();

    return ActivityEntity(id, type, kkm);
}

QVector<ActivityEntity> DatabaseModule::activities()
{
    QVector<ActivityEntity> activities;
    ///
    QSqlQuery q("SELECT id FROM Activities");
    if(!q.exec()) {
        m_errorList << "Error: in " << Q_FUNC_INFO << q.lastError().text();
        return activities;
    }
    while(q.next()) {
        auto prevErrorSize =  m_errorList.size();
        ActivityEntity c = this->activity(q.value("id").toInt());
        auto avterErrorSize = m_errorList.size();
        if(prevErrorSize == avterErrorSize) {
            activities.push_back(c);
        }
    }
    return activities;
}

QVector<ActivityEntity> DatabaseModule::activities(const QStringList &seachLine)
{
    QVector<ActivityEntity> activities;
    foreach (QString snp, seachLine) {
        QSqlQuery q(QString(" SELECT id FROM Activities     "
                            " WHERE type LIKE '%1%'       "
                            ).arg(snp));
        if(!q.exec()){
            m_errorList << "Error:" << Q_FUNC_INFO << "Wrong condition" << q.lastError().text();
            return activities;
        }
        while(q.next()) {
            auto prevErrorSize =  m_errorList.size();
            ActivityEntity c = this->activity(q.value("id").toInt());
            auto avterErrorSize = m_errorList.size();
            if(prevErrorSize == avterErrorSize) {
                activities.push_back(c);
            }
        }
    }
    return activities;
}

QVector<ActivityEntity> DatabaseModule::activities(QPair<float, float> kkmInterval)
{
    QVector<ActivityEntity> activities;

    QSqlQuery q(QString("SELECT id FROM Activities "
                        "WHERE kkal_m_km BETWEEN %1 AND %2")
                .arg(kkmInterval.first)
                .arg(kkmInterval.second));
    if(!q.exec()){
        m_errorList << "Error:" << Q_FUNC_INFO << "Wrong condition" << q.lastError().text();
        return activities;
    }
    while(q.next()) {
        auto prevErrorSize =  m_errorList.size();
        ActivityEntity c = this->activity(q.value("id").toInt());
        auto avterErrorSize = m_errorList.size();
        if(prevErrorSize == avterErrorSize) {
            activities.push_back(c);
        }
    }

    return activities;
}

void DatabaseModule::changeActivityInformation(const ActivityEntity &newActivity)
{
    //call this for testing to exists product
    auto prevErrorSize =  m_errorList.size();
    activity(newActivity.id());
    auto avterErrorSize = m_errorList.size();
    if(prevErrorSize != avterErrorSize) {
        m_errorList << "Error:" << Q_FUNC_INFO << " Error with searching activity for update";
        return;
    }

    QSqlQuery q;
    q.prepare("UPDATE Activities "
              "SET type = ?, kkal_m_km = ? "
              "WHERE id = ?"
              );
    qDebug() << newActivity.type() << newActivity.kkm() << newActivity.id();
    q.addBindValue(newActivity.type());
    q.addBindValue(newActivity.kkm());
    q.addBindValue(newActivity.id());
    if(!q.exec()) {
        m_errorList << "Error:" << Q_FUNC_INFO << q.lastError().text();
        return;
    }
}

bool DatabaseModule::addExaminationAndSetID(Examination &examination)
{
    QString strValues = "client_id, is_full_examination, date";
    QString questionMSequense;

    QVector<FormField> fieldValues = examination.fields();
    foreach (const FormField& field, fieldValues) {
        strValues += ", " + field.name();
        questionMSequense += ", ?";
    }

    QSqlQuery q;
    q.prepare("INSERT INTO Examinations (" + strValues + ")"
              "VALUES( ?, ?, ?" + questionMSequense + " );");
    q.addBindValue(examination.client().id());
    q.addBindValue(examination.isFullExamination());
    q.addBindValue(examination.date().toString(Qt::ISODate));
    foreach (const FormField& field, fieldValues) {
        q.addBindValue(field.value());
    }
    if(!q.exec()) {
        qDebug() << "Error: in addExamination(...)\n\t"
                 <<  q.lastError().text();
        return false;
    }

    examination.setId(q.lastInsertId().toInt());

    return true;
}

void DatabaseModule::deleteExamination(const Examination &examination)
{
    QSqlQuery q;
    q.prepare("DELETE FROM Examinations WHERE id=?");
    q.addBindValue(examination.id());
    if(!q.exec()) {
        m_errorList << "Error: in " << Q_FUNC_INFO << q.lastError().text();
    }
}

bool DatabaseModule::addClientAndSetID(Client &client)
{
    QSqlQuery q;
    q.prepare("INSERT INTO Clients (surname, name, patronymic, birth_date, gender, age, tel_number)"
              "VALUES( ?, ?, ?, ?, ?, ?, ? );");
    q.addBindValue(client.surname());
    q.addBindValue(client.name());
    q.addBindValue(client.patronymic());
    q.addBindValue(client.birthDate().toString(Qt::ISODate));
    q.addBindValue(client.gender());
    q.addBindValue(client.age());
    q.addBindValue(client.telNumber());
    if(!q.exec()) {
        qDebug() << "Error: in addClient(...)\n\t" <<  q.lastError().text();
        return false;
    }

    client.setId(q.lastInsertId().toInt());

    return true;
}

void DatabaseModule::deleteClient(const Client &client)
{
    QSqlQuery q;
    q.prepare("DELETE FROM Clients WHERE id=?");
    q.addBindValue(client.id());
    if(!q.exec()) {
        m_errorList << "Error: in " << Q_FUNC_INFO << q.lastError().text();
    }
}

bool DatabaseModule::changeClientInformation(const Client &client)
{
    bool isFoundClient = false;
    this->client(client.id(), isFoundClient);
    if (!isFoundClient){
        return false;
    }

    QSqlQuery q;
    q.prepare("UPDATE Clients "
              "SET surname = ?, name = ?, patronymic = ?, birth_date = ?, gender = ?, age = ?, tel_number = ? "
              "WHERE id = ?"
              );
    q.addBindValue(client.surname());
    q.addBindValue(client.name());
    q.addBindValue(client.patronymic());
    q.addBindValue(client.birthDate().toString(Qt::ISODate));
    q.addBindValue(client.gender());
    q.addBindValue(client.age());
    q.addBindValue(client.telNumber());
    q.addBindValue(client.id());

    if(!q.exec()) {
        qDebug() << "Error: in changeClientInformation(...)\n\t" <<  q.lastError().text();
        return false;
    }

    return true;
}

Client DatabaseModule::client(int id, bool& isOk) const
{
    QSqlQuery q;
    q.prepare("SELECT * FROM Clients WHERE id=?");
    q.addBindValue(id);
    if(!q.exec()) {
        qDebug() << "Error: DatabaseModule::client(int, bool)";
        isOk = false;
        return Client();
    }

    q.next();

    if(!q.isValid()){
        qDebug() << "Error:" << Q_FUNC_INFO
                 << "In DB has no Client with id:" + QString::number(id);
        isOk = false;
        return Client();
    }

    QString surname = q.value("surname").toString();
    QString name = q.value("name").toString();
    QString patronymic = q.value("patronymic").toString();
    QChar gender = q.value("gender").toString().at(0);
    QDate birthDate = QDate::fromString(q.value("birth_date").toString(), Qt::ISODate);
    short age = q.value("age").toInt();
    QString telNumber = q.value("tel_number").toString();

    isOk = true;

    return Client(id, name, surname, patronymic, birthDate, gender, age, telNumber);
}

QVector<Client> DatabaseModule::clients(const QString& snp) const
{
    QStringList snpList = snp.toLower().split(QRegExp("[\\s,.]+"), QString::SkipEmptyParts);

    QVector<Client> clients;

    foreach (QString snp, snpList) {
        snp[0] = snp[0].toUpper();

        QSqlQuery q(QString(" SELECT id FROM Clients       "
                            " WHERE surname LIKE '%1%'    "
                            "    OR name LIKE '%2%'       "
                            "    OR patronymic LIKE '%3%' "
                            ).arg(snp).arg(snp).arg(snp));

        if(!q.exec()){
            qDebug() << "Error:" << Q_FUNC_INFO
                     << "Wrong condition";
            qDebug() << q.lastError().text();
            return clients;
        }

        while(q.next()) {
            bool isOk;
            Client client = this->client(q.value("id").toInt(), isOk);
            clients.push_back(client);
        }
    }

    return clients;
}

QVector<Client> DatabaseModule::clients() const
{
    QVector<Client> clients;

    QSqlQuery q("SELECT id FROM Clients");
    if(!q.exec()) {
        qDebug() << "Error: DatabaseModule::clients()";
        return clients;
    }

    while(q.next()) {
        bool isOk;
        Client c = this->client(q.value("id").toInt(), isOk);
        if(isOk) {
            clients.push_back(c);
        }
    }

    return clients;
}

Examination DatabaseModule::examination(int id, bool& isOk, Client client) const
{
    Examination examination;

    QSqlQuery q;
    q.prepare("SELECT * FROM Examinations WHERE id=?");
    q.addBindValue(id);
    if(!q.exec()) {
        qDebug() << "Error: DatabaseModule::examination(int, bool)";
        isOk = false;
        return examination;
    }
    q.next();

    if (!client.isInit()) {
        client = this->client(q.value("client_id").toInt(), isOk);
        if (!isOk) {
            qDebug() << "Error: DatabaseModule::examination(int, bool)"
                     << "'client' information doesn't found";
            return examination;
        }
    }
    examination.setClient(client);

    examination.setId(q.value("id").toInt());
    examination.setIsFullExamination(q.value("is_full_examination").toBool());
    examination.setDate(QDateTime::fromString(q.value("date").toString(), Qt::ISODate));

    foreach (FormField field, examination.fields()) {
        QString fieldValue = q.value(field.name()).toString();
        examination.setFieldValue(field.name(), fieldValue);
    }

    isOk = true;
    return examination;
}

QVector<Examination> DatabaseModule::examinations(Client client) const
{
    QVector<Examination> examinations;

    QString addQuery = client.isInit() ? "WHERE client_id=" + QString::number(client.id())
                                       : "";
    QSqlQuery q("SELECT id FROM Examinations " + addQuery);
    if(!q.exec()) {
        qDebug() << "DatabaseModule::examinations(const Client &)";
        return examinations;
    }

    while(q.next()) {
        bool isOk;
        Examination exm = this->examination(q.value("id").toInt(), isOk, client);
        if (isOk) {
            examinations.push_back(exm);
        }
    }

    return examinations;
}

QVector<Examination> DatabaseModule::examinations(QDate from, QDate to) const
{
    QDateTime fromT(from), toT(to, QTime(23, 59, 59));
    QVector<Examination> examinations;

    QSqlQuery q;
    q.prepare("SELECT id FROM Examinations WHERE date BETWEEN ? AND ?");
    q.addBindValue(fromT.toString(Qt::ISODate));
    q.addBindValue(toT.toString(Qt::ISODate));
    if(!q.exec()) {
        qDebug() << "DatabaseModule::examinations(QDate from, QDate to)";
        return examinations;
    }

    while(q.next()) {
        bool isOk;
        Examination exm = this->examination(q.value("id").toInt(), isOk);
        if (isOk) {
            examinations.push_back(exm);
        }
    }

    return examinations;
}

bool DatabaseModule::changeExaminationInformation(Examination &examination)
{
    bool isFounExaination = false;
    this->examination(examination.id(), isFounExaination, examination.client());
    if (!isFounExaination){
        return false;
    }

    QStringList queryFields; //without id, client_id, is_full_examination, date

    for (FormField field : examination.fields()) {
        queryFields << QString("%1 = '%2'")
                .arg(field.name())
                .arg(field.value());
    }
    QSqlQuery q;
    q.prepare("UPDATE Examinations "
              "SET " + queryFields.join(", ") +
              "WHERE id = ?");
    q.addBindValue(examination.id());
    if(!q.exec()) {
        qDebug() << q.lastQuery();
        qDebug() << "Error:" << Q_FUNC_INFO << q.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseModule::importDB(const QString &fileName)
{
    if (fileName.isEmpty()){
        return false;
    }

    /// Is it possible to read the file?
    _db.setDatabaseName(fileName);
    if (!_db.open()) {
        qDebug() << "Warning:" << Q_FUNC_INFO
                 << _db.lastError().text();
        /// If the new new DB file could not be seted
        /// set the previous DB file
        _db.setDatabaseName(_DB_NAME);
        return false;
    }

    if(QFile::exists(_DB_NAME)){
        if(!QFile::remove(_DB_NAME)){
            qDebug() << "Error:" << Q_FUNC_INFO
                     <<  "Old file can not be deleted";
            return false;
        }
    } else {
        qDebug() << "Warning:" << Q_FUNC_INFO
                 << "The old file is not exist";
    }

    if(!QFile::copy(fileName, _DB_NAME)){
        qDebug() << "Error:" << Q_FUNC_INFO
                 <<  "New file can not be copied";
        return false;
    }

    _db.setDatabaseName(_DB_NAME);

    //DatabaseModule();

    return true;
}

bool DatabaseModule::exportDB(const QString &fileName)
{
    if(!QFile::copy(_DB_NAME, fileName)){
        qDebug() << "Error:" << Q_FUNC_INFO
                 <<  "New file can not be copied";
        return false;
    }

    return true;
}

bool DatabaseModule::hasUnwatchedWorkError()
{
    return !m_errorList.isEmpty();
}

QStringList DatabaseModule::unwatchedWorkError()
{
    auto ret = m_errorList;
    m_errorList.clear();
    return ret;
}

void DatabaseModule::initEmptyDB()
{
    QFile file(_DB_NAME);
    QDir dir;
    dir.mkdir("./database/");
    file.open(QIODevice::ReadWrite);
    file.close();


    QSqlQuery queryCreate("CREATE DATABASE");
    queryCreate.exec();
    _db.setDatabaseName(_DB_NAME);


    if (!_db.open()) {
        qDebug() << "Error: " << Q_FUNC_INFO
                 << _db.lastError().text();
        return;
    }
    QStringList querys;

    /*
     * Clients table
    */
    querys << QString("CREATE TABLE `Clients` ("
                      "`id`           INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
                      "`surname`      TEXT NOT NULL,"
                      "`name`         TEXT NOT NULL,"
                      "`patronymic`	TEXT NOT NULL,"
                      "`birth_date`	TEXT NOT NULL,"
                      "`gender`       TEXT NOT NULL,"
                      "`age`          INTEGER NOT NULL,"
                      "`tel_number`	TEXT NOT NULL"
                      ");"
                      );
    /*
     * Examination table
    */
    QString formfieldNames;
    Examination exm;
    foreach (FormField field, exm.fields()) {
        formfieldNames += QString(" `%1` TEXT, ").arg(field.name());
    }
    querys << QString("CREATE TABLE `Examinations` ("
                      "`id`	INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
                      "`client_id`	INTEGER NOT NULL,"
                      "`is_full_examination`	INTEGER NOT NULL,"
                      "`date`	TEXT NOT NULL,"
                      + formfieldNames +
                      "FOREIGN KEY(`client_id`) REFERENCES `Clients`(`id`) ON DELETE CASCADE ON UPDATE CASCADE"
                      ");"
                      );
    /*
     * Activities table
    */
    querys << QString("CREATE TABLE `Activities` ("
                      "`id`        INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                      "`type`      TEXT NOT NULL UNIQUE,"
                      "`kkal_m_km`	REAL NOT NULL"
                      ");"
                      );
    /*
     * CookingPoints table
    */
    querys << QString("CREATE TABLE `CookingPoints` ("
                      "`recipe_id`     INTEGER NOT NULL,"
                      "`point_num`     INTEGER NOT NULL,"
                      "`description`	TEXT NOT NULL,"
                      "    FOREIGN KEY(`recipe_id`) REFERENCES `Recipes`(`id`) ON DELETE CASCADE ON UPDATE CASCADE"
                      ");"
                      );
    /*
     * Products table
    */
    querys << QString("CREATE TABLE `Products` ("
                      "`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                      "`name`	TEXT NOT NULL UNIQUE,"
                      "`proteins`	REAL NOT NULL,"
                      "`fats`	REAL NOT NULL,"
                      "`carbohydrates`	REAL NOT NULL,"
                      "`kkal`	REAL NOT NULL,"
                      "`description`	TEXT NOT NULL,"
                      "`units`	INTEGER NOT NULL"
                      ");"
                      );
    /*
     * ProductsInRecipes table
    */
    querys << QString("CREATE TABLE `ProductsInRecipes` ("
                      "`recipe_id`	INTEGER NOT NULL,"
                      "`product_id`	INTEGER NOT NULL,"
                      "`amound`	REAL NOT NULL,"
                      "FOREIGN KEY(`product_id`) REFERENCES `Products`(`id`) ON UPDATE CASCADE,"
                      "FOREIGN KEY(`recipe_id`) REFERENCES `Recipes`(`id`) ON DELETE CASCADE ON UPDATE CASCADE"
                      ");"
                      );
    /*
     * Recipes table
    */
    querys << QString("CREATE TABLE `Recipes`("
                      "`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                      "`name`	TEXT NOT NULL,"
                      "`proteins`	REAL NOT NULL,"
                      "`fats`	REAL NOT NULL,"
                      "`carbohydrates`	REAL NOT NULL,"
                      "`kcal`	REAL NOT NULL"
                      ");"
                      );
    QSqlQuery query;
    for (auto q : querys){
        if(!query.exec(q)){
            qDebug() << "Error:" << Q_FUNC_INFO
                     << "DB was not init new empty table. ";
            qDebug() << "QUERY: --------";
            qDebug() << q;
            qDebug() << "---------------";
            return;
        }
    }
}

bool DatabaseModule::insertIntoCookingPoints(unsigned recipeID, const QStringList &cookingP)
{
    for (auto i = 0; i < cookingP.size(); ++i) {
        auto pointDescription = cookingP.at(i);
        QSqlQuery q2;
        q2.prepare("INSERT INTO CookingPoints (recipe_id, point_num, description)"
                  "VALUES( ?, ?, ? );");
        q2.addBindValue(recipeID);
        q2.addBindValue(i);
        q2.addBindValue(pointDescription);

        if(!q2.exec()) {
            m_errorList << "Error: in " << Q_FUNC_INFO << "!q2!" << q2.lastError().text();
            return false;
        }
    }
    return true;
}

bool DatabaseModule::insertIntoProductsInRecipes(unsigned recipeId, const QVector<WeightedProduct> &products)
{
    for(const auto& product : products){
        QSqlQuery q3;
        q3.prepare("INSERT INTO ProductsInRecipes (recipe_id, product_id, amound)"
                   "VALUES( ?, ?, ? );");
        q3.addBindValue(recipeId);
        q3.addBindValue(product.product().id());
        q3.addBindValue(product.amound());
        if(!q3.exec()) {
            m_errorList << "Error: in " << Q_FUNC_INFO << "!q3!" << q3.lastError().text();
            return false;
        }
    }
    return true;
}
