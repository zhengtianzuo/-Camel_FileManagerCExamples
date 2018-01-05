/*!
 *@file Camel_FileManagerC.h
 *@brief 文件管理开发组件定义
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author 郑天佐
 *@date 2013-4-3
*/
#pragma once
#include <iostream>
#include <vector>
#include <map>

using namespace std;

const unsigned int Cls_intFNameSize = 48;                                             //!<文件名长度

//!@brief 数据操作分析
const int clsFileManager_GetIndexList               = 0x00000101;                     //!<获取数据序号列表
const int clsFileManager_GetTypeList                = 0x00000102;                     //!<获取数据类型列表
const int clsFileManager_GetTypeTotalNoList         = 0x00000103;                     //!<获取数据各类型总数列表
const int clsFileManager_GetNameList                = 0x00000104;                     //!<获取数据名称列表
const int clsFileManager_GetSizeList                = 0x00000105;                     //!<获取数据大小列表

//!@brief 数据类型分析
const int clsFileManager_intDataType_Short          = 0x00000001;                     //!<短整型
const int clsFileManager_intDataType_Integer        = 0x00000002;                     //!<整型
const int clsFileManager_intDataType_Float          = 0x00000003;                     //!<单精度浮点型
const int clsFileManager_intDataType_Double         = 0x00000004;                     //!<双精度浮点型
const int clsFileManager_intDataType_Currency       = 0x00000005;                     //!<货币型
const int clsFileManager_intDataType_Date           = 0x00000006;                     //!<日期型
const int clsFileManager_intDataType_String         = 0x00000007;                     //!<字符串型
const int clsFileManager_intDataType_File           = 0x00000008;                     //!<文件型
const int clsFileManager_intDataType_ByteArray      = 0x0000000A;                     //!<字节数组
const int clsFileManager_intDataType_ShortArray     = 0x0000000B;                     //!<短整型数组
const int clsFileManager_intDataType_IntegerArray   = 0x0000000C;                     //!<整型数组
const int clsFileManager_intDataType_FloatArray     = 0x0000000D;                     //!<单精度浮点型数组
const int clsFileManager_intDataType_DoubleArray    = 0x0000000E;                     //!<双精度浮点型数组
const int clsFileManager_intDataType_CurrencyArray  = 0x0000000F;                     //!<货币型数组
const int clsFileManager_intDataType_DateArray      = 0x00000010;                     //!<日期型数组
const int clsFileManager_intDataType_StringArray    = 0x00000011;                     //!<字符串型数组

//!@brief 返回错误码分析
const int clsFileManager_intErrorCode_Success       = 0x00000001;                     //!<正确的值
const int clsFileManager_intErrorCode_Normal        = 0x00000002;                     //!<错误的值
const int clsFileManager_intErrorCode_Differ        = 0x00000003;                     //!<数据库文件数效验未通过
const int clsFileManager_intErrorCode_NoRights      = 0x00000004;                     //!<数据库密码效验未通过
const int clsFileManager_intErrorCode_DBNotExist    = 0x00000005;                     //!<数据库文件不存在
const int clsFileManager_intErrorCode_Exist         = 0x00000006;                     //!<文件已存在
const int clsFileManager_intErrorCode_NotExist      = 0x00000007;                     //!<文件不存在
const int clsFileManager_intErrorCode_OutOfRange    = 0x00000008;                     //!<超出范围
const int clsFileManager_intErrorCode_ErrorType     = 0x00000009;                     //!<类型不符
const int clsFileManager_intErrorCode_Param         = 0x0000000A;                     //!<参数错误
const int clsFileManager_intErrorCode_Compress      = 0x0000000B;                     //!<压缩错误
const int clsFileManager_intErrorCode_GetArray      = 0x0000000C;                     //!<数组错误
const int clsFileManager_intErrorCode_OutOfMemory   = 0x0000000D;                     //!<内存溢出
const int clsFileManager_intErrorCode_Handle        = 0x0000000E;                     //!<句柄错误
const int clsFileManager_intErrorCode_IO            = 0x0000000F;                     //!<IO错误

//!@brief 返回数据名称类型
const int clsFileManager_intNameType_Name           = 0x00000001;                     //!<数据名称
const int clsFileManager_intNameType_Remark         = 0x00000002;                     //!<数据备注

//!@brief 返回数据大小类型
const int clsFileManager_intSizeType_DataAllSize    = 0x00000001;                     //!<数据大小[删除数据后累加删除数据的大小]
const int clsFileManager_intSizeType_DataDeleteSize = 0x00000002;                     //!<删除的数据大小
const int clsFileManager_intSizeType_DataSize       = 0x00000003;                     //!<数据实际大小

//!@brief 数据采集回调函数
typedef unsigned(*Cls_lpfunManager)(
    int intFunction, void *pContext, void *pUserData,
    int intUserSize, void *pReturnData, int intReturnSize);
typedef unsigned(*Cls_lpfunManagerBytes)(
    int intFunction, void *pContext, void *&pUserData,
    int &intUserSize, void *pReturnData, int intReturnSize);

//!@brief 采集数据回调函数用
typedef void(clsFileManager_datafunc)(void *&, void *);

static void clsFileManager_data2string(void *&pUserData, void *pReturnData)
{
    *reinterpret_cast<string *>(pUserData) =
        *reinterpret_cast<string *>(pReturnData);
}

static void clsFileManager_data2vshort(void *&pUserData, void *pReturnData)
{
    *reinterpret_cast<vector<short>*>(pUserData) =
        *reinterpret_cast<vector<short>*>(pReturnData);
}

static void clsFileManager_data2vint(void *&pUserData, void *pReturnData)
{
    *reinterpret_cast<vector<int>*>(pUserData) =
        *reinterpret_cast<vector<int>*>(pReturnData);
}

static void clsFileManager_data2vfloat(void *&pUserData, void *pReturnData)
{
    *reinterpret_cast<vector<float>*>(pUserData) =
        *reinterpret_cast<vector<float>*>(pReturnData);
}

static void clsFileManager_data2vdouble(void *&pUserData, void *pReturnData)
{
    *reinterpret_cast<vector<double>*>(pUserData) =
        *reinterpret_cast<vector<double>*>(pReturnData);
}

static void clsFileManager_data2vstring(void *&pUserData, void *pReturnData)
{
    *reinterpret_cast<vector<string>*>(pUserData) =
        *reinterpret_cast<vector<string>*>(pReturnData);
}

typedef struct tag_Cls_stuMDCmd
{
    int intFunc;
    clsFileManager_datafunc *lpFunc;
} clsFileManager_stuMDCmd, *Cls_lpstuMDCmd;

static const clsFileManager_stuMDCmd Cls_stuFMCmd[] =
{
    { clsFileManager_intDataType_String, &clsFileManager_data2string },
    { clsFileManager_intDataType_ShortArray, &clsFileManager_data2vshort },
    { clsFileManager_intDataType_IntegerArray, &clsFileManager_data2vint },
    { clsFileManager_GetIndexList, &clsFileManager_data2vint },
    { clsFileManager_GetSizeList, &clsFileManager_data2vint },
    { clsFileManager_GetTypeList, &clsFileManager_data2vint },
    { clsFileManager_GetTypeTotalNoList, &clsFileManager_data2vint },
    { clsFileManager_intDataType_FloatArray, &clsFileManager_data2vfloat },
    { clsFileManager_intDataType_DoubleArray, &clsFileManager_data2vdouble },
    { clsFileManager_intDataType_CurrencyArray, &clsFileManager_data2vdouble },
    { clsFileManager_intDataType_DateArray, &clsFileManager_data2vdouble },
    { clsFileManager_intDataType_StringArray, &clsFileManager_data2vstring },
    { clsFileManager_GetNameList, &clsFileManager_data2vstring },
};

static map<int, clsFileManager_stuMDCmd> Cls_stuFMCmdMap;
static void clsFileManager_CmdMapInit()
{
    for (unsigned int i = 0; i < sizeof(Cls_stuFMCmd) / sizeof(clsFileManager_stuMDCmd); i++)
    {
        (void)Cls_stuFMCmdMap.insert(make_pair(Cls_stuFMCmd[i].intFunc, Cls_stuFMCmd[i]));
    }
}
