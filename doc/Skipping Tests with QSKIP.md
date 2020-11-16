第6章:使用QSKIP跳过测试

### 在测试函数中使用QSKIP(description)

如果从测试函数中调用QSKIP()宏，它将停止测试的执行，而不会向测试日志中添加失败。它可用于跳过肯定会失败的测试。QSKIP描述参数中的文本被附加到测试日志中，并解释为什么测试没有被执行。

QSKIP可用于在实现尚未完成或在某个平台上不受支持时跳过测试。当存在已知的失败时，建议使用QEXPECT_FAIL，以便始终完全执行测试。

测试函数中的QSKIP示例:

```
if ( tst_Databases::getMySqlVersion( db )
    .section( QChar('.'), 0, 0 ).toInt()<5 )
{
    QSKIP( "Test requires MySQL >= 5.0");
}
```

在数据驱动的测试中，每次对QSKIP()的调用只跳过测试数据的当前行。如果数据驱动的测试包含对QSKIP的无条件调用，它将为每一行测试数据生成一个跳过消息。


### 在数据函数中使用QSKIP

如果从_data函数调用，QSKIP()宏将停止_data函数的执行。这会阻止相关测试函数的执行。

下面是一个例子:

```
  void tst_Skip::test_data()
  {
      QTest::addColumn<bool>("bool");
      QTest::newRow("local 1") << false;
      QTest::newRow("local 2") << true;

      QSKIP("skipping all");
  }
```

### 从initTestCase()或initTestCase_data()使用QSKIP

如果从initTestCase()或initTestCase_data()调用，QSKIP()宏将跳过所有test和_data函数。