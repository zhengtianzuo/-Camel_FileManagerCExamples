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

class CamelDataManager : public QObject
{
    Q_OBJECT
public:
    CamelDataManager();
    ~CamelDataManager();

    DataTableViewModel* getTableData();
    DataListViewModel* getListData();

    Q_INVOKABLE void cls_funManagerDB_CreateDataBase(QString strName, QString strPass, QString strPath);

private:
    DataTableViewModel* m_tableData;
    DataListViewModel* m_listData;
    Camel_FileManagerCInterface *Sub_FMInterface;
    Camel_FileManagerCInt* Sub_FMInt;
};
