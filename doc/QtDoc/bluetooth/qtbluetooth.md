## Qt Bluetooth

### 概述

蓝牙是一种短距离（小于100米）的无线技术。它具有2.1 Mbit / s的相当高的数据传输速率，非常适合在设备之间传输数据。蓝牙连接基于基本的设备管理，例如扫描设备，收集有关设备的信息以及在设备之间交换数据。

Qt蓝牙支持针对客户端/中央角色用例的蓝牙低功耗开发。可以在“蓝牙低功耗概述”部分中找到更多详细信息。

自Qt Bluetooth 5.7版本以来的新增功能包括对执行外围设备/服务器角色的Bluetooth Low Energy应用程序的支持。此新API仍保留在Technology Preview中。

QtVersion : Qt5.14

Qt Bluetooth 蓝牙API提供了支持蓝牙的设备之间的连接。

平台支持情况:

| API功能 | android | ios | linux(blueZ 4.x/5.x) | macOS | UWP(Universal Windows Platform) | Win32 |
|----|----|----|----|----|----|----|
| Classic Bluetooth(经典蓝牙) | yes || yes | yes | yes | yes |
| Bluetooth LE Central(中心设备) | yes | yes | yes | yes | yes | yes |
| Bluetooth LE Peripheral(周边设备) | yes | yes | yes | yes |||
| Bluetooth LE Advertisement & Scanning(广告和扫描) |||||||

Qt 5.14添加了本机Win32端口，在Windows 7或更高版本上支持经典蓝牙，在Windows 8或更高版本上支持Bluetooth LE。必须在构建时通过配置选项-native-win32-bluetooth启用它。如果未设置此选项并且Win32目标平台支持所需的UWP API（默认要求是Windows 10版本1507，自Windows 10版本1607起服务发现有所改进），则默认情况下使用UWP后端。

### 入门

要在您的应用程序中使用C ++库，请在.pro文件中添加以下配置选项：

```
QT += bluetooth
```

要在应用程序中使用模块的类，您需要在.qml文件中使用以下import语句：

```
import QtBluetooth 5.12
```

### 相关信息

Building Qt Bluetooth

尽管可以为所有Qt平台构建该模块，但该模块并未移植到所有Qt平台。不支持的平台使用伪造或伪造的后端，当不支持该平台时会自动选择该后端。虚拟后端报告适当的错误消息和值，这些错误消息和值使Qt Bluetooth开发人员可以在运行时检测到不支持当前平台。如果在构建期间未找到BlueZ开发头，或者在没有Qt D-Bus支持的情况下构建了Qt，则在Linux上也将选择虚拟后端。

在构建和运行时，将通过适当的警告突出显示虚拟后端的用法。

### 日志类别

该QtBluetooth模块导出以下日志类别:

| 记录类别 | 描述 |
|----|----|
| qt.bluetooth | 在QtBluetooth中启用跨平台代码路径的日志 |
| qt.bluetooth.android | 启用Android实现的日志记录 |
| qt.bluetooth.bluez | 启用BLuez / Linux实现的日志记录 |
| qt.bluetooth.ios | 启用iOS实现的日志记录 |
| qt.bluetooth.osx | 启用macOS实施的日志记录 |
| qt.bluetooth.qml | 启用QtBluetooth QML实现的日志记录 |
| qt.bluetooth.winrt | 启用UWP（通用Windows平台）实现的日志记录 |
| qt.bluetooth.windows | 启用Win32实现的日志记录 |

日志记录类别可用于为QtBluetooth启用其他警告和调试输出。可以在QLoggingCategory中找到有关日志记录的更多详细信息。启用所有QtBluetooth日志记录的快速方法是在main()函数中添加以下行：

```
QLoggingCategory::setFilterRules(QStringLiteral("qt.bluetooth* = true"));
```