## Qt Test 

Qt Test提供了对Qt应用程序和库进行单元测试的类。所有公共方法都在QTest名称空间中。另外，QSignalSpy类为Qt的信号和槽提供了简单的自省，而QAbstractItemModelTester允许对项目模型进行非破坏性测试。

注意:Qt测试模块没有二进制兼容性保证。这意味着使用Qt测试的应用程序只能使用它所开发的Qt版本。但是，源代码的兼容性是有保证的。

## 文章和指南

#### Qt Test Overview(概述)

Qt测试是对基于Qt的应用程序和库进行单元测试的框架。Qt Test提供了单元测试框架中常见的所有功能，以及用于测试图形用户界面的扩展。

Qt测试是为了方便编写基于Qt的应用程序和库的单元测试:

| 功能 | 细节 |
|--|--|
| Lightweight(轻量级) | Qt测试由大约6000行代码和60个导出符号组成。 |
| Self-contained(自包含) | 对于非gui测试，Qt测试只需要Qt Core模块中的几个符号。 |
| Rapid testing(快速测试) | Qt测试不需要特殊的测试运行程序;无需为测试进行特别登记。 |
| Data-driven testing(数据驱动测试) | 可以使用不同的测试数据多次执行测试。 |
| Basic GUI testing(基本GUI测试) | Qt测试提供了鼠标和键盘模拟功能。 |
| Benchmarking(基准) | Qt测试支持基准测试，并提供多个测量后端。 |
| IDE friendly(IDE友好) | Qt测试输出的消息可以由Qt Creator、Visual Studio和KDevelop解释。 |
| Thread-safety(线程安全性) | 错误报告是线程安全和原子性的。 |
| Type-safety(类型安全) | 模板的广泛使用可以防止隐式类型转换带来的错误。 |
| Easily extendable(容易扩展) | 可以很容易地将自定义类型添加到测试数据和测试输出中。 |


* Qt Test Best Practices(最佳实践)
* Qt Test Tutorial(教程)


## 参考


* Qt Test C++ Classes

Qt Quick测试模块支持对Qt Quick应用程序进行单元测试。

* Qt Quick Test QML Types
* Qt Quick Test C++ API 

