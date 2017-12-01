#-------------------------------------------------
#
# Copyright (C) 2003-2103 CamelSoft Corporation
#
#-------------------------------------------------

QT += qml quick

CONFIG += c++11

CONFIG += debug_and_release
CONFIG(debug, debug|release){
    DESTDIR += $$PWD/../build/windows/debug
} else {
    DESTDIR += $$PWD/../build/windows/release
}

QMAKE_CFLAGS += /Zi
QMAKE_LFLAGS_RELEASE += /debug /opt:ref

SOURCES += $$PWD/src/main/main.cpp \
    $$PWD/src/cpp/CamelCrashReportTest.cpp

HEADERS += \
    $$PWD/include/CamelCrashReportDll/Camel_CrashReport.h \
    $$PWD/src/cpp/CamelCrashReportTest.h
	
RESOURCES += \
    $$PWD/qml.qrc

win32{
    RC_FILE = $$PWD/res/CamelCrashReportTest.rc
}
