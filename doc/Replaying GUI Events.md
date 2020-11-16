第四章:回放GUI事件


如何回放GUI事件。

在本章中，我们将展示如何模拟GUI事件，以及如何存储一系列GUI事件以及在小部件上重放它们。

存储一系列事件并回放它们的方法与第2章中解释的方法非常相似。你所需要做的就是添加一个数据函数到你的测试类:

```
// testgui.cpp
#include <QtWidgets>
#include <QtTest/QtTest>

class TestGui : public QObject
{
    Q_OBJECT

private slots:
    void testGui_data();
    void testGui();

};

void TestGui::testGui_data()
{
    QTest::addColumn<QTestEventList>("events");
    QTest::addColumn<QString>("expected");

    QTestEventList list1;
    list1.addKeyClick('a');
    QTest::newRow("char") << list1 << "a";

    QTestEventList list2;
    list2.addKeyClick('a');
    list2.addKeyClick(Qt::Key_Backspace);
    QTest::newRow("there and back again") << list2 << "";
}

void TestGui::testGui()
{
    QFETCH(QTestEventList, events);
    QFETCH(QString, expected);

    QLineEdit lineEdit;

    events.simulate(&lineEdit);

    QCOMPARE(lineEdit.text(), expected);
}

QTEST_MAIN(TestGui)
#include "testgui.moc"
```


### 写入数据函数

与前面一样，测试函数的关联数据函数具有相同的名称，后面加上_data。

```
void TestGui::testGui_data()
{
    QTest::addColumn<QTestEventList>("events");
    QTest::addColumn<QString>("expected");

    QTestEventList list1;
    list1.addKeyClick('a');
    QTest::newRow("char") << list1 << "a";

    QTestEventList list2;
    list2.addKeyClick('a');
    list2.addKeyClick(Qt::Key_Backspace);
    QTest::newRow("there and back again") << list2 << "";
}
```

首先，我们使用QTest::addColumn()函数定义表的元素:GUI事件列表，以及在QWidget上应用事件列表的预期结果。注意，第一个元素的类型是QTestEventList。

QTestEventList可以用GUI事件填充，这些事件可以存储为测试数据供以后使用，也可以在任何QWidget上回放。

在当前的数据函数中，我们创建了两个QTestEventList元素。第一个列表包含对“a”键的单击。我们使用QTestEventList::addKeyClick()函数将事件添加到列表中。然后使用QTest::newRow()函数为数据集提供一个名称，并将事件列表和预期结果流到表中。

第二个列表由两个按键组成:一个“a”和后面的“退格”。同样，我们使用QTestEventList::addKeyClick()将事件添加到列表中，使用QTest::newRow()将事件列表和预期结果放入具有关联名称的表中。


### 重写测试函数

我们的测试现在可以重写:

```
void TestGui::testGui()
{
    QFETCH(QTestEventList, events);
    QFETCH(QString, expected);

    QLineEdit lineEdit;

    events.simulate(&lineEdit);

    QCOMPARE(lineEdit.text(), expected);
}
```

TestGui:: TestGui()函数将执行两次，一次针对我们在关联的TestGui::testGui_data()函数中创建的测试数据中的每个条目。

首先，我们使用QFETCH()宏获取数据集的两个元素。QFETCH()接受两个参数:元素的数据类型和元素名称。然后，我们创建一个QLineEdit，并使用QTestEventList::simulate()函数在小部件上应用事件列表。

最后，我们使用QCOMPARE()宏检查行编辑的文本是否符合预期。

```
QTEST_MAIN(TestGui)
#include "testgui.moc"
```


QTEST_MAIN()宏扩展为一个简单的main()方法，该方法运行所有测试函数。注意，如果我们的测试类的声明和实现都在.cpp文件中，我们还需要包括生成的moc文件，以使Qt的自省工作。