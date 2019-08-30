
// *@file CamelFileManagerCTest.h
// *@brief CamelFileManagerCTest
// *@version 1.0
// *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
// *@author zhengtianzuo
#pragma once
#include <QObject>
#include <QThread>
#include <QCoreApplication>
#include "../../CamelFileManagerCDll/Camel_FileManagerCInterface.h"
#include "DataTableView.h"

class CamelFileManagerCTestThread : public QThread {
    Q_OBJECT

 public:
    CamelFileManagerCTestThread();
    ~CamelFileManagerCTestThread();

    void init();
    DataTableViewModel* Cls_funGetTableData();

 protected:
    void run();

 signals:
    void addInfo(QString strName, QString strCName, QString strExpect, QString strReal, int intError);
    void clearInfo();

 private:
    Camel_FileManagerCInterface * m_FMInterface;
    Camel_FileManagerCInt* m_FMInt;
    Cls_lpstuDBVerify m_dBVerify;
    Cls_lpstuFunction m_funData;
    Cls_lpstuFunction m_fun;

    static void Sub_funManagerBytes(
        int intFunction, void *pContext, char *&pUserData, int &intUserSize,
        void *pReturnData, int intReturnSize);
    static void Sub_funManagerData(
        int intFunction, void *pContext, void *pUserData, int intUserSize,
        void *pReturnData, int intReturnSize);

    void subDBTest_SetName();
    void subDBTest_GetName();
    void subDBTest_ChangePassword();

    void subDataTest_Short();
    void subDataTest_Integer();
    void subDataTest_Float();
    void subDataTest_Double();
    void subDataTest_Currency();
    void subDataTest_Date();
    void subDataTest_String();
    void subDataTest_File();
    void subDataTest_ShortArray();
    void subDataTest_IntegerArray();
    void subDataTest_FloatArray();
    void subDataTest_DoubleArray();
    void subDataTest_CurrencyArray();
    void subDataTest_DateArray();
    void subDataTest_StringArray();

    void subDataAllTest_GetSizeList();
    void subDataAllTest_GetNameList();
    void subDataAllTest_GetTypeList();
    void subDataAllTest_GetTypeTotalNoList();
    void subDataAllTest_GetIndexList();
    void subDataAllTest_GetTotalNumber();
};

class CamelFileManagerCTest : public QObject {
    Q_OBJECT
 public:
    CamelFileManagerCTest();
    ~CamelFileManagerCTest();

    DataTableViewModel* Cls_funGetTableData();
    Q_INVOKABLE void cls_funStartTest();

 private:
    CamelFileManagerCTestThread* m_pTestThread;
    DataTableViewModel* m_pTableData;
};
