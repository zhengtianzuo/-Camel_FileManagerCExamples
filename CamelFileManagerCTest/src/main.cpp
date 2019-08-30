
// *@file main.cpp
// *@brief 程序主文件
// *@version 1.0
// *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
// *@author zhengtianzuo
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "CamelFileManagerCTest.h"

 // #include "vld.h"
 // #pragma comment(lib, "vld.lib")

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    CamelFileManagerCTest fmTest;
    engine.rootContext()->setContextProperty("tableData", fmTest.Cls_funGetTableData());
    engine.rootContext()->setContextProperty("fmTest", &fmTest);
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return app.exec();
}
