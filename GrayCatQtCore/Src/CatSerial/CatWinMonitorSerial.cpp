#include "CatWinMonitorSerial.h"
#include "MonitorSerial.h"

//#include <CatLog>
#include <QDataStream>

#include <Windows.h>
#include <tchar.h>
#include <Dbt.h>
#include <setupapi.h>
#include <iostream>
#include <atlstr.h> // CString
#include <QSettings>
using namespace std;

#pragma comment (lib, "Setupapi.lib")

// 设备实例ID最大长度
#define DeviceInstanceIdSize 256

#pragma comment (lib, "Kernel32.lib")
#pragma comment (lib, "User32.lib")

CatWinMonitorSerial* CatWinMonitorSerial::_instance = nullptr;
QMutex* CatWinMonitorSerial::m_pMutex = new QMutex;

#define THRD_MESSAGE_EXIT WM_USER + 1
const _TCHAR CLASS_NAME[] = _T("Sample Window Class");

struct WinSerialPortInfo
{
    std::string portName;
    std::string description;
};

HWND hWnd;
DWORD iThread;
HANDLE hThread;

#ifndef MACRO_HIDD_VIDPID
    #define MACRO_HIDD_VIDPID
    typedef struct _HIDD_VIDPID
    {
        USHORT	VendorID;
        USHORT	ProductID;
    } HIDD_VIDPID;
#endif

static const GUID GUID_DEVINTERFACE_LIST[] =
{
    // GUID_DEVINTERFACE_USB_DEVICE
    { 0xA5DCBF10, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } },
    // GUID_DEVINTERFACE_DISK
    { 0x53f56307, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } },
    // GUID_DEVINTERFACE_HID,
    { 0x4D1E55B2, 0xF16F, 0x11CF, { 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } },
    // GUID_NDIS_LAN_CLASS
    { 0xad498944, 0x762f, 0x11d0, { 0x8d, 0xcb, 0x00, 0xc0, 0x4f, 0xc3, 0x35, 0x8c } },
    // GUID_DEVINTERFACE_COMPORT
    { 0x86e0d1e0, 0x8089, 0x11d0, { 0x9c, 0xe4, 0x08, 0x00, 0x3e, 0x30, 0x1f, 0x73 } },
    // GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR
    { 0x4D36E978, 0xE325, 0x11CE, { 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18 } },
    // GUID_DEVINTERFACE_PARALLEL
    { 0x97F76EF0, 0xF883, 0x11D0, { 0xAF, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x84, 0x5C } },
    // GUID_DEVINTERFACE_PARCLASS
    { 0x811FC6A5, 0xF728, 0x11D0, { 0xA5, 0x37, 0x00, 0x00, 0xF8, 0x75, 0x3E, 0xD1 } }
};


// 获取系统的VID和PID集合
QString WDK_WhoAllVidPid( string ssin )
{

    HIDD_VIDPID* pVidPid=new HIDD_VIDPID[9];
    int iCapacity=32;
    GUID* SetupClassGuid=NULL;
    GUID* InterfaceClassGuid=NULL;

    // 根据设备安装类GUID创建空的设备信息集合
    HDEVINFO DeviceInfoSet = SetupDiCreateDeviceInfoList( SetupClassGuid, NULL );
    if (DeviceInfoSet == INVALID_HANDLE_VALUE)
    {
        return "";
    }

    // 根据设备安装类GUID获取设备信息集合
    HDEVINFO hDevInfo;

    if(InterfaceClassGuid == NULL)
    {
        hDevInfo = SetupDiGetClassDevsEx( NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_DEVICEINTERFACE | DIGCF_PRESENT, DeviceInfoSet, NULL, NULL );
    }
    else
    {
#ifdef UNICODE
        hDevInfo = SetupDiGetClassDevsEx( InterfaceClassGuid, (PCWSTR)&"SCSI", NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT, DeviceInfoSet, NULL, NULL );
#else
        hDevInfo = SetupDiGetClassDevsEx( InterfaceClassGuid, (PCSTR)&"SCSI", NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT, DeviceInfoSet, NULL, NULL );
#endif
    }

    if (hDevInfo == INVALID_HANDLE_VALUE)
    {
        return "";
    }

    // 存储设备实例ID
    TCHAR DeviceInstanceId[DeviceInstanceIdSize];

    // 存储设备信息数据
    SP_DEVINFO_DATA DeviceInfoData;
    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    // 获取设备信息数据
    DWORD DeviceIndex = 0;
     bool k=true;
    while (SetupDiEnumDeviceInfo( hDevInfo, DeviceIndex++, &DeviceInfoData))
    {
        // 获取设备实例ID
        if (SetupDiGetDeviceInstanceId(hDevInfo, &DeviceInfoData, DeviceInstanceId, DeviceInstanceIdSize, NULL)&&k)
        {
            // 从设备实例ID中提取VID和PID
            TCHAR* pVidIndex = _tcsstr(DeviceInstanceId, TEXT("VID_"));
            if (pVidIndex == NULL)
            {
                continue;
            }

            TCHAR* pPidIndex = _tcsstr(pVidIndex + 4, TEXT("PID_"));
            if (pPidIndex == NULL)
            {
                continue;
            }

            USHORT VendorID = (USHORT)_tcstoul(pVidIndex + 4, NULL, 16);
            USHORT ProductID = (USHORT)_tcstoul(pPidIndex + 4, NULL, 16);

            //输出串口号

            TCHAR fname[56]={0};

            SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData,
                SPDRP_HARDWAREID,
                0,(PBYTE) fname,
                sizeof(fname),
                      NULL);

            //判断相应VID号的串口

            //字符串方法识别FTDI
            string str1(57,'0');
            string s1=ssin;
            for (int i=0;i<56;i++)
            {
                str1[i]=(char)fname[i];
            }


            if(str1.find(s1)==string::npos) continue;



        //清空fname
        for (int i=0;i<56;i++)
        {
            fname[i]=0;
        }

        //	输出串口号
        SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData,
            SPDRP_FRIENDLYNAME ,
            0,(PBYTE) fname,
            sizeof(fname),
            NULL);

        string str2(57,'0');
        string s2="COM";
        for (int i=0;i<56;i++)
        {
            str2[i]=(char)fname[i];
        }
        if(str2.find(s2)!=string::npos)
        {
            int num=str2.find(s2);
            string StrCom=str2.substr(num,4);
            QStringList list = QString::fromStdString(str2).split(" ");
            foreach(auto temp , list)
            {
                if(temp.mid(0, 4) == "(COM")
                {
                    temp.remove("(");
                    temp.replace(")", " ");

                    return temp.split(" ").at(0);
                }
            }

        }


        }

    }

    return "";
}

QString getPortName(int index, QString keyorvalue)
{
    QString 	commresult;
    HKEY        hKey;
    wchar_t     keyname[256]; //键名数组
    char        keyvalue[256];  //键值数组
    DWORD       keysize,type,valuesize;
    if (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 0, KEY_READ, &hKey) != 0) {
        QString error="Cannot open regedit!";   //无法打开注册表时返回error
        return error;
    }
    QString keymessage;//键名
    QString message;
    QString valuemessage;//键值
    keysize = sizeof(keyname);
    valuesize = sizeof(keyvalue);
#ifdef UNICODE
    if (RegEnumValue(hKey, index, (LPWSTR)keyname, &keysize, 0, &type, (BYTE*)keyvalue, &valuesize) == 0) { //列举键名和值
#else
    if (RegEnumValue(hKey, index, (LPSTR)keyname, &keysize, 0, &type, (BYTE*)keyvalue, &valuesize) == 0) { //列举键名和值
#endif

        for (int i=0; i<(int)keysize; i++) {
            message = keyname[i];
            keymessage.append(message);
        }
        for (int j=0; j<(int)valuesize; j++) {
            if (keyvalue[j] != 0x00) {
                valuemessage.append(keyvalue[j]);
            }
        }
        if (keyorvalue == "key") {
            commresult = keymessage;
        }
        if (keyorvalue == "value") {
            commresult=valuemessage;
        }
    } else {
        commresult = "nokey";
    }
    RegCloseKey(hKey);//关闭注册表
    return commresult;
}

//获取串口列表函数
QStringList getAvailableSerialPort()
{
    QStringList availablePortName;

        QString path = "HKEY_LOCAL_MACHINE\\HARDWARE\\DEVICEMAP\\SERIALCOMM";//注册表路径
        QSettings *settings = new QSettings(path, QSettings::NativeFormat);
        QStringList key = settings->allKeys();
        for(int i = 0;i<key.size();i++){
            QString key = getPortName(i,"key");
            QString value = getPortName(i,"value");
            //qDebug()<<key<<value;
            availablePortName<<value;
        }

    //availableSerialPortName = availablePortName;
    return availablePortName;
}


std::string wstringToString(const std::wstring& wstr)
{
    // https://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string
    if (wstr.empty())
    {
        return std::string();
    }

    int size = WideCharToMultiByte(CP_ACP, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string ret = std::string(size, 0);
    WideCharToMultiByte(CP_ACP, 0, &wstr[0], (int)wstr.size(), &ret[0], size, NULL, NULL); // CP_UTF8

    return ret;
}

bool enumDetailsSerialPorts(QVector<WinSerialPortInfo>& portInfoList)
{
    //https://msdn.microsoft.com/en-us/library/ms724256

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

    HKEY hKey;

    TCHAR       achValue[MAX_VALUE_NAME];                   // buffer for subkey name
    DWORD       cchValue = MAX_VALUE_NAME;                  // size of name string
    TCHAR       achClass[MAX_PATH] = _T("");                // buffer for class name
    DWORD       cchClassName = MAX_PATH;                    // size of class string
    DWORD       cSubKeys = 0;                               // number of subkeys
    DWORD       cbMaxSubKey;                                // longest subkey size
    DWORD       cchMaxClass;                                // longest class string
    DWORD       cKeyNum;                                    // number of values for key
    DWORD       cchMaxValue;                                // longest value name
    DWORD       cbMaxValueData;                             // longest value data
    DWORD       cbSecurityDescriptor;                       // size of security descriptor
    FILETIME    ftLastWriteTime;                            // last write time

    int iRet = -1;
    bool bRet = false;

    std::string strPortName;
    WinSerialPortInfo m_serialPortInfo;

    TCHAR strDSName[MAX_VALUE_NAME];
    memset(strDSName, 0, MAX_VALUE_NAME);
    DWORD nValueType = 0;
    DWORD nBuffLen = 10;

    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 0, KEY_READ, &hKey))
    {
        // Get the class name and the value count.
        iRet = RegQueryInfoKey(
            hKey,                    // key handle
            achClass,                // buffer for class name
            &cchClassName,           // size of class string
            NULL,                    // reserved
            &cSubKeys,               // number of subkeys
            &cbMaxSubKey,            // longest subkey size
            &cchMaxClass,            // longest class string
            &cKeyNum,                // number of values for this key
            &cchMaxValue,            // longest value name
            &cbMaxValueData,         // longest value data
            &cbSecurityDescriptor,   // security descriptor
            &ftLastWriteTime);       // last write time

        if (!portInfoList.empty())
        {
            portInfoList.clear();
        }

        // Enumerate the key values.
        if (cKeyNum > 0 && ERROR_SUCCESS == iRet)
        {
            for (int i = 0; i < (int)cKeyNum; i++)
            {
                cchValue = MAX_VALUE_NAME;
                achValue[0] = '\0';
                nBuffLen = MAX_KEY_LENGTH;//防止 ERROR_MORE_DATA 234L 错误

                if (ERROR_SUCCESS == RegEnumValue(hKey, i, achValue, &cchValue, NULL, NULL, (LPBYTE)strDSName, &nBuffLen))
                {

#ifdef UNICODE
                    strPortName = wstringToString(strDSName);
#else
                    strPortName = std::string(strDSName);
#endif
                    m_serialPortInfo.portName = strPortName;
                    portInfoList.push_back(m_serialPortInfo);
                }
            }
        }
        else
        {

        }
    }

    if (portInfoList.empty())
    {
        bRet = false;
    }
    else
    {
        bRet = true;
    }


    RegCloseKey(hKey);

    return bRet;
}



void UpdateDevice(PDEV_BROADCAST_DEVICEINTERFACE pDevInf, WPARAM wParam)
{

    static QHash<QString, QString> m_qComs = {};
    CString szDevId = pDevInf->dbcc_name + 4;
    int idx = szDevId.ReverseFind(_T('#'));
    szDevId.Truncate(idx);
    szDevId.Replace(_T('#'), _T('\\'));
    szDevId.MakeUpper();

    CString szClass;
    idx = szDevId.Find(_T('\\'));
    szClass = szDevId.Left(idx);

    CString szTmp;

    if (DBT_DEVICEARRIVAL == wParam)
    {
        szTmp.Format(_T("%s"), szDevId.GetBuffer());

        std::string STDStr(CW2A((LPCWSTR)szTmp.GetString()));
        //QString log =  "win api add: " + QString::fromStdString(STDStr);
        //CATLOG::CatLog::__Write_Log(INFO_LOG_T(log.toStdString()));
        //CATLOG::CatLog::__Write_Log("./log", INFO_LOG_T(log.toStdString()));
        QString dev = QString::fromStdString(STDStr);
        QStringList mes = dev.split('\\');
        if(mes.at(0) == "USB")
        {
            mes = mes.at(1).split('&');
            QString vid = mes.at(0).split('_').at(1);
            QString pid = mes.at(1).split('_').at(1);

            qint64 nvid = vid.toUInt(nullptr, 16), npid = pid.toUInt(nullptr, 16);

            if(!CatWinMonitorSerial::Instance()->m_pSerials.contains(mes.at(1)))
            {
                CatWinMonitorSerial::Instance()->m_pSerials[mes.at(1)] = WDK_WhoAllVidPid( mes.at(1).toStdString() );
                emit CatWinMonitorSerial::Instance()->AddSerial(npid, nvid, WDK_WhoAllVidPid( mes.at(1).toStdString() ));
            }
            ;
        }

    }
    else
    {
        szTmp.Format(_T("%s"), szDevId.GetBuffer());

        std::string STDStr(CW2A((LPCWSTR)szTmp.GetString()));
        //QString log =  "win api del: " + QString::fromStdString(STDStr);
        //CATLOG::CatLog::__Write_Log(INFO_LOG_T(log.toStdString()));
        //CATLOG::CatLog::__Write_Log("./log", INFO_LOG_T(log.toStdString()));

        QString dev = QString::fromStdString(STDStr);
        QStringList mes = dev.split('\\');
        if(mes.at(0) == "USB")
        {
            mes = mes.at(1).split('&');
            QString vid = mes.at(0).split('_').at(1);
            QString pid = mes.at(1).split('_').at(1);

            qint64 nvid = vid.toUInt(nullptr, 16), npid = pid.toUInt(nullptr, 16);
            if(CatWinMonitorSerial::Instance()->m_pSerials.contains(mes.at(1)))
            {
                QString dev = CatWinMonitorSerial::Instance()->m_pSerials[mes.at(1)];
                CatWinMonitorSerial::Instance()->m_pSerials.remove(mes.at(1));
                emit CatWinMonitorSerial::Instance()->DeleteSerial(npid, nvid, dev);
            }
        }
    }

}

LRESULT DeviceChange(UINT message, WPARAM wParam, LPARAM lParam)
{
    if (DBT_DEVICEARRIVAL == wParam || DBT_DEVICEREMOVECOMPLETE == wParam)
    {
        PDEV_BROADCAST_HDR pHdr = (PDEV_BROADCAST_HDR)lParam;
        PDEV_BROADCAST_DEVICEINTERFACE pDevInf;
        PDEV_BROADCAST_HANDLE pDevHnd;
        PDEV_BROADCAST_OEM pDevOem;
        PDEV_BROADCAST_PORT pDevPort;
        PDEV_BROADCAST_VOLUME pDevVolume;
        switch (pHdr->dbch_devicetype)
        {
        case DBT_DEVTYP_DEVICEINTERFACE:
            pDevInf = (PDEV_BROADCAST_DEVICEINTERFACE)pHdr;
            UpdateDevice(pDevInf, wParam);
            break;

        case DBT_DEVTYP_HANDLE:
            pDevHnd = (PDEV_BROADCAST_HANDLE)pHdr;
            break;

        case DBT_DEVTYP_OEM:
            pDevOem = (PDEV_BROADCAST_OEM)pHdr;
            break;

        case DBT_DEVTYP_PORT:
            pDevPort = (PDEV_BROADCAST_PORT)pHdr;
            break;

        case DBT_DEVTYP_VOLUME:
            pDevVolume = (PDEV_BROADCAST_VOLUME)pHdr;
            break;
        }
    }
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        break;
    case WM_SIZE:
        break;
    case WM_DEVICECHANGE:
        return DeviceChange(message, wParam, lParam);
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

ATOM MyRegisterClass()
{
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    return RegisterClass(&wc);
}

bool CreateMessageOnlyWindow()
{
    hWnd = CreateWindowEx(0, CLASS_NAME, _T(""), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,       // Parent window
        NULL,       // Menu
        GetModuleHandle(NULL),  // Instance handle
        NULL        // Additional application data
        );

    return hWnd != NULL;
}

void RegisterDeviceNotify()
{
    HDEVNOTIFY hDevNotify;
    for (int i = 0; i < sizeof(GUID_DEVINTERFACE_LIST) / sizeof(GUID); i++)
    {
        DEV_BROADCAST_DEVICEINTERFACE NotificationFilter;
        ZeroMemory(&NotificationFilter, sizeof(NotificationFilter));
        NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
        NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
        NotificationFilter.dbcc_classguid = GUID_DEVINTERFACE_LIST[i];
        hDevNotify = RegisterDeviceNotification(hWnd, &NotificationFilter, DEVICE_NOTIFY_WINDOW_HANDLE);
    }
}

DWORD WINAPI ThrdFunc(LPVOID lpParam)
{
    if (0 == MyRegisterClass())
        return -1;

    if (!CreateMessageOnlyWindow())
        return -1;

    RegisterDeviceNotify();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (msg.message == THRD_MESSAGE_EXIT)
        {
            //cout << "worker receive the exiting Message..." << endl;
            return 0;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


QStringList CatWinMonitorSerial::Serials()
{
    return getAvailableSerialPort();
}

CatWinMonitorSerial::CatWinMonitorSerial()
{
    m_pSerials.clear();
    hThread = CreateThread(NULL, 0, ThrdFunc, NULL, 0, &iThread);
    if (hThread == NULL) {
        //QString log = "CatWinMonitorSerial CreateThread Error ";
        //CATLOG::CatLog::__Write_Log(ERROR_LOG_T(log.toStdString()));
    }
}

CatWinMonitorSerial::~CatWinMonitorSerial()
{
    PostThreadMessage(iThread, THRD_MESSAGE_EXIT, 0, 0);
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
}
