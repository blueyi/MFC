# Microsoft Developer Studio Project File - Name="TemplateMFC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TemplateMFC - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TemplateMFC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TemplateMFC.mak" CFG="TemplateMFC - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TemplateMFC - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TemplateMFC - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TemplateMFC - Win32 Release"

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
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ole32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "TemplateMFC - Win32 Debug"

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
# ADD CPP /nologo /MDd /W4 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "STRICT" /D _WIN32_WINNT=0x0400 /FD /c
# SUBTRACT CPP /Fr /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ole32.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "TemplateMFC - Win32 Release"
# Name "TemplateMFC - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AssociateObjectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CategoryNameDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CategoryTest.cpp
# End Source File
# Begin Source File

SOURCE=.\ComCatInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ComCatInformation.cpp
# End Source File
# Begin Source File

SOURCE=.\ComCatRegister.cpp
# End Source File
# Begin Source File

SOURCE=.\ComException.cpp
# End Source File
# Begin Source File

SOURCE=.\ComGUID.cpp
# End Source File
# Begin Source File

SOURCE=.\ComUsesCom.cpp
# End Source File
# Begin Source File

SOURCE=.\DisassociateDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GUIDRegistryList.cpp
# End Source File
# Begin Source File

SOURCE=.\JBListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\JBListBoxPair.cpp
# End Source File
# Begin Source File

SOURCE=.\JBListButton.cpp
# End Source File
# Begin Source File

SOURCE=.\JBListButtonList.cpp
# End Source File
# Begin Source File

SOURCE=.\Olestring.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistryKey.cpp
# End Source File
# Begin Source File

SOURCE=.\RegKeyIterator.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "TemplateMFC - Win32 Release"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "TemplateMFC - Win32 Debug"

# SUBTRACT CPP /YX /Yc

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TemplateMFC.cpp
# End Source File
# Begin Source File

SOURCE=.\TemplateMFC.rc
# End Source File
# Begin Source File

SOURCE=.\TemplateMFCDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Utils.cpp
# End Source File
# Begin Source File

SOURCE=.\Win32Exception.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AssociateObjectDlg.h
# End Source File
# Begin Source File

SOURCE=.\CategoryNameDlg.h
# End Source File
# Begin Source File

SOURCE=.\CategoryTest.h
# End Source File
# Begin Source File

SOURCE=.\ComCatInfo.hpp
# End Source File
# Begin Source File

SOURCE=.\ComCatInformation.hpp
# End Source File
# Begin Source File

SOURCE=.\ComCatRegister.hpp
# End Source File
# Begin Source File

SOURCE=.\ComException.hpp
# End Source File
# Begin Source File

SOURCE=.\ComGUID.hpp
# End Source File
# Begin Source File

SOURCE=.\ComGUIDListBox.hpp
# End Source File
# Begin Source File

SOURCE=.\ComUsesCom.hpp
# End Source File
# Begin Source File

SOURCE=.\DisassociateDlg.h
# End Source File
# Begin Source File

SOURCE=.\GUIDRegistryList.hpp
# End Source File
# Begin Source File

SOURCE=.\IEnumIterator.hpp
# End Source File
# Begin Source File

SOURCE=.\IterateCATEGORYINFO.hpp
# End Source File
# Begin Source File

SOURCE=.\IterateCATID.hpp
# End Source File
# Begin Source File

SOURCE=.\IterateGUID.hpp
# End Source File
# Begin Source File

SOURCE=.\RegistryList.hpp
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TemplateAFX.hpp
# End Source File
# Begin Source File

SOURCE=.\TemplateMFC.h
# End Source File
# Begin Source File

SOURCE=.\TemplateMFCDlg.h
# End Source File
# Begin Source File

SOURCE=.\TListBox.hpp
# End Source File
# Begin Source File

SOURCE=.\Win32Exception.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\TemplateMFC.ico
# End Source File
# Begin Source File

SOURCE=.\res\TemplateMFC.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\std.lnt
# End Source File
# End Target
# End Project
