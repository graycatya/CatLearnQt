第5章:编写基准测试

如何编写基准测试。

在最后一章，我们将演示如何使用Qt测试编写基准测试。

### 基准测试

为了创建基准测试，我们使用QBENCHMARK宏扩展了测试函数。基准测试函数通常由设置代码和QBENCHMARK宏组成，该宏包含要测量的代码。这个测试函数对QString::localeAwareCompare()进行基准测试。

```
// benchmarking.cpp
#include <QtWidgets>
#include <qtest.h>

class TestBenchmark : public QObject
{
    Q_OBJECT

private slots:
    void simple();
    void multiple_data();
    void multiple();
    void series_data();
    void series();


};

void TestBenchmark::simple()
{
    QString str1 = QLatin1String("This is a test string");
    QString str2 = QLatin1String("This is a test string");

    QCOMPARE(str1.localeAwareCompare(str2), 0);

    QBENCHMARK {
        str1.localeAwareCompare(str2);
    }
}

void TestBenchmark::multiple_data()
{
    QTest::addColumn<bool>("useLocaleCompare");
    QTest::newRow("locale aware compare") << true;
    QTest::newRow("standard compare") << false;
}

void TestBenchmark::multiple()
{
    QFETCH(bool, useLocaleCompare);
    QString str1 = QLatin1String("This is a test string");
    QString str2 = QLatin1String("This is a test string");

    int result;
    if(useLocaleCompare)
    {
        QBENCHMARK {
            result = str1.localeAwareCompare(str2);
        }
    } else {
        QBENCHMARK {
            result = (str1 == str2);
        }
    }

    Q_UNUSED(result);
}

void TestBenchmark::series_data()
{
    QTest::addColumn<bool>("useLocaleCompare");
    QTest::addColumn<int>("stringSize");

    for(int i = 1; i < 10000; i += 2000)
    {
        QByteArray size = QByteArray::number(i);
        QTest::newRow(("locale aware compare--" + size).constData()) << true << i;
        QTest::newRow(("standard compare--" + size).constData()) << false << i;
    }
}

void TestBenchmark::series()
{
    QFETCH(bool, useLocaleCompare);
    QFETCH(int, stringSize);

    QString str1 = QString().fill('A', stringSize);
    QString str2 = QString().fill('A', stringSize);
    int result;
    if(useLocaleCompare) {
        QBENCHMARK {
            result = str1.localeAwareCompare(str2);
        }
    } else {
        QBENCHMARK {
            result = (str1 == str2);
        }
    }

    Q_UNUSED(result);
}


QTEST_MAIN(TestBenchmark)
#include "benchmarking.moc"
```


### 解答

```
void TestBenchmark::simple()
{
    QString str1 = QLatin1String("This is a test string");
    QString str2 = QLatin1String("This is a test string");

    QCOMPARE(str1.localeAwareCompare(str2), 0);

    QBENCHMARK {
        str1.localeAwareCompare(str2);
    }
}
```

设置可以在函数开始时完成，此时时钟不运行。QBENCHMARK宏中的代码将被测量，为了得到准确的测量结果，可能会重复几次。

有几个后端可用:

* Walltime
* CPU tick counter
* Event Counter
* Valgrind Callgrind
* Linux Perf

### 数据功能

数据函数对于创建比较多个数据输入的基准测试非常有用，例如支持语言环境的比较和标准的比较。

```
void TestBenchmark::multiple_data()
{
    QTest::addColumn<bool>("useLocaleCompare");
    QTest::newRow("locale aware compare") << true;
    QTest::newRow("standard compare") << false;
}
```

测试函数然后使用这些数据来确定要进行基准测试的内容。

```
void TestBenchmark::multiple()
{
    QFETCH(bool, useLocaleCompare);
    QString str1 = QLatin1String("This is a test string");
    QString str2 = QLatin1String("This is a test string");

    int result;
    if(useLocaleCompare)
    {
        QBENCHMARK {
            result = str1.localeAwareCompare(str2);
        }
    } else {
        QBENCHMARK {
            result = (str1 == str2);
        }
    }

    Q_UNUSED(result);
}
```

“if (useLocaleCompare)”开关被放置在QBENCHMARK宏之外，以避免测量其开销。每个基准测试函数可以有一个活动的QBENCHMARK宏。


### 测试模拟数据

```
********* Start testing of TestBenchmark *********
Config: Using QtTest library 5.14.0, Qt 5.14.0 (i386-little_endian-ilp32 shared (dynamic) debug build; by MSVC 2017)
PASS   : TestBenchmark::initTestCase()
PASS   : TestBenchmark::simple()
RESULT : TestBenchmark::simple():
     0.0021 msecs per iteration (total: 70, iterations: 32768)
PASS   : TestBenchmark::multiple(locale aware compare)
RESULT : TestBenchmark::multiple():"locale aware compare":
     0.0014 msecs per iteration (total: 94, iterations: 65536)
PASS   : TestBenchmark::multiple(standard compare)
RESULT : TestBenchmark::multiple():"standard compare":
     0.00010 msecs per iteration (total: 54, iterations: 524288)
PASS   : TestBenchmark::series(locale aware compare--1)
RESULT : TestBenchmark::series():"locale aware compare--1":
     0.0011 msecs per iteration (total: 76, iterations: 65536)
PASS   : TestBenchmark::series(standard compare--1)
RESULT : TestBenchmark::series():"standard compare--1":
     0.000088 msecs per iteration (total: 93, iterations: 1048576)
PASS   : TestBenchmark::series(locale aware compare--2001)
RESULT : TestBenchmark::series():"locale aware compare--2001":
     0.024 msecs per iteration (total: 51, iterations: 2048)
PASS   : TestBenchmark::series(standard compare--2001)
RESULT : TestBenchmark::series():"standard compare--2001":
     0.00094 msecs per iteration (total: 62, iterations: 65536)
PASS   : TestBenchmark::series(locale aware compare--4001)
RESULT : TestBenchmark::series():"locale aware compare--4001":
     0.0493 msecs per iteration (total: 101, iterations: 2048)
PASS   : TestBenchmark::series(standard compare--4001)
RESULT : TestBenchmark::series():"standard compare--4001":
     0.0018 msecs per iteration (total: 60, iterations: 32768)
PASS   : TestBenchmark::series(locale aware compare--6001)
RESULT : TestBenchmark::series():"locale aware compare--6001":
     0.073 msecs per iteration (total: 75, iterations: 1024)
PASS   : TestBenchmark::series(standard compare--6001)
RESULT : TestBenchmark::series():"standard compare--6001":
     0.0027 msecs per iteration (total: 90, iterations: 32768)
PASS   : TestBenchmark::series(locale aware compare--8001)
RESULT : TestBenchmark::series():"locale aware compare--8001":
     0.096 msecs per iteration (total: 99, iterations: 1024)
PASS   : TestBenchmark::series(standard compare--8001)
RESULT : TestBenchmark::series():"standard compare--8001":
     0.0035 msecs per iteration (total: 58, iterations: 16384)
PASS   : TestBenchmark::cleanupTestCase()
Totals: 15 passed, 0 failed, 0 skipped, 0 blacklisted, 3976ms
********* Finished testing of TestBenchmark *********
```


### 外部工具

用于处理和可视化测试数据的工具是qtestlib-tools项目的一部分。其中包括用于比较从测试运行中获得的性能数据的工具，以及用于生成基于web的性能数据图的实用程序。

有关这些工具的更多信息和一个简单的图形示例，请参阅qtestlib工具声明。