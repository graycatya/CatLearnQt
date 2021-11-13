
## Directory

[中文说明](./README.md)


- [Directory](#directory)
- [CatLearnQt](#catlearnqt)
- [Project Address](#project-address)
- [Badge Preview](#badge-preview)
  - [Project](#project)
  - [Compile](#compile)
- [DevelopmentEnvironment](#developmentenvironment)
  - [ProjectDescription](#projectdescription)
  - [CoreLibrary](#corelibrary)
    - [How to use Core Library](#how-to-use-core-library)
      - [GrayCatQt](#graycatqt)
        - [qmake](#qmake)
        - [cmake](#cmake)
      - [GrayCatQtQuick](#graycatqtquick)
        - [qmake](#qmake-1)
        - [cmake](#cmake-1)
      - [GrayCatQtCore](#graycatqtcore)
        - [qmake](#qmake-2)
        - [cmake](#cmake-2)
  - [ExamplesProject](#examplesproject)
    - [CatQuickExamplesEffectPreview](#catquickexampleseffectpreview)
      - [Controls](#controls)
      - [Demo](#demo)
      - [FigmaPrototype](#figmaprototype)
    - [CatWidgetExamplesEffectPreview](#catwidgetexampleseffectpreview)
    - [MetroDemo_HuizhouMetroCaseEffectPreview](#metrodemo_huizhoumetrocaseeffectpreview)

## CatLearnQt

CatLearnQt Record your own learning Qt process.

CatLearnQt is released under the GPL v3 license. If you use CatLearnQt or its component libraries, you must abide by the relevant license terms.


## Project Address

| Mirro Repo | Address |
|:--:|:--:|
| ![GitHub] | [Github](https://github.com/graycatya/CatLearnQt) |
| ![Gitee] | [Gitee](https://gitee.com/graycatya/CatLearnQt) |
| ![CodeChina] | [CodeChina](https://codechina.csdn.net/qq_32312307/CatLearnQt) |

[GitHub]: ./doc/Images/github.svg
[Gitee]: ./doc/Images/gitee-fill-round.svg
[CodeChina]: ./doc/Images/codechina.png

## Badge Preview

### Project

|[BestPracticePlan][CII-link]|[License][license-link]| [OnlineCommunity][Gitter-link] |
|:--:|:--:|:--:|
|![CII-badge]|![license-badge]|![Gitter]|

[CII-badge]: https://bestpractices.coreinfrastructure.org/projects/4578/badge
[CII-link]: https://bestpractices.coreinfrastructure.org/zh-CN/projects/4578

[license-link]: https://github.com/graycatya/CatLearnQt/blob/main/Licence.md "LICENSE"
[license-badge]: https://img.shields.io/github/license/graycatya/CatLearnQt?style=plastic

[Gitter-link]: https://gitter.im/CatLearnQt/community
[Gitter]: https://badges.gitter.im/CatLearnQt/community.svg "community"


### Compile

| [Windows][win-link]| [Ubuntu][ubuntu-link]|[MacOS][macos-link]|[Android][android-link]|[IOS][ios-link]|
|---------------|---------------|-----------------|-----------------|----------------|
| ![win-badge]  | ![ubuntu-badge]      | ![macos-badge] |![android-badge]   |![ios-badge]   |


[win-link]: https://github.com/graycatya/CatLearnQt/actions?query=workflow%3AWindows "WindowsAction"
[win-badge]: https://github.com/graycatya/CatLearnQt/workflows/Windows/badge.svg  "Windows"

[ubuntu-link]: https://github.com/graycatya/CatLearnQt/actions?query=workflow%3AUbuntu "UbuntuAction"
[ubuntu-badge]: https://github.com/graycatya/CatLearnQt/workflows/Ubuntu/badge.svg "Ubuntu"

[macos-link]: https://github.com/graycatya/CatLearnQt/actions?query=workflow%3AMacOS "MacOSAction"
[macos-badge]: https://github.com/graycatya/CatLearnQt/workflows/MacOS/badge.svg "MacOS"

[android-link]: https://github.com/graycatya/CatLearnQt/actions?query=workflow%3AAndroid "AndroidAction"
[android-badge]: https://github.com/graycatya/CatLearnQt/workflows/Android/badge.svg "Android"

[ios-link]: https://github.com/graycatya/CatLearnQt/actions?query=workflow%3AIOS "IOSAction"
[ios-badge]: https://github.com/graycatya/CatLearnQt/workflows/IOS/badge.svg "IOS"


## DevelopmentEnvironment

* Qt5.12 and above

* Support qt5.15


### ProjectDescription

| Directory | Explanation | Remark |
|:--:|:--:|:--:|
| doc | Document Directory | Save the documents required by the project, describe the configuration of each platform, and the project moduleExplanation, etc. |
| GrayCatQt | GrayCatQt module | Provides a set of custom controls based on QWidget and QGraphicsView. |
| GrayCatQtQuick | GrayCatQtQuickmodule | Provides a collection of custom controls based on Quick and Qml. |
| GrayCatQtCore | GrayCatQtCoremodule | Provides modules such as serial port, network, Bluetooth, log, thread, etc. |
| Examples | Module Integrated demo project | This project is developed on the basis of QWidget and demonstrates the projects of modules such as QWidget, QQuickWidget, QGraphicsView, etc. |
| scripts | Script file path | Continuous integration related configuration, used to automate the construction and release of scripts, and provide qml library tailoring scripts |
| .github | github-Actions configuration | Continuous integration related configuration for automated construction and release |


### CoreLibrary

| Library | Explanation link |
|:--:|:--:|
| GrayCatQt | Provides a set of custom controls based on QWidget and QGraphicsView. |
| GrayCatQtQuick | Provides based on GraphicsViewmodule and control set |
| GrayCatQtCore | Provides modules such as serial port, network, Bluetooth, log, thread, etc. |

#### How to use Core Library

##### GrayCatQt

###### qmake

* Usage of pri file

Use the core library only need to import, the'.pri' file under the module folder

The resources that GrayCatYa needs to use will be quoted in the form of qrc resources. Pay attention to the path name of the resource, and do not re-path with the new qrc resource file.

After importing pri, no additional compilation is required to generate dll or plug-in

>Steps

```
include(GrayCatQt/GrayCatQt.pri)
```

* Usage of pro file

If you need to compile into a library, open the pro file in the GrayCatQt directory and compile it.

```
cd GrayCatQt
qmake GrayCatQt.pro
```

###### cmake

1. First copy the module folder to your project directory, there are modules used by cmake

```
# Use the module in your CMakeLists.txt
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/module/cmake")
include(GrayCatQt)
```

2. Copy GrayCatQt to your project directory, and note that it is at the same level as the module file

```
# Use the module in your CMakeLists.txt
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GrayCatQt GrayCatQt.out)
```


##### GrayCatQtQuick

###### qmake

* Usage of pri file

Use the core library only need to import, the'.pri' file under the module folder

The resources that GrayCatQtQuick needs to use will be quoted as qrc resources. Pay attention to the path name of the resource and do not re-path with the new qrc resource file.

After importing pri, no additional compilation is required to generate dll or plug-in

>Steps

```
include(GrayCatQtQuick/GrayCatQtQuick.pri)
```

* Usage of pro file

If you need to compile into a library, open the pro file in the GrayCatQtQuick directory and compile it.

```
cd GrayCatQtQuick
qmake GrayCatQtQuick.pro
```

###### cmake

1. First copy the module folder to your project directory, there are modules used by cmake

```
# Use the module in your CMakeLists.txt
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/module/cmake")
include(GrayCatQt)
```

2. Copy GrayCatQtQuick to your project directory, note that it is at the same level as the module file

```
# Use the module in your CMakeLists.txt
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GrayCatQtQuick GrayCatQtQuick.out)
```

##### GrayCatQtCore

###### qmake

* Usage of pri file

Use the core library only need to import, the'.pri' file under the module folder

After importing pri, no additional compilation is required to generate dll or plug-in

>Steps

```
include(GrayCatQtCore/GrayCatQtCore.pri)
```

* Usage of pro file

If you need to compile into a library, open the pro file in the GrayCatQtCore directory and compile it.

```
cd GrayCatQtCore
qmake GrayCatQtCore.pro
```

###### cmake

1. First copy the module folder to your project directory, there are modules used by cmake

```
# Use the module in your CMakeLists.txt
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/module/cmake")
include(GrayCatQt)
```

2. Copy GrayCatQtCore to your project directory, and note that it is at the same level as the module file

```
# Use the module in your CMakeLists.txt
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GrayCatQtCore GrayCatQtCore.out)
```

### ExamplesProject

| Directory | Explanation |
|:--:|:--:|
| Examples/CatQuickExamples | Based on the Quick version of the project demo |
| Examples/CatWidgetExamples | Widgdet version project demo |
| Examples/CatWidgetWebAssEmblyExamples | CatWidgetExamples cut version WebAssmbly version project demo |
| Examples/MetroDemo | Implement HuizhouMetroCase based on Quick |

#### CatQuickExamplesEffectPreview

##### Controls

| Controls | Explanation |
|:--:|:--:|
| ImageFlipable | Flip picture |
| ImageFlicker | Flash picture |
| ImageFlickerGradient | Picture flashing progressive |
| ImageMove | Move picture |
| ImageScale | zoom picture |
| Marquee | Text scroll, barrage |
| TextOneByOneShow | Show text one by one |
| CatRectangle | Custom rounded rectangle, single rounded corner |
| QParentQrenCode | qml QR code |
| CatCalendar | Calendar module |
| Image3dRotation | Picture 3d rotation |
| CatECharts | WebEngine demo ECharts chart |
| CatSideColumn | Sliding sidebar |

##### Demo

![QuickExamples_0](./doc/PubImages/QuickExamples_0.png)

![QuickExamples_1](./doc/PubImages/QuickExamples_1.png)

![QuickExamples_2](./doc/PubImages/QuickExamples_2.png)


##### FigmaPrototype

[CatQuickExamples_Figma](https://www.figma.com/community/file/1002381105559834769/CatQuickExamples)


#### CatWidgetExamplesEffectPreview

* Widget-based controls

![widgetdemo](./doc/PubImages/widgetdemo.png)

* Demo based on QGraphicsView drawing board control

![boarddemo](./doc/PubImages/boarddemo.png)

* Demo based on QQuickWidget control

![quickwidgetdemo](./doc/PubImages/quickwidgetdemo.png)

* Settings related

![settingdemo](./doc/PubImages/settingdemo.png)

#### MetroDemo_HuizhouMetroCaseEffectPreview

[Online Demo(https://graycatya.gitee.io/webassemblyExample/MetroDemo/MetroDemo.html)](https://graycatya.gitee.io/webassemblyExample/MetroDemo/MetroDemo.html)

![Metro Demo](./doc/PubImages/metrodemo.gif)


