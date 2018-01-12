#-------------------------------------------------
#
# Copyright (C) 2003-2103 CamelSoft Corporation
#
#-------------------------------------------------

QT += qml quick

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
    $$PWD/src/main.cpp \
    $$PWD/src/CamelFileManagerCTest.cpp \
    $$PWD/src/DataTableView.cpp

HEADERS += \
    $$PWD/../CamelFileManagerCDll/Camel_FileManagerC.h \
    $$PWD/../CamelFileManagerCDll/Camel_FileManagerCInterface.h \
    $$PWD/src/CamelFileManagerCTest.h \
    $$PWD/src/DataTableView.h

RESOURCES += \
    $$PWD/qml.qrc
