#pragma once
#include "ui_MDI_program.h"
#include "windows.h"
#include "databasemodule.h"


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QMainWindow* wgt = 0);

private slots:
    void slotImport();
    void slotExport();
    void slotClientAdd();
    void slotClientSeach();
    void slotExaminationSeach();
    void slotWindowsSort();
    void slotIssueReport();
    void slotAboutProgram();

private:
    void setClientEditConnect(ClientEdit* );
    void setClientInfoConnect(ClientInfo* );
    void setClientSearchConnect(ClientSearch* );
    void setExaminationEditConnect(ExaminationEdit* );
    void setExaminationInfoConnect(ExaminationInfo* );
    void setExaminationSearchConnect(ExaminationSearch* );

    Ui::mainWindow _ui;

    ClientEdit*         _formClientEdit;
    ClientInfo*         _formClientInfo;
    ClientSearch*       _formClientSeach;
    ExaminationEdit*    _formExaminationEdit;
    ExaminationInfo*    _formExaminationInfo;
    ExaminationSearch*  _formExaminationSearch;

    DatabaseModule _database;
};
