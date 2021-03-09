[返回](../../README.md) 

# 惠州地铁动态地图案例

目录内容

```
.
├── ArcPathway.qml(圆弧轨道进度条)
├── CurrentStationUi.qml(到达站显示界面)
├── DoorOpen.qml(开门动画)
├── DoorOtherOpened.qml(禁止开门动画)
├── main.qml
├── NextStationUi.qml(下一站显示界面)
├── Pathway.qml(条形轨道进度条)
├── README.md
├── StationAnimation.qml(站点动画)
├── StationName.qml(站点名控件)
├── Station.qml(站点)
├── Train.qml(列车动画控件)
├── UiConfig.js(站点中英文名定义)
└── WelcomeUi.qml(启动界面显示)
```

***main.qml***

```
    //第一个文字逐个显示界面(软件启动显示)
    WelcomeUi {
        id: welcomeui
        visible: true
    }
    //到达站-显示界面
    CurrentStationUi {
        id: currentstationui 
        visible: false
        endstation: root.endstation
        thisstation: root.startstation
        doorOpen: root.doorOpen
        just: root.just 
    }
    //下一站显示界面
    NextStationUi {
        id: nextstationui
        visible: false
        startstation: root.startstation
        endstation: root.endstation 
        nextstation: root.nextstation 
        just: root.just 
    }
    //这里是整个界面的自动运行逻辑，一般会把它用C++来实现，这样逻辑与界面能很好分离
    Timer {
        id: timer
        interval: 6000
        repeat: true 
        running: true
        property bool berth: true //主要用来做到站界面和下一站界面标志
        onTriggered: {
            welcomeui.visible = false
            //判断是否为正向行驶
            if(root.startstation <= root.endstation && root.just == true)
            {
                root.just = true
                //到站界面标志
                if(berth)
                {
                    //反向行驶设置
                    if(root.startstation >= root.endstation)
                    { 
                        root.startstation = 25
                        root.endstation = 0
                        root.nextstation = 25
                        root.just = false
                    }
                    root.startstation = root.nextstation;
                    currentstationui.visible = true 
                    nextstationui.visible = false 
                    timer.berth = false
                } else {
                    currentstationui.visible = false 
                    nextstationui.visible = true
                    root.nextstation = root.startstation + 1;
                    root.doorOpen = !root.doorOpen;
                    timer.berth = true
                }
            } else if(root.startstation >= root.endstation && root.just == false)
            {
                root.just = false
                if(berth)
                {
                    if(root.startstation <= root.endstation)
                    {
                        root.startstation = 0
                        root.endstation = 25
                        root.nextstation = 0
                        root.just = true
                    }
                    root.startstation = root.nextstation;
                    currentstationui.visible = true 
                    nextstationui.visible = false 
                    timer.berth = false
                } else {
                    currentstationui.visible = false 
                    nextstationui.visible = true
                    root.nextstation = root.startstation - 1;
                    root.doorOpen = !root.doorOpen;
                    timer.berth = true
                }
            }
        }
    }
```

***WelcomeUi.qml***

该界面是程序启动时第一个显示的界面

```
Item {
    width: 1366
    height: 256
    Image {
        id:imagebackground
        source: "qrc:/png/background.png"
        width: source.width 
        height: source.height
    }
    Image {
        x: 76; y: 18
        source: "qrc:/png/logotext.png"
        width: source.width 
        height: source.height
    }
    //图标旋转控件
    ImageFlipable {
        x: 19; y: 16
        width: 45
        height: 42
        fronturl: "qrc:/png/logo.png"
        backurl: "qrc:/png/logo.png"
        state: "axisY"
    }
    //文字逐个显示控件
    TextOneByOneShow {
        x: 332; y: 96
        textVar: ["欢", " 迎", " 乘", " 坐", " 惠", " 州", " 地", " 铁"]
        textfont.pixelSize: 72
        textfont.family: "Ubuntu"
        color: "#8b1d22"
    }
}
```

***CurrentStationUi.qml***

#### 组成控件

1. 到站列表

2. 到站动画

> onThisstationChanged槽函数主要是接收thisstation参数的变化来设置到站动画的变化

3. 开关门动画


***NextStationUi.qml***

#### 组成控件

    1. 下一站列表
    2. 站点轨道
    3. 站点
    4. 列车

## Fps控件

```
//在3个界面中都有使用来测试画面刷新率
    Fps {
        x: 1270; y: 0
        implicitHeight: 26
        implicitWidth: 26
        textSize: 26
    }
```


