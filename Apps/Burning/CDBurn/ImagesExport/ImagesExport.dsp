# Microsoft Developer Studio Project File - Name="ImagesExport" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ImagesExport - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ImagesExport.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ImagesExport.mak" CFG="ImagesExport - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ImagesExport - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImagesExport - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ImagesExport - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Build\Bin"
# PROP Intermediate_Dir "..\..\Build\ImagesExport\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_WINDLL" /D "_AFXEXT" /D "WIN32" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 Uuid.lib shlwapi.lib JpegLib.lib /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "ImagesExport - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Build\BinDebug"
# PROP Intermediate_Dir "..\..\Build\\ImagesExport\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /EHsc /EHsc /GZ "_AFXDLL" /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Uuid.lib shlwapi.lib JpegLib.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ImagesExport - Win32 Release"
# Name "ImagesExport - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DataBackupInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\DynLine.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportDataTask.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportSettingsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ImagesExport.cpp
# End Source File
# Begin Source File

SOURCE=.\ImagesExport.def
# End Source File
# Begin Source File

SOURCE=.\ImagesExport.rc
# End Source File
# Begin Source File

SOURCE=.\JPEGFILE.CPP
# End Source File
# Begin Source File

SOURCE=.\ProgressAndTipDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WaitingExportImagesDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE="C:\Program Files\Microsoft Visual Studio\VC98\MFC\Include\AFXVER_.H"
# End Source File
# Begin Source File

SOURCE=.\DataBackupInterface.h
# End Source File
# Begin Source File

SOURCE=.\DynLine.h
# End Source File
# Begin Source File

SOURCE=.\ExportDataTask.h
# End Source File
# Begin Source File

SOURCE=.\ExportSettingsDlg.h
# End Source File
# Begin Source File

SOURCE=.\JCONFIG.h
# End Source File
# Begin Source File

SOURCE=.\JMORECFG.h
# End Source File
# Begin Source File

SOURCE=.\JPEGFILE.H
# End Source File
# Begin Source File

SOURCE=.\JPEGLIB.h
# End Source File
# Begin Source File

SOURCE=.\ProgressAndTipDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WaitingExportImagesDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\dynaline.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ImagesExport.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
