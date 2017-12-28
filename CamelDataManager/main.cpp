/*!
 *@file main.cpp
 *@brief 程序主文件
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "src/DataTableView.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    DataTableViewModel tableData;
    tableData.add(QStringLiteral("初始化"), QStringLiteral("999"), QStringLiteral("888"));
    engine.rootContext()->setContextProperty("tableData", &tableData);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    return app.exec();
}
