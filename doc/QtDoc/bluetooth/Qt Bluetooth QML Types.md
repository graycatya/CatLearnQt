## Qt Bluetooth QML Types

Qt蓝牙QML类型使应用程序能够以比C ++类更简单的方式扫描设备并进行连接和交互。但是，它比C ++ API有更多限制。您始终可以使用C ++ API以所需的灵活性来创建QML插件。

要在应用程序中使用模块的类，您需要在.qml文件中使用以下import语句：

```js
import QtBluetooth 5.14
```

| 类名 | 描述 |
|----|----|
| BluetoothDiscoveryModel | 可以搜索范围内的蓝牙设备和服务 |
| BluetoothService | 提供有关特定蓝牙服务的信息 |
| BluetoothSocket | 启用与蓝牙服务或设备的连接并与之通信 |