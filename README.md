
![](https://github.com/zhengtianzuo/Camel_FileManagerCExamples/blob/master/Camel_FileManagerCExamples.jpg?raw=true)

# Camel_FileManagerCExamples
 Camel_FileManagerC相关的技术分享

访问博客[CSDN博客](http://blog.csdn.net/zhengtianzuo06)

![](https://img.shields.io/badge/%E7%89%88%E6%9D%83%E8%AE%B8%E5%8F%AF-MIT-orange.svg)
![](https://img.shields.io/badge/Qt-5.9-blue.svg)
![](https://img.shields.io/badge/VS-2015-blue.svg)
![](https://img.shields.io/badge/QtQuick-2.0-blue.svg)
![](https://img.shields.io/badge/Camel_FileManagerC-1.0.0.0-blue.svg)
![](https://img.shields.io/badge/%E7%89%88%E6%9C%AC-1.0.0.0-blue.svg)
![](https://img.shields.io/badge/%E7%BC%96%E8%AF%91-%E6%88%90%E5%8A%9F-brightgreen.svg)

***
#### 组件介绍:
***
###### Camel_CrashReport:
程序异常崩溃时生成Dump文件和日志, **非开源** 属于CamelSoft系列基础开发组件.

Dump文件是进程的内存镜像。可以把程序的执行状态通过调试器保存到dump文件中。

支持平台：Windows
***
###### Camel_FileManagerC:
自主研发的分布式数据存储中间件, **非开源** 属于CamelSoft系列基础开发组件.

作用： 可用于文件打包，数据整合，加密存放等多种用途。可以方便快捷的搭建和部署基于分布式存储应用的云端系统, 轻松实现跨区域分布式存储系统.

特点：
1. 可读取数据库中的图片在内存中直接进行加载，无需存盘。
2. 可读取数据库中的音频文件在内存中直接进行播放，无需存盘。
3. 存放文件可自由选择压缩。
4. 可将C++类，结构体，数据流等按照二进制数据方式存储和读取。

加密与压缩方式：修改过的256位AES算法加密，修改过的zlib算法压缩。

维护方式：定期对数据库进行压缩，以整合频繁使用所产生的碎片空间。

支持平台：Windows/Android/IOS/MacOS/Linux





***
CamelCrashReportTest: 崩溃报告开发组件测试程序

![](https://github.com/zhengtianzuo/Camel_FileManagerCExamples/blob/master/CamelCrashReportTest/show.jpg?raw=true)

![](https://github.com/zhengtianzuo/Camel_FileManagerCExamples/blob/master/CamelCrashReportTest/show1.jpg?raw=true)
异常崩溃时生成的dump文件, 在VisualStudio下调试直接定位到代码行, 当然也可以使用WinDbg调试

***

计划加入的工程:
1. CamelFileManagerCTest: 文件管理开发组件测试程序
2. DataManager: CamelFileManagerC数据库的可视化开发工具
3. QmlSkins: Qml全局动态换肤
4. SilkConfig: Silk配置管理程序
