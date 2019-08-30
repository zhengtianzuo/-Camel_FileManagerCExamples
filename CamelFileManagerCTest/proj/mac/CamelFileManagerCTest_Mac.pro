#-------------------------------------------------
#
# Copyright (C) 2003-2103 CamelSoft Corporation
#
#-------------------------------------------------

QT += qml quick

CONFIG += c++11

CONFIG += debug_and_release
CONFIG(debug, debug|release){
    DESTDIR += $$PWD/../../bin/mac/debug
} else {
    DESTDIR += $$PWD/../../bin/mac/release
}

CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../../../CamelFileManagerCDll/mac/Debug -lCamel_FileManagerC -L$$PWD
} else {
    LIBS += -L$$PWD/../../../CamelFileManagerCDll/mac/Release -lCamel_FileManagerC -L$$PWD
}

include($$PWD/../CamelFileManagerCTest.pri)
