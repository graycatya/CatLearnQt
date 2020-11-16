以下各节包含有关Qt安装程序框架的详细信息：

* 配置文件
* 包目录
* 控制器脚本
* 组件脚本
* 运作方式
* 工具类
* 脚本API
* C ++ API

## ***配置文件***


配置文件可自定义安装程序的用户界面和行为。该文件通常被调用config.xml并位于config目录中。

最小配置文件由一个<Installer>根元素<Name>和一个<Version>作为子元素的元素组成。所有其他元素都是可选的，并且可以按任意顺序出现。

以下示例显示了一个典型的配置文件：

```
<?xml version="1.0"?>
<Installer>
    <Name>Some Application</Name>
    <Version>1.0.0</Version>
    <Title>Some Application Setup</Title>
    <Publisher>Your Company</Publisher>
    <ProductUrl>http://www.your-fantastic-company.com</ProductUrl>
    <InstallerWindowIcon>installericon</InstallerWindowIcon>
    <InstallerApplicationIcon>installericon</InstallerApplicationIcon>
    <Logo>logo.png</Logo>
    <Watermark>watermark.png</Watermark>
    <RunProgram>@TargetDir@/YourAppToRun</RunProgram>
    <RunProgramArguments>
        <Argument>Argument 1</Argument>
        <Argument>Argument 2</Argument>
    </RunProgramArguments>
    <RunProgramDescription>My nice application</RunProgramDescription>
    <StartMenuDir>Some Application Entry Dir</StartMenuDir>
    <MaintenanceToolName>SDKMaintenanceTool</MaintenanceToolName>
    <AllowNonAsciiCharacters>true</AllowNonAsciiCharacters>
    <Background>background.png</Background>

    <TargetDir>@HomeDir@/testinstall</TargetDir>
    <AdminTargetDir>@RootDir@/testinstall</AdminTargetDir>
    <RemoteRepositories>
        <Repository>
            <Url>http://www.your-repo-location/packages/</Url>
        </Repository>
    </RemoteRepositories>
</Installer>
```

##### 配置文件元素摘要

下表总结了配置文件中的元素。

注意：我们建议您将引用的所有文件放在config目录的配置文件中。但是，您也可以使用相对路径，这些路径工具会相对于config.xml文件的位置进行解析。

您可以使用预定义的变量（嵌入@字符）作为元素的值。有关更多信息，请参见预定义变量。

| 元素 | 描述 |
|--|--|
| Name | 正在安装的产品的名称。这是强制性的。 |
| Version | 正在安装的产品版本格式:[0-9]+(((\.|-)[0-9]+)*如1-1;1.2 - 2;3.4.7。这是强制性的。 |
| Title | 安装程序的名称，显示在标题栏上。 |
| Publisher | 软件的发行者(如视窗控制面板所示)。 |
| ProductUrl | URL指向web站点上包含产品信息的页面。 |
| Icon | 自定义安装程序图标的文件名。通过附加一个'.icns' (macOS), '.ico' (Windows) or '.png' (Unix)来查找实际文件后缀。不赞成使用<InstallerApplicationIcon>或<InstallerWindowIcon>代替。 |
| InstallerApplicationIcon | 自定义安装程序图标的文件名。通过附加一个 '.icns' (macOS), '.ico' (Windows).来查找实际的文件。在Unix上没有此功能。 |
| Logo | 用于QWizard::LogoPixmap徽标的文件名。 |
| Watermark | 水印的文件名用于QWizard::WatermarkPixmap。 |
| Banner | 标题的文件名用作QWizard::BannerPixmap(仅用于现代风格)。 |
| Background | 用作QWizard::BackgroundPixmap(仅用于MacStyle)图像的文件名。 |
| WizardStyle | 设置要使用的向导样式("Modern", "Mac", "Aero" or "Classic"). |
| StyleSheet | 设置样式表文件。 |
| WizardDefaultWidth | 设置向导的默认宽度，单位为像素。设置一个横幅图像将覆盖这一点。您可以向指定的值添加em或ex后缀来使用em或ex单元，就像在CSS文件中一样。 |
| WizardDefaultHeight | 设置向导的默认高度，单位为像素。设置一个水印图像将覆盖这一点。您可以向指定的值添加em或ex后缀来使用em或ex单元，就像在CSS文件中一样。 |
| TitleColor | 设置标题和字幕的颜色(接受HTML颜色代码，如“#88FF33”)。 |
| RunProgram | 如果用户接受操作，则安装程序完成后执行的命令。提供应用程序的完整路径。 |
| RunProgramArguments | 传递给<RunProgram>中指定的程序的参数。您可以添加几个<Argument>子元素，每个子元素指定<RunProgram>的一个参数。 |
| RunProgramDescription | 安装后运行程序的复选框旁边显示的文本。如果设置了<RunProgram>但没有提供描述，UI现在将显示Run <Name>。代替。 |
| StartMenuDir | Windows开始菜单中该产品的默认程序组的名称。 |
| TargetDir | 安装的默认目标目录。在Linux上，这通常是用户的主目录。 |
| AdminTargetDir | 具有管理员权限的安装的默认目标目录。仅在Linux上可用，在Linux上您通常不希望安装在管理员用户的主目录中。 |
| RemoteRepositories | 远程存储库列表。该元素可以包含几个<Repository>子元素，每个子元素都包含指定访问存储库的Url的<Url>子元素。有关更多信息，请参见配置存储库。 |
| RepositoryCategories | 可以包含<RemoteRepositories>子元素列表的类别的名称。有关更多信息，请参见配置存储库类别。 |
| MaintenanceToolName | 生成的维护工具的文件名。默认为maintenancetool。附加特定于平台的可执行文件扩展名。 |
| RemoveTargetDir | 如果卸载时不应该删除目标目录，则设置为false。 |
| AllowNonAsciiCharacters | 如果安装路径可以包含非ascii字符，则设置为true。 |
| DisableAuthorizationFallback | 如果安装在出现授权错误时不要求用户运行授权回退，则设置为true。相反，立即中止安装。 |
| RepositorySettingsPageVisible | 设置为false将存储库设置页隐藏在设置对话框内。 |
| AllowSpaceInPath | 如果安装路径不包含空格字符，则设置为false。 |
| DependsOnLocalInstallerBinary | 如果希望从外部资源(如网络驱动器)禁止安装，则设置为true。这对于大型安装程序来说是有意义的。该选项仅在Windows上使用。 |
| TargetConfigurationFile | 目标上配置文件的文件名。默认是components.xml。 |
| Translations | 用于翻译用户界面的语言代码列表。要添加多个语言变体，请指定几个<Translation>子元素，每个子元素指定语言变体的名称。可选的。有关更多信息，请参见翻译页面。 |
| UrlQueryString | 该字符串需要以"key=value"的形式出现，并将被附加到存档下载请求中。这可以用来将信息传输到承载存储库的web服务器。 |
| ControlScript | 自定义安装程序控制脚本的文件名。看控制器脚本。 |
| CreateLocalRepository | 如果您想在安装目录中创建一个本地存储库，请设置为true。此选项对在线安装程序没有影响。存储库将自动添加到默认存储库列表中。 |
| InstallActionColumnVisible | 如果希望在组件树中添加显示安装操作的额外列，则设置为true。这个额外的列指示组件是要安装还是卸载，还是保持安装还是卸载。 |
| SupportsModify | 如果产品不支持修改现有安装，则设置为false。 |
| SaveDefaultRepositories | 如果不应该保存到MaintenanceToolName.ini，则设置为false。默认情况下保存默认存储库<RemoteRepositories>。不保存存储库意味着您运行maintenancetool时没有使用默认存储库。 |
| AllowUnstableComponents | 如果其他组件允许安装，尽管有不稳定的组件，设置为true。如果组件缺少依赖项，脚本中有错误，等等，那么它是不稳定的。不稳定组件在组件树中是灰色的，因此不能被选择。默认情况下，该值为false，这意味着如果发现不稳定的组件，安装将中止。 |


## ***包目录***

安装程序包含嵌入到安装程序中或从远程存储库加载的组件。在这两种情况下，都需要为安装程序可以读取的组件使用文件格式和结构。

#### 包目录结构

将所有组件放在同一根目录中，该根目录称为package目录。该目录名称充当类似于域的标识符，用于标识所有组件。例如，com.vendor.root。

在根目录中，创建名为data和的子目录meta。

软件包目录如下所示：

```
-packages
    - com.vendor.root
        - data
        - meta
    - com.vendor.root.component1
        - data
        - meta
    - com.vendor.root.component1.subcomponent1
        - data
        - meta
    - com.vendor.root.component2
        - data
        - meta
```

#### 元目录

该meta目录包含指定部署设置和安装过程的文件。安装程序不会提取文件。该目录必须至少包含一个软件包信息文件以及您在软件包信息文件中引用的所有文件，例如脚本，用户界面文件和翻译。

#### 软件包信息文件语法


package.xml文件是有关组件的主要信息来源。以下是打包文件的示例：

```
<?xml version="1.0"?>
<Package>
    <DisplayName>QtGui</DisplayName>
    <Description>Qt gui libraries</Description>
    <Description xml:lang="de_de">Qt GUI Bibliotheken</Description>
    <Version>1.2.3</Version>
    <ReleaseDate>2009-04-23</ReleaseDate>
    <Name>com.vendor.root.component2</Name>
    <Dependencies>com.vendor.root.component1</Dependencies>
    <Virtual>false</Virtual>
    <Licenses>
        <License name="License Agreement" file="license.txt" />
    </Licenses>
    <Script>installscript.qs</Script>
    <UserInterfaces>
        <UserInterface>specialpage.ui</UserInterface>
        <UserInterface>errorpage.ui</UserInterface>
    </UserInterfaces>
    <Translations>
        <Translation>sv_se.qm</Translation>
        <Translation>de_de.qm</Translation>
    </Translations>
    <DownloadableArchives>component2.7z, component2a.7z</DownloadableArchives>
    <AutoDependOn>com.vendor.root.component3</AutoDependOn>
    <SortingPriority>123</SortingPriority>
    <UpdateText>This changed compared to the last release</UpdateText>
    <Default>false</Default>
    <ForcedInstallation>false</ForcedInstallation>
    <Essential>false</Essential>
    <Replaces>com.vendor.root.component2old</Replaces>
</Package>
```

#### 软件包信息文件元素的摘要

| 元素 | 描述 |
|--|--|
| DisplayName | 可读的组件名称。必需的。将组件名称的翻译指定为附加DisplayName标记的值，并将xml:lang属性设置为正确的语言环境。 |
| Description | 可读的组件描述。必需的。翻译的指定可以类似于DisplayName标签。如果没有找到与语言环境匹配的本地化，并且存在未翻译的版本，则将使用该本地化。否则将不会显示该语言环境的描述。用户可点击的外部链接，例如组件的主页，可以通过指定一个URL地址包括在组件描述中:{external-link}='https://www.qt.io/'。URL必须是有效的，并包含到所需资源的完整路径。 |
| Version | 组件版本号按以下格式:[0-9]+((\.|-)[0-9]+)*如1-1;1.2 - 2;3.4.7。必需的。如果一个包需要显示子包的版本号而不是它自己的版本号(由于对子包进行分组)，那么可以指定属性inheritVersionFrom和需要继承的版本的包名。 |
| ReleaseDate | 该组件版本发布的日期。必需的。 |
| Name | 此组件的类域标识。必需的。 |
| Dependencies | 此组件所依赖的组件的标识符的逗号分隔列表。也可以指定版本号，用破折号(-)分隔。可以在版本号前面加上比较运算符(=、>、<、>=或<=)。请记住，必须使用字符引用"&lt;"来转义左尖括号(用"&lt;"代替"<"，用"&lt;="代替"<=")。可选的。有关更多信息，请参见组件依赖关系。 |
| AutoDependOn | 此组件自动依赖的组件的标识符的逗号分隔列表。当且仅当所有指定的依赖项都得到满足时，才会安装该组件。如果一个组件自动依赖于其他组件，那么在组件树中，该组件旁边的复选框将不可见。选择将自动执行。如果之前没有安装该组件，则只有在也选择此列表中的所有组件进行安装时才会选择该组件进行安装。如果已经安装了该组件，则在此列表中至少有一个组件也被选择用于卸载时，将选择该组件进行卸载。有关更多信息，请参见组件依赖关系。 |
| Virtual | 设置为true将组件从安装程序中隐藏。注意，在根组件上设置这个参数是无效的。 |
| SortingPriority | 树中组件的优先级。树从最高优先级到最低优先级排序，最高优先级位于顶部。 |
| Licenses | 安装用户接受的许可协议列表。要添加多个许可证，请添加几个<License>子元素，每个元素指定许可证名称和文件。许可文件支持ASCII和UTF8文件格式。
如果该组件列出了翻译，安装程序还将查找翻译的许可证。这些文件需要与原始许可文件具有相同的名称，但要添加语言环境标识符。例如，如果许可文件名为license.txt，并且指定了德语翻译，安装程序还将包括一个license_de_de.txt文件(并在安装德语系统时显示)。 |
| Script | 正在加载的脚本的文件名。可选的。有关更多信息，请参见添加操作。 |
| UserInterfaces | 要加载的页面列表。要添加多个页面，请添加几个<UserInterface>子元素，每个元素指定页面的文件名。可选的。有关更多信息，请参见添加页面。 |
| Translations | 要加载的翻译文件列表。要添加多个语言变体，请指定几个<Translation>子元素，每个子元素指定语言变体的文件名。可选的。有关更多信息，请参见翻译页面。 |
| UpdateText | 如果这是对组件的更新，则添加到组件描述。可选的。 |
| Default | 可能的值是:真、假和脚本。设置为true以在安装程序中预选组件。这只对没有可见子组件的组件有效。布尔值直接计算，而脚本在运行时解析。将脚本名称作为< script >元素的值添加到该文件中。有关示例脚本，请参见选择默认内容。 |
| Essential | 将包标记为强制重新启动维护程序库的必要组件。如果基本组件有可用的更新，则包管理器将保持禁用状态，直到该组件得到更新。在运行更新程序时，会自动安装新引入的必要组件。 |
| ForcedInstallation | 确定必须始终安装包。终端用户无法在安装程序中取消选择。 |
| Replaces | 要替换的组件的逗号分隔列表。可选的。 |
| DownloadableArchives | 列出在线安装程序要下载的数据文件(以逗号分隔)。如果组件中有一些数据，并且包.xml和/或脚本没有DownloadableArchives值，那么repogen工具会自动注册找到的数据。 |
| RequiresAdminRights | 如果包需要以提升的权限安装，则设置为true。可选的。 |
| Checkable | 如果要隐藏某项的复选框，请将该值设置为false。当应该只选择少数子组件而不是所有子组件时，这是有用的。可选的。 |
| ExpandedByDefault | 如果想在默认情况下展开此项，则设置为真。可选的。 |


#### 组件依赖性

组件可以取决于一个或几个实际或虚拟组件。依赖关系是通过使用组件标识符和（可选）组件版本来定义的。使用破折号（-）将版本号与标识符分开。

您可以使用比较运算符（=，>，＆lt;（<），> =或＆lt; =（<=））作为版本号的前缀，以指示该软件包的版本号已与所需版本进行比较，并且必须为等于，大于，小于，大于或等于或小于依赖性中指定的版本号。如果没有给出比较运算符，则默认为=。

#### 资料目录

该data目录包含安装程序在安装过程中提取的内容。您必须将数据打包为7zip存档（.7z）。您可以使用Qt Installer框架随附的archivegen工具，也可以使用其他生成7zip存档的工具。