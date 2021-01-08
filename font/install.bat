
@echo off 
color 3f 
title 字体批量安装脚本 
echo A|xcopy *.ttf %windir%\fonts\ 
echo 安装完毕，任意键退出.... 
pause>nul 
exit 
