## Qt Installer Framework命令


Qt安装程序框架包含以下工具：

* installerbase(安装程序库)
* binarycreator(二进制创建者)
* repogen(您可以使用现有存储库将软件包重新打包到另一个存储库或脱机安装程序)
* archivegen(档案库)
* devtool(开发工具)


### installerbase

installerbase工具描述了核心安装程序本。所有数据和元信息都将打包到此二进制文件中。对于安装程序的创建过程，您无需直接调用它。

### binarycreator

使用该binarycreator工具创建离线和在线安装程序。组件信息和数据将附加到脱机安装程序二进制文件中，该文件使文件提取和安装后脚本无需Internet连接即可工作。

联机安装程序存储包含数据的存储库的位置。在启动时，他们加载组件信息，而不是数据。

您还可以创建混合安装程序，以在本地存储某些组件，并通过网络连接接收其他组件。

注意:如果更改此配置，则必须重新编译该installerbase工具。

您可以使用该binarycreator工具创建离线和在线安装程序。一些选项具有默认值，因此您可以忽略它们:

* Windows

```
<location-of-ifw>\binarycreator.exe -t  <location-of-ifw>\installerbase.exe -p <package_directory> -c <config_directory>\<config_file> <installer_name>
```

* Linux and macOS

```
<location-of-ifw>/binarycreator -t <location-of-ifw>/installerbase -p <package_directory> -c <config_directory>/<config_file> <installer_name>
```

要创建仅在线安装程序，可以使用--online-only，它定义了要从Web服务器上的在线存储库安装的所有软件包：

* Windows

```
<location-of-ifw>\binarycreator.exe -t <location-of-ifw>\installerbase.exe -p <package_directory> -c <config_directory>\<config_file> -e <packages> <installer_name>
```

* Linux and macOS

```
<location-of-ifw>/binarycreator -t <location-of-ifw>/installerbase -p <package_directory> -c <config_directory>/<config_file> -e <packages> <installer_name>
```


***binarycreator参数***

|参数|使用|
|---|---|
| -t or --template file | 使用file作为模板安装到二进制该部件信息被附加。如果省略此参数，installerbase则使用模板。 |
| -p or --packages directory | 使用directory作为包目录。默认为当前工作目录。 |
| --repository directory | 使用directory作为存储库目录与包重新包装。可以多次输入该条目。 |
| -n or --online-only | 无需安装程序二进制文件中的任何组件即可进行编译。 |
| -f or --offline-only | 创建一个永远不会访问在线存储库的脱机安装程序。 |
| -c or --config file | 使用file的配置文件。 |
| -e or --exclude p1,...,pn | 从联机存储库检索的软件包的逗号分隔列表。这些软件包不包含在安装程序二进制文件中。 |
| -i or --include p1,...,pn | 要从安装程序二进制文件中检索的软件包的逗号分隔列表。你不能合并或合并--include和--exclude。 |
| -r or --resources | 以逗号分隔的要包含在安装程序二进制文件中的资源列表。 |
| --ignore-translations | 禁用翻译文件以加快测试速度。 |
| --ignore-invalid-packages | 忽略没有有效元数据信息（package.xml）的组件或软件包目录，以加快测试速度。 |
| --ignore-invalid-repositories | 忽略没有有效元数据信息（Updates.xml）的存储库目录，而不是中止该目录。 |
| -v or --verbose | 显示调试输出。 |
| -s or --sign identity | 仅在macOS上可用。允许指定用于对生成的应用程序包进行签名的代码签名身份。 |

这些参数后跟目标二进制文件的名称以及可用于安装的软件包列表。

注意：除非您指定--nodeps参数，否则列出的软件包以及所有它们的依赖项和共享相同前缀的所有软件包都包含在安装程序中。

在通过--resources参数指定的可选资源文件中，fonts/可以使用特殊路径来发送自定义字体。这些字体将自动加载，因此在可通过StyleSheet变量指定的样式表中可用。

在Windows上，如果未指定扩展名，则目标二进制文件的名称将自动使用.exe扩展名。在Mac上，目标将作为带有扩展名.app的应用程序捆绑包创建，如果未提供，则会自动添加该扩展名。此外，您可以指定.dmg扩展名，以创建包含.app捆绑包的DMG磁盘映像。

***使用图标***

在macOS上，如果目标二进制文件带有.app后缀，则会创建一个macOS应用程序捆绑包。您在config.xml中指定的图标以.icns扩展，并用作创建的包的图标。

在Windows上，您在config.xml中指定的图标将以.ico扩展，并用作.exe文件的应用程序图标。

在Linux上，您在config.xml中指定的图标将扩展为.png并用作窗口图标。

### repogen

使用该repogen工具生成在线存储库。

该repogen工具按以下顺序需要以下参数：

```
repogen.exe -p <package_directory> <repository_directory>
```

创建存储库后，您可以将其上传到任何地方。在为其创建安装程序时，必须在安装程序配置文件中指定该位置。

您可以使用现有存储库将软件包重新打包到另一个存储库或脱机安装程序。


***repogen参数概述***

| 参数 | 使用 |
|---|---|
| -p or --packages directory | 使用directory作为包目录。这是强制性的。 |
| --repository directory | 使用directory与包库目录重新包装（不带有强制性目标库目录混淆）。可以多次输入该条目。 |
| repository directory | 存储库的目标目录。初始安装期间，该目录必须尚未存在。更新时，该目录可能存在并且其内容可能会被覆盖或删除。这是强制性的。 |
| -e or --exclude p1,...,pn | 软件包目录中所有软件包的集合中将忽略以逗号分隔的软件包列表。 |
| -i or --include p1,...,pn | 包目录中所有包的集合中要使用的包的逗号分隔列表 |
| --update | 更新packages目录中的所有软件包。该列表可以与被进一步过滤-i，-e参数。 |
| --update-new-components | 仅更新新组件或具有更高版本的组件。可以使用-i，-e参数进一步过滤列表。 |
| -r or --remove | 强制删除现有目标目录，然后再次生成它。 |
| -v or --verbose | 显示调试输出。 |

注意：我们建议您使用该--update-new-packages参数来更新现有存储库，尤其是在具有内容交付系统的情况下。这可帮助您避免更新未更改的组件，并且使内容交付系统更轻松地仅分发新文件，因为仅为已更新的组件分配了新的SHA校验和。


### archivegen

您可以用来archivegen将文件和目录打包到7zip（.7z）归档文件中。

该archivegen工具按以下顺序需要以下参数：

```
archivegen <name.7z> <data>
```

其中，<name.7z>是要创建的存档的路径和文件名，而<data>包含要打包到存档中的文件或目录的路径和名称，以空格分隔。

### devtool

您可以使用devtool新的安装程序基础来更新现有的安装程序或维护工具，将二进制内容从安装程序或维护工具转储到目标并执行操作。有关可用操作的摘要，请参见“操作”。

devtool 按以下顺序需要以下参数：

```
devtool [options] binary
```

其中binary是现有安装程序或维护工具的路径和名称。

devtool参数摘要

| 参数 | 使用 |
|---|---|
| -?, -h, --help | 显示帮助。 |
| -v, --version | 显示版本信息。 |
| --verbose | 显示其他信息。 |
| update <binary> <installerbase> | 使用新的安装程序基础更新现有的安装程序或维护工具。 |
| dump <binary> <folder> | 将属于安装程序或维护工具的二进制内容转储到目标中。 |
| operation <mode,name,args,...> | 执行带有参数列表的操作。
mode可以是DO或UNDO，具体取决于该步骤是否包含针对安装程序或卸载程序的说明。 |