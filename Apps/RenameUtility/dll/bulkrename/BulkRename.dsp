# Microsoft Developer Studio Project File - Name="BulkRename" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=BulkRename - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BulkRename.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BulkRename.mak" CFG="BulkRename - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BulkRename - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "BulkRename - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BulkRename - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\Debug"
# PROP BASE Intermediate_Dir "..\..\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Debug"
# PROP Intermediate_Dir "..\..\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /I ".\inc" /I ".\third_party\inc" /I " ..\..\inc" /ZI /W3 /Od /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_USRDLL" /D "__BULKRENAME" /D "_AFXDLL" /D "_MBCS" /Gm /YX /GZ /c /GX 
# ADD CPP /nologo /MDd /I ".\inc" /I ".\third_party\inc" /I " ..\..\inc" /ZI /W3 /Od /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_USRDLL" /D "__BULKRENAME" /D "_AFXDLL" /D "_MBCS" /Gm /YX /GZ /c /GX 
# ADD BASE MTL /nologo /D"_DEBUG" /win32 
# ADD MTL /nologo /D"_DEBUG" /win32 
# ADD BASE RSC /l 1033 /d "_DEBUG" /i "$(IntDir)" 
# ADD RSC /l 1033 /d "_DEBUG" /i "$(IntDir)" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib shlwapi.lib /nologo /dll /out:"..\..\Debug\BulkRename.dll" /incremental:yes /def:".\src\BulkRename.def" /debug /pdbtype:sept /subsystem:windows /implib:"$(OutDir)/BulkRename.lib" /machine:ix86 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib shlwapi.lib /nologo /dll /out:"..\..\Debug\BulkRename.dll" /incremental:yes /def:".\src\BulkRename.def" /debug /pdbtype:sept /subsystem:windows /implib:"$(OutDir)/BulkRename.lib" /machine:ix86 

!ELSEIF  "$(CFG)" == "BulkRename - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\release"
# PROP BASE Intermediate_Dir "..\..\release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\release"
# PROP Intermediate_Dir "..\..\release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /I ".\inc" /I ".\third_party\inc" /I " ..\..\inc" /Zi /W3 /O2 /Og /Ob1 /Oy /G6 /GA /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_USRDLL" /D "__BULKRENAME" /D "_AFXDLL" /D "_MBCS" /GF /Gy /YX /c /GX 
# ADD CPP /nologo /MD /I ".\inc" /I ".\third_party\inc" /I " ..\..\inc" /Zi /W3 /O2 /Og /Ob1 /Oy /G6 /GA /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_USRDLL" /D "__BULKRENAME" /D "_AFXDLL" /D "_MBCS" /GF /Gy /YX /c /GX 
# ADD BASE MTL /nologo /D"NDEBUG" /win32 
# ADD MTL /nologo /D"NDEBUG" /win32 
# ADD BASE RSC /l 1033 /d "NDEBUG" /i "$(IntDir)" 
# ADD RSC /l 1033 /d "NDEBUG" /i "$(IntDir)" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib shlwapi.lib /nologo /dll /out:"..\..\release\BulkRename.dll" /incremental:no /def:".\src\BulkRename.def" /debug /pdbtype:sept /subsystem:windows /opt:ref /opt:icf /implib:"$(OutDir)/BulkRename.lib" /machine:ix86 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib shlwapi.lib /nologo /dll /out:"..\..\release\BulkRename.dll" /incremental:no /def:".\src\BulkRename.def" /debug /pdbtype:sept /subsystem:windows /opt:ref /opt:icf /implib:"$(OutDir)/BulkRename.lib" /machine:ix86 

!ENDIF

# Begin Target

# Name "BulkRename - Win32 Debug"
# Name "BulkRename - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;def;odl;idl;hpj;bat;asm"
# Begin Source File

SOURCE=src\BulkRename.cpp
# End Source File
# Begin Source File

SOURCE=src\BulkRename.def
# End Source File
# Begin Source File

SOURCE=src\bulkrenameclass.cpp
# End Source File
# Begin Source File

SOURCE=src\stdafx.cpp
# End Source File
# Begin Group "third_party"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\third_party\src\genfile.cpp
# End Source File
# Begin Source File

SOURCE=.\third_party\Src\HtmlLogger.cpp
# End Source File
# Begin Source File

SOURCE=third_party\src\Path.cpp
# End Source File
# Begin Source File

SOURCE=.\third_party\Src\SmartString.cpp
# End Source File
# Begin Source File

SOURCE=third_party\src\Tokenizer.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;inc"
# Begin Source File

SOURCE=inc\BulkRename.h
# End Source File
# Begin Source File

SOURCE=..\..\inc\bulkrenameclass.h
# End Source File
# Begin Source File

SOURCE=inc\Resource.h
# End Source File
# Begin Source File

SOURCE=inc\stdafx.h
# End Source File
# Begin Group "third_party"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\third_party\inc\genfile.h
# End Source File
# Begin Source File

SOURCE=.\third_party\Inc\HtmlLogger.h
# End Source File
# Begin Source File

SOURCE=third_party\inc\Path.h
# End Source File
# Begin Source File

SOURCE=.\third_party\Inc\SmartString.h
# End Source File
# Begin Source File

SOURCE=.\third_party\Inc\synchronizations.h
# End Source File
# Begin Source File

SOURCE=third_party\inc\Tokenizer.h
# End Source File
# Begin Source File

SOURCE=.\third_party\Inc\Typedefs.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=res\BulkRename.rc
# End Source File
# Begin Source File

SOURCE=res\BulkRename.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=ReadMe.txt
# End Source File
# End Target
# End Project

