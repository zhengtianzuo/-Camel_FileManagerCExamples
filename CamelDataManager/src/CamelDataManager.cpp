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
    for (int i = 0; i < 100; i++)
    {
        m_tableData->add(QStringLiteral("这是一个数据"), QStringLiteral("字符串数组"), QStringLiteral("12.53M"));
    }
}

CamelDataManager::~CamelDataManager()
{
    delete m_tableData;
    Sub_FMInterface->Cls_funTerminate(Sub_FMInt);
    delete Sub_FMInterface;
}

DataTableViewModel *CamelDataManager::getTableData()
{
    return (m_tableData);
}
