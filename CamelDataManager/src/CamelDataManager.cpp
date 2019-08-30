
// *@file CamelDataManager.h
// *@brief CamelDataManager
// *@version 1.0
// *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
// *@author zhengtianzuo
#include "CamelDataManager.h"
#include <QFileInfo>
#include <QDateTime>

Camel_FileManagerCInt* m_FMInt = nullptr;
Cls_lpstuDBVerify m_dBVerify = nullptr;
QMap<int, QString> type2StringCmdMap;

void deleteDBVerify() {
    if (m_dBVerify) {
        delete m_dBVerify->chrPassword;
        delete m_dBVerify->chrDBFileName;
        delete m_dBVerify;
        m_dBVerify = nullptr;
    }
}

QString size2String(int nSize) {
    if (nSize < 1024) {
        return (QString::number(nSize) + QString(" B"));
    } else if (nSize < 1024 * 1024) {
        return (QString::number(nSize / 1024) + QString(" KB"));
    } else if (nSize < 1024 * 1024 * 1024) {
        return (QString::number(nSize / 1024 / 1024) + QString(" MB"));
    } else {
        return (QString::number(nSize / 1024 / 1024 / 1024) + QString(" GB"));
    }
}

void type2StringInit() {
    (void)type2StringCmdMap.insert(1, QString("Short"));
    (void)type2StringCmdMap.insert(2, QString("Integer"));
    (void)type2StringCmdMap.insert(3, QString("Float"));
    (void)type2StringCmdMap.insert(4, QString("Double"));
    (void)type2StringCmdMap.insert(5, QString("Currency"));
    (void)type2StringCmdMap.insert(6, QString("Date"));
    (void)type2StringCmdMap.insert(7, QString("String"));
    (void)type2StringCmdMap.insert(8, QString("File"));
    (void)type2StringCmdMap.insert(10, QString("ByteArray"));
    (void)type2StringCmdMap.insert(11, QString("ShortArray"));
    (void)type2StringCmdMap.insert(12, QString("IntegerArray"));
    (void)type2StringCmdMap.insert(13, QString("FloatArray"));
    (void)type2StringCmdMap.insert(14, QString("DoubleArray"));
    (void)type2StringCmdMap.insert(15, QString("CurrencyArray"));
    (void)type2StringCmdMap.insert(16, QString("DateArray"));
    (void)type2StringCmdMap.insert(17, QString("StringArray"));
}

QString type2String(int nType) {
    QMap<int, QString>::iterator it = type2StringCmdMap.find(nType);
    if (it == type2StringCmdMap.end()) { return (QString()); }
    return it.value();
}

CamelDataManagerDB::CamelDataManagerDB() :
    m_listData(nullptr),
    m_FMInterface(nullptr),
    m_DBSuffix("") {
}

CamelDataManagerDB::~CamelDataManagerDB() {
    delete m_listData;
    if (m_dBVerify != nullptr) {
        m_FMInt->Cls_funManagerDB_CloseDataBase(m_dBVerify);
        deleteDBVerify();
    }
    m_FMInterface->Cls_funTerminate(m_FMInt);
    delete m_FMInterface;
}

void CamelDataManagerDB::init() {
    m_FMInterface = new Camel_FileManagerCInterface();
    m_FMInt = m_FMInterface->Cls_funInitialize();
    m_FMInt->Cls_funManagerInitialize();
    clsFileManager_CmdMapInit();
    m_listData = new DataListViewModel();
    m_dBVerify = nullptr;
    m_DBSuffix = ".Ztz";
    type2StringInit();
}

DataListViewModel *CamelDataManagerDB::getListData() {
    return (m_listData);
}

int CamelDataManagerDB::cls_funManagerDB_CreateDataBase(
    QString strName, QString strPass, QString strPath) {
    string sDBName = strName.toLocal8Bit().toStdString();
    string sDBPass = strPass.toStdString();
    string sAppPath = strPath.toLocal8Bit().toStdString();
    string sDBFileName = sAppPath + sDBName + m_DBSuffix.toStdString();

    Cls_stuDBVerify dBVerify(sDBFileName.c_str(), sDBPass.c_str());
    int intError = m_FMInt->Cls_funManagerDB_CreateDataBase(&dBVerify, sDBName.c_str(), true);
    if (intError == clsFileManager_intErrorCode_Success) {
        m_listData->add(strName, strPath);
    }
    return intError;
}

void CamelDataManagerDB::subOpenDataBase(string sDBFileName, QString strName, QString strPath) {
    int nFileSize = 0;
    if (strName.length() == 0) {
        QFileInfo fileInfo;
        fileInfo.setFile(sDBFileName.c_str());
        strName = fileInfo.fileName();
        strName = strName.replace(m_DBSuffix, "");
        nFileSize = static_cast<int>(fileInfo.size());
    }
    m_listData->add(strName, strPath);

    int nFileNum = 0;
    m_FMInt->Cls_funManagerDB_GetTotalNumber(m_dBVerify, nFileNum);

    char *chrDBName = new char[Cls_intFNameSize + 1];
    m_FMInt->Cls_funManagerDB_GetName(m_dBVerify, chrDBName);

    emit sOpenDataBase(QString(chrDBName).trimmed(), sDBFileName.c_str(),
        QString::number(nFileNum), size2String(nFileSize));
    delete chrDBName;
}

int CamelDataManagerDB::cls_funManagerDB_OpenDataBase(
    QString strName, QString strPass, QString strPath) {
    if (strName.endsWith(m_DBSuffix)) { strName.replace(m_DBSuffix, ""); }
    if (strPath.endsWith(m_DBSuffix)) { strPath.replace(m_DBSuffix, ""); }
    string sDBPass = strPass.toStdString();
    string sDBFileName = strPath.toLocal8Bit().toStdString() +
        strName.toLocal8Bit().toStdString() + m_DBSuffix.toStdString();

    deleteDBVerify();
    char* cName = new char[260];
    memset(cName, 0, 260);
    snprintf(cName, 260, "%s", sDBFileName.c_str());
    char* cPass = new char[Cls_intFNameSize+1];
    memset(cPass, 0, Cls_intFNameSize+1);
    snprintf(cPass, Cls_intFNameSize + 1, "%s", sDBPass.c_str());
    m_dBVerify = new Cls_stuDBVerify(cName, cPass);
    int intError = m_FMInt->Cls_funManagerDB_OpenDataBase(m_dBVerify);
    if (intError != clsFileManager_intErrorCode_Success) { return (intError); }
    subOpenDataBase(sDBFileName, strName, strPath);
    return clsFileManager_intErrorCode_Success;
}

int CamelDataManagerDB::cls_funManagerDB_SetName(QString strDBName) {
    string sDBName = strDBName.toLocal8Bit().toStdString();
    int intError = m_FMInt->Cls_funManagerDB_SetName(m_dBVerify, sDBName.c_str());
    return intError;
}

int CamelDataManagerDB::cls_funManagerDB_ChangePassword(QString strNewPass) {
    string sDBPass = strNewPass.toStdString();
    int intError = m_FMInt->Cls_funManagerDB_ChangePassword(
        m_dBVerify, m_dBVerify->chrPassword, sDBPass.c_str());
    return intError;
}

int CamelDataManagerDB::cls_funManagerDB_CheckSpace() {
    return 0;
}

CamelDataManagerData::CamelDataManagerData():
    m_tableData(nullptr),
    m_stringCmdMap(),
    m_funData(nullptr),
    m_fun(nullptr),
    m_cUserData() {
}

CamelDataManagerData::~CamelDataManagerData() {
    delete m_tableData;
    delete m_funData;
    delete m_fun;
}

void CamelDataManagerData::init() {
    m_tableData = new DataTableViewModel();
    m_funData = new Cls_stuFunction(&Sub_funManagerData, this);
    m_fun = new Cls_stuFunction(nullptr, nullptr);
    stringCmdMapInit();
}

DataTableViewModel *CamelDataManagerData::getTableData() {
    return (m_tableData);
}

int CamelDataManagerData::cls_funManagerData_Combine(
    int nDataType, QString strName, QString strValue) {
    nDataType++;
    if (nDataType > 8) { nDataType++; }
    string sName = strName.toStdString();
    Cls_stuDataType sDataType(nDataType, -1, sName.c_str());
    Cls_lpstuUserData sUserData = m_cUserData.makeUserData(nDataType, strValue);
    if (sUserData == nullptr) { return -1; }
    int intError = m_FMInt->Cls_funManagerData_Combine(
        m_dBVerify, &sDataType, nullptr, sUserData, false, -1);
    if (intError == clsFileManager_intErrorCode_Success) {
        int intSize = 0;
        intError = m_FMInt->Cls_funManagerData_GetSize(
            m_dBVerify, clsFileManager_intSizeType_DataSize, &sDataType, intSize);
        if (intError == clsFileManager_intErrorCode_Success) {
            m_tableData->add(strName, type2String(nDataType), size2String(intSize));
        }
    }
    delete[] reinterpret_cast<char*>(sUserData->pUserData);
    delete sUserData;
    return intError;
}

int CamelDataManagerData::cls_funManagerData_GetAllList() {
    vector<string> aryDataNameList;
    Cls_stuUserData userData(&aryDataNameList, -1);
    int intError = m_FMInt->Cls_funManagerData_GetNameList(
        m_dBVerify, clsFileManager_intNameType_Name, m_funData, &userData);
    if (intError != clsFileManager_intErrorCode_Success) { return intError; }

    vector<int> aryDataTypeList;
    Cls_stuUserData userData1(&aryDataTypeList, -1);
    intError = m_FMInt->Cls_funManagerData_GetTypeList(m_dBVerify, m_funData, &userData1);
    if (intError != clsFileManager_intErrorCode_Success) { return intError; }
    if (aryDataTypeList.size() != aryDataNameList.size()) { return -1; }

    vector<int> aryDataSizeList;
    Cls_stuUserData userData2(&aryDataSizeList, -1);
    intError = m_FMInt->Cls_funManagerData_GetSizeList(
        m_dBVerify, clsFileManager_intSizeType_DataSize, m_funData, &userData2);
    if (intError != clsFileManager_intErrorCode_Success) { return intError; }
    if (aryDataSizeList.size() != aryDataNameList.size()) { return -1; }

    for (unsigned int i = 0; i < aryDataNameList.size(); i++) {
        m_tableData->add(QString(aryDataNameList.at(i).c_str()),
            type2String(aryDataTypeList.at(i)), size2String(aryDataSizeList.at(i)));
    }

    return intError;
}

QString CamelDataManagerData::cls_funManagerData_GetName(int nRow) {
    Cls_stuDataType sDType(-1, nRow+2, nullptr);
    char *chrDataName = new char[Cls_intFNameSize + 1];
    int nError = m_FMInt->Cls_funManagerData_GetName(
        m_dBVerify, &sDType, clsFileManager_intNameType_Name, chrDataName);
    if (nError != clsFileManager_intErrorCode_Success) {return "";}
    QString strDataName = QString(chrDataName);
    delete chrDataName;
    return strDataName;
}

int CamelDataManagerData::cls_funManagerData_GetType(int nRow) {
    Cls_stuDataType sDType(-1, nRow+2, nullptr);
    int nType = 0;
    int nError = m_FMInt->Cls_funManagerData_GetType(m_dBVerify, &sDType, nType);
    if (nError != clsFileManager_intErrorCode_Success) { return -1; }
    return nType;
}

QString CamelDataManagerData::cls_funManagerData_GetData(int nRow) {
    int nType = cls_funManagerData_GetType(nRow);
    if (nType == -1) {return "";}
    Cls_stuDataType sDataType(nType, nRow + 2, nullptr);
    QMap<int, cls_stringfunc>::iterator it = m_stringCmdMap.find(nType);
    if (it == m_stringCmdMap.end()) { return ""; }
    cls_stringfunc lfunc = reinterpret_cast<cls_stringfunc>(it.value());
    return ((this->*lfunc)(&sDataType));
}

int CamelDataManagerData::cls_funManagerData_Delete(int nRow) {
    Cls_stuDataType sDType(-1, nRow+2, nullptr);
    int intError = m_FMInt->Cls_funManagerData_Delete(m_dBVerify, &sDType);
    return intError;
}

int CamelDataManagerData::cls_funManagerData_Modify(
    int nDataType, QString strName, QString strValue) {
    string sName = strName.toStdString();
    Cls_stuDataType sDataType(nDataType, -1, sName.c_str());
    Cls_lpstuUserData sUserData = m_cUserData.makeUserData(nDataType, strValue);
    if (sUserData == nullptr) { return -1 ;}
    int intError = m_FMInt->Cls_funManagerData_Modify(
        m_dBVerify, &sDataType, sUserData, true);
    if (intError == clsFileManager_intErrorCode_Success) {
        int intSize = 0;
        intError = m_FMInt->Cls_funManagerData_GetSize(
            m_dBVerify, clsFileManager_intSizeType_DataSize, &sDataType, intSize);
        if (intError == clsFileManager_intErrorCode_Success) {
            m_tableData->update(strName, 2, size2String(intSize));
        }
    }
    delete[] reinterpret_cast<char*>(sUserData->pUserData);
    delete sUserData;
    return intError;
}

void CamelDataManagerData::Sub_funManagerData(
    int intFunction, void *pContext, void *pUserData,
    int intUserSize, void *pReturnData, int intReturnSize) {
    Q_UNUSED(pContext);
    Q_UNUSED(intUserSize);
    Q_UNUSED(intReturnSize);
    Cls_stuFMCmdMap[intFunction].lpFunc(pUserData, pReturnData);
}

QString CamelDataManagerData::short2QString(Cls_lpstuDataType lpstuDataType) {
    int intSize = 0;
    short srtShort = 0;
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(srtShort), intSize);
    int intError = m_FMInt->Cls_funManagerData_Extract(
        m_dBVerify, lpstuDataType, m_fun, &getUserData);
    if (intError != clsFileManager_intErrorCode_Success) {return "";}
    return (QString::number(srtShort));
}

QString CamelDataManagerData::int2QString(Cls_lpstuDataType lpstuDataType) {
    int intSize = 0;
    int intInt = 0;
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(intInt), intSize);
    int intError = m_FMInt->Cls_funManagerData_Extract(
        m_dBVerify, lpstuDataType, m_fun, &getUserData);
    if (intError != clsFileManager_intErrorCode_Success) {return "";}
    return (QString::number(intInt));
}

QString CamelDataManagerData::float2QString(Cls_lpstuDataType lpstuDataType) {
    int intSize = 0;
    float fltFloat = 0.0;
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(fltFloat), intSize);
    int intError = m_FMInt->Cls_funManagerData_Extract(
        m_dBVerify, lpstuDataType, m_fun, &getUserData);
    if (intError != clsFileManager_intErrorCode_Success) {return "";}
    return QString::number(fltFloat);
}

QString CamelDataManagerData::double2QString(Cls_lpstuDataType lpstuDataType) {
    int intSize = 0;
    double dblDouble = 0.0;
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(dblDouble), intSize);
    int intError = m_FMInt->Cls_funManagerData_Extract(
        m_dBVerify, lpstuDataType, m_fun, &getUserData);
    if (intError != clsFileManager_intErrorCode_Success) {return "";}
    return QString::number(dblDouble);
}

QString CamelDataManagerData::currency2QString(Cls_lpstuDataType lpstuDataType) {
    int intSize = 0;
    double cryCurrency = 0.0;
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(cryCurrency), intSize);
    int intError = m_FMInt->Cls_funManagerData_Extract(
        m_dBVerify, lpstuDataType, m_fun, &getUserData);
    if (intError != clsFileManager_intErrorCode_Success) {return "";}
    return QString::number(cryCurrency);
}

QString CamelDataManagerData::dateTime2QString(Cls_lpstuDataType lpstuDataType) {
    int intSize = 0;
    double dateTime = 0.0;
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(dateTime), intSize);
    int intError = m_FMInt->Cls_funManagerData_Extract(
        m_dBVerify, lpstuDataType, m_fun, &getUserData);
    if (intError != clsFileManager_intErrorCode_Success) {return "";}
    QString strTime = QDateTime::fromMSecsSinceEpoch(dateTime).toString("yyyy-MM-dd hh:mm:ss");
    return strTime;
}

QString CamelDataManagerData::string2QString(Cls_lpstuDataType lpstuDataType) {
    int intSize = 0;
    string strString = "";
    Cls_stuGetUserData getUserData(reinterpret_cast<void*&>(strString), intSize);
    int intError = m_FMInt->Cls_funManagerData_Extract(
        m_dBVerify, lpstuDataType, m_funData, &getUserData);
    if (intError != clsFileManager_intErrorCode_Success) {return "";}
    return (QString::fromLocal8Bit(strString.c_str()));
}

void CamelDataManagerData::stringCmdMapInit() {
    (void)m_stringCmdMap.insert(1, &CamelDataManagerData::short2QString);
    (void)m_stringCmdMap.insert(2, &CamelDataManagerData::int2QString);
    (void)m_stringCmdMap.insert(3, &CamelDataManagerData::float2QString);
    (void)m_stringCmdMap.insert(4, &CamelDataManagerData::double2QString);
    (void)m_stringCmdMap.insert(5, &CamelDataManagerData::currency2QString);
    (void)m_stringCmdMap.insert(6, &CamelDataManagerData::dateTime2QString);
    (void)m_stringCmdMap.insert(7, &CamelDataManagerData::string2QString);
}

CamelDataManagerUserData::CamelDataManagerUserData():
    m_userDataCmdMap() {
    userDataCmdMapInit();
}

CamelDataManagerUserData::~CamelDataManagerUserData() {
}

Cls_lpstuUserData CamelDataManagerUserData::short2UserData(QString strValue) {
    short* sData = new short(strValue.toShort());
    return new Cls_stuUserData(sData, 0);
}

Cls_lpstuUserData CamelDataManagerUserData::int2UserData(QString strValue) {
    int* sData = new int(strValue.toInt());
    return new Cls_stuUserData(sData, 0);
}

Cls_lpstuUserData CamelDataManagerUserData::float2UserData(QString strValue) {
    float* sData = new float(strValue.toFloat());
    return new Cls_stuUserData(sData, 0);
}

Cls_lpstuUserData CamelDataManagerUserData::double2UserData(QString strValue) {
    double* sData = new double(strValue.toDouble());
    return new Cls_stuUserData(sData, 0);
}

Cls_lpstuUserData CamelDataManagerUserData::currency2UserData(QString strValue) {
    double* sData = new double(strValue.toDouble());
    return new Cls_stuUserData(sData, 0);
}

Cls_lpstuUserData CamelDataManagerUserData::datetime2UserData(QString strValue) {
    double* sData = new double(strValue.toDouble());
    return new Cls_stuUserData(sData, 0);
}

Cls_lpstuUserData CamelDataManagerUserData::string2UserData(QString strValue) {
    string *sData = new string(strValue.toLocal8Bit().data());
    return new Cls_stuUserData(sData, 0);
}

void CamelDataManagerUserData::userDataCmdMapInit() {
    (void)m_userDataCmdMap.insert(1, &CamelDataManagerUserData::short2UserData);
    (void)m_userDataCmdMap.insert(2, &CamelDataManagerUserData::int2UserData);
    (void)m_userDataCmdMap.insert(3, &CamelDataManagerUserData::float2UserData);
    (void)m_userDataCmdMap.insert(4, &CamelDataManagerUserData::double2UserData);
    (void)m_userDataCmdMap.insert(5, &CamelDataManagerUserData::currency2UserData);
    (void)m_userDataCmdMap.insert(6, &CamelDataManagerUserData::datetime2UserData);
    (void)m_userDataCmdMap.insert(7, &CamelDataManagerUserData::string2UserData);
}

Cls_lpstuUserData CamelDataManagerUserData::makeUserData(int nDataType, QString strValue) {
    QMap<int, cls_userDatafunc>::iterator it = m_userDataCmdMap.find(nDataType);
    if (it == m_userDataCmdMap.end()) {return (nullptr);}
    cls_userDatafunc lfunc = reinterpret_cast<cls_userDatafunc>(it.value());
    return (this->*lfunc)(strValue);
}
