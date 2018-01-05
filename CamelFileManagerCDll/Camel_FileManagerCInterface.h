/*!
 *@file Camel_FileManagerCInterface.h
 *@brief 文件管理开发组件接口
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author 郑天佐
 *@date 2013-4-3
*/
#pragma once

//!@brief 导出函数定义
#undef Camel_FileManagerC_LIB
#if defined (WIN32)
#define Camel_FileManagerC_ATR
#if defined (Camel_FileManagerC_dllexport)
#define Camel_FileManagerC_LIB _declspec(dllexport)
#else
#define Camel_FileManagerC_LIB _declspec(dllimport)
#endif
#else
#define Camel_FileManagerC_ATR __attribute__((visibility("default")))
#define Camel_FileManagerC_LIB
#endif
#include "Camel_FileManagerC.h"

//!@brief 参数类型定义
typedef struct tag_Cls_stuDBVerify
{
    const char *chrDBFileName;
    const char *chrPassword;
    tag_Cls_stuDBVerify(const char *pDBFileName, const char *pPassword)
    {
        chrDBFileName = pDBFileName;
        chrPassword = pPassword;
    }
} Cls_stuDBVerify, *Cls_lpstuDBVerify;

typedef struct tag_Cls_stuDataType
{
    tag_Cls_stuDataType(int nDataType, int nDataIndex, const char *cDataName)
    {
        intDataType = nDataType;
        intDataIndex = nDataIndex;
        chrDataName = cDataName;
    }

    int Sub_getDataType()
    {
        return (intDataType);
    }

    int Sub_getDataIndex()
    {
        return (intDataIndex);
    }

    const char *Sub_getDataName()
    {
        return (chrDataName);
    }

private:
    int intDataType;
    int intDataIndex;
    const char *chrDataName;
} Cls_stuDataType, *Cls_lpstuDataType;

typedef struct tag_Cls_stuUserData
{
    void *pUserData;
    int intUserSize;
    tag_Cls_stuUserData(void *userData, int nUserSize)
    {
        pUserData = userData;
        intUserSize = nUserSize;
    }
} Cls_stuUserData, *Cls_lpstuUserData;

typedef struct tag_Cls_stuGetUserData
{
    void **pUserData;
    int *intUserSize;
    tag_Cls_stuGetUserData(void *&userData, int &nUserSize)
    {
        pUserData = &userData;
        intUserSize = &nUserSize;
    }
} Cls_stuGetUserData, *Cls_lpstuGetUserData;

typedef struct tag_Cls_stuFunction
{
    void *pFunction;
    void *pContext;
    tag_Cls_stuFunction(void *fun, void *context)
    {
        pFunction = fun;
        pContext = context;
    }
} Cls_stuFunction, *Cls_lpstuFunction;

//!@class 文件管理模块类
class Camel_FileManagerC_LIB Camel_FileManagerCInt
{
public:
    Camel_FileManagerCInt() {};
    virtual ~Camel_FileManagerCInt() {};

    /*!
    *@name Cls_funManagerInitialize
    *@brief 组件初始化
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerInitialize() = 0;

    /*!
    *@name Cls_funManagerTerminate
    *@brief 组件销毁
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerTerminate() = 0;

    /*!
    *@name Cls_funManagerDB_CreateDataBase
    *@brief 创建数据库
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrDBName 数据库名称
    *@param[in] chrDBPassword 数据库密码
    *@param[in] OverWrite 是否重写
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerDB_CreateDataBase(
        Cls_lpstuDBVerify pDBVerify, const char *chrDBName, bool const OverWrite) = 0;

    /*!
    *@name Cls_funManagerDB_OpenDataBase
    *@brief 打开数据库
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerDB_OpenDataBase(
        Cls_lpstuDBVerify pDBVerify) = 0;

	/*!
	*@name Cls_funManagerDB_CloseDataBase
	*@brief 打开数据库
	*@param[in] chrDBFileName 数据库文件路径
	*@param[in] chrPassword 数据库密码
	*@return int
	*@author 郑天佐
	*@date 2013-4-3
	*/
	virtual int Cls_funManagerDB_CloseDataBase(
		Cls_lpstuDBVerify pDBVerify) = 0;

    /*!
    *@name Cls_funManagerDB_ChangePassword
    *@brief 修改密码
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] chrOldPassword 当前数据库密码
    *@param[in] chrNewPassword 新的数据库密码
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerDB_ChangePassword(
        Cls_lpstuDBVerify pDBVerify, const char *chrOldPassword, const char *chrNewPassword) = 0;

    /*!
    *@name Cls_funManagerDB_GetName
    *@brief 获取数据库名称
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[out] chrDBName 数据库名称
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerDB_GetName(
        Cls_lpstuDBVerify pDBVerify, char chrDBName[Cls_intFNameSize + 1]) = 0;

    /*!
    *@name Cls_funManagerDB_GetTotalNumber
    *@brief 获取数据库数据总数
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[out] intFileNumber 数据库数据总数
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerDB_GetTotalNumber(
        Cls_lpstuDBVerify pDBVerify, int &intFileNumber) = 0;

    /*!
    *@name Cls_funManagerDB_ReBuild
    *@brief 重建数据库
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] chrNewDBFileName 新的数据库文件路径
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerDB_ReBuild(
        Cls_lpstuDBVerify pDBVerify, const char *chrNewDBFileName) = 0;

    /*!
    *@name Cls_funManagerDB_SetName
    *@brief 设置数据库名称
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] chrDBName 数据库名称
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerDB_SetName(
        Cls_lpstuDBVerify pDBVerify, const char *chrDBName) = 0;

    /*!
    *@name Cls_funManagerDB_SetTotalNumber
    *@brief 设置数据库总数
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] intAddFileNumber 数据库总数
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerDB_SetTotalNumber(
        Cls_lpstuDBVerify pDBVerify, int const intAddFileNumber) = 0;



    /*!
    *@name Cls_funManagerData_Check
    *@brief 检测数据有效性
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] intDataType 数据类型
    *@param[in] intDataIndex 数据序号
    *@param[in] chrDataName 数据名称
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerData_Check(
        Cls_lpstuDBVerify pDBVerify, Cls_lpstuDataType pDataType) = 0;

    /*!
    *@name Cls_funManagerData_Combine
    *@brief 加入数据
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] intDataType 数据类型
    *@param[in] chrDataName 数据名称
    *@param[in] chrRemark 数据备注
    *@param[in] pUserData 数据内容指针
    *@param[in] intUserSize 数据内容大小
    *@param[in] bolCompress 是否压缩
    *@param[in] intDataIndex 数据序号
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerData_Combine(
        Cls_lpstuDBVerify pDBVerify, Cls_lpstuDataType pDataType,
        const char *chrRemark, Cls_lpstuUserData pstuUserData,
        bool const bolCompress, int const intDataIndex) = 0;

    /*!
    *@name Cls_funManagerData_Modify
    *@brief 修改数据
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] intDataType 数据类型
    *@param[in] intDataIndex 数据序号
    *@param[in] chrDataName 数据名称
    *@param[in] pUserData 数据内容指针
    *@param[in] intUserSize 数据内容大小
    *@param[in] bolCompress 是否压缩
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerData_Modify(
        Cls_lpstuDBVerify pDBVerify, Cls_lpstuDataType pDataType,
        Cls_lpstuUserData pstuUserData, bool const bolCompress) = 0;

    /*!
    *@name Cls_funManagerData_ModifyFile
    *@brief 修改文件
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] intDataType 数据类型
    *@param[in] chrDataName 数据名称
    *@param[in] chrFileName 文件路径
    *@param[in] bolCompress 是否压缩
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerData_ModifyFile(
        Cls_lpstuDBVerify pDBVerify, Cls_lpstuDataType pDataType,
        const char *chrRemark, char *chrFileName, bool const bolCompress) = 0;

    /*!
    *@name Cls_funManagerData_Extract
    *@brief 获取数据
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] intDataType 数据类型
    *@param[in] intDataIndex 数据序号
    *@param[in] chrDataName 数据名称
    *@param[in] pFunction 获取数据函数指针
    *@param[in] pContext 回调上下文
    *@param[out] pUserData 数据内容指针
    *@param[out] intUserSize 数据内容大小
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerData_Extract(
        Cls_lpstuDBVerify pDBVerify, Cls_lpstuDataType pDataType,
        Cls_lpstuFunction pstuFunction, Cls_lpstuGetUserData pstuGetUserData) = 0;

    /*!
    *@name Cls_funManagerData_ExtractBytes
    *@brief 获取数据流
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] intDataType 数据类型
    *@param[in] intDataIndex 数据序号
    *@param[in] chrDataName 数据名称
    *@param[in] pFunction 获取数据函数指针
    *@param[in] pContext 回调上下文
    *@param[out] pUserData 数据内容指针
    *@param[out] intUserSize 数据内容大小
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerData_ExtractBytes(
        Cls_lpstuDBVerify pDBVerify, Cls_lpstuDataType pDataType,
        Cls_lpstuFunction pstuFunction, Cls_lpstuGetUserData pstuGetUserData) = 0;

    /*!
    *@name Cls_funManagerData_ExtractFile
    *@brief 获取文件
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] intDataType 数据类型
    *@param[in] intDataIndex 数据序号
    *@param[in] chrDataName 数据名称
    *@param[in] chrFileName 文件路径
    *@param[out] OverWrite 是否重写
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerData_ExtractFile(
        Cls_lpstuDBVerify pDBVerify, Cls_lpstuDataType pDataType,
        char *chrFileName, bool const OverWrite) = 0;

    /*!
    *@name Cls_funManagerData_Delete
    *@brief 删除数据
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] intDataIndex 数据序号
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerData_Delete(
        Cls_lpstuDBVerify pDBVerify, Cls_lpstuDataType pDataType) = 0;

    /*!
    *@name Cls_funManagerData_GetIndex
    *@brief 获取序号
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] intDataIndex 数据序号
    *@param[in] intDataIndexCode 数据序号代码
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerData_GetIndex(
        Cls_lpstuDBVerify pDBVerify,
        Cls_lpstuDataType pDataType, int &intDataIndexCode) = 0;

    /*!
    *@name Cls_funManagerData_GetIndexList
    *@brief 获取序号列表
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] pFunction 获取数据函数指针
    *@param[in] pContext 回调上下文
    *@param[out] pUserData 数据内容指针
    *@param[out] intUserSize 数据内容大小
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerData_GetIndexList(
        Cls_lpstuDBVerify pDBVerify, Cls_lpstuFunction pstuFunction,
        Cls_lpstuUserData pstuUserData) = 0;

    /*!
    *@name Cls_funManagerData_SetIndex
    *@brief 设置序号
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] intDataIndex 数据序号
    *@param[in] intNewDataIndex 新的数据序号
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerData_SetIndex(
        Cls_lpstuDBVerify pDBVerify, Cls_lpstuDataType pDataType,
        int const intNewDataIndex) = 0;

    /*!
    *@name Cls_funManagerData_GetName
    *@brief 获取数据名称
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] intDataIndex 数据序号
    *@param[in] intNameType 名称类型
    *@param[out] chrUserName 数据名称
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerData_GetName(
        Cls_lpstuDBVerify pDBVerify, Cls_lpstuDataType pDataType,
        int const intNameType, char chrUserName[Cls_intFNameSize + 1]) = 0;

    /*!
    *@name Cls_funManagerData_ReName
    *@brief 修改数据名称
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] intDataIndex 数据序号
    *@param[in] chrNewDataName 新的数据名称
    *@param[out] chrNewRemark 新的数据备注
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerData_ReName(
        Cls_lpstuDBVerify pDBVerify, Cls_lpstuDataType pDataType,
        const char *chrNewDataName, const char *chrNewRemark) = 0;

    /*!
    *@name Cls_funManagerData_GetNameList
    *@brief 获取数据名称列表
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] intNameType 名称类型
    *@param[in] pFunction 获取数据函数指针
    *@param[in] pContext 回调上下文
    *@param[out] pUserData 数据内容指针
    *@param[out] intUserSize 数据内容大小
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerData_GetNameList(
        Cls_lpstuDBVerify pDBVerify, int const intNameType,
        Cls_lpstuFunction pstuFunction, Cls_lpstuUserData pstuUserData) = 0;

    /*!
    *@name Cls_funManagerData_GetType
    *@brief 获取数据类型
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] intDataIndex 数据序号
    *@param[out] intDataTypeCode 数据类型
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerData_GetType(
        Cls_lpstuDBVerify pDBVerify, Cls_lpstuDataType pDataType,
        int &intDataTypeCode) = 0;

    /*!
    *@name Cls_funManagerData_GetTypeList
    *@brief 获取数据类型列表
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] pFunction 获取数据函数指针
    *@param[in] pContext 回调上下文
    *@param[out] pUserData 数据内容指针
    *@param[out] intUserSize 数据内容大小
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerData_GetTypeList(
        Cls_lpstuDBVerify pDBVerify, Cls_lpstuFunction pstuFunction,
        Cls_lpstuUserData pstuUserData) = 0;

    /*!
    *@name Cls_funManagerData_GetTypeTotalNo
    *@brief 获取数据类型总数
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] intDataTypeCode 数据类型
    *@param[out] intDataTypeTotalNo 数据类型总数
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerData_GetTypeTotalNo(
        Cls_lpstuDBVerify pDBVerify, int const intDataTypeCode,
        int &intDataTypeTotalNo) = 0;

    /*!
    *@name Cls_funManagerData_GetTypeTotalNoList
    *@brief 获取数据类型总数列表
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] pFunction 获取数据函数指针
    *@param[in] pContext 回调上下文
    *@param[out] pUserData 数据内容指针
    *@param[out] intUserSize 数据内容大小
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerData_GetTypeTotalNoList(
        Cls_lpstuDBVerify pDBVerify, Cls_lpstuFunction pstuFunction,
        Cls_lpstuUserData pstuUserData) = 0;

    /*!
    *@name Cls_funManagerData_GetSize
    *@brief 获取数据大小
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] intSizeType 数据大小类型
    *@param[in] intDataIndex 数据序号
    *@param[out] intDataSize 数据大小
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerData_GetSize(
        Cls_lpstuDBVerify pDBVerify, int const intSizeType,
        Cls_lpstuDataType pDataType, int &intDataSize) = 0;

    /*!
    *@name Cls_funManagerData_GetSizeList
    *@brief 获取数据大小列表
    *@param[in] chrDBFileName 数据库文件路径
    *@param[in] chrPassword 数据库密码
    *@param[in] intSizeType 数据大小类型
    *@param[in] pFunction 获取数据函数指针
    *@param[in] pContext 回调上下文
    *@param[out] pUserData 数据内容指针
    *@param[out] intUserSize 数据内容大小
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerData_GetSizeList(
        Cls_lpstuDBVerify pDBVerify, int const intSizeType,
        Cls_lpstuFunction pstuFunction, Cls_lpstuUserData pstuUserData) = 0;
};

//!@class 文件管理接口
class Camel_FileManagerC_LIB Camel_FileManagerCInterface
{
public:
    Camel_FileManagerCInterface();
    virtual ~Camel_FileManagerCInterface();

    /*!
    *@name Cls_funInitialize
    *@brief 接口初始化
    *@param[in] 无
    *@return 模块类指针
    *@author 郑天佐
    *@date 2013-4-3
    */
    static Camel_FileManagerCInt *Cls_funInitialize();

    /*!
    *@name Cls_funTerminate
    *@brief 接口销毁
    *@param[in] pFileManagerC 模块类指针
    *@return 无
    *@author 郑天佐
    *@date 2013-4-3
    */
    static void Cls_funTerminate(Camel_FileManagerCInt *&pFileManagerC);
};

//!@class 数据管理模块类
class Camel_FileManagerC_LIB Camel_DataManagerCInt
{
public:
    Camel_DataManagerCInt() {};
    virtual ~Camel_DataManagerCInt() {};

    /*!
    *@name Cls_funManagerInitialize
    *@brief 接口初始化
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerInitialize() = 0;

    /*!
    *@name Cls_funTerminate
    *@brief 接口销毁
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int Cls_funManagerTerminate() = 0;
};

//!@class 数据管理接口
class Camel_FileManagerC_LIB Camel_DataManagerCInterface
{
public:
    Camel_DataManagerCInterface();
    virtual ~Camel_DataManagerCInterface();

    /*!
    *@name Cls_funInitialize
    *@brief 接口初始化
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-4-3
    */
    static Camel_DataManagerCInt *Cls_funInitialize();

    /*!
    *@name Cls_funTerminate
    *@brief 接口销毁
    *@param[in] pDataManagerC 模块类指针
    *@return 无
    *@author 郑天佐
    *@date 2013-4-3
    */
    static void Cls_funTerminate(Camel_DataManagerCInt *&pDataManagerC);
};
