/*!
 *@file Camel_CrashReport.h
 *@brief 崩溃报告 开发组件
 *@version 1.0
 *@author 郑天佐
 *@date 2014-5-17
*/
#pragma once

//!@enum 返回错误码分析
enum CrashReport_eumErrorCode
{
    clsCrashReport_intErrorCode_Success    =           0x00000001,         //!<正确的值
    clsCrashReport_intErrorCode_NoRights   =           0x00000002,         //!<效验未通过
    clsCrashReport_intErrorCode_UserExit   =           0x00000099          //!<自行退出
};

//!@enum 异常运行参数
enum CrashReport_eumParam
{
    clsCrashReport_intParam_Normal          =           0x00000001,         //!<正常操作
    clsCrashReport_intParam_NoMiniDump      =           0x00000002,         //!<不写入MiniDump
    clsCrashReport_intParam_NoLog           =           0x00000003,         //!<不写入Log
    clsCrashReport_intParam_None            =           0x00000004          //!<不写入MiniDump和Log
};

//!@brief 导出函数定义
#ifdef Camel_CrashReport_dllexport
#define Camel_CrashReport_LIB __declspec(dllexport)
#else
#define Camel_CrashReport_LIB __declspec(dllimport)

typedef int (*lpCls_funCrashReportInitialize)(void);
typedef int (*lpCls_funCrashReportTerminate)(void);
typedef int (*lpCls_funGetException)(PEXCEPTION_POINTERS const pExceptPtrs, WORD const srtParam);
#endif

/*!
 *@name Cls_funCrashReportInitialize
 *@brief 组件初始化
 *@param[in] 无
 *@return int
 *@see ::CrashReport_eumErrorCode
 *@author 郑天佐
 *@date 2014-5-17
*/
extern "C" Camel_CrashReport_LIB int Cls_funCrashReportInitialize(void);

/*!
 *@name Cls_funCrashReportTerminate
 *@brief 组件销毁
 *@param[in] 无
 *@return int
 *@see ::CrashReport_eumErrorCode
 *@author 郑天佐
 *@date 2014-5-17
*/
extern "C" Camel_CrashReport_LIB int Cls_funCrashReportTerminate(void);

/*!
 *@name Cls_funGetException
 *@brief 获取异常信息
 *@param[in] pExceptPtrs 异常信息
 *@param[in] srtParam 异常运行参数
 *@see ::CrashReport_eumParam
 *@return int
 *@see ::CrashReport_eumErrorCode
 *@author 郑天佐
 *@date 2014-5-17
*/
extern "C" Camel_CrashReport_LIB int Cls_funGetException(PEXCEPTION_POINTERS pExceptPtrs, WORD srtParam);

#undef Camel_CrashReport_LIB
