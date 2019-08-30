
// *@file main.cpp
// *@brief 程序主文件
// *@version 1.0
// *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
// *@author zhengtianzuo
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "src/CamelDataManager.h"

//#include "vld.h"
//#pragma comment(lib, "vld.lib")

int main(int argc, char *argv[]) {
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    CamelDataManagerDB cDataManagerDB;
    cDataManagerDB.init();
    CamelDataManagerData cDataManagerData;
    cDataManagerData.init();
    QQmlContext *rootContext = engine.rootContext();
    rootContext->setContextProperty("cDataManagerDB", &cDataManagerDB);
    rootContext->setContextProperty("listData", cDataManagerDB.getListData());
    rootContext->setContextProperty("cDataManagerData", &cDataManagerData);
    rootContext->setContextProperty("tableData", cDataManagerData.getTableData());
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    return app.exec();
}
