Log version: CatLog_Sington 1.0.0.0
=======

[![Build Status](https://travis-ci.org/graycatya/Log.svg?branch=master)](https://travis-ci.org/graycatya/Log)

* 轻量级C++ Log模块
* 单例模式+多生产者-单消费者模型
* 支持线程安全
* 内部提供打印模块实现(该模块支持在Qt中使用)
* 内部提供写文件模块该模块可将日志写入文件(支持线程安全,多文件写日志)
* 日志模块内部提供Log数据头实现(获取时间,文件路径,函数名,触发日志所在行)

Requirements
=======

* C++11 新特性

目录结构
======= 

```
.
├── CatLog
│   ├── CatLog_Message.hpp
│   ├── CatLog_Sington.cpp
│   ├── CatLog_Sington.h
│   └── CMakeLists.txt
├── README.md
└── Test
    ├── CMakeLists.txt
    └── test.cpp
```
1.  CatLog文件夹为日志模块实现

```
#Linux下生成库文件(会生成Lib目录)
cmake .
make -j2

#windows下生成库文件(会生成Lib目录)
cmake -G "MinGW Makefile"
make -j2
```

2. Test为案例代码
```
#Linux下生成库文件(会生成Bin目录)
cmake .
make -j2

#windows下生成库文件(会生成Bin目录)
cmake -G "MinGW Makefile"
make -j2
```

Example
======

```
//声明CatLog对象
CatLog::Instance();

//lambda + 线程使用方式
std::thread thread_test_0([]{
    for(int i = 0; i < NUM; i++)
    {
        //在线程中将日志写入文件中
        CATLOG::__Write_Log("./test0",__DEBUG_LOG("log: " + std::to_string(i)));
    }
});
thread_test_0.join();

//在程序结束时需要释放CatLog日志模块避免造成内存泄漏
CatLog::Delete();

```

