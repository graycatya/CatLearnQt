第1章:编写单元测试

如何编写单元测试。
在第一章中，我们将看到如何为一个类编写一个简单的单元测试，以及如何执行它。


### 编写一个测试

假设您想要测试QString类的行为。首先，您需要一个包含测试函数的类。这个类必须继承QObject:

```
//testqstring.cpp
#include <QtTest/QtTest>


class TestQString : public QObject
{
    Q_OBJECT
private slots:
    void toUpper();
};

void TestQString::toUpper()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
    QVERIFY(str.toUpper() == "HELLO");
}

QTEST_MAIN(TestQString)
#include "testqstring.moc"
```

注意:您需要包含QTest头，并将测试函数声明为私有槽，以便测试框架查找并执行它。

然后您需要实现测试函数本身。实现可以是这样的:

```
void TestQString::toUpper()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}
```


QVERIFY()宏计算作为参数传递的表达式。如果表达式的计算结果为true，则继续执行测试函数。否则，一个描述失败的消息被附加到测试日志中，并且测试函数停止执行。

但是如果你想要一个更详细的输出到测试日志，你应该使用QCOMPARE()宏代替:

```
  void TestQString::toUpper()
  {
      QString str = "Hello";
      QVERIFY(str.toUpper() == "HELLO");
  }
```

如果字符串不相等，两个字符串的内容被附加到测试日志中，使它立即显示出比较失败的原因。

最后，要使我们的测试用例成为独立的可执行文件，需要以下两行代码:

```
QTEST_MAIN(TestQString)
#include "testqstring.moc"
```

QTEST_MAIN()宏扩展为一个简单的main()方法，该方法运行所有测试函数。注意，如果我们的测试类的声明和实现都在.cpp文件中，我们还需要包括生成的moc文件，以使Qt的自省工作。

### 执行一个测试

现在我们已经完成了测试的编写，我们想要执行它。假设我们的测试被保存为testqstring.cpp在一个空目录中，我们使用qmake构建测试来创建一个项目并生成一个makefile。

```
/myTestDirectory$ qmake -project "QT += testlib"
/myTestDirectory$ qmake
/myTestDirectory$ make
```

注意:如果您使用的是windows，请将make替换为nmake或任何您使用的构建工具。

### 测试输出内容

运行结果的可执行文件应该给你以下输出:

```
********* Start testing of TestQString *********
Config: Using QtTest library 5.14.0, Qt 5.14.0 (i386-little_endian-ilp32 shared (dynamic) debug build; by MSVC 2017)
PASS   : TestQString::initTestCase()
PASS   : TestQString::toUpper()
PASS   : TestQString::cleanupTestCase()
Totals: 3 passed, 0 failed, 0 skipped, 0 blacklisted, 1ms
********* Finished testing of TestQString *********
```