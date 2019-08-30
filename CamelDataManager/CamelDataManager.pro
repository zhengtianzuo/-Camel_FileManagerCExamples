#-------------------------------------------------
#
# Copyright (C) 2003-2103 CamelSoft Corporation
#
#-------------------------------------------------

QT += qml quick widgets charts

CONFIG += c++11

QMAKE_CFLAGS += /Zi
QMAKE_LFLAGS_RELEASE += /debug /opt:ref

CONFIG(debug, debug|release) {
    win32{
    LIBS += -L$$PWD/../CamelFileManagerCDll/windows/Debug -lCamel_FileManagerC -L$$PWD/
    }
} else {
    win32{
    LIBS += -L$$PWD/../CamelFileManagerCDll/windows/Release -lCamel_FileManagerC -L$$PWD/
    }
}

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/src/DataTableView.cpp \
    $$PWD/src/CamelDataManager.cpp \
    $$PWD/src/DataListView.cpp

RESOURCES += qml.qrc

HEADERS += \
    $$PWD/../CamelFileManagerCDll/Camel_FileManagerC.h \
    $$PWD/../CamelFileManagerCDll/Camel_FileManagerCInterface.h \
    $$PWD/src/DataTableView.h \
    $$PWD/src/CamelDataManager.h \
    $$PWD/src/DataListView.h

win32{
    RC_FILE = $$PWD/CamelDataManager.rc
}
