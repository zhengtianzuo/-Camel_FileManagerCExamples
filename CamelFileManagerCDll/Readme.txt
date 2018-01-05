Camel_FileManagerC: 基于分布式文件存储的NoSql数据库

自主研发的分布式数据存储中间件, 非开源 属于CamelSoft系列基础开发组件.

作用： 可用于文件打包，数据整合，加密存放等多种用途。可以方便快捷的搭建和部署基于分布式存储应用的云端系统, 轻松实现跨区域分布式存储系统.

特点：

可读取数据库中的图片在内存中直接进行加载，无需存盘。
可读取数据库中的音频文件在内存中直接进行播放，无需存盘。
存放文件可自由选择压缩。
可将C++类，结构体，数据流等按照二进制数据方式存储和读取。
加密与压缩方式：修改过的256位AES算法加密，修改过的zlib算法压缩。

维护方式：定期对数据库进行压缩，以整合频繁使用所产生的碎片空间。

支持平台：Windows/Android/IOS/MacOS/Linux

编译环境:

Windows:
Visual Studio 2017 15.5.2 Visual C++ 2017 14.11.25325

Android:
android-ndk-r15c

IOS:
Apple LLVM version 7.3.0 (clang-703.0.31)

Ubuntu:
gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.5)

Mac:
Apple LLVM version 7.3.0 (clang-703.0.31)
