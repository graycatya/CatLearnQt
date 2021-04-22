## Qt Bluetooth C++ Classes

启用基本的蓝牙操作，例如扫描设备并连接它们。

### 命名空间

|  |  |
|----|----|
| QBluetooth | 与蓝牙相关的类和功能 |

### 功能类

| 类名 | 描述 |
|----|----|
| QBluetoothAddress | 为蓝牙设备分配地址 |
| QBluetoothDeviceDiscoveryAgent | 发现附近的蓝牙设备 |
| QBluetoothDeviceInfo | 存储有关蓝牙设备的信息 |
| QBluetoothHostInfo | 封装本地QBluetooth设备的详细信息 |
| QBluetoothLocalDevice | 启用对本地蓝牙设备的访问 |
| QBluetoothServer | 使用RFCOMM或L2cap协议与蓝牙设备进行通信 |
| QBluetoothServiceDiscoveryAgent | 使您能够查询蓝牙服务 |
| QBluetoothServiceInfo | 启用对蓝牙服务属性的访问 |
| QBluetoothServiceInfo::Alternative | 存储蓝牙数据元素替代项的属性 |
| QBluetoothServiceInfo::Sequence | 存储蓝牙数据元素序列的属性 |
| QBluetoothSocket | 启用与运行蓝牙服务器的蓝牙设备的连接 |
| QBluetoothTransferManager | 使用对象推送配置文件（OPP）将数据传输到另一台设备 |
| QBluetoothTransferReply | 存储对数据传输请求的响应 |
| QBluetoothTransferRequest | 存储有关数据传输请求的信息 |
| QBluetoothUuid | 为每个蓝牙服务生成一个UUID |
| QLowEnergyAdvertisingData | 表示在蓝牙低功耗广告期间要广播的数据 |
| QLowEnergyAdvertisingParameters | 代表用于蓝牙低功耗广告的参数 |
| QLowEnergyAdvertisingParameters::AddressInfo | QLowEnergyAdvertisingParameters::AddressInfo定义白名单的元素 |
| QLowEnergyCharacteristic | 存储有关蓝牙低功耗服务特征的信息 |
| QLowEnergyCharacteristicData | 用于设置GATT服务数据 |
| QLowEnergyConnectionParameters | 在请求或报告蓝牙LE连接的参数更新时使用 |
| QLowEnergyController | 接入低功耗蓝牙设备 |
| QLowEnergyDescriptor | 存储有关低功耗蓝牙描述符的信息 |
| QLowEnergyDescriptorData | 用于创建GATT服务数据 |
| QLowEnergyService | 代表低功耗蓝牙设备上的一项服务 |
| QLowEnergyServiceData | 用于设置GATT服务数据 |

### 详细说明

在Qt的蓝牙C ++ API使应用程序能够扫描设备和比一个更灵活的方式连接，并与他们进行互动的Qt蓝牙QML类型。