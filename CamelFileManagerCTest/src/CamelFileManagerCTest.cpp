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
    Sub_pTestThread = new CamelFileManagerCTestThread();
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

void CamelFileManagerCTest::Cls_funStartTest()
{

}

CamelFileManagerCTestThread::CamelFileManagerCTestThread(Camel_FileManagerCInt* pFMInt, DataTableViewModel* pTableData)
{
    Sub_FMInt = pFMInt;
    Sub_pTableData = pTableData;
}

void CamelFileManagerCTestThread::run()
{

}
