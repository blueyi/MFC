# Microsoft Developer Studio Project File - Name="Demo_Outlook" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Demo_Outlook - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Demo_Outlook.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Demo_Outlook.mak" CFG="Demo_Outlook - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Demo_Outlook - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Demo_Outlook - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Src/MFC demos/Demo_Outlook", KKDAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Demo_Outlook - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"..\Lib\Demo_Outlook.exe" /libpath:"..\Lib"

!ELSEIF  "$(CFG)" == "Demo_Outlook - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\Lib\Demo_Outlook.exe" /pdbtype:sept /libpath:"..\Lib"

!ENDIF 

# Begin Target

# Name "Demo_Outlook - Win32 Release"
# Name "Demo_Outlook - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Demo_Outlook.cpp
# End Source File
# Begin Source File

SOURCE=.\Demo_Outlook.rc
# End Source File
# Begin Source File

SOURCE=.\Demo_OutlookDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Demo_OutlookView.cpp
# End Source File
# Begin Source File

SOURCE=.\LeftView.cpp
# End Source File
# Begin Source File

SOURCE=.\ListMenuView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\RightView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Demo_Outlook.h
# End Source File
# Begin Source File

SOURCE=.\Demo_OutlookDoc.h
# End Source File
# Begin Source File

SOURCE=.\Demo_OutlookView.h
# End Source File
# Begin Source File

SOURCE=.\LeftView.h
# End Source File
# Begin Source File

SOURCE=.\ListMenuView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RightView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Calendar.ico
# End Source File
# Begin Source File

SOURCE=.\res\cj_logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Contacts.ico
# End Source File
# Begin Source File

SOURCE=.\res\Deleted.ico
# End Source File
# Begin Source File

SOURCE=.\res\Demo_Outlook.ico
# End Source File
# Begin Source File

SOURCE=.\res\Demo_Outlook.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Demo_OutlookDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\demo_ui_outlook.ico
# End Source File
# Begin Source File

SOURCE=.\res\demo_ui_outlookdoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Drafts.ico
# End Source File
# Begin Source File

SOURCE=.\res\header.bmp
# End Source File
# Begin Source File

SOURCE=.\res\header_0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\header_1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\header_2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\header_3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Inbox.ico
# End Source File
# Begin Source File

SOURCE=.\res\Journal.ico
# End Source File
# Begin Source File

SOURCE=.\res\Notes.ico
# End Source File
# Begin Source File

SOURCE=.\res\Outbox.ico
# End Source File
# Begin Source File

SOURCE=.\res\Outlook.ico
# End Source File
# Begin Source File

SOURCE=.\res\Public.ico
# End Source File
# Begin Source File

SOURCE=.\res\Sent.ico
# End Source File
# Begin Source File

SOURCE=.\res\Tasks.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section Demo_Outlook : {72ADFD6C-2C39-11D0-9903-00A0C91BC942}
# 	1:16:POPUP_RIGHT_VIEW:102
# End Section
