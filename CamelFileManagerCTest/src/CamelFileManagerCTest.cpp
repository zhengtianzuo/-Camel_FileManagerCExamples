
// *@file CamelFileManagerCTest.cpp
// *@brief CamelFileManagerCTest
// *@version 1.0
// *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
// *@author zhengtianzuo
#include <QDateTime>
#include "CamelFileManagerCTest.h"

CamelFileManagerCTest::CamelFileManagerCTest() :
    m_pTestThread(nullptr),
    m_pTableData(nullptr) {
    m_pTableData = new DataTableViewModel();
    m_pTestThread = new CamelFileManagerCTestThread();
    m_pTestThread->init();

    connect(m_pTestThread, SIGNAL(addInfo(QString, QString, QString, QString, int)),
            m_pTableData, SLOT(add(QString, QString, QString, QString, int)));
    connect(m_pTestThread, SIGNAL(clearInfo()),
            m_pTableData, SLOT(clear()));
}

CamelFileManagerCTest::~CamelFileManagerCTest() {
    delete m_pTestThread;
    delete m_pTableData;
}

DataTableViewModel *CamelFileManagerCTest::Cls_funGetTableData() {
    return(m_pTableData);
}

void CamelFileManagerCTest::cls_funStartTest() {
    if (m_pTestThread->isRunning()) return;
    m_pTestThread->start();
}

CamelFileManagerCTestThread::CamelFileManagerCTestThread() :
    m_FMInterface(nullptr),
    m_FMInt(nullptr),
    m_dBVerify(nullptr),
    m_funData(nullptr),
    m_fun(nullptr) {
}

CamelFileManagerCTestThread::~CamelFileManagerCTestThread() {
    if (m_dBVerify) {
        delete m_dBVerify->chrPassword;
        delete m_dBVerify->chrDBFileName;
        delete m_dBVerify;
        m_dBVerify = nullptr;
    }
    m_FMInterface->Cls_funTerminate(m_FMInt);
    delete m_FMInterface;
    delete m_funData;
    delete m_fun;
}

void CamelFileManagerCTestThread::init() {
    m_FMInterface = new Camel_FileManagerCInterface();
    m_FMInt = m_FMInterface->Cls_funInitialize();
    m_FMInt->Cls_funManagerInitialize();
    clsFileManager_CmdMapInit();

    string sDBPass = "pass";
    string sAppPath = QCoreApplication::applicationDirPath().toStdString() + "/";
    string sDBFileName = sAppPath + "test.ztz";

    char* cName = new char[260];
    memset(cName, 0, 260);
    snprintf(cName, 260, "%s", sDBFileName.c_str());
    char* cPass = new char[Cls_intFNameSize + 1];
    memset(cPass, 0, Cls_intFNameSize + 1);
    snprintf(cPass, Cls_intFNameSize + 1, "%s", sDBPass.c_str());

    m_dBVerify = new Cls_stuDBVerify(cName, cPass);
    m_funData = new Cls_stuFunction(reinterpret_cast<void*>(&Sub_funManagerData), this);
    m_fun = new Cls_stuFunction(nullptr, nullptr);
}

void CamelFileManagerCTestThread::run() {
    //清除结果
    emit clearInfo();

    //创建数据库
    string sDBName = "test";
    int intError = m_FMInt->Cls_funManagerDB_CreateDataBase(m_dBVerify, sDBName.c_str(), true);
    emit addInfo("Cls_funManagerDB_CreateDataBase", QStringLiteral(" 创建数据库"), "1", QString::number(intError), intError);

    //打开数据库
    intError = m_FMInt->Cls_funManagerDB_OpenDataBase(m_dBVerify);
    emit addInfo("Cls_funManagerDB_OpenDataBase", QStringLiteral(" 打开数据库"), "1", QString::number(intError), intError);

    //进行数据库操作相关测试
    subDBTest_SetName();
    subDBTest_GetName();
    subDBTest_ChangePassword();

    //进行数据操作相关测试
    subDataTest_Short();
    subDataTest_Integer();
    subDataTest_Float();
    subDataTest_Double();
    subDataTest_Currency();
    subDataTest_Date();
    subDataTest_String();
    subDataTest_File();
    subDataTest_ShortArray();
    subDataTest_IntegerArray();
    subDataTest_FloatArray();
    subDataTest_DoubleArray();
    subDataTest_CurrencyArray();
    subDataTest_DateArray();
    subDataTest_StringArray();

    //进行数据统计相关测试
    subDataAllTest_GetSizeList();
    subDataAllTest_GetNameList();
    subDataAllTest_GetTypeList();
    subDataAllTest_GetTypeTotalNoList();
    subDataAllTest_GetIndexList();
    subDataAllTest_GetTotalNumber();

    //关闭数据库
    intError = m_FMInt->Cls_funManagerDB_CloseDataBase(m_dBVerify);
    emit addInfo("Cls_funManagerDB_CloseDataBase", QStringLiteral(" 关闭数据库"), "1", QString::number(intError), intError);
}

void CamelFileManagerCTestThread::Sub_funManagerBytes(
    int intFunction, void *pContext, char *&pUserData,
    int &intUserSize, void *pReturnData, int intReturnSize) {
    Q_UNUSED(pContext);
    Q_UNUSED(intUserSize);
    switch (intFunction) {
    case clsFileManager_intDataType_String:
    case clsFileManager_intDataType_File: {
        pUserData = new char[static_cast<unsigned int>(intReturnSize)];
        memcpy(pUserData, pReturnData, static_cast<unsigned int>(intReturnSize));
    }
    break;
    default:
        break;
    }
}

void CamelFileManagerCTestThread::Sub_funManagerData(
    int intFunction, void *pContext, void *pUserData,
    int intUserSize, void *pReturnData, int intReturnSize) {
    Q_UNUSED(pContext);
    Q_UNUSED(intUserSize);
    Q_UNUSED(intReturnSize);
    Cls_stuFMCmdMap[intFunction].lpFunc(pUserData, pReturnData);
}

void CamelFileManagerCTestThread::subDBTest_SetName() {
    //设置数据库名称
    string sDBName = "newname";
    int intError = m_FMInt->Cls_funManagerDB_SetName(m_dBVerify, sDBName.c_str());
    emit addInfo("Cls_funManagerDB_SetName", QStringLiteral(" 设置数据库名称"), "1", QString::number(intError), intError);
}

void CamelFileManagerCTestThread::subDBTest_GetName() {
    //获取数据库名称
    char *chrDBName = new char[Cls_intFNameSize + 1];
    int intError = m_FMInt->Cls_funManagerDB_GetName(m_dBVerify, chrDBName);
    QString strData = chrDBName;
    delete[] chrDBName;
    strData = strData.replace(" ", "");
    emit addInfo("Cls_funManagerDB_GetName", QStringLiteral(" 获取数据库名称"), "1", QString::number(intError), intError);
}

void CamelFileManagerCTestThread::subDBTest_ChangePassword() {
    //修改密码
    string sDBPass = "pass";
    string sNewDBPass = "newpass";
    int intError = m_FMInt->Cls_funManagerDB_ChangePassword(m_dBVerify, sDBPass.c_str(), sNewDBPass.c_str());
    if (intError == clsFileManager_intErrorCode_Success) {
        char* cPass = new char[Cls_intFNameSize + 1];
        memset(cPass, 0, Cls_intFNameSize + 1);
        snprintf(cPass, Cls_intFNameSize + 1, "%s", sNewDBPass.c_str());
        delete m_dBVerify->chrPassword;
        m_dBVerify->chrPassword = cPass;
    }
    emit addInfo("Cls_funManagerDB_ChangePassword", QStringLiteral(" 修改密码"), "1", QString::number(intError), intError);
}

void CamelFileManagerCTestThread::subDataTest_Short() {
    //加入短整型数据
    short srtShort = 1234;
    Cls_stuDataType dataType(clsFileManager_intDataType_Short, -1, "short");
    Cls_stuUserData userData(&srtShort, 0);
    int intError = m_FMInt->Cls_funManagerData_Combine(m_dBVerify, &dataType, nullptr, &userData, false, -1);
    emit addInfo("Cls_funManagerData_Combine", QStringLiteral(" 加入短整型数据"), "1", QString::number(intError), intError);

    //修改短整型数据
    srtShort = 1122;
    intError = m_FMInt->Cls_funManagerData_Modify(m_dBVerify, &dataType, &userData, false);
    emit addInfo("Cls_funManagerData_Modify", QStringLiteral(" 修改短整型数据"), "1", QString::number(intError), intError);

    //获取短整型数据
    srtShort = 0;
    int intSize = 0;
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(srtShort), intSize);
    intError = m_FMInt->Cls_funManagerData_Extract(m_dBVerify, &dataType, m_fun, &getUserData);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取短整型数据"), QString("1122"), QString::number(srtShort), intError);

    //获取短整型数据大小
    intSize = 0;
    intError = m_FMInt->Cls_funManagerData_GetSize(m_dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
    emit addInfo("Cls_funManagerData_GetSize", QStringLiteral(" 获取短整型数据大小"), QString::number(sizeof(short)), QString::number(intSize), intError);
}

void CamelFileManagerCTestThread::subDataTest_Integer() {
    //加入整型数据
    int intInt = 1234;
    Cls_stuDataType dataType(clsFileManager_intDataType_Integer, -1, "int");
    Cls_stuUserData userData(&intInt, 0);
    int intError = m_FMInt->Cls_funManagerData_Combine(m_dBVerify, &dataType, nullptr, &userData, false, -1);
    emit addInfo("Cls_funManagerData_Combine", QStringLiteral(" 加入整型数据"), "1", QString::number(intError), intError);

    //修改整型数据
    intInt = 1122;
    intError = m_FMInt->Cls_funManagerData_Modify(m_dBVerify, &dataType, &userData, false);
    emit addInfo("Cls_funManagerData_Modify", QStringLiteral(" 修改整型数据"), "1", QString::number(intError), intError);

    //获取整型数据
    intInt = 0;
    int intSize = 0;
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(intInt), intSize);
    intError = m_FMInt->Cls_funManagerData_Extract(m_dBVerify, &dataType, m_fun, &getUserData);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取整型数据"), QString("1122"), QString::number(intInt), intError);

    //获取整型数据大小
    intSize = 0;
    intError = m_FMInt->Cls_funManagerData_GetSize(m_dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
    emit addInfo("Cls_funManagerData_GetSize", QStringLiteral(" 获取整型数据大小"), QString::number(sizeof(int)), QString::number(intSize), intError);
}

void CamelFileManagerCTestThread::subDataTest_Float() {
    //加入浮点型数据
    float fltFloat = static_cast<float>(1234.56);
    Cls_stuDataType dataType(clsFileManager_intDataType_Float, -1, "float");
    Cls_stuUserData userData(&fltFloat, 0);
    int intError = m_FMInt->Cls_funManagerData_Combine(m_dBVerify, &dataType, nullptr, &userData, false, -1);
    emit addInfo("Cls_funManagerData_Combine", QStringLiteral(" 加入浮点型数据"), "1", QString::number(intError), intError);

    //修改浮点型数据
    fltFloat = static_cast<float>(1122.33);
    intError = m_FMInt->Cls_funManagerData_Modify(m_dBVerify, &dataType, &userData, false);
    emit addInfo("Cls_funManagerData_Modify", QStringLiteral(" 修改浮点型数据"), "1", QString::number(intError), intError);

    //获取浮点型数据
    fltFloat = 0.0;
    int intSize = 0;
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(fltFloat), intSize);
    intError = m_FMInt->Cls_funManagerData_Extract(m_dBVerify, &dataType, m_fun, &getUserData);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取浮点型数据"), QString("1122.33"), QString::number(fltFloat), intError);

    //获取浮点型数据大小
    intSize = 0;
    intError = m_FMInt->Cls_funManagerData_GetSize(m_dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
    emit addInfo("Cls_funManagerData_GetSize", QStringLiteral(" 获取浮点型数据大小"), QString::number(sizeof(float)), QString::number(intSize), intError);
}

void CamelFileManagerCTestThread::subDataTest_Double() {
    //加入双浮点型数据
    double dblDouble = 1234.56;
    Cls_stuDataType dataType(clsFileManager_intDataType_Double, -1, "double");
    Cls_stuUserData userData(&dblDouble, 0);
    int intError = m_FMInt->Cls_funManagerData_Combine(m_dBVerify, &dataType, nullptr, &userData, false, -1);
    emit addInfo("Cls_funManagerData_Combine", QStringLiteral(" 加入双浮点型数据"), "1", QString::number(intError), intError);

    //修改双浮点型数据
    dblDouble = 1122.33;
    intError = m_FMInt->Cls_funManagerData_Modify(m_dBVerify, &dataType, &userData, false);
    emit addInfo("Cls_funManagerData_Modify", QStringLiteral(" 修改双浮点型数据"), "1", QString::number(intError), intError);

    //获取双浮点型数据
    dblDouble = 0.0;
    int intSize = 0;
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(dblDouble), intSize);
    intError = m_FMInt->Cls_funManagerData_Extract(m_dBVerify, &dataType, m_fun, &getUserData);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取双浮点型数据"), QString("1122.33"), QString::number(dblDouble), intError);

    //获取双浮点型数据大小
    intSize = 0;
    intError = m_FMInt->Cls_funManagerData_GetSize(m_dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
    emit addInfo("Cls_funManagerData_GetSize", QStringLiteral(" 获取双浮点型数据大小"), QString::number(sizeof(double)), QString::number(intSize), intError);
}

void CamelFileManagerCTestThread::subDataTest_Currency() {
    //加入货币型数据
    double cryCurrency = 1234.56;
    Cls_stuDataType dataType(clsFileManager_intDataType_Currency, -1, "currency");
    Cls_stuUserData userData(&cryCurrency, 0);
    int intError = m_FMInt->Cls_funManagerData_Combine(m_dBVerify, &dataType, nullptr, &userData, false, -1);
    emit addInfo("Cls_funManagerData_Combine", QStringLiteral(" 加入货币型数据"), "1", QString::number(intError), intError);

    //修改货币型数据
    cryCurrency = 1122.33;
    intError = m_FMInt->Cls_funManagerData_Modify(m_dBVerify, &dataType, &userData, false);
    emit addInfo("Cls_funManagerData_Modify", QStringLiteral(" 修改货币型数据"), "1", QString::number(intError), intError);

    //获取货币型数据
    cryCurrency = 0.0;
    int intSize = 0;
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(cryCurrency), intSize);
    intError = m_FMInt->Cls_funManagerData_Extract(m_dBVerify, &dataType, m_fun, &getUserData);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取货币型数据"), QString("1122.33"), QString::number(cryCurrency), intError);

    //获取货币型数据大小
    intSize = 0;
    intError = m_FMInt->Cls_funManagerData_GetSize(m_dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
    emit addInfo("Cls_funManagerData_GetSize", QStringLiteral(" 获取货币型数据大小"), QString::number(sizeof(double)), QString::number(intSize), intError);
}

void CamelFileManagerCTestThread::subDataTest_Date() {
    //加入日期型数据
    double dateTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    Cls_stuDataType dataType(clsFileManager_intDataType_Date, -1, "datetime");
    Cls_stuUserData userData(&dateTime, 0);
    int intError = m_FMInt->Cls_funManagerData_Combine(m_dBVerify, &dataType, nullptr, &userData, false, -1);
    emit addInfo("Cls_funManagerData_Combine", QStringLiteral(" 加入日期型数据"), "1", QString::number(intError), intError);

    //修改日期型数据
    dateTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    double dateTimeNow = QDateTime::currentDateTime().toMSecsSinceEpoch();
    intError = m_FMInt->Cls_funManagerData_Modify(m_dBVerify, &dataType, &userData, false);
    emit addInfo("Cls_funManagerData_Modify", QStringLiteral(" 修改日期型数据"), "1", QString::number(intError), intError);

    //获取日期型数据
    dateTime = 0.0;
    int intSize = 0;
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(dateTime), intSize);
    intError = m_FMInt->Cls_funManagerData_Extract(m_dBVerify, &dataType, m_fun, &getUserData);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取日期型数据"), QDateTime::fromMSecsSinceEpoch(dateTimeNow).toString("yyyy-MM-dd hh:mm:ss"), QDateTime::fromMSecsSinceEpoch(dateTime).toString("yyyy-MM-dd hh:mm:ss"), intError);

    //获取日期型数据大小
    intSize = 0;
    intError = m_FMInt->Cls_funManagerData_GetSize(m_dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
    emit addInfo("Cls_funManagerData_GetSize", QStringLiteral(" 获取日期型数据大小"), QString::number(sizeof(double)), QString::number(intSize), intError);
}

void CamelFileManagerCTestThread::subDataTest_String() {
    //加入字符串型数据
    string strString = "这是一段字符串abc";
    Cls_stuDataType dataType(clsFileManager_intDataType_String, -1, "string");
    Cls_stuUserData userData(&strString, 0);
    int intError = m_FMInt->Cls_funManagerData_Combine(m_dBVerify, &dataType, nullptr, &userData, false, -1);
    emit addInfo("Cls_funManagerData_Combine", QStringLiteral(" 加入字符串型数据"), "1", QString::number(intError), intError);

    //修改字符串型数据
    strString = "这是一段修改后的字符串abc";
    unsigned int intLength = strString.length();
    intError = m_FMInt->Cls_funManagerData_Modify(m_dBVerify, &dataType, &userData, false);
    emit addInfo("Cls_funManagerData_Modify", QStringLiteral(" 修改字符串型数据"), "1", QString::number(intError), intError);

    //获取字符串型数据
    strString.clear();
    int intSize = 0;
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(strString), intSize);
    intError = m_FMInt->Cls_funManagerData_Extract(m_dBVerify, &dataType, m_funData, &getUserData);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取字符串型数据"), QStringLiteral("这是一段修改后的字符串abc"), QString::fromLocal8Bit(strString.c_str()), intError);

    //获取字符串型数据大小
    intSize = 0;
    intError = m_FMInt->Cls_funManagerData_GetSize(m_dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
    emit addInfo("Cls_funManagerData_GetSize", QStringLiteral(" 获取字符串型数据大小"), QString::number(intLength), QString::number(strString.length()), intError);
}

void CamelFileManagerCTestThread::subDataTest_File() {
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
    Cls_stuUserData userData(chrFile, 0);
    int intError = m_FMInt->Cls_funManagerData_Combine(m_dBVerify, &dataType, nullptr, &userData, true, -1);
    emit addInfo("Cls_funManagerData_Combine", QStringLiteral(" 添加文件"), "1", QString::number(intError), intError);

    //获取文件大小
    int intSize = 0;
    intError = m_FMInt->Cls_funManagerData_GetSize(m_dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
    emit addInfo("Cls_funManagerData_GetSize", QStringLiteral(" 获取文件大小"), QString("461824"), QString::number(intSize), intError);

    //获取数据流
    intSize = 0;
    void *chrData = nullptr;
    Cls_stuGetUserData getUserData(chrData, intSize);
    Cls_stuFunction fun(reinterpret_cast<void*>(&Sub_funManagerBytes), this);
    intError = m_FMInt->Cls_funManagerData_ExtractBytes(m_dBVerify, &dataType, &fun, &getUserData);
    emit addInfo("Cls_funManagerData_ExtractBytes", QStringLiteral(" 获取数据流"), QString("461824"), QString::number(intSize), intError);

    //删除文件
    intError = m_FMInt->Cls_funManagerData_Delete(m_dBVerify, &dataType);
    emit addInfo("Cls_funManagerData_Delete", QStringLiteral(" 删除文件"), "1", QString::number(intError), intError);

    //添加文件流
    Cls_stuUserData userData2(chrData, intSize);
    intError = m_FMInt->Cls_funManagerData_Combine(m_dBVerify, &dataType, "", &userData2, true, -1);
    emit addInfo("Cls_funManagerData_Combine", QStringLiteral(" 添加文件流"), "1", QString::number(intError), intError);
    delete reinterpret_cast<char*>(chrData);

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
    intError = m_FMInt->Cls_funManagerData_ExtractFile(m_dBVerify, &dataType, chrOutFile, true);
    emit addInfo("Cls_funManagerData_ExtractFile", QStringLiteral(" 获取文件"), "1", QString::number(intError), intError);
}

void CamelFileManagerCTestThread::subDataTest_ShortArray() {
    //添加短整型数组
    int intSize = -1;
    vector<short> aryShort;
    aryShort.push_back(234);
    aryShort.push_back(345);
    aryShort.push_back(456);
    Cls_stuDataType dataType(clsFileManager_intDataType_ShortArray, -1, "shortarray");
    Cls_stuUserData userData(&aryShort, 0);
    int intError = m_FMInt->Cls_funManagerData_Combine(m_dBVerify, &dataType, nullptr, &userData, false, -1);
    emit addInfo("Cls_funManagerData_Combine", QStringLiteral(" 添加短整型数组"), "1", QString::number(intError), intError);

    //修改短整型数组
    aryShort.at(0) = 222;
    aryShort.at(1) = 333;
    aryShort.at(2) = 444;
    intError = m_FMInt->Cls_funManagerData_Modify(m_dBVerify, &dataType, &userData, false);
    emit addInfo("Cls_funManagerData_Modify", QStringLiteral(" 修改短整型数组"), "1", QString::number(intError), intError);

    //获取短整型数组
    aryShort.clear();
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(aryShort), intSize);
    intError = m_FMInt->Cls_funManagerData_Extract(m_dBVerify, &dataType, m_funData, &getUserData);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取短整型数组"), QString("222"), QString::number(aryShort.at(0)), intError);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取短整型数组"), QString("333"), QString::number(aryShort.at(1)), intError);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取短整型数组"), QString("444"), QString::number(aryShort.at(2)), intError);

    //获取短整型数组大小
    intSize = 0;
    intError = m_FMInt->Cls_funManagerData_GetSize(m_dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
    emit addInfo("Cls_funManagerData_GetSize", QStringLiteral(" 获取短整型数组大小"), QString::number(sizeof(short)*3), QString::number(intSize), intError);
}

void CamelFileManagerCTestThread::subDataTest_IntegerArray() {
    //添加整型数组
    int intSize = -1;
    vector<int> aryInt;
    aryInt.push_back(345);
    aryInt.push_back(456);
    aryInt.push_back(567);
    Cls_stuDataType dataType(clsFileManager_intDataType_IntegerArray, -1, "intarray");
    Cls_stuUserData userData(&aryInt, 0);
    int intError = m_FMInt->Cls_funManagerData_Combine(m_dBVerify, &dataType, nullptr, &userData, false, -1);
    emit addInfo("Cls_funManagerData_Combine", QStringLiteral(" 添加整型数组"), "1", QString::number(intError), intError);

    //修改整型数组
    aryInt.at(0) = 333;
    aryInt.at(1) = 444;
    aryInt.at(2) = 555;
    intError = m_FMInt->Cls_funManagerData_Modify(m_dBVerify, &dataType, &userData, false);
    emit addInfo("Cls_funManagerData_Modify", QStringLiteral(" 修改整型数组"), "1", QString::number(intError), intError);

    //获取整型数组
    aryInt.clear();
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(aryInt), intSize);
    intError = m_FMInt->Cls_funManagerData_Extract(m_dBVerify, &dataType, m_funData, &getUserData);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取整型数组"), QString("333"), QString::number(aryInt.at(0)), intError);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取整型数组"), QString("444"), QString::number(aryInt.at(1)), intError);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取整型数组"), QString("555"), QString::number(aryInt.at(2)), intError);

    //获取整型数组大小
    intSize = 0;
    intError = m_FMInt->Cls_funManagerData_GetSize(m_dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
    emit addInfo("Cls_funManagerData_GetSize", QStringLiteral(" 获取整型数组大小"), QString::number(sizeof(int)*3), QString::number(intSize), intError);
}

void CamelFileManagerCTestThread::subDataTest_FloatArray() {
    //添加浮点型数组
    int intSize = -1;
    vector<float> aryFloat;
    aryFloat.push_back(static_cast<float>(123.45));
    aryFloat.push_back(static_cast<float>(234.56));
    aryFloat.push_back(static_cast<float>(345.67));
    Cls_stuDataType dataType(clsFileManager_intDataType_FloatArray, -1, "floatarray");
    Cls_stuUserData userData(&aryFloat, 0);
    int intError = m_FMInt->Cls_funManagerData_Combine(m_dBVerify, &dataType, nullptr, &userData, false, -1);
    emit addInfo("Cls_funManagerData_Combine", QStringLiteral(" 添加浮点型数组"), "1", QString::number(intError), intError);

    //修改浮点型数组
    aryFloat.at(0) = static_cast<float>(234.56);
    aryFloat.at(1) = static_cast<float>(345.67);
    aryFloat.at(2) = static_cast<float>(456.78);
    intError = m_FMInt->Cls_funManagerData_Modify(m_dBVerify, &dataType, &userData, false);
    emit addInfo("Cls_funManagerData_Modify", QStringLiteral(" 修改浮点型数组"), "1", QString::number(intError), intError);

    //获取浮点型数组
    aryFloat.clear();
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(aryFloat), intSize);
    intError = m_FMInt->Cls_funManagerData_Extract(m_dBVerify, &dataType, m_funData, &getUserData);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取浮点型数组"), QString("234.56"), QString::number(aryFloat.at(0)), intError);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取浮点型数组"), QString("345.67"), QString::number(aryFloat.at(1)), intError);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取浮点型数组"), QString("456.78"), QString::number(aryFloat.at(2)), intError);

    //获取浮点型数组大小
    intSize = 0;
    intError = m_FMInt->Cls_funManagerData_GetSize(m_dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
    emit addInfo("Cls_funManagerData_GetSize", QStringLiteral(" 获取浮点型数组大小"), QString::number(sizeof(float)*3), QString::number(intSize), intError);
}

void CamelFileManagerCTestThread::subDataTest_DoubleArray() {
    //添加双浮点型数组
    int intSize = -1;
    vector<double> aryDouble;
    aryDouble.push_back(234.56);
    aryDouble.push_back(345.67);
    aryDouble.push_back(456.78);
    Cls_stuDataType dataType(clsFileManager_intDataType_DoubleArray, -1, "doublearray");
    Cls_stuUserData userData(&aryDouble, 0);
    int intError = m_FMInt->Cls_funManagerData_Combine(m_dBVerify, &dataType, nullptr, &userData, false, -1);
    emit addInfo("Cls_funManagerData_Combine", QStringLiteral(" 添加双浮点型数组"), "1", QString::number(intError), intError);

    //修改双浮点型数组
    aryDouble.at(0) = 345.67;
    aryDouble.at(1) = 456.78;
    aryDouble.at(2) = 567.89;
    intError = m_FMInt->Cls_funManagerData_Modify(m_dBVerify, &dataType, &userData, false);
    emit addInfo("Cls_funManagerData_Modify", QStringLiteral(" 修改双浮点型数组"), "1", QString::number(intError), intError);

    //获取双浮点型数组
    aryDouble.clear();
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(aryDouble), intSize);
    intError = m_FMInt->Cls_funManagerData_Extract(m_dBVerify, &dataType, m_funData, &getUserData);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取双浮点型数组"), QString("345.67"), QString::number(aryDouble.at(0)), intError);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取双浮点型数组"), QString("456.78"), QString::number(aryDouble.at(1)), intError);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取双浮点型数组"), QString("567.89"), QString::number(aryDouble.at(2)), intError);

    //获取双浮点型数组大小
    intSize = 0;
    intError = m_FMInt->Cls_funManagerData_GetSize(m_dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
    emit addInfo("Cls_funManagerData_GetSize", QStringLiteral(" 获取双浮点型数组大小"), QString::number(sizeof(double)*3), QString::number(intSize), intError);
}

void CamelFileManagerCTestThread::subDataTest_CurrencyArray() {
    //添加货币型数组
    int intSize = -1;
    vector<double> aryCurrency;
    aryCurrency.push_back(234.56);
    aryCurrency.push_back(345.67);
    aryCurrency.push_back(456.78);
    Cls_stuDataType dataType(clsFileManager_intDataType_CurrencyArray, -1, "currencyarray");
    Cls_stuUserData userData(&aryCurrency, 0);
    int intError = m_FMInt->Cls_funManagerData_Combine(m_dBVerify, &dataType, nullptr, &userData, false, -1);
    emit addInfo("Cls_funManagerData_Combine", QStringLiteral(" 添加货币型数组"), "1", QString::number(intError), intError);

    //修改货币型数组
    aryCurrency.at(0) = 345.67;
    aryCurrency.at(1) = 456.78;
    aryCurrency.at(2) = 567.89;
    intError = m_FMInt->Cls_funManagerData_Modify(m_dBVerify, &dataType, &userData, false);
    emit addInfo("Cls_funManagerData_Modify", QStringLiteral(" 修改货币型数组"), "1", QString::number(intError), intError);

    //获取货币型数组
    aryCurrency.clear();
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(aryCurrency), intSize);
    intError = m_FMInt->Cls_funManagerData_Extract(m_dBVerify, &dataType, m_funData, &getUserData);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取货币型数组"), QString("345.67"), QString::number(aryCurrency.at(0)), intError);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取货币型数组"), QString("456.78"), QString::number(aryCurrency.at(1)), intError);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取货币型数组"), QString("567.89"), QString::number(aryCurrency.at(2)), intError);

    //获取货币型数组大小
    intSize = 0;
    intError = m_FMInt->Cls_funManagerData_GetSize(m_dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
    emit addInfo("Cls_funManagerData_GetSize", QStringLiteral(" 获取货币型数组大小"), QString::number(sizeof(double)*3), QString::number(intSize), intError);
}

void CamelFileManagerCTestThread::subDataTest_DateArray() {
    //添加日期型数组
    int intSize = -1;
    double dateTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    vector<double> aryDate;
    aryDate.push_back(dateTime);
    aryDate.push_back(dateTime+100);
    aryDate.push_back(dateTime+200);
    Cls_stuDataType dataType(clsFileManager_intDataType_DateArray, -1, "datearray");
    Cls_stuUserData userData(&aryDate, 0);
    int intError = m_FMInt->Cls_funManagerData_Combine(m_dBVerify, &dataType, nullptr, &userData, false, -1);
    emit addInfo("Cls_funManagerData_Combine", QStringLiteral(" 添加日期型数组"), "1", QString::number(intError), intError);

    //修改日期型数组
    dateTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    double dateTimeNow = dateTime;
    aryDate.at(0) = dateTime;
    aryDate.at(1) = dateTime+100;
    aryDate.at(2) = dateTime+200;
    intError = m_FMInt->Cls_funManagerData_Modify(m_dBVerify, &dataType, &userData, false);
    emit addInfo("Cls_funManagerData_Modify", QStringLiteral(" 修改日期型数组"), "1", QString::number(intError), intError);

    //获取日期型数组
    aryDate.clear();
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(aryDate), intSize);
    intError = m_FMInt->Cls_funManagerData_Extract(m_dBVerify, &dataType, m_funData, &getUserData);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取日期型数组"), QDateTime::fromMSecsSinceEpoch(dateTimeNow).toString("yyyy-MM-dd hh:mm:ss"), QDateTime::fromMSecsSinceEpoch(dateTime).toString("yyyy-MM-dd hh:mm:ss"), intError);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取日期型数组"), QDateTime::fromMSecsSinceEpoch(dateTimeNow + 100).toString("yyyy-MM-dd hh:mm:ss"), QDateTime::fromMSecsSinceEpoch(dateTime + 100).toString("yyyy-MM-dd hh:mm:ss"), intError);
    emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取日期型数组"), QDateTime::fromMSecsSinceEpoch(dateTimeNow + 200).toString("yyyy-MM-dd hh:mm:ss"), QDateTime::fromMSecsSinceEpoch(dateTime + 200).toString("yyyy-MM-dd hh:mm:ss"), intError);

    //获取日期型数组大小
    intSize = 0;
    intError = m_FMInt->Cls_funManagerData_GetSize(m_dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
    emit addInfo("Cls_funManagerData_GetSize", QStringLiteral(" 获取日期型数组大小"), QString::number(sizeof(double)*3), QString::number(intSize), intError);
}

void CamelFileManagerCTestThread::subDataTest_StringArray() {
    //添加字符串型数组
    int intSize = -1;
    vector<string> aryString;
    aryString.push_back("abc");
    aryString.push_back("英文");
    aryString.push_back("英文abc");
    Cls_stuDataType dataType(clsFileManager_intDataType_StringArray, -1, "stringarray");
    Cls_stuUserData userData(&aryString, 0);
    int intError = m_FMInt->Cls_funManagerData_Combine(m_dBVerify, &dataType, nullptr, &userData, false, -1);
    emit addInfo("Cls_funManagerData_Combine", QStringLiteral(" 添加字符串型数组"), "1", QString::number(intError), intError);

    //修改字符串型数组
    aryString.at(0) = "bcd";
    aryString.at(1) = "中文";
    aryString.at(2) = "中文bcd";
    intError = m_FMInt->Cls_funManagerData_Modify(m_dBVerify, &dataType, &userData, false);
    emit addInfo("Cls_funManagerData_Modify", QStringLiteral(" 修改字符串型数组"), "1", QString::number(intError), intError);

    //获取字符串型数组
    vector<string> aryGetString;
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(aryGetString), intSize);
    intError = m_FMInt->Cls_funManagerData_Extract(m_dBVerify, &dataType, m_funData, &getUserData);
    for (size_t i = 0; i < aryString.size(); i++) {
        emit addInfo("Cls_funManagerData_Extract", QStringLiteral(" 获取字符串型数组"), QString::fromLocal8Bit(aryString.at(i).c_str()), QString::fromLocal8Bit(aryGetString.at(i).c_str()), intError);
    }

    //获取字符串型数组大小
    intSize = 0;
    unsigned int stringSize = aryString.at(0).length() + aryString.at(1).length() + aryString.at(2).length();
    intError = m_FMInt->Cls_funManagerData_GetSize(m_dBVerify, clsFileManager_intSizeType_DataSize, &dataType, intSize);
    emit addInfo("Cls_funManagerData_GetSize", QStringLiteral(" 获取字符串型数组大小"), QString::number(stringSize), QString::number(intSize), intError);
}


void CamelFileManagerCTestThread::subDataAllTest_GetSizeList() {
    //获取数据大小列表
    int intSize = -1;
    vector<int> aryDataSizeList;
    Cls_stuUserData userData(&aryDataSizeList, intSize);
    int intError = m_FMInt->Cls_funManagerData_GetSizeList(m_dBVerify, clsFileManager_intSizeType_DataSize, m_funData, &userData);
    for (unsigned int i = 0; i < aryDataSizeList.size(); i++) {
        emit addInfo("Cls_funManagerData_GetSizeList", QStringLiteral(" 获取数据大小列表"), QString::number(i), QString::number(aryDataSizeList.at(i)), intError);
    }
}

void CamelFileManagerCTestThread::subDataAllTest_GetNameList() {
    //获取数据名称列表
    int intSize = -1;
    vector<string> aryDataNameList;
    Cls_stuUserData userData(&aryDataNameList, intSize);
    int intError = m_FMInt->Cls_funManagerData_GetNameList(m_dBVerify, clsFileManager_intNameType_Name, m_funData, &userData);
    for (unsigned int i = 0; i < aryDataNameList.size(); i++) {
        string sTemp = aryDataNameList.at(i);
        emit addInfo("Cls_funManagerData_GetNameList", QStringLiteral(" 获取数据名称列表"), QString::number(i), QString::fromLocal8Bit(sTemp.c_str()), intError);
    }
}

void CamelFileManagerCTestThread::subDataAllTest_GetTypeList() {
    //获取数据类型列表
    int intSize = -1;
    vector<int> aryDataTypeList;
    Cls_stuUserData userData(&aryDataTypeList, intSize);
    int intError = m_FMInt->Cls_funManagerData_GetTypeList(m_dBVerify, m_funData, &userData);
    for (unsigned int i = 0; i < aryDataTypeList.size(); i++) {
        emit addInfo("Cls_funManagerData_GetTypeList", QStringLiteral(" 获取数据类型列表"), QString::number(i), QString::number(aryDataTypeList.at(i)), intError);
    }
}

void CamelFileManagerCTestThread::subDataAllTest_GetTypeTotalNoList() {
    //获取数据各类型总数列表
    int intSize = -1;
    vector<int> aryDataTypeTotalNoList;
    Cls_stuUserData userData(&aryDataTypeTotalNoList, intSize);
    int intError = m_FMInt->Cls_funManagerData_GetTypeTotalNoList(m_dBVerify, m_funData, &userData);
    for (unsigned int i = 0; i < aryDataTypeTotalNoList.size(); i++) {
        emit addInfo("Cls_funManagerData_GetTypeTotalNoList", QStringLiteral(" 获取数据各类型总数列表"), QString::number(i), QString::number(aryDataTypeTotalNoList.at(i)), intError);
    }
}

void CamelFileManagerCTestThread::subDataAllTest_GetIndexList() {
    //获取数据序号列表
    int intSize = -1;
    vector<int> aryDataIndexList;
    Cls_stuUserData userData(&aryDataIndexList, intSize);
    int intError = m_FMInt->Cls_funManagerData_GetIndexList(m_dBVerify, m_funData, &userData);
    for (unsigned int i = 0; i < aryDataIndexList.size(); i++) {
        emit addInfo("Cls_funManagerData_GetIndexList", QStringLiteral(" 获取数据序号列表"), QString::number(i), QString::number(aryDataIndexList.at(i)), intError);
    }
}

void CamelFileManagerCTestThread::subDataAllTest_GetTotalNumber() {
    //获取数据库文件总数
    int intFileNumber = 0;
    int intError = m_FMInt->Cls_funManagerDB_GetTotalNumber(m_dBVerify, intFileNumber);
    emit addInfo("Cls_funManagerDB_GetTotalNumber", QStringLiteral(" 获取数据库文件总数"), QString::number(0), QString::number(intFileNumber), intError);
}
