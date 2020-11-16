第2章:数据驱动测试

如何创建数据驱动测试。

在本章中，我们将演示如何使用不同的测试数据多次执行测试。

到目前为止，我们已经将想要测试的数据硬编码到测试函数中。如果我们添加更多的测试数据，函数可能像这样:


```
QCOMPARE(QString("hello").toUpper(), QString("HELLO"));
QCOMPARE(QString("Hello").toUpper(), QString("HELLO"));
QCOMPARE(QString("HellO").toUpper(), QString("HELLO"));
QCOMPARE(QString("HELLO").toUpper(), QString("HELLO"));
```

为了防止函数因为重复的代码而变得混乱，Qt Test支持向测试函数添加测试数据。我们所需要的是添加另一个私有槽到我们的测试类:

```
#include <QtTest/QtTest>


class TestQString : public QObject
{
    Q_OBJECT
private slots:
    void toUpper();
    void toUpper_data();
};

void TestQString::toUpper()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
    QVERIFY(str.toUpper() == "HELLO");

    QFETCH(QString, string);
    QFETCH(QString, result);

    QCOMPARE(string.toUpper(), result);
}

void TestQString::toUpper_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("result");

    QTest::newRow("all lower") << "hello" << "HELLO";
    QTest::newRow("mixed") << "Hello" << "HELLO";
    QTest::newRow("all upper") << "HELLO" << "HELLO";
}

QTEST_MAIN(TestQString)
#include "testqstring.moc"
```


### 写入数据函数

测试函数的关联数据函数具有相同的名称，后面加上_data。我们的数据函数是这样的:

```
void TestQString::toUpper_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("result");

    QTest::newRow("all lower") << "hello" << "HELLO";
    QTest::newRow("mixed")     << "Hello" << "HELLO";
    QTest::newRow("all upper") << "HELLO" << "HELLO";
}
```

首先，我们使用QTest::addColumn()函数定义测试表的两个元素:一个测试字符串，以及将QString::toUpper()函数应用到该字符串的预期结果。

然后使用QTest::newRow()函数向表中添加一些数据。每一组数据将成为测试表中的单独一行。

QTest::newRow()接受一个参数:一个将与数据集相关联的名称，并在测试日志中用于识别数据集。然后我们将数据集流进新表行。首先是一个任意字符串，然后是对该字符串应用QString::toUpper()函数的预期结果。

您可以将测试数据视为一个二维表。在我们的例子中，它有两个列，称为string和result，以及三行。此外，每一行都有一个名称和一个索引:

| index | name | string | result |
|--|--|--|--|
| 0 | all lower | "hello" | HELLO |
| 1 | mixed | "Hello" | HELLO |
| 2 | all upper | "HELLO" | HELLO |

当数据流到行中时，断言每个数据以匹配它提供值的列的类型。如果任何断言失败，测试将中止。

### 重写测试函数

我们的测试函数现在可以重写:

```
void TestQString::toUpper()
{
    QFETCH(QString, string);
    QFETCH(QString, result);

    QCOMPARE(string.toUpper(), result);
}
```

TestQString::toUpper()函数将执行三次，一次针对我们在关联的TestQString::toUpper_data()函数中创建的测试表中的每个条目。

首先，我们使用QFETCH()宏获取数据集的两个元素。QFETCH()接受两个参数:元素的数据类型和元素名称。然后使用QCOMPARE()宏执行测试。

这种方法使得在不修改测试本身的情况下向测试添加新数据变得非常容易。


同样，要使我们的测试用例成为一个独立的可执行文件，需要以下两行代码:

```
QTEST_MAIN(TestQString)
#include "testqstring.moc"
```

与前面一样，QTEST_MAIN()宏扩展为一个简单的main()方法，它运行所有测试函数，而且由于测试类的声明和实现都在.cpp文件中，所以我们还需要包括生成的moc文件，以使Qt的自检工作。