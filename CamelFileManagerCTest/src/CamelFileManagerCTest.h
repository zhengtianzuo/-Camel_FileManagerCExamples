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
#include "../../CamelFileManagerCDll/Camel_FileManagerCInterface.h"
#include "DataTableView.h"

class CamelFileManagerCTestThread : public QThread
{
    Q_OBJECT
public:
    CamelFileManagerCTestThread(Camel_FileManagerCInt* pFMInt, DataTableViewModel* pTableData);

protected:
    void run();

private:
    Camel_FileManagerCInt* Sub_FMInt;
    DataTableViewModel* Sub_pTableData;
};

class CamelFileManagerCTest : public QObject
{
    Q_OBJECT
public:
    CamelFileManagerCTest();
    ~CamelFileManagerCTest();
    DataTableViewModel* Cls_funGetTableData();
    void Cls_funStartTest();

signals:

private:
    Camel_FileManagerCInterface *Sub_FMInterface;
    Camel_FileManagerCInt* Sub_FMInt;
    DataTableViewModel* Sub_pTableData;
    CamelFileManagerCTestThread* Sub_pTestThread;
};
