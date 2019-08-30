
// *@file CamelDataManager.h
// *@brief CamelDataManager
// *@version 1.0
// *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
// *@author zhengtianzuo
#pragma once
#include <QObject>
#include "../../CamelFileManagerCDll/Camel_FileManagerCInterface.h"
#include "DataTableView.h"
#include "DataListView.h"

class CamelDataManagerDB : public QObject {
    Q_OBJECT
 public:
    CamelDataManagerDB();
    ~CamelDataManagerDB();
    void init();

    DataListViewModel* getListData();

    Q_INVOKABLE int cls_funManagerDB_CreateDataBase(QString strName, QString strPass, QString strPath);
    Q_INVOKABLE int cls_funManagerDB_OpenDataBase(QString strName, QString strPass, QString strPath);
    Q_INVOKABLE int cls_funManagerDB_SetName(QString strDBName);
    Q_INVOKABLE int cls_funManagerDB_ChangePassword(QString strNewPass);
    Q_INVOKABLE int cls_funManagerDB_CheckSpace();

 signals:
    void sOpenDataBase(QString strName, QString strPath, QString strFileNum, QString strFileSize);

 private:
    DataListViewModel* m_listData;
    Camel_FileManagerCInterface *m_FMInterface;
    QString m_DBSuffix;

    void subOpenDataBase(string sDBFileName, QString strName, QString strPath);};

class CamelDataManagerData;
class CamelDataManagerUserData;
typedef QString(CamelDataManagerData:: *cls_stringfunc)(Cls_lpstuDataType);
typedef Cls_lpstuUserData(CamelDataManagerUserData:: *cls_userDatafunc)(QString);

class CamelDataManagerUserData : public QObject {
    Q_OBJECT
 public:
    CamelDataManagerUserData();
    ~CamelDataManagerUserData();

    Cls_lpstuUserData makeUserData(int nDataType, QString strValue);

 private:
    void userDataCmdMapInit();
    Cls_lpstuUserData short2UserData(QString strValue);
    Cls_lpstuUserData int2UserData(QString strValue);
    Cls_lpstuUserData float2UserData(QString strValue);
    Cls_lpstuUserData double2UserData(QString strValue);
    Cls_lpstuUserData currency2UserData(QString strValue);
    Cls_lpstuUserData datetime2UserData(QString strValue);
    Cls_lpstuUserData string2UserData(QString strValue);

 private:
    QMap<int, cls_userDatafunc> m_userDataCmdMap;
};

class CamelDataManagerData : public QObject {
    Q_OBJECT
 public:
    CamelDataManagerData();
    ~CamelDataManagerData();
    void init();

    DataTableViewModel* getTableData();

    Q_INVOKABLE int cls_funManagerData_Combine(int nDataType, QString strName, QString strValue);
    Q_INVOKABLE int cls_funManagerData_GetAllList();
    Q_INVOKABLE QString cls_funManagerData_GetName(int nRow);
    Q_INVOKABLE int cls_funManagerData_GetType(int nRow);
    Q_INVOKABLE QString cls_funManagerData_GetData(int nRow);
    Q_INVOKABLE int cls_funManagerData_Delete(int nRow);
    Q_INVOKABLE int cls_funManagerData_Modify(int nDataType, QString strName, QString strValue);

 private:
    DataTableViewModel* m_tableData;
    QMap<int, cls_stringfunc> m_stringCmdMap;
    Cls_lpstuFunction m_funData;
    Cls_lpstuFunction m_fun;
    CamelDataManagerUserData m_cUserData;

    static void Sub_funManagerData(
        int intFunction, void *pContext, void *pUserData, int intUserSize,
        void *pReturnData, int intReturnSize);

    void stringCmdMapInit();
    QString short2QString(Cls_lpstuDataType lpstuDataType);
    QString int2QString(Cls_lpstuDataType lpstuDataType);
    QString float2QString(Cls_lpstuDataType lpstuDataType);
    QString double2QString(Cls_lpstuDataType lpstuDataType);
    QString currency2QString(Cls_lpstuDataType lpstuDataType);
    QString dateTime2QString(Cls_lpstuDataType lpstuDataType);
    QString string2QString(Cls_lpstuDataType lpstuDataType);
};
