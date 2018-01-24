/*!
 *@file CamelFileManagerCTest.h
 *@brief CamelFileManagerCTest
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
#pragma once
#include <QObject>
#include <QThread>
#include <QCoreApplication>
#include "../../CamelFileManagerCDll/Camel_FileManagerCInterface.h"
#include "DataTableView.h"

class CamelFileManagerCTestThread : public QThread
{
    Q_OBJECT
public:
    CamelFileManagerCTestThread(Camel_FileManagerCInt* pFMInt);

protected:
    void run();

signals:
    void addInfo(QString strName, QString strCName, QString strExpect, QString strReal, QString strError);
    void setInfo(int row, int column, QString strText);
    void delInfo(int row);
    void refreshInfo();

private:
    Camel_FileManagerCInt* Sub_FMInt;
    static void Sub_funManagerBytes(
        int intFunction, void *pContext, char *&pUserData, int &intUserSize,
        void *pReturnData, int intReturnSize);
    static void Sub_funManagerData(
        int intFunction, void *pContext, void *pUserData, int intUserSize,
        void *pReturnData, int intReturnSize);

    void Sub_subDBTest();
    void Sub_subDataTest();
};

class CamelFileManagerCTest : public QObject
{
    Q_OBJECT
public:
    CamelFileManagerCTest();
    ~CamelFileManagerCTest();
    DataTableViewModel* Cls_funGetTableData();
    Q_INVOKABLE void cls_funStartTest();

signals:

private:
    Camel_FileManagerCInterface *Sub_FMInterface;
    Camel_FileManagerCInt* Sub_FMInt;
    DataTableViewModel* Sub_pTableData;
    CamelFileManagerCTestThread* Sub_pTestThread;
};
