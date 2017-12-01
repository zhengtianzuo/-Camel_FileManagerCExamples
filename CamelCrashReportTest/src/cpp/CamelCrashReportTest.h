/*!
 *@file CamelCrashReportTest.h
 *@brief 崩溃报告开发组件测试程序
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
#include <QObject>

class CamelCrashReportTest : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE void doSomething();
};
