mkdir _backup
cd _backup
del _backup.zip
mkdir hlp
mkdir res
cd ..
pause
cls
copy *.zip     _backup\*.*
copy *.h     _backup\*.*
copy *.pfl     _backup\*.*
pause
cls
copy *.cpp   _backup\*.*
pause
cls
copy *.rc    _backup\*.*
copy *.mak   _backup\*.*
copy *.tx*   _backup\*.*
copy *.def   _backup\*.*
pause
cls
copy *.clw   _backup\*.*
copy *.aps   _backup\*.*
copy *.bat   _backup\*.*
copy *.mdp   _backup\*.*
pause
cls
copy res\*.* _backup\res\*.*
pause
cls
copy hlp\*.* _backup\hlp\*.*
rem copy __data\*.* _backup\__data\*.*
echo.
echo.
echo WILL NOW ZIP THE FILES
pause
cls
cd _backup
if not exist stdafx.h goto jump2
if exist _backup.zip goto junp2
zip _backup
goto jump3
:jump2
echo MAJOR ERROR   MAJOR ERROR   MAJOR ERROR   MAJOR ERROR   MAJOR ERROR 
pause
:jump3
cls
echo off
echo.
echo.
echo                   ALL DONE !!!
