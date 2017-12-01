/*!
 *@file CamelCrashReportTest.cpp
 *@brief 崩溃报告开发组件测试程序
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
#include "CamelCrashReportTest.h"

void CamelCrashReportTest::doSomething()
{
    //运行异常代码
    char* chr = NULL;
    memset(chr, 0, 10);
}
