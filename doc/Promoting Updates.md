## 促进更新

创建在线安装程序，以便能够向安装您的产品的最终用户推广更新。

需要以下步骤来促进更新：

1. 将更新的内容复制到软件包目录。
2. 增加<Version>package.xml文件中已更新组件的元素值。
3. 使用该repogen工具重新创建具有更新内容的联机存储库，并在存储库的根目录中生成Updates.xml文件。
4. 将存储库上载到Web服务器。
5. 使用该binarycreator工具创建安装程序。

### 配置更新

安装程序在启动时会下载Updates.xml文件，并将安装的版本与文件中的版本进行比较。如果文件中的联机版本号大于本地版本号，则安装程序将其显示在可用更新列表中。

<Version>在package.xml文件中增加组件元素的值。

### 重新创建存储库

提供更新的最简单方法是重新创建存储库并将其上载到Web服务器。有关更多信息，请参见创建存储库。

### 部分更新存储库

在以下情况下，对整个存储库进行完整更新可能不是最佳选择：

* 该存储库非常大，因为上传会花费很长时间。
* 您只想交付已更改的组件。


注意:每次调用7zip归档时，repogen都会重新创建它。由于7zip存储所包含文件(在此过程中移动或复制)的时间戳，所以每个归档文件的SHA和会发生变化。SHA sum用于验证存档的下载，因此SHA需要与7zip匹配。由于SHAs存储在update .xml文件中，您将被迫上传完整的存储库。这可以通过使用repogen的——update选项来规避。


### 创建部分更新

重新创建在线存储库时，请使用--update参数。它以现有存储库作为输入，仅更改指定为其他参数的组件。全局配置中也仅更改那些SHA总和。

### 上载部分更新

将以下项目上载到Web服务器：

* 组件目录（通常类似于com.vendor.product.updatedpart）。

* 全局Updates.xml存储在联机存储库的根目录中。

注意：上传项目的顺序非常重要。如果在实时服务器上更新存储库，请首先更新组件，然后更新Updates.xml。软件包名称包括版本号，因此，最终用户会收到旧软件包，直到新软件包完全上传为止。


### 变更储存库

要使当前更新存储库指向其他存储库，请在当前存储库中编辑Updates.xml文件。您可以添加，替换或删除存储库。

```
<RepositoryUpdate>
    <Repository action="..." OPTIONS />
    <Repository action="..." OPTIONS />
</RepositoryUpdate>
```

### 添加存储库

要更新存储库，请使用以下选项将<Repository>子元素添加到<RepositoryUpdate>元素：

```
<Repository action="add" url="http://www.example.com/repository" name="user" password="password"
               displayname="Example Repository" />
```

url将被用作基本url来解析针对的update .xml文件。如果url本身是相对的，它将根据当前文档的基url进行解析。

displayname指定如何在维护工具的设置页面中命名存储库。

名称和密码可选地指定受保护存储库的凭据。


### 删除存储库

要删除存储库，请使用以下选项将<Repository>子元素添加到<RepositoryUpdate>元素：

```
<Repository action="remove" url="http://www.example.com/repository" />
```

url 必须与要删除的网址完全匹配。

#### 更换储存库

要将一个存储库替换为另一个存储库，请使用以下选项将<Repository>子元素添加到该<RepositoryUpdate>元素：

```
<Repository action="replace" oldUrl="http://www.example.com/repository"
            newUrl="http://www.example.com/newrepository" name="user" password="password"
            displayname="New Example Repository" />
```

oldUrl 必须与要替换的网址完全匹配。

newUrl 必须与要替换的网址完全匹配。

#### 可移动存储库

一些项目包含多个存储库。要创建一组可重定位的存储库，您应该使用相对路径。
因此，如果在地址http://www.example.com/repositories/generic和Updates.xml上可用的通用存储库包含< repository >元素和以下选项:

```
<Repository action="add" url="../module" name="user" password="password"
            displayname="Module Repository" />
```

然后，添加的存储库的解析地址将是http://www.example.com/repositories/module，这样存储库就不包含关于它们的绝对位置的信息。

如果您想要更改地址，只需原样复制一组存储库即可。建议在一段时间内维护旧的通用存储库，并替换如上所述的地址。您还可以为更新后的安装程序提供新的通用地址。

可以为<Repository>元素中的参数url、oldUrl和newUrl使用相对路径。

