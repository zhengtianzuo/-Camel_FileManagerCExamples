/*!
 *@file CamelDataManager.h
 *@brief CamelDataManager
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
#pragma once
#include <QObject>
#include "../../CamelFileManagerCDll/Camel_FileManagerCInterface.h"
#include "DataTableView.h"
#include "DataListView.h"

const QString DBSuffix = ".Ztz";

class CamelDataManager : public QObject
{
    Q_OBJECT
public:
    CamelDataManager();
    ~CamelDataManager();

    DataTableViewModel* getTableData();
    DataListViewModel* getListData();

    Q_INVOKABLE int cls_funManagerDB_CreateDataBase(QString strName, QString strPass, QString strPath);
    Q_INVOKABLE int cls_funManagerDB_OpenDataBase(QString strName, QString strPass, QString strPath);
    Q_INVOKABLE int cls_funManagerDB_SetName(QString strDBName);
    Q_INVOKABLE int cls_funManagerDB_ChangePassword(QString strNewPass);
    Q_INVOKABLE int cls_funManagerDB_CheckSpace();
    Q_INVOKABLE int cls_funManagerData_Combine(int nDataType, QString strName, QString strValue);
    Q_INVOKABLE int cls_funManagerDat_GetAllList();

signals:
    void sOpenDataBase(QString strName, QString strPath, QString strFileNum, QString strFileSize);

private:
    static void Sub_funManagerBytes(
        int intFunction, void *pContext, char *&pUserData, int &intUserSize,
        void *pReturnData, int intReturnSize);
    static void Sub_funManagerData(
        int intFunction, void *pContext, void *pUserData, int intUserSize,
        void *pReturnData, int intReturnSize);

    int type2RealType(int nType);
    QString type2String(int nType);
    QString size2String(int nSize);

    DataTableViewModel* m_tableData;
    DataListViewModel* m_listData;
    Camel_FileManagerCInterface *Sub_FMInterface;
    Camel_FileManagerCInt* Sub_FMInt;
    string m_strCurDBName;
    string m_strCurDBPass;
    string m_strCurDBPath;
};
