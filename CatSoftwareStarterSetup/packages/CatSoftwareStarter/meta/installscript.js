function Component()
{
}



function operationForLinux()
{
    var params = "Name=CatSoftwareStarter" + "\n";
    params += "Icon=@TargetDir@/../../Resource/logo.png" + "\n";
    params += "Version=@Version@" + "\n";
    params += "Exec=@TargetDir@/CatSoftwareStarter" + "\n";
    params += "Terminal=false" + "\n";
    params += "Encoding=UTF-8" + "\n";
    params += "Type=Application" + "\n";
    params += "Categories=Network" + "\n";
 
    var desktop = "CatSoftwareStarter.desktop";
    component.addOperation("CreateDesktopEntry", desktop, params);
 
    var homeDir = installer.environmentVariable("HOME");
    if(homeDir.length > 0)
    {
        var XDG_DATA_HOME = installer.environmentVariable("XDG_DATA_HOME"); //获取XDG_DATA_HOME环境变量
        if(XDG_DATA_HOME.length > 0)
        {
	        var XDG_DESKTOP_DIR = installer.environmentVariable("XDG_DESKTOP_DIR");
            component.addOperation("Copy", XDG_DATA_HOME+"/applications/" + desktop, homeDir + XDG_DESKTOP_DIR);
        }
    }
}

function operationForWindows()
{
    //开始菜单快捷方式
    component.addOperation("CreateShortcut",                // 创建快捷方式
        "@TargetDir@/CatWidgetExamples.exe",    // 默认安装目录/CatWidgetExamples.exe
        "@StartMenuDir@/CatWidgetExamples/CatWidgetExamples.lnk", //开始菜单
        "workingDirectory=@TargetDir@");
        
    component.addOperation("CreateShortcut",                // 创建快捷方式
        "@TargetDir@/MaintenanceTool.exe",    // 默认安装目录/MaintenanceTool.exe
        "@StartMenuDir@/CatWidgetExamples/MaintenanceTool.lnk", //开始菜单
        "workingDirectory=@TargetDir@");

    //桌面快捷方式
    component.addOperation("CreateShortcut",
        "@TargetDir@/CatWidgetExamples.exe",
        "@DesktopDir@/CatWidgetExamples.lnk",
        "workingDirectory=@TargetDir@");
}



Component.prototype.createOperations = function()
{
    component.createOperations(); 
    if (systemInfo.productType === "windows") 
	{
        operationForWindows();
    } else if(systemInfo.productType === "linux")
    {
        operationForLinux();
    }
}
