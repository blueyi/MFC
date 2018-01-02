# Microsoft Developer Studio Project File - Name="ExToolBar" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ExToolBar - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ExToolBar.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ExToolBar.mak" CFG="ExToolBar - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ExToolBar - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ExToolBar - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ExToolBar - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "CoolBar" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ExToolBar - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "CoolBar" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ExToolBar - Win32 Release"
# Name "ExToolBar - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ExToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ExToolBar.odl
# End Source File
# Begin Source File

SOURCE=.\ExToolBar.rc

!IF  "$(CFG)" == "ExToolBar - Win32 Release"

!ELSEIF  "$(CFG)" == "ExToolBar - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ExToolBarDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ExToolBarView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\OOExToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ExToolBar.h
# End Source File
# Begin Source File

SOURCE=.\ExToolBarDoc.h
# End Source File
# Begin Source File

SOURCE=.\ExToolBarView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\16_std_toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\16_std_toolbar_bw.bmp
# End Source File
# Begin Source File

SOURCE=.\res\16_std_toolbar_db.bmp
# End Source File
# Begin Source File

SOURCE=.\res\256_std_toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\256_std_toolbar_bw.bmp
# End Source File
# Begin Source File

SOURCE=.\res\256_std_toolbar_db.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\256_wnd_toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\256_wnd_toolbar_bw.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\256_wnd_toolbar_db.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ExToolBar.ico
# End Source File
# Begin Source File

SOURCE=.\res\ExToolBar.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ExToolBarDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\id_filen.ico
# End Source File
# Begin Source File

SOURCE=.\res\Image3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LG.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LGBW.bmp
# End Source File
# Begin Source File

SOURCE=.\res\small_16_std_toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\small_16_std_toolbar_bw.bmp
# End Source File
# Begin Source File

SOURCE=.\res\small_16_std_toolbar_db.bmp
# End Source File
# Begin Source File

SOURCE=.\res\small_256_std_toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\small_256_std_toolbar_bw.bmp
# End Source File
# Begin Source File

SOURCE=.\res\small_256_std_toolbar_db.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\small_256_wnd_toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\small_256_wnd_toolbar_bw.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\small_256_wnd_toolbar_db.bmp
# End Source File
# Begin Source File

SOURCE=".\res\smartsensor 2.ico"
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\toolbar1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ExToolBar.reg
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
