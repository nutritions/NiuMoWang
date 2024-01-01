@echo off
setlocal

set "registryPath=HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings"
set "registryKey=ProxyServer"

:: 通过reg query命令获取ProxyServer的值
for /f "tokens=2,*" %%A in ('reg query "%registryPath%" /v "%registryKey%" ^| find "%registryKey%"') do set "proxyServer=%%B"



:: 在终端中执行命令
git config --global https.proxy http://%proxyServer%"
git config --global http.proxy http://%proxyServer%"
git pull origin main

endlocal

