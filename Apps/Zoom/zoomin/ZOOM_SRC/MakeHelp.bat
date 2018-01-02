@echo off
echo Building Win32 Help files
start /wait hcw /C /E /M "ZoomIn.hpj"
if errorlevel 1 goto :Error
if not exist "ZoomIn.hlp" goto :Error
echo.
if exist Debug\nul copy "ZoomIn.hlp" Debug
if exist Release\nul copy "ZoomIn.hlp" Release
echo.
goto :done

:Error
echo ZoomIn.hpj(1) : error: Problem encountered creating help file

:done
echo.
