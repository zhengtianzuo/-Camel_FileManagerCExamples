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

    connect(Sub_pTestThread, SIGNAL(addInfo(QString,QString,QString,QString,QString)),
                Sub_pTableData, SLOT(add(QString,QString,QString,QString,QString)));

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

    //创建数据库
    intError = Sub_FMInt->Cls_funManagerDB_CreateDataBase(&dBVerify, sDBName.c_str(), true);
    emit addInfo(QString("Cls_funManagerDB_CreateDataBase"), QStringLiteral(" 创建数据库"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

    //打开数据库
    intError = Sub_FMInt->Cls_funManagerDB_OpenDataBase(&dBVerify);
    emit addInfo(QString("Cls_funManagerDB_OpenDataBase"), QStringLiteral(" 打开数据库"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

    //进行数据库操作相关测试
    Sub_subDBTest();

    //进行数据操作相关测试
    Sub_subDataTest();

    //关闭数据库
    intError = Sub_FMInt->Cls_funManagerDB_CloseDataBase(&dBVerify);
    emit addInfo(QString("Cls_funManagerDB_CloseDataBase"), QStringLiteral(" 关闭数据库"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));
}

void CamelFileManagerCTestThread::Sub_subDBTest()
{
    int intError = clsFileManager_intErrorCode_Success;
    string sDBName = "newName";
    string sDBPass = "pass";
    string sDBPassNew = "newpass";
    string sAppPath = QCoreApplication::applicationDirPath().toStdString() + "/";
    string sDBFileName = sAppPath + "test.ztz";
    Cls_stuDBVerify dBVerify(sDBFileName.c_str(), sDBPass.c_str());

    //设置数据库名称
    intError = Sub_FMInt->Cls_funManagerDB_SetName(&dBVerify, sDBName.c_str());
    emit addInfo(QString("Cls_funManagerDB_SetName"), QStringLiteral(" 设置数据库名称"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

    //获取数据库名称
    char chrDBName[Cls_intFNameSize + 1];
    intError = Sub_FMInt->Cls_funManagerDB_GetName(&dBVerify, chrDBName);
    QString strData = chrDBName;
    strData = strData.replace(" ", "");
    emit addInfo(QString("Cls_funManagerDB_GetName"), QStringLiteral(" 获取数据库名称"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

    //修改密码
    intError = Sub_FMInt->Cls_funManagerDB_ChangePassword(&dBVerify, sDBPass.c_str(), sDBPassNew.c_str());
    emit addInfo(QString("Cls_funManagerDB_ChangePassword"), QStringLiteral(" 修改密码"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

}

void CamelFileManagerCTestThread::Sub_subDataTest()
{
    int intError = clsFileManager_intErrorCode_Success;
    string sDBName = "newName";
    string sDBPass = "newpass";
    string sAppPath = QCoreApplication::applicationDirPath().toStdString() + "/";
    string sDBFileName = sAppPath + "test.ztz";
    Cls_stuDBVerify dBVerify(sDBFileName.c_str(), sDBPass.c_str());
    int intSize = 0;

    //加入短整型数据
    short srtShort = 1234;
    Cls_stuDataType dataType(clsFileManager_intDataType_Short, -1, "short");
    Cls_stuUserData userData(&srtShort, 0);
    intError = Sub_FMInt->Cls_funManagerData_Combine(&dBVerify, &dataType, nullptr, &userData, false, -1);
    emit addInfo(QString("Cls_funManagerData_Combine"), QStringLiteral(" 加入短整型数据"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

    //修改短整型数据
    srtShort = 1122;
    intError = Sub_FMInt->Cls_funManagerData_Modify(&dBVerify, &dataType, &userData, false);
    emit addInfo(QString("Cls_funManagerData_Modify"), QStringLiteral(" 修改短整型数据"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

    //获取短整型数据
    srtShort = 0;
    intSize = 0;
    Cls_stuFunction fun(nullptr, nullptr);
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(srtShort), intSize);
    intError = Sub_FMInt->Cls_funManagerData_Extract(&dBVerify, &dataType, &fun, &getUserData);
    emit addInfo(QString("Cls_funManagerData_Extract"), QStringLiteral(" 获取短整型数据"), QString("1122"), QString::number(srtShort), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));



}
