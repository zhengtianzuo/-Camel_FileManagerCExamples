/*!
 *@file CamelDataManager.h
 *@brief CamelDataManager
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
#include "CamelDataManager.h"

CamelDataManager::CamelDataManager()
{
    Sub_FMInterface = new Camel_FileManagerCInterface();
    Sub_FMInt = Sub_FMInterface->Cls_funInitialize();
    Sub_FMInt->Cls_funManagerInitialize();
    clsFileManager_CmdMapInit();
    m_tableData = new DataTableViewModel();
    //    for (int i = 0; i < 100; i++)
    //    {
    //        m_tableData->add(QStringLiteral("数据")+QString::number(i), QStringLiteral("文件"), QStringLiteral("1.234M"));
    //    }
    m_listData = new DataListViewModel();
    //    for (int i = 0; i < 100; i++)
    //    {
    //        m_listData->add(QStringLiteral("名称")+QString::number(i), QStringLiteral("路径"));
    //    }
}

CamelDataManager::~CamelDataManager()
{
    delete m_tableData;
    delete m_listData;
    Sub_FMInterface->Cls_funTerminate(Sub_FMInt);
    delete Sub_FMInterface;
}

DataTableViewModel *CamelDataManager::getTableData()
{
    return (m_tableData);
}

DataListViewModel *CamelDataManager::getListData()
{
    return (m_listData);
}

void CamelDataManager::cls_funManagerDB_CreateDataBase(QString strName, QString strPass, QString strPath)
{
    string sDBName = strName.toLocal8Bit();
    string sDBPass = strPass.toStdString();
    string sAppPath = strPath.toLocal8Bit();
    string sDBFileName = sAppPath + sDBName + ".ztz";

    Cls_stuDBVerify dBVerify(sDBFileName.c_str(), sDBPass.c_str());
    int intError = Sub_FMInt->Cls_funManagerDB_CreateDataBase(&dBVerify, sDBName.c_str(), true);
    if (intError == clsFileManager_intErrorCode_Success)
    {
        m_listData->add(strName, strPath);
    }
}

void CamelDataManager::Cls_funManagerDB_OpenDataBase(QString strName, QString strPass, QString strPath, bool bAdd)
{
    string sDBPass = strPass.toStdString();
    string sAppPath = strPath.toLocal8Bit();

    Cls_stuDBVerify dBVerify(sAppPath.c_str(), sDBPass.c_str());
    int intError = Sub_FMInt->Cls_funManagerDB_OpenDataBase(&dBVerify);
    if (intError == clsFileManager_intErrorCode_Success)
    {
        if (bAdd == true)
        {
            m_listData->add(strName, strPath);
        }
    }
}
