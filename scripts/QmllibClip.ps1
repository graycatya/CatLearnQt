# qml 库裁剪工具，主要裁剪debug库和pdb文件
$curdir = Get-Location
$version = "1.0"

function TraversalClipPath($trClipPath) {
    #Write-Host "TraversalClipPath $trClipPath"

    Get-ChildItem $trClipPath | ForEach-Object -Process{
        if(!($_ -is [System.IO.FileInfo]))
        {
            #Write-Host($trClipPath + $_.name);
            $dirname = $_.name;
            $dirpath = $_.Fullname;
            Write-Host("path: " + $dirpath);
            TraversalClipPath $dirpath
            Remove-Item $dirpath\* -include *.pdb,*d.dll
        }
        
    }   
}


function Main {
    $clipdir = $args[0]

    # 判断裁剪目录是否有效
    if (![String]::IsNullOrEmpty($clipdir))
    {
        Write-Host "work dir $curdir, clipdir $clipdir"

        if(Test-Path $clipdir)
        {
            Write-Host "clipdir $clipdir valid"
            TraversalClipPath $clipdir
        } Else {
            Write-Host "clipdir $clipdir invalid"
            return;
        }
    } Else {
        Write-Host "clipdir is empty"
        return;
    }
}


Main $args