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
    for (int i = 0; i < 100; i++)
    {
        tableData.add(QStringLiteral("这是一个数据"), QStringLiteral("字符串数组"), QStringLiteral("12.53M"));
    }
    engine.rootContext()->setContextProperty("tableData", &tableData);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    return app.exec();
}
