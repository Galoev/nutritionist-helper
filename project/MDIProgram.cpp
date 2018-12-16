#include "MDIProgram.h"
#include "printer.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QMainWindow* wgt)
    :QMainWindow(wgt)
{
    _ui.setupUi(this);
    connect(_ui.action_import,              SIGNAL(triggered()), SLOT(slotImport()));
    connect(_ui.action_export,              SIGNAL(triggered()), SLOT(slotExport()));
    connect(_ui.action_examinationSeach,    SIGNAL(triggered()), SLOT(slotExaminationSeach()));
    connect(_ui.action_clientAdd,           SIGNAL(triggered()), SLOT(slotClientAdd()));
    connect(_ui.action_clientSeach,         SIGNAL(triggered()), SLOT(slotClientSeach()));
    connect(_ui.action_productAdd,          SIGNAL(triggered()), SLOT(slotProductAdd()));
    connect(_ui.action_productSearch,       SIGNAL(triggered()), SLOT(slotProductSearch()));
    connect(_ui.action_activityAdd,         SIGNAL(triggered()), SLOT(slotActivityAdd()));
    connect(_ui.action_activitySearch,      SIGNAL(triggered()), SLOT(slotActivitySearch()));
    connect(_ui.action_recipeAdd,           SIGNAL(triggered()), SLOT(slotRecipeAdd()));
    connect(_ui.action_recipeSearch,        SIGNAL(triggered()), SLOT(slotRecipeSearch()));
    connect(_ui.action_fastProtocol,        SIGNAL(triggered()), SLOT(slotFastProtocol()));
    connect(_ui.action_activityCalc,        SIGNAL(triggered()), SLOT(slotActivityCalc()));
    connect(_ui.action_windowsSort,         SIGNAL(triggered()), SLOT(slotWindowsSort()));
    connect(_ui.action_issueReport,         SIGNAL(triggered()), SLOT(slotIssueReport()));
    connect(_ui.action_aboutProgram,        SIGNAL(triggered()), SLOT(slotAboutProgram()));
    connect(_ui.action_exit,                SIGNAL(triggered()), SLOT(close()));
}

void MainWindow::slotImport()
{
    static QString title = tr("Импорт базы данных");

    QString file = QFileDialog::getOpenFileName(this
                                                , title
                                                , QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
                                                , tr("Файл базы данных (*.sqlite);;All Files (*)")
                                                );
     if (!file.isEmpty()) {
         if(_database.importDB(file)){
             QMessageBox::information(this, title, tr("База данных успешно импортирована"));
         } else {
            QMessageBox::warning(this, title, tr("Ошибка импорта базы данных"));
         }
     }
}

void MainWindow::slotExport()
{
   static QString title = tr("Экспорт базы данных");

    QString file = QFileDialog::getSaveFileName(this
                                                , tr("Экспорт файла базы данных")
                                                , QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
                                                , tr("Файл базы данных (*.sqlite);;Все файлы (*))")
                                                );
     if (!file.isEmpty()) {
         if (_database.exportDB(file)) {
             QMessageBox::information(this, title, tr("База данных успешно импортирована"));
         } else {
            QMessageBox::warning(this, title, tr("Ошибка импорта базы данных"));
         }
     }
}

void MainWindow::slotClientAdd()
{
    m_formClientEdit = new ClientEdit;                       //NOTE: Сan we use the local version?
    setClientEditConnect(m_formClientEdit);
    addSubWindowAndShow(m_formClientEdit);
}

void MainWindow::slotClientSeach()
{
    m_formClientSeach = new ClientSearch;                    //NOTE: Сan we use the local version?
    auto allClients = _database.clients();
    if(_database.hasUnwatchedWorkError()){
        QMessageBox::warning(this, "Получение списка Клиентов", "Список всех Клиентов не был получен");
        qDebug() << _database.unwatchedWorkError();
    }
    m_formClientSeach->setInformation(allClients);
    setClientSearchConnect(m_formClientSeach);
    addSubWindowAndShow(m_formClientSeach);
}

void MainWindow::slotExaminationSeach()
{
    m_formExaminationSearch = new ExaminationSearch;         //NOTE: Сan we use the local version?
    auto allExaminations = _database.examinations();
    if(_database.hasUnwatchedWorkError()){
        QMessageBox::warning(this, "Получение списка Исследований", "Список всех Исследований не был получен");
        qDebug() << _database.unwatchedWorkError();
    }
    m_formExaminationSearch->setInformation(allExaminations);

    setExaminationSearchConnect(m_formExaminationSearch);
    addSubWindowAndShow(m_formExaminationSearch);
}

void MainWindow::slotProductAdd()
{
    m_formProductEdit = new ProductEdit;
    setProductEditConnect(m_formProductEdit);
    addSubWindowAndShow(m_formProductEdit);
}

void MainWindow::slotProductSearch()
{
    m_formProductSearch = new ProductSeach;
    auto allProducts = _database.products();
    if(_database.hasUnwatchedWorkError()){
        QMessageBox::warning(this, "Получение списка Продуктов", "Список всех Продуктов не был получен");
        qDebug() << _database.unwatchedWorkError();
    }
    m_formProductSearch->setInformation(allProducts);
    setProductSeachConnect(m_formProductSearch);
    addSubWindowAndShow(m_formProductSearch);
}

void MainWindow::slotActivityAdd()
{
    m_formActivityEdit = new ActivityEdit;
    setActivityEditConnect(m_formActivityEdit);
    addSubWindowAndShow(m_formActivityEdit);
}

void MainWindow::slotActivitySearch()
{
    m_formActivitySeach = new ActivitySeach;
    auto allActivities = _database.activities();
    if(_database.hasUnwatchedWorkError()){
        QMessageBox::warning(this, "Получение списка Активностей", "Список всех Активностей не был получен");
        qDebug() << _database.unwatchedWorkError();
    }
    m_formActivitySeach->setInformation(allActivities);
    setActivitySeachConnect(m_formActivitySeach);
    addSubWindowAndShow(m_formActivitySeach);
}

void MainWindow::slotRecipeAdd()
{
    m_formRecipeEdit = new RecipeEdit;
    auto allProducts = _database.products();
    if(_database.hasUnwatchedWorkError()){
        QMessageBox::warning(this, "Получение списка Продуктов", "Список всех Продуктов для обрласти поиска не был получен");
        qDebug() << _database.unwatchedWorkError();
    }
    m_formRecipeEdit->setSearchedProducts(allProducts);
    setRecipeEditConnect(m_formRecipeEdit);
    addSubWindowAndShow(m_formRecipeEdit);
}

void MainWindow::slotRecipeSearch()
{
    m_formRecipeSeach = new RecipeSeach;
    auto allRecipes = _database.recipes();
    if(_database.hasUnwatchedWorkError()){
        QMessageBox::warning(this, "Получение списка Рецептов", "Список всех Рецептов не был получен");
        qDebug() << _database.unwatchedWorkError();
    }
    m_formRecipeSeach->setInformation(allRecipes);
    setRecipeSeachConnect(m_formRecipeSeach);
    addSubWindowAndShow(m_formRecipeSeach);
}

void MainWindow::slotActivityCalc()
{
    m_formActivityCalculation = new ActivityCalculation;
    auto allProducts = _database.products();
    if(_database.hasUnwatchedWorkError()){
        QMessageBox::warning(this, "Получение списка Продуктов", "Список всех Продуктов не был получен");
        qDebug() << _database.unwatchedWorkError();
    }
    auto allActivities = _database.activities();
    if(_database.hasUnwatchedWorkError()){
        QMessageBox::warning(this, "Получение списка Активностей", "Список всех Активностей не был получен");
        qDebug() << _database.unwatchedWorkError();
    }
    m_formActivityCalculation->setSearcingActivities(allActivities);
    m_formActivityCalculation->setSearcingProducts(allProducts);
    setActivityCalculationConnect(m_formActivityCalculation);
    addSubWindowAndShow(m_formActivityCalculation);
}

void MainWindow::slotFastProtocol()
{
    QMessageBox::warning(this, "slotFastProtocol", "slotFastProtocol");
}

void MainWindow::slotWindowsSort()
{
    _ui.mdiArea->cascadeSubWindows();
}

void MainWindow::slotIssueReport()
{
    QDesktopServices::openUrl(QUrl("https://github.com/Ilkin-Galoev/nutritionist-helper/issues/new"));
}

void MainWindow::slotAboutProgram()
{
    QString msgText = "Программа: \"Помощник Диетолога\""
                      "\nРазработчики: Аржевитин Б.К., Галоев И.Б."
                      "\nВерсия: " + QString(APP_VERSION);
    ///
    QMessageBox::about(this, "О программе", msgText);
}

void MainWindow::setClientEditConnect(ClientEdit *ce)
{
    //ce->setAttribute(Qt::WA_DeleteOnClose);

    connect(ce, &ClientEdit::formNewClientReady, [this, ce](){
        Client client = ce->client();
        if(_database.addClientAndSetID(client)){
            if ( QMessageBox::question(this, tr("Добавление клиента")
                                       , tr("Клиент успешно добавлен\nЖелаете открыть окно Информации о клиенте?")
                                       , QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes){
                m_formClientInfo = new ClientInfo();
                setClientInfoConnect(m_formClientInfo);
                m_formClientInfo->setInformation(client, _database.examinations(client));
                _ui.mdiArea->addSubWindow(m_formClientInfo);
                m_formClientInfo->show();
            }
        } else {
            QMessageBox::warning(this, tr("Добавление клиента"), tr("Клиент не был добавлен"));
        }
        ce->parent()->deleteLater();
    });

    connect(ce, &ClientEdit::formEditedClientReady, [this, ce](){
        Client client = ce->client();
        qDebug() << "ok";
        if(_database.changeClientInformation(client)){
//            if (m_formClientSeach){
//                m_formClientSeach->updateInformationIfExist(client);
//            }
            if ( QMessageBox::question(this, tr("Редактирование клиента")
                                       , tr("Клиент успешно отредактирован\nЖелаете открыть окно Информация о клиенте?")
                                       , QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes){
                m_formClientInfo = new ClientInfo();
                setClientInfoConnect(m_formClientInfo);
                m_formClientInfo->setInformation(client, _database.examinations(client));
                _ui.mdiArea->addSubWindow(m_formClientInfo);
                m_formClientInfo->show();
            } 
        } else {
            QMessageBox::warning(this, tr("Редактирование клиента"), tr("Клиент не был обновлен"));
        }
        ce->parent()->deleteLater();
    });
}

void MainWindow::setClientInfoConnect(ClientInfo *ci)
{
    ci->setAttribute(Qt::WA_DeleteOnClose);

    connect(ci, &ClientInfo::newExaminationHalfButtonPressed, [this, ci](){
        m_formExaminationEdit = new ExaminationEdit;             //NOTE: Сan we use the local version?
        m_formExaminationEdit->setInformation(ci->client(), false);
        setExaminationEditConnect(m_formExaminationEdit);
        _ui.mdiArea->addSubWindow(m_formExaminationEdit);
        m_formExaminationEdit->show();
        ci->parent()->deleteLater();
    });

    connect(ci, &ClientInfo::newExaminationFullButtonPressed, [this, ci](){
        m_formExaminationEdit = new ExaminationEdit;             //NOTE: Сan we use the local version?
        m_formExaminationEdit->setInformation(ci->client(), true);
        setExaminationEditConnect(m_formExaminationEdit);
        _ui.mdiArea->addSubWindow(m_formExaminationEdit);
        m_formExaminationEdit->show();
        ci->parent()->deleteLater();
    });

    connect(ci, &ClientInfo::examinationSelectedForShow, [this, ci](){
        m_formExaminationInfo = new ExaminationInfo;             //NOTE: Сan we use the local version?
        m_formExaminationInfo->setInformation(ci->selectedExamination());
        setExaminationInfoConnect(m_formExaminationInfo);
        _ui.mdiArea->addSubWindow(m_formExaminationInfo);
        m_formExaminationInfo->show();
        ci->parent()->deleteLater();
    });

    connect(ci, &ClientInfo::editClientButtonPressed, [this, ci](){
        ci->parent()->deleteLater();
        m_formClientEdit = new ClientEdit;                       //NOTE: Сan we use the local version?
        m_formClientEdit->setInformation(ci->client());
        setClientEditConnect(m_formClientEdit);
        _ui.mdiArea->addSubWindow(m_formClientEdit);
        m_formClientEdit->show();
    });

    connect(ci, &ClientInfo::deleteClientButtonPressed, [this, ci](){
        if ( QMessageBox::question(this, "Удаление клиента"
                                   , "Вы уверены, что хотите удалить всю информацию о Клиенте?"
                                   , QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {

            _database.deleteClient(ci->client());
            if(_database.hasUnwatchedWorkError()){
                QMessageBox::warning(this, "Удаление клиента", "Ошибка удаления информации о клиенте");
                qDebug() << _database.unwatchedWorkError();
            } else {
                auto client = ci->client();
                ci->parent()->deleteLater();
                QMessageBox::information(this, "Удаление клиента", "Вся информация о Клиенте была удалена");
//                if (m_formClientSeach){
//                    m_formClientSeach->hideInformationIfExists(client);
//                }
            }
        }
    });
}

void MainWindow::setClientSearchConnect(ClientSearch *cs)
{
    //cs->setAttribute(Qt::WA_DeleteOnClose);

    connect(cs, &ClientSearch::seachLineReady, [this, cs](const QString& sl){
        QVector<Client> clients = _database.clients(sl);
        if(clients.isEmpty()) {
            QMessageBox::information(this, tr("Поиск клиентов"), tr("Информация не найдена"));
        }
        cs->setInformation(clients);
    });

    connect(cs, &ClientSearch::selectedForShow, [this, cs](){
        QVector<Examination> examinations = _database.examinations(cs->selectedClient());
        m_formClientInfo = new ClientInfo;                                //NOTE: Сan we use the local version?
        m_formClientInfo->setInformation(cs->selectedClient(), examinations);
        setClientInfoConnect(m_formClientInfo);
        _ui.mdiArea->addSubWindow(m_formClientInfo);
        m_formClientInfo->show();
    });

    connect(cs, &ClientSearch::requireUpdateAllInform, [this, cs](){
        auto allClients = _database.clients();
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Получение списка Клиентов", "Список всех Клиентов не был получен");
            qDebug() << _database.unwatchedWorkError();
        }
        cs->setInformation(allClients);
    });
}

void MainWindow::setExaminationEditConnect(ExaminationEdit *ee)
{
    //ee->setAttribute(Qt::WA_DeleteOnClose);

    connect(ee, &ExaminationEdit::formReady, [this, ee](){
        Examination examination = ee->examination();
        //_ui.mdiArea->removeSubWindow(ee);
        if(_database.addExaminationAndSetID(examination)){
            if (QMessageBox::question(this, tr("Создание исследования")
                                       , tr("Исследование успешно сохранено\nЖелаете открыть окно Информация об исследовании?")
                                       , QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes){
                m_formExaminationInfo = new ExaminationInfo();
                setExaminationInfoConnect(m_formExaminationInfo);
                m_formExaminationInfo->setInformation(examination);
                _ui.mdiArea->addSubWindow(m_formExaminationInfo);
                m_formExaminationInfo->show();
            }
        } else {
            QMessageBox::warning(this, tr("Создание исследования"), tr("Исследование не было сохранено"));
        }
        ee->parent()->deleteLater();
    });
}

void MainWindow::setExaminationInfoConnect(ExaminationInfo *ei)
{
    ei->setAttribute(Qt::WA_DeleteOnClose);

    connect(ei, &ExaminationInfo::deleteExamination, [this, ei](){
        if ( QMessageBox::question(this, "Удаление Иследования"
                                   , "Вы уверены, что хотите удалить Исследование?"
                                   , QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {

            _database.deleteExamination(ei->examination());
            if(_database.hasUnwatchedWorkError()){
                QMessageBox::warning(this, "Удаление Иследования", "Ошибка удаления Исследования");
                qDebug() << _database.unwatchedWorkError();
            } else {
                auto examination = ei->examination();
                ei->parent()->deleteLater();
                QMessageBox::information(this, "Удаление Иследования", "Исследование успешно удалено");
//                if(m_formExaminationSearch){
//                    m_formExaminationSearch->hideInformationIfExists(examination);
//                }
            }
        }
    });

    connect(ei, &ExaminationInfo::printExamination, [this, ei](bool ifFull){
        Printer* printer = new Printer(this);
        printer->previewExamination(ei->examination(), ifFull);
    });
}

void MainWindow::setExaminationSearchConnect(ExaminationSearch *es)
{
    es->setAttribute(Qt::WA_DeleteOnClose);

    connect(es, &ExaminationSearch::seachLineDateReady, [this, es](const QDate& from, const QDate& to){
        QVector<Examination> examinations = _database.examinations(from, to);
        if(examinations.isEmpty()) {
            QMessageBox::information(this, tr("Поиск исследований"), tr("Информация не найдена"));
        }
        es->setInformation(examinations);
    });

    connect(es, &ExaminationSearch::seachLineClientReady, [this, es](const QString& str){
        QVector<Examination> examinations;
        foreach (Client client, _database.clients(str)) {
            examinations.append(_database.examinations(client));
        }
        if(examinations.isEmpty()) {
            QMessageBox::information(this, tr("Поиск исследований"), tr("Информация не найдена"));
        }
        es->setInformation(examinations);
    });

    connect(es, &ExaminationSearch::selectedForShow, [this, es](){
        m_formExaminationInfo = new ExaminationInfo;                 //NOTE: Сan we use the local version?
        m_formExaminationInfo->setInformation(es->selectedExamination());
        setExaminationInfoConnect(m_formExaminationInfo);
        _ui.mdiArea->addSubWindow(m_formExaminationInfo);
        m_formExaminationInfo->show();
    });

    connect(es, &ExaminationSearch::requireUpdateAllInform, [this, es](){
        auto allExaminations = _database.examinations();
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Получение списка Исследований", "Список всех Исследований не был получен");
            qDebug() << _database.unwatchedWorkError();
        }
        es->setInformation(allExaminations);

    });
}

void MainWindow::setProductEditConnect(ProductEdit *p)
{
    //p->setAttribute(Qt::WA_DeleteOnClose);

    connect(p, &ProductEdit::formNewProductReady, [this, p](){
        auto newProduct = m_formProductEdit->product();

        auto id = _database.addProduct(newProduct);
        if(!_database.hasUnwatchedWorkError()){
            auto ret = QMessageBox::question(this, "Добавление продукта"
                                             ,"Продукт успешно добавлен\nЖелаете открыть окно Информация о продукте?"
                                             , QMessageBox::Yes, QMessageBox::No);
            if (ret == QMessageBox::Yes){
                newProduct.setId(id);
                m_formProductInfo = new ProductInfo;
                this->setProductInfoConnect(m_formProductInfo);
                m_formProductInfo->setInformation(newProduct);
                this->addSubWindowAndShow(m_formProductInfo);
            }
        } else {
            QMessageBox::warning(this, "Добавление продукта", "Продукт не был добавлен");
            qDebug() << _database.unwatchedWorkError();
        }
        p->parent()->deleteLater();
    });
    connect(p, &ProductEdit::formEditedProductReady, [this, p](){
        auto editedProduct = m_formProductEdit->product();

        _database.changeProductInformation(editedProduct);
        if(!_database.hasUnwatchedWorkError()){
//            if (m_formProductSearch){
//                m_formProductSearch->hideInformationIfExists(editedProduct);
//            }
            auto ret = QMessageBox::question(this, "Редактирование продукта"
                                             ,"Информация о продукте успешно обновлена\nЖелаете открыть окно Информация о продукте?"
                                             , QMessageBox::Yes, QMessageBox::No);
            if (ret == QMessageBox::Yes){
                m_formProductInfo = new ProductInfo;
                this->setProductInfoConnect(m_formProductInfo);
                m_formProductInfo->setInformation(editedProduct);
                this->addSubWindowAndShow(m_formProductInfo);
            }
        } else {
            QMessageBox::warning(this, "Редактирование продукта", "Продукт не был обновлен");
            qDebug() << _database.unwatchedWorkError();
        }
        p->parent()->deleteLater();
    });
}

void MainWindow::setProductInfoConnect(ProductInfo *p)
{
    //p->setAttribute(Qt::WA_DeleteOnClose);
    connect(p, &ProductInfo::editProductButtonPressed, [this, p](){
        m_formProductEdit = new ProductEdit;
        m_formProductEdit->setInformation(p->product());
        this->setProductEditConnect(m_formProductEdit);
        this->addSubWindowAndShow(m_formProductEdit);
        p->parent()->deleteLater();
    });

    connect(p, &ProductInfo::deleteProductButtonPressed, [this, p](){
        if ( QMessageBox::question(this, "Удаление Продукта"
                                   , "Вы уверены, что хотите удалить Продукт?"
                                   , QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {

            _database.deleteProduct(p->product());
            if(_database.hasUnwatchedWorkError()){
                QMessageBox::warning(this, "Удаление Продукта", "Ошибка удаления Продукта");
                qDebug() << _database.unwatchedWorkError();
            } else {
                auto product = p->product();
                p->parent()->deleteLater();
                QMessageBox::information(this, "Удаление Продукта", "Продукт успешно удален");
//                if (m_formProductSearch){
//                    m_formProductSearch->hideInformationIfExists(product);
//                }
            }
        }
    });
}

void MainWindow::setProductSeachConnect(ProductSeach *p)
{
    //p->setAttribute(Qt::WA_DeleteOnClose);

    connect(p, &ProductSeach::seachLineProductReady, [this, p](const QString& s){
        auto products = _database.products(s.split(' '));
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Поиск продуктов", "Продукты с указанным названием не были получены из базы данных");
            qDebug() << _database.unwatchedWorkError();
        } else if (products.isEmpty()){
            QMessageBox::information(this, "Поиск продуктов", "Продукты с указанным названием не были найдены");
        }
        p->setInformation(products);
    });
    connect(p, &ProductSeach::seachLineProteinReady, [this, p](const int from, const int to){
        auto products = _database.products(QPair<float,float>(from, to),'p');
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Поиск продуктов", "Продукты для заданного диапазона белков не были получены из базы данных");
            qDebug() << _database.unwatchedWorkError();
        } else if (products.isEmpty()){
            QMessageBox::information(this, "Поиск продуктов", "Продукты для заданного диапазона белков не были найдены");
        }
        p->setInformation(products);
    });
    connect(p, &ProductSeach::seachLineFatsReady, [this, p](const int from, const int to){
        auto products = _database.products(QPair<float,float>(from, to),'f');
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Поиск продуктов", "Продукты для заданного диапазона жиров не были получены из базы данных");
            qDebug() << _database.unwatchedWorkError();
        } else if (products.isEmpty()){
            QMessageBox::information(this, "Поиск продуктов", "Продукты для заданного диапазона жиров не были найдены");
        }
        p->setInformation(products);
    });
    connect(p, &ProductSeach::seachLineCarbohydratesReady, [this, p](const int from, const int to){
        auto products = _database.products(QPair<float,float>(from, to),'c');
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Поиск продуктов", "Продукты для заданного диапазона углеводов не были получены из базы данных");
            qDebug() << _database.unwatchedWorkError();
        } else if (products.isEmpty()){
            QMessageBox::information(this, "Поиск продуктов", "Продукты для заданного диапазона углеводов не были найдены");
        }
        p->setInformation(products);
    });
    connect(p, &ProductSeach::selectedForShow, [this, p](){
        auto selectedProduct = p->selectedProduct();
        m_formProductInfo = new ProductInfo;
        m_formProductInfo->setInformation(selectedProduct);
        this->setProductInfoConnect(m_formProductInfo);
        this->addSubWindowAndShow(m_formProductInfo);
    });

    connect(p, &ProductSeach::requireUpdateAllInform, [this, p](){
        auto allProducts = _database.products();
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Получение списка Продуктов", "Список всех Продуктов не был получен");
            qDebug() << _database.unwatchedWorkError();
        }
        p->setInformation(allProducts);
    });
}

void MainWindow::setActivityEditConnect(ActivityEdit *p)
{
    //p->setAttribute(Qt::WA_DeleteOnClose);

    connect(p, &ActivityEdit::formNewActivityReady, [this, p](){
        auto newActivity = p->activity();
        auto id = _database.addActivity(newActivity);
        if(!_database.hasUnwatchedWorkError()){
//            if(m_formActivitySeach){
//                m_formActivitySeach->updateInformationIfExist(newActivity);
//            }
            auto ret = QMessageBox::question(this, "Добавление вида активности"
                                             ,"Вид двигательной активности был успешно добавлен\nЖелаете открыть окно Информация об активности?"
                                             , QMessageBox::Yes, QMessageBox::No);
            if (ret == QMessageBox::Yes){
                newActivity.setId(id);
                m_formActivityInfo = new ActivityInfo;
                this->setActivityInfoConnect(m_formActivityInfo);
                m_formActivityInfo->setInformation(newActivity);
                this->addSubWindowAndShow(m_formActivityInfo);
            }
        } else {
            QMessageBox::warning(this, "Добавление вида активности", "Новый вид двигательной активности не был добавлен");
            qDebug() << _database.unwatchedWorkError();
        }
        p->parent()->deleteLater();
    });
    connect(p, &ActivityEdit::formEditedActivityReady, [this, p](){
        auto editiedActivity = p->activity();
        _database.changeActivityInformation(editiedActivity);
        if(!_database.hasUnwatchedWorkError()){
//            if(m_formActivitySeach){
//                m_formActivitySeach->updateInformationIfExist(editiedActivity);
//            }
            auto ret = QMessageBox::question(this, "Редактирование вида активности"
                                             ,"Информация о двигательной активности была успешно обновлена\nЖелаете открыть окно Информация об активности?"
                                             , QMessageBox::Yes, QMessageBox::No);
            if (ret == QMessageBox::Yes){
                m_formActivityInfo = new ActivityInfo;
                this->setActivityInfoConnect(m_formActivityInfo);
                m_formActivityInfo->setInformation(editiedActivity);
                this->addSubWindowAndShow(m_formActivityInfo);
            }
        } else {
            QMessageBox::warning(this, "Редактирование вида активности", "Информация о виде двигательной активности не была обновлена");
            qDebug() << _database.unwatchedWorkError();
        }
        p->parent()->deleteLater();
    });
}

void MainWindow::setActivityInfoConnect(ActivityInfo *p)
{
    //p->setAttribute(Qt::WA_DeleteOnClose);
    connect(p, &ActivityInfo::editActivityButtonPressed, [this, p](){
        m_formActivityEdit = new ActivityEdit;
        m_formActivityEdit->setInformation(p->activity());
        this->setActivityEditConnect(m_formActivityEdit);
        this->addSubWindowAndShow(m_formActivityEdit);
        p->parent()->deleteLater();
    });

    connect(p, &ActivityInfo::deleteActivityButtonPressed, [this, p](){
        if ( QMessageBox::question(this, "Удаление Активности"
                                   , "Вы уверены, что хотите удалить Активность?"
                                   , QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {

            _database.deleteActivity(p->activity());
            if(_database.hasUnwatchedWorkError()){
                QMessageBox::warning(this, "Удаление Активности", "Ошибка удаления Активности");
                qDebug() << _database.unwatchedWorkError();
            } else {
                auto activity = p->activity();
//                if(m_formActivitySeach){
//                    m_formActivitySeach->hideInformationIfExists(activity);
//                }
                p->parent()->deleteLater();
                QMessageBox::information(this, "Удаление Активности", "Активность успешно удалена");
            }
        }
    });
}

void MainWindow::setActivitySeachConnect(ActivitySeach *p)
{
    //p->setAttribute(Qt::WA_DeleteOnClose);

    connect(p, &ActivitySeach::seachLineActivityReady, [this, p](const QString& s){
        auto activities = _database.activities(s.split(' '));
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Поиск информации об активности", "Виды двигательной активности по указанному запросу не были получены из базы данных");
            qDebug() << _database.unwatchedWorkError();
        } else if (activities.isEmpty()){
            QMessageBox::information(this, "Поиск информации об активности", "Виды двигательной активности по указанному запросу не были найдены");
        }
        p->setInformation(activities);
    });
    connect(p, &ActivitySeach::seachLineKcalReady, [this, p](const int from, const int to){
        auto products = _database.activities(QPair<float, float>(from, to));
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Поиск информации об активности", "Виды двигательной активности для заданного интервала не были получены из базы данных");
            qDebug() << _database.unwatchedWorkError();
        } else if (products.isEmpty()){
            QMessageBox::information(this, "Поиск информации об активности", "Виды двигательной активности для заданного интервала не были найдены");
        }
        p->setInformation(products);
    });
    connect(p, &ActivitySeach::selectedForShow, [this, p](){
        auto selectedActivity = p->selectedActivity();
        m_formActivityInfo = new ActivityInfo;
        m_formActivityInfo->setInformation(selectedActivity);
        this->setActivityInfoConnect(m_formActivityInfo);
        this->addSubWindowAndShow(m_formActivityInfo);
    });

    connect(p, &ActivitySeach::requireUpdateAllInform, [this, p](){
        auto allActivities = _database.activities();
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Получение списка Активностей", "Список всех Активностей не был получен");
            qDebug() << _database.unwatchedWorkError();
        }
        p->setInformation(allActivities);
    });
}

void MainWindow::setRecipeEditConnect(RecipeEdit *p)
{
    //p->setAttribute(Qt::WA_DeleteOnClose, true);

    connect(p, &RecipeEdit::formNewRecipeReady, [this, p](){
        auto newRecipe = p->recipe();
        auto id = _database.addRecipe(newRecipe);
        if(!_database.hasUnwatchedWorkError()){
            auto ret = QMessageBox::question(this, "Добавление рецепта"
                                             ,"Новый рецепт был успешно добавлен\nЖелаете открыть окно Информация о рецепте?"
                                             , QMessageBox::Yes, QMessageBox::No);
            if (ret == QMessageBox::Yes){
                newRecipe.setId(id);
                m_formRecipeInfo = new RecipeInfo;
                newRecipe.setId(id);
                this->setRecipeInfoConnect(m_formRecipeInfo);
                m_formRecipeInfo->setInformation(newRecipe);
                this->addSubWindowAndShow(m_formRecipeInfo);
            }
        } else {
            QMessageBox::warning(this, "Добавление рецепта", "Новый рецепт не был добавлен");
            qDebug() << _database.unwatchedWorkError();
        }
        p->parent()->deleteLater();
    });
    connect(p, &RecipeEdit::formEditedRecipeReady, [this, p](){
        auto editiedRecipe = p->recipe();
        _database.changeRecipeInformation(editiedRecipe);
        if(!_database.hasUnwatchedWorkError()){
//            if(m_formRecipeSeach){
//                m_formRecipeSeach->hideInformationIfExists(editiedRecipe);
//            }
            auto ret = QMessageBox::question(this, "Редактирование рецепта"
                                             ,"Информация по рецепту была успешно обновлена\nЖелаете открыть окно Информация о рецепте?"
                                             , QMessageBox::Yes, QMessageBox::No);
            if (ret == QMessageBox::Yes){
                m_formRecipeInfo = new RecipeInfo;
                m_formRecipeInfo->setInformation(editiedRecipe);
                this->setRecipeInfoConnect(m_formRecipeInfo);
                this->addSubWindowAndShow(m_formRecipeInfo);
            }
        } else {
            QMessageBox::warning(this, "Редактирование рецепта", "Информация по рецепту не была обновлена");
            qDebug() << _database.unwatchedWorkError();
        }
        p->parent()->deleteLater();
    });

    connect(p, &RecipeEdit::productSearchLineReady, [this, p](const QString& s){
        auto products = _database.products(s.split(' '));
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Поиск продуктов", "Продукты с указанным названием не были получены из базы данных");
            qDebug() << _database.unwatchedWorkError();
        } else if (products.isEmpty()){
            QMessageBox::information(this, "Поиск продуктов", "Продукты с указанным названием не были найдены");
        }
        p->setSearchedProducts(products);
    });
    connect(p, &RecipeEdit::productSearchProteinReady, [this, p](const int from, const int to){
        auto products = _database.products(QPair<float,float>(from, to),'p');
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Поиск продуктов", "Продукты для заданного диапазона белков не были получены из базы данных");
            qDebug() << _database.unwatchedWorkError();
        } else if (products.isEmpty()){
            QMessageBox::information(this, "Поиск продуктов", "Продукты для заданного диапазона белков не были найдены");
        }
        p->setSearchedProducts(products);
    });
    connect(p, &RecipeEdit::productSearchFatsReady, [this, p](const int from, const int to){
        auto products = _database.products(QPair<float,float>(from, to),'f');
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Поиск продуктов", "Продукты для заданного диапазона жиров не были получены из базы данных");
            qDebug() << _database.unwatchedWorkError();
        } else if (products.isEmpty()){
            QMessageBox::information(this, "Поиск продуктов", "Продукты для заданного диапазона жиров не были найдены");
        }
        p->setSearchedProducts(products);
    });
    connect(p, &RecipeEdit::productSearchCarbohydratesReady, [this, p](const int from, const int to){
        auto products = _database.products(QPair<float,float>(from, to),'c');
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Поиск продуктов", "Продукты для заданного диапазона углеводов не были получены из базы данных");
            qDebug() << _database.unwatchedWorkError();
        } else if (products.isEmpty()){
            QMessageBox::information(this, "Поиск продуктов", "Продукты для заданного диапазона углеводов не были найдены");
        }
        p->setSearchedProducts(products);
    });
    connect(p, &RecipeEdit::productSelectedForShow, [this, p](){
        //QMessageBox::critical(this, "NOT IMPLEMENTED", "---");
//        auto selectedProduct = p->selectedProduct();
//        m_formProductInfo = new ProductInfo;
//        m_formProductInfo->setInformation(selectedProduct);
//        this->setProductInfoConnect(m_formProductInfo);
//        this->addSubWindowAndShow(m_formProductInfo);
    });
    connect(p, &RecipeEdit::productRequireUpdateAllInform, [this, p](){
        auto allProducts = _database.products();
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Получение списка Продуктов", "Список всех Продуктов не был получен");
            qDebug() << _database.unwatchedWorkError();
        }
        p->setSearchedProducts(allProducts);
    });
}

void MainWindow::setRecipeInfoConnect(RecipeInfo *p)
{
    //p->setAttribute(Qt::WA_DeleteOnClose);
    connect(p, &RecipeInfo::editRecipeButtonPressed, [this, p](){
        auto editiedRecipe = _database.recipe(p->recipe().id());
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::critical(this, "Редактирование рецепта", "Рецепт не может быть отредактирован, так как он отсутствует в базе данных");
            qDebug() << _database.unwatchedWorkError();
        }
        m_formRecipeEdit = new RecipeEdit(this);
        m_formRecipeEdit->setInformation(editiedRecipe);
        this->setRecipeEditConnect(m_formRecipeEdit);
        this->addSubWindowAndShow(m_formRecipeEdit);
        p->parent()->deleteLater();
    });


    connect(p, &RecipeInfo::deleteRecipeButtonPressed, [this, p](){
        if ( QMessageBox::question(this, "Удаление Рецепта"
                                   , "Вы уверены, что хотите удалить Рецепт?"
                                   , QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {

            _database.deleteRecipe(p->recipe());
            if(_database.hasUnwatchedWorkError()){
                QMessageBox::warning(this, "Удаление Рецепта", "Ошибка удаления Рецепта");
                qDebug() << _database.unwatchedWorkError();
            } else {
                auto recipe = p->recipe();
                p->parent()->deleteLater();
                QMessageBox::information(this, "Удаление Рецепта", "Рецепт успешно удалена");
//                if(m_formRecipeSeach){
//                    m_formRecipeSeach->hideInformationIfExists(recipe);
//                }
            }
        }
    });
}

void MainWindow::setRecipeSeachConnect(RecipeSeach *p)
{
    //p->setAttribute(Qt::WA_DeleteOnClose);

    connect(p, &RecipeSeach::seachLineRecipeReady, [this, p](const QString& s){
        auto recipe = _database.recipes(s.split(' '));
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Поиск рецепта", "Рецепты по заданному запросу не были получены из базы данных");
            qDebug() << _database.unwatchedWorkError();
        } else if (recipe.isEmpty()){
            QMessageBox::information(this, "Поиск рецепта", "Рецепты по заданному запросу не были найдены");
        }
        p->setInformation(recipe);
    });
    connect(p, &RecipeSeach::seachLineProteinReady, [this, p](const int from, const int to){
        auto recipe = _database.recipes(QPair<float,float>(from, to),'p');
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Поиск рецепта", "Рецепты для указанного диапазона белков не были получены из базы данных");
            qDebug() << _database.unwatchedWorkError();
        } else if (recipe.isEmpty()){
            QMessageBox::information(this, "Поиск рецепта", "Рецепты для указанного диапазона белков не были найдены");
        }
        p->setInformation(recipe);
    });
    connect(p, &RecipeSeach::seachLineFatsReady, [this, p](const int from, const int to){
        auto recipe = _database.recipes(QPair<float,float>(from, to),'f');
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Поиск рецепта", "Рецепты для указанного диапазона жиров не были получены из базы данных");
            qDebug() << _database.unwatchedWorkError();
        } else if (recipe.isEmpty()){
            QMessageBox::information(this, "Поиск рецепта", "Рецепты для указанного диапазона жиров не были найдены");
        }
        p->setInformation(recipe);
    });
    connect(p, &RecipeSeach::seachLineCarbohydratesReady, [this, p](const int from, const int to){
        auto recipe = _database.recipes(QPair<float,float>(from, to),'c');
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Поиск рецепта", "Рецепты для указанного диапазона углеводов не были получены из базы данных");
            qDebug() << _database.unwatchedWorkError();
        } else if (recipe.isEmpty()){
            QMessageBox::information(this, "Поиск рецепта", "Рецепты для указанного диапазона углеводов не были найдены");
        }
        p->setInformation(recipe);
    });
    connect(p, &RecipeSeach::selectedForShow, [this, p](){
        auto selectedRecipe = p->selectedRecipe();
        m_formRecipeInfo = new RecipeInfo;
        m_formRecipeInfo->setInformation(selectedRecipe);
        this->setRecipeInfoConnect(m_formRecipeInfo);
        this->addSubWindowAndShow(m_formRecipeInfo);
    });

    connect(p, &RecipeSeach::requireUpdateAllInform, [this, p](){
        auto allRecipes = _database.recipes();
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Получение списка Рецептов", "Список всех Рецептов не был получен");
            qDebug() << _database.unwatchedWorkError();
        }
        p->setInformation(allRecipes);
    });
}

void MainWindow::setActivityCalculationConnect(ActivityCalculation *p)
{
    connect(p, &ActivityCalculation::productSearchLineReady, [this, p](const QString& s){
        auto products = _database.products(s.split(' '));
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Поиск продуктов", "Продукты с указанным названием не были получены из базы данных");
            qDebug() << _database.unwatchedWorkError();
        } else if (products.isEmpty()){
            QMessageBox::information(this, "Поиск продуктов", "Продукты с указанным названием не были найдены");
        }
        p->setSearcingProducts(products);
    });
    connect(p, &ActivityCalculation::productSearchProteinReady, [this, p](const int from, const int to){
        auto products = _database.products(QPair<float,float>(from, to),'p');
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Поиск продуктов", "Продукты для заданного диапазона белков не были получены из базы данных");
            qDebug() << _database.unwatchedWorkError();
        } else if (products.isEmpty()){
            QMessageBox::information(this, "Поиск продуктов", "Продукты для заданного диапазона белков не были найдены");
        }
        p->setSearcingProducts(products);
    });
    connect(p, &ActivityCalculation::productSearchFatsReady, [this, p](const int from, const int to){
        auto products = _database.products(QPair<float,float>(from, to),'f');
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Поиск продуктов", "Продукты для заданного диапазона жиров не были получены из базы данных");
            qDebug() << _database.unwatchedWorkError();
        } else if (products.isEmpty()){
            QMessageBox::information(this, "Поиск продуктов", "Продукты для заданного диапазона жиров не были найдены");
        }
        p->setSearcingProducts(products);
    });
    connect(p, &ActivityCalculation::productSearchCarbohydratesReady, [this, p](const int from, const int to){
        auto products = _database.products(QPair<float,float>(from, to),'c');
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Поиск продуктов", "Продукты для заданного диапазона углеводов не были получены из базы данных");
            qDebug() << _database.unwatchedWorkError();
        } else if (products.isEmpty()){
            QMessageBox::information(this, "Поиск продуктов", "Продукты для заданного диапазона углеводов не были найдены");
        }
        p->setSearcingProducts(products);
    });
    connect(p, &ActivityCalculation::productRequireUpdateAllInform, [this, p](){
        auto allProducts = _database.products();
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Получение списка Продуктов", "Список всех Продуктов не был получен");
            qDebug() << _database.unwatchedWorkError();
        }
        p->setSearcingProducts(allProducts);
    });

    connect(p, &ActivityCalculation::activitySeachLineActivityReady, [this, p](const QString& s){
        auto activities = _database.activities(s.split(' '));
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Поиск информации об активности", "Виды двигательной активности по указанному запросу не были получены из базы данных");
            qDebug() << _database.unwatchedWorkError();
        } else if (activities.isEmpty()){
            QMessageBox::information(this, "Поиск информации об активности", "Виды двигательной активности по указанному запросу не были найдены");
        }
        p->setSearcingActivities(activities);
    });
    connect(p, &ActivityCalculation::activitySeachLineKcalReady, [this, p](const int from, const int to){
        auto activities = _database.activities(QPair<float, float>(from, to));
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Поиск информации об активности", "Виды двигательной активности для заданного интервала не были получены из базы данных");
            qDebug() << _database.unwatchedWorkError();
        } else if (activities.isEmpty()){
            QMessageBox::information(this, "Поиск информации об активности", "Виды двигательной активности для заданного интервала не были найдены");
        }
        p->setSearcingActivities(activities);
    });
    connect(p, &ActivityCalculation::activityRequireUpdateAllInform, [this, p](){
        auto allActivities = _database.activities();
        if(_database.hasUnwatchedWorkError()){
            QMessageBox::warning(this, "Получение списка Активностей", "Список всех Активностей не был получен");
            qDebug() << _database.unwatchedWorkError();
        }
        p->setSearcingActivities(allActivities);
    });
}

void MainWindow::addSubWindowAndShow(QWidget *widget)
{
    _ui.mdiArea->addSubWindow(widget);
    widget->show();
}
