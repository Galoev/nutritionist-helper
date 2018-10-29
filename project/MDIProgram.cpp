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
    connect(_ui.action_clientAdd,           SIGNAL(triggered()), SLOT(slotClientAdd()));
    connect(_ui.action_clientSeach,         SIGNAL(triggered()), SLOT(slotClientSeach()));
    connect(_ui.action_examinationSeach,    SIGNAL(triggered()), SLOT(slotExaminationSeach()));
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
    _formClientEdit = new ClientEdit;                       //NOTE: Сan we use the local version?
    setClientEditConnect(_formClientEdit);
    _ui.mdiArea->addSubWindow(_formClientEdit);
    _formClientEdit->show();
}

void MainWindow::slotClientSeach()
{
    _formClientSeach = new ClientSearch;                    //NOTE: Сan we use the local version?
    setClientSearchConnect(_formClientSeach);
    _ui.mdiArea->addSubWindow(_formClientSeach);
    _formClientSeach->show();
}

void MainWindow::slotExaminationSeach()
{
    _formExaminationSearch = new ExaminationSearch;         //NOTE: Сan we use the local version?
    setExaminationSearchConnect(_formExaminationSearch);
    _ui.mdiArea->addSubWindow(_formExaminationSearch);
    _formExaminationSearch->show();
}

void MainWindow::slotWindowsSort()
{
    _ui.mdiArea->cascadeSubWindows();
}

void MainWindow::slotIssueReport()
{
    QDesktopServices::openUrl(QUrl("https://github.com/ArnMips/nutritionist-helper/issues/new"));
}

void MainWindow::slotAboutProgram()
{
    QMessageBox::about(this, tr("О программе"), tr("Программа ""Помощник Диетолога"""
                                                   "\nРазработчик: Аржевитин Б.К."));
}

void MainWindow::setClientEditConnect(ClientEdit *ce)
{
    ce->setAttribute(Qt::WA_DeleteOnClose);

    connect(ce, ClientEdit::formNewClientReady, [this, ce](){
        Client client = ce->client();
        if(_database.addClientAndSetID(client)){
            if ( QMessageBox::question(this, tr("Добавление клиента")
                                       , tr("Клиент успешно добавлен\nЖелаете открыть окно Информации о клиенте?")
                                       , QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes){
                _formClientInfo = new ClientInfo();
                setClientInfoConnect(_formClientInfo);
                _formClientInfo->setInformation(client, _database.examinations(client));
                _ui.mdiArea->addSubWindow(_formClientInfo);
                _formClientInfo->show();
            }
        } else {
            QMessageBox::warning(this, tr("Добавление клиента"), tr("Клиент не был добавлен"));
        }
    });

    connect(ce, ClientEdit::formEditedClientReady, [this, ce](){
        Client client = ce->client();
        qDebug() << "ok";
        if(_database.changeClientInformation(client)){
            if ( QMessageBox::question(this, tr("Редактирование клиента")
                                       , tr("Клиент успешно отредактирован\nЖелаете открыть окно Информации о клиенте?")
                                       , QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes){
                _formClientInfo = new ClientInfo();
                setClientInfoConnect(_formClientInfo);
                _formClientInfo->setInformation(client, _database.examinations(client));
                _ui.mdiArea->addSubWindow(_formClientInfo);
                _formClientInfo->show();
            }
        } else {
            QMessageBox::warning(this, tr("Добавление клиента"), tr("Клиент не был добавлен"));
        }
    });
}

void MainWindow::setClientInfoConnect(ClientInfo *ci)
{
    ci->setAttribute(Qt::WA_DeleteOnClose);

    connect(ci, ClientInfo::newExaminationHalfButtonPressed, [this, ci](){
        _formExaminationEdit = new ExaminationEdit;             //NOTE: Сan we use the local version?
        _formExaminationEdit->setInformation(ci->client(), false);
        setExaminationEditConnect(_formExaminationEdit);
        _ui.mdiArea->addSubWindow(_formExaminationEdit);
        _formExaminationEdit->show();
    });

    connect(ci, ClientInfo::newExaminationFullButtonPressed, [this, ci](){
        _formExaminationEdit = new ExaminationEdit;             //NOTE: Сan we use the local version?
        _formExaminationEdit->setInformation(ci->client(), true);
        setExaminationEditConnect(_formExaminationEdit);
        _ui.mdiArea->addSubWindow(_formExaminationEdit);
        _formExaminationEdit->show();
    });

    connect(ci, ClientInfo::examinationSelectedForShow, [this, ci](){
        _formExaminationInfo = new ExaminationInfo;             //NOTE: Сan we use the local version?
        _formExaminationInfo->setInformation(ci->selectedExamination());
        setExaminationInfoConnect(_formExaminationInfo);
        _ui.mdiArea->addSubWindow(_formExaminationInfo);
        _formExaminationInfo->show();
    });

    connect(ci, ClientInfo::editClientButtonPressed, [this, ci](){
        _formClientEdit = new ClientEdit;                       //NOTE: Сan we use the local version?
        _formClientEdit->setInformation(ci->client());
        setClientEditConnect(_formClientEdit);
        _ui.mdiArea->addSubWindow(_formClientEdit);
        _formClientEdit->show();
    });
}

void MainWindow::setClientSearchConnect(ClientSearch *cs)
{
    cs->setAttribute(Qt::WA_DeleteOnClose);

    connect(cs, ClientSearch::seachLineReady, [this, cs](const QString& sl){
        QVector<Client> clients = _database.clients(sl);
        if(clients.isEmpty()) {
            QMessageBox::information(this, tr("Поиск клиентов"), tr("Информация не найдена"));
        }
        cs->setInformation(clients);
    });

    connect(cs, ClientSearch::selectedForShow, [this, cs](){
        QVector<Examination> examinations = _database.examinations(cs->selectedClient());
        _formClientInfo = new ClientInfo;                                //NOTE: Сan we use the local version?
        _formClientInfo->setInformation(cs->selectedClient(), examinations);
        setClientInfoConnect(_formClientInfo);
        _ui.mdiArea->addSubWindow(_formClientInfo);
        _formClientInfo->show();
    });
}

void MainWindow::setExaminationEditConnect(ExaminationEdit *ee)
{
    ee->setAttribute(Qt::WA_DeleteOnClose);

    connect(ee, ExaminationEdit::formReady, [this, ee](){
        Examination examination = ee->examination();
        _ui.mdiArea->removeSubWindow(ee);
        if(_database.addExaminationAndSetID(examination)){
            if (QMessageBox::question(this, tr("Создание исследования")
                                       , tr("Исследование успешно сохранено\nЖелаете открыть окно Информации об исследовании?")
                                       , QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes){
                _formExaminationInfo = new ExaminationInfo();
                setExaminationInfoConnect(_formExaminationInfo);
                _formExaminationInfo->setInformation(examination);
                _ui.mdiArea->addSubWindow(_formExaminationInfo);
                _formExaminationInfo->show();
            }
        } else {
            QMessageBox::warning(this, tr("Создание исследования"), tr("Исследование не было сохранено"));
        }
    });
}

void MainWindow::setExaminationInfoConnect(ExaminationInfo *ei)
{
    ei->setAttribute(Qt::WA_DeleteOnClose);

    connect(ei, ExaminationInfo::deleteExamination, [this, ei](){
        QMessageBox::information(this, "No content", "Delete examination"); //TODO: Need to add functionality!
        ei->examination();
    });

    connect(ei, ExaminationInfo::printExamination, [this, ei](bool ifFull){    
        Printer* printer = new Printer(this);
        printer->previewExamination(ei->examination(), ifFull);
    });
}

void MainWindow::setExaminationSearchConnect(ExaminationSearch *es)
{
    es->setAttribute(Qt::WA_DeleteOnClose);

    connect(es, ExaminationSearch::seachLineDateReady, [this, es](const QDate& from, const QDate& to){
        QVector<Examination> examinations = _database.examinations(from, to);
        if(examinations.isEmpty()) {
            QMessageBox::information(this, tr("Поиск исследований"), tr("Информация не найдена"));
        }
        es->setInformation(examinations);
    });

    connect(es, ExaminationSearch::seachLineClientReady, [this, es](const QString& str){       
        QVector<Examination> examinations;
        foreach (Client client, _database.clients(str)) {
            examinations.append(_database.examinations(client));
        }
        if(examinations.isEmpty()) {
            QMessageBox::information(this, tr("Поиск исследований"), tr("Информация не найдена"));
        }
        es->setInformation(examinations);        
    });

    connect(es, ExaminationSearch::selectedForShow, [this, es](){
        _formExaminationInfo = new ExaminationInfo;                 //NOTE: Сan we use the local version?
        _formExaminationInfo->setInformation(es->selectedExamination());
        setExaminationInfoConnect(_formExaminationInfo);
        _ui.mdiArea->addSubWindow(_formExaminationInfo);
        _formExaminationInfo->show();
    });
}
