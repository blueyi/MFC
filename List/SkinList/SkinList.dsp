# Microsoft Developer Studio Project File - Name="SkinList" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SkinList - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SkinList.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SkinList.mak" CFG="SkinList - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SkinList - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SkinList - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SkinList - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "SkinList - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
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

# Name "SkinList - Win32 Release"
# Name "SkinList - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\SkinHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\SkinHorizontalScrollbar.cpp
# End Source File
# Begin Source File

SOURCE=.\SkinList.cpp
# End Source File
# Begin Source File

SOURCE=.\SkinList.rc
# End Source File
# Begin Source File

SOURCE=.\SkinListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\SkinListDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SkinVerticleScrollbar.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SkinHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\SkinHorizontalScrollbar.h
# End Source File
# Begin Source File

SOURCE=.\SkinList.h
# End Source File
# Begin Source File

SOURCE=.\SkinListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\SkinListDlg.h
# End Source File
# Begin Source File

SOURCE=.\SkinVerticleScrollbar.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ColumnHeaderEnd.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ColumnHeaderSpan.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ColumnHeaderStart.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HorizontalScrollBarLeftArrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HorizontalScrollBarRightArrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HorizontalScrollBarSpan.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HorizontalScrollBarThumb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HorizontalScrollBarThumb2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ListCtrl_Tile.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ScrollBarArrowDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ScrollBarArrowUp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ScrollBarSpan.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ScrollBarThumb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ScrollBarTop.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SkinList.ico
# End Source File
# Begin Source File

SOURCE=.\res\SkinList.rc2
# End Source File
# Begin Source File

SOURCE=.\res\VerticleScrollbarBottom.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VerticleScrollBarDownArrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VerticleScrollBarSpan.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VerticleScrollBarThumb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VerticleScrollbarTop.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VerticleScrollBarUpArrow.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
