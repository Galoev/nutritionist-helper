
QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nutritionist-helper
TEMPLATE = app
CONFIG += c++17

win32:RC_ICONS += resources/icon.ico

DEFINES += QT_DEPRECATED_WARNINGS \
           APP_VERSION=\"\\\"$${VER}\\\"\"

SOURCES += main.cpp \
    windows/ClientEdit.cpp \
    windows/ClientInfo.cpp \
    windows/ClientSeach.cpp \
    windows/ExaminationEdit.cpp \
    windows/ExaminationInfo.cpp \
    windows/ExaminationSearch.cpp \
    windows/ActivitySeach.cpp \
    windows/ActivityEdit.cpp \
    windows/ActivityInfo.cpp \
    windows/RecipeInfo.cpp \
    windows/RecipeEdit.cpp \
    windows/RecipeSeach.cpp \
    windows/ProductSeach.cpp \
    windows/ProductInfo.cpp \
    windows/ProductEdit.cpp \
    windows/ActivityCalculation.cpp \
    databasemodule.cpp \
    MDIProgram.cpp \
    printer.cpp \
    entities/client.cpp \
    entities/examination.cpp \
    entities/activity.cpp \
    entities/recipe.cpp \
    entities/product.cpp

HEADERS += \
    windows/ClientEdit.h \
    windows/ClientInfo.h \
    windows/ClientSeach.h \
    windows/ExaminationEdit.h \
    windows/ExaminationInfo.h \
    windows/ExaminationSearch.h \
    windows/ActivitySeach.h \
    windows/ActivityEdit.h \
    windows/ActivityInfo.h \
    windows/RecipeInfo.h \
    windows/RecipeEdit.h \
    windows/RecipeSeach.h \
    windows/ProductSeach.h \
    windows/ProductInfo.h \
    windows/ProductEdit.h \
    windows/ActivityCalculation.h \
    databasemodule.h \
    MDIProgram.h \
    windows.h \
    printer.h \
    entities/client.h \
    entities/examination.h \
    entities/activity.h \
    entities/recipe.h \
    entities/product.h

FORMS += \
    forms/Client_edit.ui \
    forms/Client_info.ui \
    forms/Client_search.ui \
    forms/Examination_edit.ui \
    forms/Examination_info.ui \
    forms/Examination_search.ui \
    forms/MDI_program.ui \
    forms/Activity_seach.ui \
    forms/Activity_edit.ui \
    forms/Activity_info.ui \
    forms/Recipe_info.ui \
    forms/Recipe_edit.ui \
    forms/Recipe_seach.ui \
    forms/Product_seach.ui \
    forms/Product_info.ui \
    forms/Product_edit.ui \
    forms/Activity_calculation.ui

RESOURCES += \
    rec.qrc

# Default path for deployment.
Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc
Release:UI_DIR = release/.ui
Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc
Debug:UI_DIR = debug/.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
