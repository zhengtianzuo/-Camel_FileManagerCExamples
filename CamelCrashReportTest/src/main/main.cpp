/*!
 *@file main.cpp
 *@brief 程序主文件
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "../cpp/CamelCrashReportTest.h"

#ifdef WIN32
//Camel_CrashReport函数指针
#include <Windows.h>
#include "../../include/CamelCrashReportDll/Camel_CrashReport.h"
HINSTANCE hCrashReport;
lpCls_funCrashReportInitialize funInitialize;
lpCls_funCrashReportTerminate funTerminate;
lpCls_funGetException funGetException;
#endif

void init(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    CamelCrashReportTest crashReport;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("crashReport", &crashReport);
    engine.load(QUrl(QLatin1String("qrc:/src/ui/main.qml")));
    app.exec();
}

int main(int argc, char *argv[])
{
#ifdef WIN32
    //初始化Camel_CrashReport
    hCrashReport = LoadLibrary(L"Camel_CrashReport.dll");
    funInitialize = NULL;
    funGetException = NULL;
    funTerminate = NULL;
    if (hCrashReport != NULL)
    {
        funInitialize = (lpCls_funCrashReportInitialize)GetProcAddress(
                            hCrashReport, "Cls_funCrashReportInitialize");
        funGetException = (lpCls_funGetException)GetProcAddress(
                              hCrashReport, "Cls_funGetException");
        funTerminate = (lpCls_funCrashReportTerminate)GetProcAddress(
                           hCrashReport, "Cls_funCrashReportTerminate");
        funInitialize();
    }

    __try
    {
#endif

    init(argc, argv);

#ifdef WIN32
    }
    __except (funGetException(
                  GetExceptionInformation(), clsCrashReport_intParam_Normal))
    {
        ;
    }

    //卸载Camel_CrashReport
    if (hCrashReport != NULL)
    {
        funTerminate();
        funInitialize = NULL;
        funGetException = NULL;
        funTerminate = NULL;
        FreeLibrary(hCrashReport);
        hCrashReport = NULL;
    }
#endif
    return(0);
}
