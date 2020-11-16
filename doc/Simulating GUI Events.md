## 第三章:模拟GUI事件

如何模拟GUI事件。

Qt测试提供了一些测试图形用户界面的机制。Qt Test不模拟本机窗口系统事件，而是发送内部Qt事件。这意味着在运行测试的机器上没有副作用。

在本章中，我们将看到如何编写一个简单的GUI测试。

### 编写GUI测试

这一次，假设您想要测试QLineEdit类的行为。和以前一样，你需要一个包含测试函数的类:


```
// testgui.cpp
#include <QtWidgets>
#include <QtTest/QtTest>


class TestGui : public QObject
{
    Q_OBJECT

private slots:
    void testGui();

};

void TestGui::testGui()
{
    QLineEdit lineEdit;

    QTest::keyClicks(&lineEdit, "hello world");

    QCOMPARE(lineEdit.text(), QString("hello world"));
}

QTEST_MAIN(TestGui)
#include "testgui.moc"
```

惟一的区别是，除了QTest名称空间之外，还需要包括Qt GUI类定义。

```
void TestGui::testGui()
{
    QLineEdit lineEdit;

    QTest::keyClicks(&lineEdit, "hello world");

    QCOMPARE(lineEdit.text(), QString("hello world"));
}
```

在测试函数的实现中，我们首先创建一个QLineEdit。然后，我们模拟使用QTest::keyClicks()函数在行编辑中编写“hello world”。

注意:为了正确地测试键盘快捷键，还必须显示小部件。

QTest::keyClicks()模拟在小部件上单击一系列键。可选地，可以指定键盘修饰符以及在每次键单击后测试的延迟(毫秒)。以类似的方式，您可以使用QTest::keyClick()、QTest::keyPress()、QTest::keyRelease()、QTest::mouseClick()、QTest::mouseDClick()、QTest::mouseMove()、QTest::mousePress()和QTest::mouseRelease()函数来模拟相关的GUI事件。

最后，我们使用QCOMPARE()宏检查行编辑的文本是否符合预期。

和以前一样，要使我们的测试用例成为一个独立的可执行文件，需要以下两行代码:

```
QTEST_MAIN(TestGui)
#include "testgui.moc"
```


QTEST_MAIN()宏扩展为一个简单的main()方法，该方法运行所有测试函数。注意，如果我们的测试类的声明和实现都在.cpp文件中，我们还需要包括生成的moc文件，以使Qt的自省工作。