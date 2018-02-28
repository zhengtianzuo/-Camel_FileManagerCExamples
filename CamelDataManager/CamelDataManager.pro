#-------------------------------------------------
#
# Copyright (C) 2003-2103 CamelSoft Corporation
#
#-------------------------------------------------

QT += qml quick widgets charts

CONFIG += c++11

CONFIG(debug, debug|release) {
    win32{
    LIBS += -L$$PWD/../CamelFileManagerCDll/windows/Debug -lCamel_FileManagerC
    }
} else {
    win32{
    LIBS += -L$$PWD/../CamelFileManagerCDll/windows/Release -lCamel_FileManagerC
    }
}

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/src/DataTableView.cpp \
    $$PWD/src/CamelDataManager.cpp \
    src/DataListView.cpp

RESOURCES += qml.qrc

HEADERS += \
    $$PWD/../CamelFileManagerCDll/Camel_FileManagerC.h \
    $$PWD/../CamelFileManagerCDll/Camel_FileManagerCInterface.h \
    $$PWD/src/DataTableView.h \
    $$PWD/src/CamelDataManager.h \
    src/DataListView.h
