
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
    client.cpp \
    examination.cpp \
    databasemodule.cpp \
    MDIProgram.cpp \
    printer.cpp

HEADERS += \
    windows/ClientEdit.h \
    windows/ClientInfo.h \
    windows/ClientSeach.h \
    windows/ExaminationEdit.h \
    windows/ExaminationInfo.h \
    windows/ExaminationSearch.h \
    client.h \
    examination.h \
    databasemodule.h \
    MDIProgram.h \
    windows.h \
    printer.h

FORMS += \
    forms/Client_edit.ui \
    forms/Client_info.ui \
    forms/Client_search.ui \
    forms/Examination_edit.ui \
    forms/Examination_info.ui \
    forms/Examination_search.ui \
    forms/MDI_program.ui

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
