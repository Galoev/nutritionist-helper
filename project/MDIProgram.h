#pragma once
#include "ui_MDI_program.h"
#include "windows.h"
#include "databasemodule.h"


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QMainWindow* wgt = nullptr);

private slots:
    void slotImport();
    void slotExport();
    void slotClientAdd();
    void slotClientSeach();
    void slotExaminationSeach();
    void slotProductAdd();
    void slotProductSearch();
    void slotActivityAdd();
    void slotActivitySearch();
    void slotRecipeAdd();
    void slotRecipeSearch();
    void slotActivityCalc();
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
    void setProductEditConnect(ProductEdit* );
    void setProductInfoConnect(ProductInfo* );
    void setProductSeachConnect(ProductSeach* );
    void setActivityEditConnect(ActivityEdit* );
    void setActivityInfoConnect(ActivityInfo* );
    void setActivitySeachConnect(ActivitySeach* );
    void setRecipeEditConnect(RecipeEdit* );
    void setRecipeInfoConnect(RecipeInfo* );
    void setRecipeSeachConnect(RecipeSeach* );
    void setActivityCalculationConnect(ActivityCalculation* );

    void addSubWindowAndShow(QWidget *widget );

    Ui::mainWindow _ui;

    //TODO:, имеет ли смысл хранить эти указатели?
    ClientEdit*         m_formClientEdit;
    ClientInfo*         m_formClientInfo;
    ClientSearch*       m_formClientSeach;
    ExaminationEdit*    m_formExaminationEdit;
    ExaminationInfo*    m_formExaminationInfo;
    ExaminationSearch*  m_formExaminationSearch;
    ProductEdit*        m_formProductEdit;
    ProductInfo*        m_formProductInfo;
    ProductSeach*       m_formProductSearch;
    ActivityEdit*       m_formActivityEdit;
    ActivityInfo*       m_formActivityInfo;
    ActivitySeach*      m_formActivitySeach;
    RecipeEdit*         m_formRecipeEdit;
    RecipeInfo*         m_formRecipeInfo;
    RecipeSeach*        m_formRecipeSeach;
    ActivityCalculation*m_formActivityCalculation;

    QLabel* m_text;

    DatabaseModule _database;
};
