/*!
 *@file CamelFileManagerCTest.cpp
 *@brief CamelFileManagerCTest
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
#include "CamelFileManagerCTest.h"


CamelFileManagerCTest::CamelFileManagerCTest()
{
    Sub_FMInterface = new Camel_FileManagerCInterface();
    Sub_FMInt = Sub_FMInterface->Cls_funInitialize();
    Sub_FMInt->Cls_funManagerInitialize();
    Sub_pTableData = new DataTableViewModel();
    Sub_pTestThread = new CamelFileManagerCTestThread(Sub_FMInt);

    connect(Sub_pTestThread, SIGNAL(addInfo(QString,QString,QString,QString)),
                Sub_pTableData, SLOT(add(QString,QString,QString,QString)));

}

CamelFileManagerCTest::~CamelFileManagerCTest()
{
    delete Sub_pTestThread;
    delete Sub_pTableData;
    Sub_FMInterface->Cls_funTerminate(Sub_FMInt);
    delete Sub_FMInterface;
}

DataTableViewModel *CamelFileManagerCTest::Cls_funGetTableData()
{
    return(Sub_pTableData);
}

void CamelFileManagerCTest::cls_funStartTest()
{
    if (Sub_pTestThread->isRunning()) return;
    Sub_pTestThread->start();
}

CamelFileManagerCTestThread::CamelFileManagerCTestThread(Camel_FileManagerCInt* pFMInt)
{
    Sub_FMInt = pFMInt;
}

void CamelFileManagerCTestThread::run()
{
    int intError = clsFileManager_intErrorCode_Success;
    string sDBName = "test";
    string sDBPass = "pass";
    string sAppPath = QCoreApplication::applicationDirPath().toStdString() + "/";
    string sDBFileName = sAppPath + "test.ztz";

    Cls_stuDBVerify dBVerify(sDBFileName.c_str(), sDBPass.c_str());
    intError = Sub_FMInt->Cls_funManagerDB_CreateDataBase(&dBVerify, sDBName.c_str(), true);
    emit addInfo(QString("Cls_funManagerDB_CreateDataBase"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

    intError = Sub_FMInt->Cls_funManagerDB_OpenDataBase(&dBVerify);
    emit addInfo(QString("Cls_funManagerDB_OpenDataBase"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

    goDBTest();
}

void CamelFileManagerCTestThread::goDBTest()
{
    int intError = clsFileManager_intErrorCode_Success;
    string sDBName = "newName";
    string sDBPass = "pass";
    string sAppPath = QCoreApplication::applicationDirPath().toStdString() + "/";
    string sDBFileName = sAppPath + "test.ztz";

    Cls_stuDBVerify dBVerify(sDBFileName.c_str(), sDBPass.c_str());
    intError = Sub_FMInt->Cls_funManagerDB_SetName(&dBVerify, sDBName.c_str());
    emit addInfo(QString("Cls_funManagerDB_SetName"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

    char chrDBName[Cls_intFNameSize + 1];
    intError = Sub_FMInt->Cls_funManagerDB_GetName(&dBVerify, chrDBName);
    QString strData = chrDBName;
    emit addInfo(QString("Cls_funManagerDB_GetName"), QString(sDBName.c_str()), strData, (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

}
