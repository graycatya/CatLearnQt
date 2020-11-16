## 定制安装程序

您可以通过以下方式使用脚本来定制安装程序：

* 添加由脚本准备并由安装程序执行的 Qt Installer Framework 操作。
* 添加您在package.xml文件中指定的新页面并将其放置在packages目录中。
* 通过将自定义用户界面元素作为单个窗口小部件插入到现有页面中来进行修改。
* 添加语言国际化。

您可以同时使用组件脚本和控制脚本来自定义安装程序。通过在Script组件的package.xml文件的元素中指定组件脚本，可以将组件脚本与特定组件关联。提取组件的元数据时将加载脚本。有关组件脚本的更多信息，请参见组件脚本。

通过在安装程序ControlScript的control.xml文件的元素中指定控制脚本，可以将其与整个安装程序关联。控制脚本可以是安装程序资源的一部分，也可以在命令行中传递。它们可用于修改在加载组件之前向用户显示的安装程序页面。另外，您可以使用它们来修改卸载程序中的页面。有关更多信息，请参见Controller Scripting。

有关可在组件和控制脚本中使用的全局JavaScript对象的更多信息，请参见Scripting API。

### 添加操作

您可以在安装过程中使用组件脚本执行Qt Installer Framework操作。通常，操作通过移动，复制或打补丁来操纵文件。使用QInstaller::Component::addOperation或QInstaller::Component::addElevatedOperation函数添加操作。有关更多信息，请参见向组件添加操作。

此外，可以通过派生KDUpdater::UpdateOperation实现在安装程序中注册自定义安装操作的方法。有关更多信息，请参见注册自定义操作。

有关可用操作的摘要，请参见操作。


### 添加页面

一个组件可以包含一个或多个用户界面文件，这些文件由一个组件或控制脚本放置在安装程序中。安装程序将自动加载UserInterfacespackage.xml文件的元素中列出的所有用户界面文件。

### 使用组件脚本添加页面

要向安装程序添加新页面，请使用installer::addWizardPage()方法并指定新页面的位置。例如，下面的代码在准备安装页面之前添加了一个MyPage实例:

```
installer.addWizardPage( component, "MyPage", QInstaller.ReadyForInstallation );
```

您可以使用组件脚本来访问加载的小部件，方法是使用组件的类名调用component::userInterface()方法，如下面的代码片段所示:

```
component.userInterface( "MyPage" ).checkbox.checked = true;
```

您还可以为添加的页面提供一个回调。要访问它，使用UI文件中设置的对象名称(例如，“MyPage”)。然后创建动态${ObjectName}回调函数(例如DynamicMyPageCallback):

```
Component.prototype.DynamicMyPageCallback = function()
{
    var page = gui.pageWidgetByObjectName("DynamicMyPage");
    page.myButton.click,
    page.myWidget.subWidget.setText("hello")
}
```

您可以通过使用UI文件中设置的小部件对象名称来访问它们。例如，myButton和myWidget是上面代码中的小部件对象名称。

### 添加小部件

您可以使用组件或控制脚本将自定义用户界面元素作为单个窗口小部件（例如复选框）插入安装程序。

要插入单个小部件，请使用installer::addWizardPageItem方法。例如，下面的代码片段将MyWidget实例从脚本中添加到组件选择页面:

```
installer.addWizardPageItem( component, "MyWidget", QInstaller.ComponentSelection );
```

### 与安装程序功能交互

例如，您可以使用控制脚本在测试中自动执行安装程序功能。以下代码段说明了如何自动单击目标目录选择页面上的“ 下一步”按钮：

```
Controller.prototype.TargetDirectoryPageCallback = function()
{
    gui.clickButton(buttons.NextButton);
}
```

### 翻译页面

安装程序使用Qt转换系统来支持将用户可读的输出转换为多种语言。要为最终用户提供组件脚本和用户界面中包含的字符串的本地化版本，请创建QTranslator文件，安装系统将与组件一起加载该文件。安装程序将加载与当前系统区域设置匹配的转换文件。例如，如果系统区域设置为德语，则将加载de.qm文件。此外，如果找到本地化语言，license_de.txt则显示该语言而不是默认语言license.txt。

需要将翻译添加到package.xml要为组件激活的文件中：


```
<Translations>
    <Translation>de.qm</Translation>
</Translations>
```

qsTr()在脚本中将函数用于文字文本。此外，您可以将Component.prototype.retranslateUi方法添加到脚本中。当安装程序的语言发生更改并加载翻译文件时，将调用该方法。

用于翻译的上下文是使用时脚本文件的基本名称，qsTr或者是翻译用户界面时UI文件的类名称。例如，如果脚本文件名为installscript.qs，则上下文将为installscript。

注意：翻译系统也可以用于自定义UI。使用例如en.ts文件将安装程序中的任何文本替换为自定义英文版本。