
## 目录

- [目录](#目录)
- [CatLearnQt](#catlearnqt)
- [项目地址](#项目地址)
- [徽章预览](#徽章预览)
  - [项目](#项目)
  - [编译](#编译)
- [开发环境](#开发环境)
- [环境搭建](#环境搭建)
- [项目结构](#项目结构)
  - [项目根目录说明](#项目根目录说明)
  - [现成模块](#现成模块)
    - [GrayCatQt 模块](#graycatqt-模块)
    - [Examples 项目](#examples-项目)

## CatLearnQt

CatLearnQt 记录自己学习Qt过程.

CatLearnQt是根据GPL v3许可发行，如果您使用CatLearnQt或其组成库，则必须遵守相关许可条款。


## 项目地址

| 镜像仓库 | 地址 |
|:--:|:--:|
| ![GitHub] | [Github](https://github.com/graycatya/CatLearnQt) |
| ![Gitee] | [Gitee](https://gitee.com/graycatya/CatLearnQt) |

[GitHub]: ./doc/Images/github.svg
[Gitee]: ./doc/Images/gitee-fill-round.svg

## 徽章预览

### 项目

|[最佳实践计划][CII-link]|[许可][license-link]| [在线社区][Gitter-link] |
|:--:|:--:|:--:|
|![CII-badge]|![license-badge]|![Gitter]|

[CII-badge]: https://bestpractices.coreinfrastructure.org/projects/4578/badge
[CII-link]: https://bestpractices.coreinfrastructure.org/zh-CN/projects/4578

[license-link]: https://github.com/graycatya/CatLearnQt/blob/main/Licence.md "LICENSE"
[license-badge]: https://img.shields.io/cran/l/devtools "GPL 3"

[Gitter-link]: https://gitter.im/CatLearnQt/community
[Gitter]: https://badges.gitter.im/CatLearnQt/community.svg "community"


### 编译

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


## 开发环境

* Qt5.12以上

* 支持qt5.15

## 环境搭建


|系统|文档|
|:--:|:--:|
| Windows | [windows.md](doc/windows/windows.md) |
| Linux | [linux.md](doc/linux/linux.md) |
| MacOs | [macos.md](doc/macos/macos.md) |
| Android | [android.md](doc/android/android.md) |
| Ios | [ios.md](doc/ios/ios.md) |
| WebAssEmblyExamples | [webassembly.md](doc/QtDoc/webassembly/webassembly.md) |



## 项目结构

| 描述 | 文档 |
|:--:|:--:|
| 项目目录结构 | [ProjectDirectoryStructure](./doc/ProjectDirectoryStructure.md) |


### 项目根目录说明

| 目录 | 说明 | 备注 |
|:--:|:--:|:--:|
| doc | 文档目录 | 保存了项目所需的文档，描述了各个平台的配置，以及项目模块说明等。 |
| GrayCatQt | GrayCatQt模块 | 提供了基于QWidget，QGraphicsView自定义控件集。 |
| GrayCatQtQuick | GrayCatQtQuick模块 | 提供了基于Quick,Qml实现的自定义控件集合。 |
| GrayCatQtCore | GrayCatQtCore模块 | 提供了串口，网络，蓝牙，日志，线程等模块。 |
| Examples | 模块集成演示项目 | 该项目以QWidget为基础开发，演示了QWidget，QQuickWidget，QGraphicsView等模块的项目。 |
| scripts | 脚步文件路径 | 持续集成相关配置，用于自动化构建、发布所需要的脚步 |
| .github | github-Actions配置 | 持续集成相关配置，用于自动化构建、发布 |


### 现成模块

#### GrayCatQt 模块

| 目录 | 说明 | 文档 |
|:--:|:--:|:--:|
| GrayCatQt/Src/CatControl | 提供了自定义子控件 | [doc](./GrayCatQt/Src/CatControl/README.md) |
| GrayCatQt/Src/CatGraphiceView | 提供了基于GraphiceView模块与控件集 | [doc](./GrayCatQt/Src/CatGraphicsView/README.md) |
| GrayCatQt/Src/CatLog | 日志模块 | [doc](./GrayCatQt/Src/CatLog/README.md) |
| GrayCatQt/Src/CatNetWork | 网络模块 | [doc](./GrayCatQt/Src/CatNetWork/README.md) |
| GrayCatQt/Src/CatSerial | 串口模块 | [doc](./GrayCatQt/Src/CatSerial/README.md) |
| GrayCatQt/Src/CatUniversal | 通用模块，文件，字体，QSetting配置，线程，与线程池 | [doc](./GrayCatQt/Src/CatUniversal/README.md) |
| GrayCatQt/Src/CatWidget | 提供了基于Widget实现的模块，与CatControl不同的是它是由多个子控件实现的一整个模块体系。 | [doc](./GrayCatQt/Src/CatWidget/README.md) |
| GrayCatQt/Src/SingleApplication | 程序单例模块 | [doc](./GrayCatQt/Src/SingleApplication/README.md) |


#### Examples 项目

| 目录 | 说明 |
|:--:|:--:|
| Examples/CatQuickExamples | 演示项目开发中 |
| Examples/CatWidgetExamples | Widgdet版项目演示 |
| Examples/CatWidgetWebAssEmblyExamples | CatWidgetExamples裁减版WebAssmbly版项目演示 |
