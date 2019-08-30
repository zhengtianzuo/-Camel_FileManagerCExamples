#-------------------------------------------------
#
# Copyright (C) 2003-2103 CamelSoft Corporation
#
#-------------------------------------------------

QT += qml quick

CONFIG += c++11

CONFIG += debug_and_release
CONFIG(debug, debug|release){
    DESTDIR += $$PWD/../../bin/linux/debug
} else {
    DESTDIR += $$PWD/../../bin/linux/release
}

CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../../../CamelFileManagerCDll/linux/Debug -lCamel_FileManagerC -llz4 -L$$PWD
} else {
    LIBS += -L$$PWD/../../../CamelFileManagerCDll/linux/Release -lCamel_FileManagerC -llz4 -L$$PWD
}

include($$PWD/../CamelFileManagerCTest.pri)
