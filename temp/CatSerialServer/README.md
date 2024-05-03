## 前言

CatSerialServer是一个跨平台串口通信服务进程，或许有疑问为什么串口通信要用独立进程放在客户端主进程上不好吗，也不是不可以而是在windows系统会有点问题，如果你客户端UI主程序程序用了windows原生边框，以及去掉了边框而去边框的底层实现是使用了windows原生的API，重写nativeEvent，这些方式在界面拖到改变大小的时候都会阻塞了串口底层数据收发，考虑过多种方式解决该问题，最后考虑使用多进程方式解决。

## 软件架构

- 使用Qt RemoteObjects作为进程间通信方式之一，使用IPC实现本机间进程通信

- 使用 QWebSocket 作为进程间通信方式之一，实现跨进程，与跨设备通信，只要支持websocket的应用都可对接该服务

### 目录结构

| 目录 | 功能 |
|--|--|
| ClientSdk | Qt RemoteObjects实现客户端sdk |
| RepResource | Qt RemoteObjects rep文件 |
| ServerProgram | 服务端进程 |
| WebSocketSdk | QWebSocket客户端sdk |

### 头文件, 实现请看源码

```
// 服务端头文件
// SerialDevList.h
#ifndef SERIALDEVLIST_H
#define SERIALDEVLIST_H

#include <QObject>
#include <QMutex>
#include "CatSerial"

class SerialState;

class SerialDevList : public QObject
{
    Q_OBJECT
public:
    static SerialDevList* Instance() noexcept
    {
        if(_instance == nullptr)
        {
            m_pMutex->lock();
            if(_instance == nullptr)
            {
                _instance = new SerialDevList;
            }
            m_pMutex->unlock();
        }
        return _instance;
    }

    static void Delete( void ) noexcept
    {
        if(_instance != nullptr)
        {
            if(m_pMutex != nullptr)
            {
                delete m_pMutex;
                m_pMutex = nullptr;
            }
            delete _instance;
            _instance = nullptr;
        }
    }

    QList<QString> GetSerialDevList();

    void OpenSerialPort(QString port, qint32 baudRate, int stopBits);
    void CloseSerialPort(QString port);
    void WriteData(QString port, QByteArray data);


signals:
    void SerialOpenSucceed(QString port);
    void SerialCloseSucceed(QString port);
    void SerialDisconnect(QString port);
    void SerialError(QString port, quint64 error);
    void ReadData(QString port, QByteArray data);
    //void SerialLists(QList<QString> ports);
    void AddDev(QString port);
    void DelDev(QString port);


private:
    SerialDevList();
    ~SerialDevList();

    void InitConnect();

    void AddDevs(QList<QSerialPortInfo> devs);
    void DelDevs(QList<QSerialPortInfo> devs);

    bool IsDev(QSerialPortInfo &info);

private:
    static SerialDevList* _instance;
    static QMutex* m_pMutex;
    QHash<QString, SerialState*> m_ySerials;

};

#endif // SERIALDEVLIST_H

// SerialServerInitialize.h
#ifndef SERIALSERVERINITIALIZE_H
#define SERIALSERVERINITIALIZE_H

#include <QObject>
#include "SerialServerRemote.h"
#include "SerialServerWebSocket.h"
#include <QRemoteObjectHost>

class SerialServerInitialize : public QObject
{
    Q_OBJECT
public:
    explicit SerialServerInitialize(QObject* parent = nullptr);
    ~SerialServerInitialize();

private:
    void InitServer();

private:

    SerialServerRemote* m_pSerialServerRemote = nullptr;
    SerialServerWebSocket* m_pSerialServerWebSocket = nullptr;
    QRemoteObjectHost *m_pHost = nullptr;
};

#endif // SERIALSERVERINITIALIZE_H

// SerialServerRemote.h
#ifndef SERIALSERVERREMOTE_H
#define SERIALSERVERREMOTE_H

#include "rep_CatSerialRemote_source.h"

class SerialServerRemote : public CatSerialRemoteSource
{
    Q_OBJECT
public:
    explicit SerialServerRemote(QObject *parent = nullptr);
    ~SerialServerRemote();
    virtual void SerialDevList();
    virtual void OpenSerialPort(QString port, qint32 baudRate, int stopBits);
    virtual void CloseSerialPort(QString port);
    virtual void WriteData(QString port, QByteArray data);

private:
    void InitConnect();

};

#endif // SERIALSERVERREMOTE_H

// SerialServerWebSocket.h
#ifndef SERIALSERVERWEBSOCKET_H
#define SERIALSERVERWEBSOCKET_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>

class SerialServerWebSocket : public QObject
{
    Q_OBJECT
    Q_ENUMS(PROTOCOL_CMD)
public:
    enum PROTOCOL_CMD {
        NEWCONNECTSOCKET = 1,
        ADDDEV,
        DELDEV,
        SERIALERROR,
        READDATA,
        SERIALOPENSUCCEED,
        SERIALCLOSESUCCEED,
        SERIALDISCONNECT,
        SERIALDEVLIST,
        OPENSERIALPORT,
        CLOSESERIALPORT,
        WRITEDATA
    };
    explicit SerialServerWebSocket(QObject *parent = nullptr);
    ~SerialServerWebSocket();

private:
    void InitProperty();
    void InitConnect();

    void DecodeData(QString data);

    QString NewConnectSocket();
    QString AddDev(QString port);
    QString DelDev(QString port);
    QString SerialError(QString port, quint64 error);
    QString ReadData(QString port, QByteArray data);
    QString SerialOpenSucceed(QString port);
    QString SerialCloseSucceed(QString port);
    QString SerialDisconnect(QString port);

    void DecodeNewConnectSocket(QString data);
    void DecodeAddDev(QString data);
    void DecodeDelDev(QString data);
    void DecodeSerialError(QString data);
    void DecodeReadData(QString data);
    void DecodeSerialOpenSucceed(QString data);
    void DecodeSerialCloseSucceed(QString data);
    void DecodeSerialDisconnect(QString data);
    void DecodeSerialDevList(QString data);
    void DecodeOpenSerialPort(QString data);
    void DecodeCloseSerialPort(QString data);
    void DecodeWriteData(QString data);

private slots:
    void onNewConnection();
    void ontextMessageReceived(const QString &message);
    void ontextFrameReceived(const QByteArray &message);
    void onDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket*> m_pSockets;
};

#endif // SERIALSERVERWEBSOCKET_H

// main.cpp
#include <QCoreApplication>
#include "ServerConfig.h"
#include "CatLog"
#include "Src/SerialDevList.h"
#include "Src/SerialServerInitialize.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName("CatSerialServer");

    qRegisterMetaType<QSerialPortInfo>("QSerialPortInfo");
    qRegisterMetaType<QList<QSerialPortInfo>>("QList<QSerialPortInfo>");


    ServerConfig::Instance()->Instance();
    SerialDevList::Instance();
    CATLOG::CatLog::Instance()->__Write_Log(INFO_LOG_T("start SerialServer"));

    SerialServerInitialize initialize;

    return app.exec();
}
```

```
// Qt RemoteObjects客户端sdk
// CatSerialClient.h
#ifndef CATSERIALCLIENT_H
#define CATSERIALCLIENT_H

#include <QObject>
#include <QThread>
#include <QRemoteObjectNode>
#include "rep_CatSerialRemote_replica.h"


class CatSerialClient : public QThread
{
    Q_OBJECT
public:
    explicit CatSerialClient(QObject* parent = nullptr);
    ~CatSerialClient();

private:
    void InitProperty();
    void InitConnect();

protected:
    void run() override;

signals:
    void SerialDevListSign(QList<QString> ports);
    void SerialOpenSucceed(QString port);
    void SerialCloseSucceed(QString port);
    void SerialDisconnect(QString port);
    void SerialError(QString port, quint64 error);
    void ReadData(QString port, QByteArray data);
    void AddDev(QString port);
    void DelDev(QString port);

public slots:
    void SerialDevList();
    void OpenSerialPort(QString port, qint32 baudRate, int stopBits);
    void CloseSerialPort(QString port);
    void WriteData(QString port, QByteArray data);

private:
    QRemoteObjectNode * m_pRemoteNode = nullptr;
    CatSerialRemoteReplica *m_pCatSerialRemoteReplica = nullptr;
};

#endif // CATSERIALCLIENT_H

```

```
// CatWebSocketClient.h
#ifndef CATWEBSOCKETCLIENK_H
#define CATWEBSOCKETCLIENK_H

#include <QObject>
#include <QThread>
#include <QWebSocket>

class CatWebSocketClient : public QThread
{
    Q_OBJECT
public:
    enum PROTOCOL_CMD {
        NEWCONNECTSOCKET = 1,
        ADDDEV,
        DELDEV,
        SERIALERROR,
        READDATA,
        SERIALOPENSUCCEED,
        SERIALCLOSESUCCEED,
        SERIALDISCONNECT,
        SERIALDEVLIST,
        OPENSERIALPORT,
        CLOSESERIALPORT,
        WRITEDATA
    };
    explicit CatWebSocketClient(QObject *parent = nullptr);
    ~CatWebSocketClient();

    void Open(QUrl url);
    void Close();

private:
    void InitProperty();
    void InitConnect();

    void DecodeData(QString data);

    void DecodeNewConnectSocket(QString data);
    void DecodeAddDev(QString data);
    void DecodeDelDev(QString data);
    void DecodeSerialError(QString data);
    void DecodeReadData(QString data);
    void DecodeSerialOpenSucceed(QString data);
    void DecodeSerialCloseSucceed(QString data);
    void DecodeSerialDisconnect(QString data);
    void DecodeSerialDevList(QString data);
    void DecodeOpenSerialPort(QString data);
    void DecodeCloseSerialPort(QString data);
    void DecodeWriteData(QString data);

protected:
    void run() override;

signals:
    void SerialDevListSign(QList<QString> ports);
    void SerialOpenSucceed(QString port);
    void SerialCloseSucceed(QString port);
    void SerialDisconnect(QString port);
    void SerialError(QString port, quint64 error);
    void ReadData(QString port, QByteArray data);
    void AddDev(QString port);
    void DelDev(QString port);
    void WriteDataSign(const QString data);

public slots:
    void SerialDevList();
    void OpenSerialPort(QString port, qint32 baudRate, int stopBits);
    void CloseSerialPort(QString port);
    void WriteData(QString port, QByteArray data);

private:
    QWebSocket *m_pWebSocket = nullptr;
    QUrl m_qUrl;

};

#endif

```


## 功能需求

### 服务端功能

1. 支持串口热插拔

2. 获取串口列表

3. 打开，关闭串口设备

4. 获取当前打开的串口设备

5. 打开成功，打开失败，串口占用，断开连接API接口

6. 发送和接收数据API接口

7. websocket实现json格式api

8. 同时支持windows，linux，mac

9. 同时支持 mingw，msvc，gcc等

10. config配置可配置pid，vid过滤

### 客户端SDK

1. 使用Qt RemoteObjects实现进程间通信，需要配合服务端的Qt RemoteObjects接口

2. 使用 WebSocket实现网络通信接口。

 

### 服务端ini配置

```C++
//SerialServerConfig.ini
[General]
WebSocketServer_Port=10024
// 配置串口需要过滤的pid，vid
[SerialFilter_Pid_Vid]
1\0="11111,0000"
2\1="11112,0000"
size=2


```


## Qt RemoteObjects

### 服务端串口异常返回值

```C++
10001 - 需要打开的串口无效
10002 - 需要打开的串口已被该软件打开
10003 - 需要打开的串口已被占用
10004 - 串口其它错误
10005 - 需要关闭的串口无效
10006 - 需要发送数据的串口无效

```


## WebSocketServer

### 客户端连接后服务端回复状态API

```C++
{
  Cmd: 0
  ServerName: "Server"
  ServerPort: 8000
  ServerUrl: "ws://0.0.0.0:8000"
  State: 200
}
```


### 设备热插拔API

```C++
// 设备插入
{
  Cmd: 1
  ServerUrl: "ws://0.0.0.0:8000"
  Dev: "COM1"
  State: 200
}

// 设备拔出
{
  Cmd: 2
  ServerUrl: "ws://0.0.0.0:8000"
  Dev: "COM1"
  State: 200
}

```


### 串口返回错误API

```C++
// 串口错误
{
  Cmd: 3
  ServerUrl: "ws://0.0.0.0:8000"
  Dev: "COM1"
  Error: 10001
  State: 200
}
```


### 串口读取返回数据API

```C++
{
  Cmd: 4
  ServerUrl: "ws://0.0.0.0:8000"
  Dev: "COM1"
  Data: "data"
  State: 200
}
```


### 返回串口打开成功API

```C++
{
  Cmd: 5
  ServerUrl: "ws://0.0.0.0:8000"
  Dev: "COM1"
  State: 200
}
```


### 返回串口关闭成功API

```C++
{
  Cmd: 6
  ServerUrl: "ws://0.0.0.0:8000"
  Dev: "COM1"
  State: 200
}
```


### 返回串口断开API

```C++
{
  Cmd: 7
  ServerUrl: "ws://0.0.0.0:8000"
  Dev: "COM1"
  State: 200
}
```


### 返回串口列表API

```JavaScript
{
  Cmd: 9
  ServerUrl: "ws://0.0.0.0:8000"
  Devs: ["COM1", "COM2"]
  State: 200
}
```