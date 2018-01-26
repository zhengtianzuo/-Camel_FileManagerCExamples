/*!
 *@file CamelFileManagerCTest.cpp
 *@brief CamelFileManagerCTest
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
#include "CamelFileManagerCTest.h"
#include <QDateTime>

CamelFileManagerCTest::CamelFileManagerCTest()
{
    Sub_FMInterface = new Camel_FileManagerCInterface();
    Sub_FMInt = Sub_FMInterface->Cls_funInitialize();
    Sub_FMInt->Cls_funManagerInitialize();
    Sub_pTableData = new DataTableViewModel();
    Sub_pTestThread = new CamelFileManagerCTestThread(Sub_FMInt);
    clsFileManager_CmdMapInit();

    connect(Sub_pTestThread, SIGNAL(addInfo(QString,QString,QString,QString,QString)),
            Sub_pTableData, SLOT(add(QString,QString,QString,QString,QString)));
    connect(Sub_pTestThread, SIGNAL(clearInfo()),
            Sub_pTableData, SLOT(clear()));
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

    //清除结果
    emit clearInfo();

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

void CamelFileManagerCTestThread::Sub_funManagerBytes(
    int intFunction, void *pContext, char *&pUserData,
    int &intUserSize, void *pReturnData, int intReturnSize)
{
    Q_UNUSED(pContext);
    Q_UNUSED(intUserSize);
    switch (intFunction)
    {
    case clsFileManager_intDataType_String:
    case clsFileManager_intDataType_File:
    {
        pUserData = new char[intReturnSize];
        memcpy(pUserData, pReturnData, intReturnSize);
    }
    break;
    default:
        break;
    }
}

void CamelFileManagerCTestThread::Sub_funManagerData(
    int intFunction, void *pContext, void *pUserData,
    int intUserSize, void *pReturnData, int intReturnSize)
{
    Q_UNUSED(pContext);
    Q_UNUSED(intUserSize);
    Q_UNUSED(intReturnSize);
    Cls_stuFMCmdMap[intFunction].lpFunc(pUserData, pReturnData);
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
    string sDBPass = "newpass";
    string sAppPath = QCoreApplication::applicationDirPath().toStdString() + "/";
    string sDBFileName = sAppPath + "test.ztz";
    Cls_stuDBVerify dBVerify(sDBFileName.c_str(), sDBPass.c_str());
    Cls_stuFunction fun(nullptr, nullptr);
    int intSize = 0;

    {
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
        Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(srtShort), intSize);
        intError = Sub_FMInt->Cls_funManagerData_Extract(&dBVerify, &dataType, &fun, &getUserData);
        emit addInfo(QString("Cls_funManagerData_Extract"), QStringLiteral(" 获取短整型数据"), QString("1122"), QString::number(srtShort), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //获取短整型数据大小
        intSize = 0;
        intError = Sub_FMInt->Cls_funManagerData_GetSize(&dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
        emit addInfo(QString("Cls_funManagerData_GetSize"), QStringLiteral(" 获取短整型数据大小"), QString::number(sizeof(short)), QString::number(intSize), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));
    }

    {
        //加入整型数据
        int intInt = 1234;
        Cls_stuDataType dataType(clsFileManager_intDataType_Integer, -1, "int");
        Cls_stuUserData userData(&intInt, 0);
        intError = Sub_FMInt->Cls_funManagerData_Combine(&dBVerify, &dataType, nullptr, &userData, false, -1);
        emit addInfo(QString("Cls_funManagerData_Combine"), QStringLiteral(" 加入整型数据"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //修改整型数据
        intInt = 1122;
        intError = Sub_FMInt->Cls_funManagerData_Modify(&dBVerify, &dataType, &userData, false);
        emit addInfo(QString("Cls_funManagerData_Modify"), QStringLiteral(" 修改整型数据"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //获取整型数据
        intInt = 0;
        intSize = 0;
        Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(intInt), intSize);
        intError = Sub_FMInt->Cls_funManagerData_Extract(&dBVerify, &dataType, &fun, &getUserData);
        emit addInfo(QString("Cls_funManagerData_Extract"), QStringLiteral(" 获取整型数据"), QString("1122"), QString::number(intInt), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //获取整型数据大小
        intSize = 0;
        intError = Sub_FMInt->Cls_funManagerData_GetSize(&dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
        emit addInfo(QString("Cls_funManagerData_GetSize"), QStringLiteral(" 获取整型数据大小"), QString::number(sizeof(int)), QString::number(intSize), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));
    }

    {
        //加入浮点型数据
        float fltFloat = 1234.56;
        Cls_stuDataType dataType(clsFileManager_intDataType_Float, -1, "float");
        Cls_stuUserData userData(&fltFloat, 0);
        intError = Sub_FMInt->Cls_funManagerData_Combine(&dBVerify, &dataType, nullptr, &userData, false, -1);
        emit addInfo(QString("Cls_funManagerData_Combine"), QStringLiteral(" 加入浮点型数据"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //修改浮点型数据
        fltFloat = 1122.33;
        intError = Sub_FMInt->Cls_funManagerData_Modify(&dBVerify, &dataType, &userData, false);
        emit addInfo(QString("Cls_funManagerData_Modify"), QStringLiteral(" 修改浮点型数据"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //获取浮点型数据
        fltFloat = 0.0;
        intSize = 0;
        Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(fltFloat), intSize);
        intError = Sub_FMInt->Cls_funManagerData_Extract(&dBVerify, &dataType, &fun, &getUserData);
        emit addInfo(QString("Cls_funManagerData_Extract"), QStringLiteral(" 获取浮点型数据"), QString("1122.33"), QString::number(fltFloat), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //获取浮点型数据大小
        intSize = 0;
        intError = Sub_FMInt->Cls_funManagerData_GetSize(&dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
        emit addInfo(QString("Cls_funManagerData_GetSize"), QStringLiteral(" 获取浮点型数据大小"), QString::number(sizeof(float)), QString::number(intSize), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));
    }

    {
        //加入双浮点型数据
        double dblDouble = 1234.56;
        Cls_stuDataType dataType(clsFileManager_intDataType_Double, -1, "double");
        Cls_stuUserData userData(&dblDouble, 0);
        intError = Sub_FMInt->Cls_funManagerData_Combine(&dBVerify, &dataType, nullptr, &userData, false, -1);
        emit addInfo(QString("Cls_funManagerData_Combine"), QStringLiteral(" 加入双浮点型数据"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //修改双浮点型数据
        dblDouble = 1122.33;
        intError = Sub_FMInt->Cls_funManagerData_Modify(&dBVerify, &dataType, &userData, false);
        emit addInfo(QString("Cls_funManagerData_Modify"), QStringLiteral(" 修改双浮点型数据"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //获取双浮点型数据
        dblDouble = 0.0;
        intSize = 0;
        Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(dblDouble), intSize);
        intError = Sub_FMInt->Cls_funManagerData_Extract(&dBVerify, &dataType, &fun, &getUserData);
        emit addInfo(QString("Cls_funManagerData_Extract"), QStringLiteral(" 获取双浮点型数据"), QString("1122.33"), QString::number(dblDouble), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //获取双浮点型数据大小
        intSize = 0;
        intError = Sub_FMInt->Cls_funManagerData_GetSize(&dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
        emit addInfo(QString("Cls_funManagerData_GetSize"), QStringLiteral(" 获取双浮点型数据大小"), QString::number(sizeof(double)), QString::number(intSize), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));
    }

    {
        //加入日期型数据
        double dateTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
        Cls_stuDataType dataType(clsFileManager_intDataType_Date, -1, "datetime");
        Cls_stuUserData userData(&dateTime, 0);
        intError = Sub_FMInt->Cls_funManagerData_Combine(&dBVerify, &dataType, nullptr, &userData, false, -1);
        emit addInfo(QString("Cls_funManagerData_Combine"), QStringLiteral(" 加入日期型数据"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //修改日期型数据
        dateTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
        double dateTimeNow = QDateTime::currentDateTime().toMSecsSinceEpoch();
        intError = Sub_FMInt->Cls_funManagerData_Modify(&dBVerify, &dataType, &userData, false);
        emit addInfo(QString("Cls_funManagerData_Modify"), QStringLiteral(" 修改日期型数据"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //获取日期型数据
        dateTime = 0.0;
        intSize = 0;
        Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(dateTime), intSize);
        intError = Sub_FMInt->Cls_funManagerData_Extract(&dBVerify, &dataType, &fun, &getUserData);
        QString strTime = QDateTime::fromMSecsSinceEpoch(dateTime).toString("yyyy-MM-dd hh:mm:ss");
        QString strTimeNow = QDateTime::fromMSecsSinceEpoch(dateTimeNow).toString("yyyy-MM-dd hh:mm:ss");
        emit addInfo(QString("Cls_funManagerData_Extract"), QStringLiteral(" 获取日期型数据"), strTimeNow, strTime, (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //获取日期型数据大小
        intSize = 0;
        intError = Sub_FMInt->Cls_funManagerData_GetSize(&dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
        emit addInfo(QString("Cls_funManagerData_GetSize"), QStringLiteral(" 获取日期型数据大小"), QString::number(sizeof(double)), QString::number(intSize), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));
    }

    {
        //加入字符串型数据
        string strString = "这是一段字符串abc";
        Cls_stuDataType dataType(clsFileManager_intDataType_String, -1, "string");
        Cls_stuUserData userData(&strString, 0);
        intError = Sub_FMInt->Cls_funManagerData_Combine(&dBVerify, &dataType, nullptr, &userData, false, -1);
        emit addInfo(QString("Cls_funManagerData_Combine"), QStringLiteral(" 加入字符串型数据"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //修改字符串型数据
        strString = "这是一段修改后的字符串abc";
        int intLength = strString.length();
        intError = Sub_FMInt->Cls_funManagerData_Modify(&dBVerify, &dataType, &userData, false);
        emit addInfo(QString("Cls_funManagerData_Modify"), QStringLiteral(" 修改字符串型数据"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //获取字符串型数据
        strString = "";
        intSize = 0;
        Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(strString), intSize);
        Cls_stuFunction funString(&Sub_funManagerData, this);
        intError = Sub_FMInt->Cls_funManagerData_Extract(&dBVerify, &dataType, &funString, &getUserData);
        emit addInfo(QString("Cls_funManagerData_Extract"), QStringLiteral(" 获取字符串型数据"), QStringLiteral("这是一段修改后的字符串abc"), QString::fromLocal8Bit(strString.c_str()), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //获取字符串型数据大小
        intSize = 0;
        intError = Sub_FMInt->Cls_funManagerData_GetSize(&dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
        emit addInfo(QString("Cls_funManagerData_GetSize"), QStringLiteral(" 获取字符串型数据大小"), QString::number(intLength), QString::number(strString.length()), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));
    }

    {
        //添加文件
#ifdef Q_OS_WIN32
        char chrFile[] = "Camel_FileManagerC.dll";
#endif
#ifdef Q_OS_LINUX
        char chrFile[] = "libCamel_FileManagerC.so";
#endif
#ifdef Q_OS_OSX
        char chrFile[] = "libCamel_FileManagerC.dylib";
#endif
        Cls_stuDataType dataType(clsFileManager_intDataType_File, -1, "file");
        Cls_stuUserData userDataFile(chrFile, 0);
        intError = Sub_FMInt->Cls_funManagerData_Combine(&dBVerify, &dataType, nullptr, &userDataFile, true, -1);
        emit addInfo(QString("Cls_funManagerData_Combine"), QStringLiteral(" 添加文件"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //获取文件大小
        intSize = 0;
        intError = Sub_FMInt->Cls_funManagerData_GetSize(&dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
        emit addInfo(QString("Cls_funManagerData_GetSize"), QStringLiteral(" 获取文件大小"), QString("461824"), QString::number(intSize), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //获取数据流
        intSize = 0;
        void *chrData = nullptr;
        Cls_stuFunction funFile(&Sub_funManagerBytes, this);
        Cls_stuGetUserData getUserData(chrData, intSize);
        intError = Sub_FMInt->Cls_funManagerData_ExtractBytes(&dBVerify, &dataType, &funFile, &getUserData);
        emit addInfo(QString("Cls_funManagerData_ExtractBytes"), QStringLiteral(" 获取数据流"), QString("461824"), QString::number(intSize), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //删除文件
        intError = Sub_FMInt->Cls_funManagerData_Delete(&dBVerify, &dataType);
        emit addInfo(QString("Cls_funManagerData_Delete"), QStringLiteral(" 删除文件"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //添加文件流
        Cls_stuUserData userData(chrData, intSize);
        intError = Sub_FMInt->Cls_funManagerData_Combine(&dBVerify, &dataType, "", &userData, true, -1);
        emit addInfo(QString("Cls_funManagerData_Combine"), QStringLiteral(" 添加文件流"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));
        delete[] chrData;

        //获取文件
#ifdef Q_OS_WIN32
        char chrOutFile[] = "Camel_FileManagerC_Out.dll";
#endif
#ifdef Q_OS_LINUX
        char chrOutFile[] = "libCamel_FileManagerC_Out.so";
#endif
#ifdef Q_OS_OSX
        char chrOutFile[] = "libCamel_FileManagerC_Out.dylib";
#endif
        intError = Sub_FMInt->Cls_funManagerData_ExtractFile(&dBVerify, &dataType, chrOutFile, true);
        emit addInfo(QString("Cls_funManagerData_ExtractFile"), QStringLiteral(" 获取文件"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

    }

    {
        //添加短整型数组
        intSize = -1;
        vector<short> aryShort;
        aryShort.push_back(234);
        aryShort.push_back(345);
        aryShort.push_back(456);
        Cls_stuDataType dataType(clsFileManager_intDataType_ShortArray, -1, "shortarray");
        Cls_stuUserData userData(&aryShort, 0);
        intError = Sub_FMInt->Cls_funManagerData_Combine(&dBVerify, &dataType, nullptr, &userData, false, -1);
        emit addInfo(QString("Cls_funManagerData_Combine"), QStringLiteral(" 添加短整型数组"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //修改短整型数组
        aryShort.at(0) = 222;
        aryShort.at(1) = 333;
        aryShort.at(2) = 444;
        intError = Sub_FMInt->Cls_funManagerData_Modify(&dBVerify, &dataType, &userData, false);
        emit addInfo(QString("Cls_funManagerData_Modify"), QStringLiteral(" 修改短整型数组"), QString("1"), QString::number(intError), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //获取短整型数组
        aryShort.clear();
        Cls_stuFunction funShort(&Sub_funManagerData, this);
        Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(aryShort), intSize);
        intError = Sub_FMInt->Cls_funManagerData_Extract(&dBVerify, &dataType, &funShort, &getUserData);
        emit addInfo(QString("Cls_funManagerData_Extract"), QStringLiteral(" 获取短整型数组"), QString("222"), QString::number(aryShort.at(0)), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));
        emit addInfo(QString("Cls_funManagerData_Extract"), QStringLiteral(" 获取短整型数组"), QString("333"), QString::number(aryShort.at(1)), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));
        emit addInfo(QString("Cls_funManagerData_Extract"), QStringLiteral(" 获取短整型数组"), QString("444"), QString::number(aryShort.at(2)), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));

        //获取短整型数组大小
        intSize = 0;
        intError = Sub_FMInt->Cls_funManagerData_GetSize(&dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
        emit addInfo(QString("Cls_funManagerData_GetSize"), QStringLiteral(" 获取短整型数组大小"), QString::number(sizeof(short)*3), QString::number(intSize), (intError==1)?QStringLiteral("成功"):QStringLiteral("错误!!!"));



    }




}
