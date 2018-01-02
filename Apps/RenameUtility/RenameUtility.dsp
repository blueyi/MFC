# Microsoft Developer Studio Project File - Name="RenameUtility" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=RenameUtility - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RenameUtility.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RenameUtility.mak" CFG="RenameUtility - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RenameUtility - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "RenameUtility - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RenameUtility - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\inc" /I ".\third_party\inc" /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_AFXDLL" /D "_MBCS" /YX /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\inc" /I ".\third_party\inc" /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_AFXDLL" /D "_MBCS" /YX /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x409 /i "$(IntDir)" /d "_DEBUG"
# ADD RSC /l 0x409 /i "$(IntDir)" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib BulkRename.lib /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept /libpath:"$(OutDir)/"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib BulkRename.lib /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept /libpath:"$(OutDir)/"

!ELSEIF  "$(CFG)" == "RenameUtility - Win32 Release"

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
# ADD BASE CPP /nologo /G6 /MD /W3 /GX /Zi /Og /Oy /Ob1 /Gy /I ".\inc" /I ".\third_party\inc" /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_AFXDLL" /D "_MBCS" /YX /GA /GF /c
# ADD CPP /nologo /G6 /MD /W3 /GX /Zi /Og /Oy /Ob1 /Gy /I ".\inc" /I ".\third_party\inc" /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_AFXDLL" /D "_MBCS" /YX /GA /GF /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x409 /i "$(IntDir)" /d "NDEBUG"
# ADD RSC /l 0x409 /i "$(IntDir)" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib BulkRename.lib /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept /libpath:"$(OutDir)/" /opt:ref /opt:icf
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib BulkRename.lib /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept /libpath:"$(OutDir)/" /opt:ref /opt:icf

!ENDIF 

# Begin Target

# Name "RenameUtility - Win32 Debug"
# Name "RenameUtility - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;def;odl;idl;hpj;bat;asm"
# Begin Group "third_party"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\third_party\src\CeXDib.cpp
DEP_CPP_CEXDI=\
	".\inc\stdafx.h"\
	".\third_party\inc\CeXDib.h"\
	
# End Source File
# Begin Source File

SOURCE=third_party\src\DirDialog.cpp
DEP_CPP_DIRDI=\
	".\inc\DirDialog.h"\
	".\inc\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\third_party\src\PPDrawManager.cpp
DEP_CPP_PPDRA=\
	".\inc\stdafx.h"\
	".\third_party\inc\CeXDib.h"\
	".\third_party\inc\PPDrawManager.h"\
	
# End Source File
# Begin Source File

SOURCE=.\third_party\src\PPHtmlDrawer.cpp
DEP_CPP_PPHTM=\
	".\inc\stdafx.h"\
	".\third_party\inc\CeXDib.h"\
	".\third_party\inc\PPDrawManager.h"\
	".\third_party\inc\PPHtmlDrawer.h"\
	
# End Source File
# Begin Source File

SOURCE=.\third_party\src\PPTooltip.cpp
DEP_CPP_PPTOO=\
	".\inc\stdafx.h"\
	".\third_party\inc\CeXDib.h"\
	".\third_party\inc\PPDrawManager.h"\
	".\third_party\inc\PPHtmlDrawer.h"\
	".\third_party\inc\PPTooltip.h"\
	
# End Source File
# Begin Source File

SOURCE=.\third_party\Src\SkinProgress.cpp
DEP_CPP_SKINP=\
	".\inc\stdafx.h"\
	".\third_party\Inc\SkinProgress.h"\
	
# End Source File
# End Group
# Begin Source File

SOURCE=src\RenameUtility.cpp
DEP_CPP_RENAM=\
	".\inc\bulkrenameclass.h"\
	".\inc\RenameUtility.h"\
	".\inc\RenameUtilityDlg.h"\
	".\inc\stdafx.h"\
	".\third_party\inc\CeXDib.h"\
	".\third_party\inc\PPDrawManager.h"\
	".\third_party\inc\PPHtmlDrawer.h"\
	".\third_party\inc\PPTooltip.h"\
	".\third_party\Inc\SkinProgress.h"\
	
# End Source File
# Begin Source File

SOURCE=src\RenameUtilityDlg.cpp
DEP_CPP_RENAME=\
	".\inc\bulkrenameclass.h"\
	".\inc\DirDialog.h"\
	".\inc\RenameUtility.h"\
	".\inc\RenameUtilityDlg.h"\
	".\inc\stdafx.h"\
	".\third_party\inc\CeXDib.h"\
	".\third_party\inc\PPDrawManager.h"\
	".\third_party\inc\PPHtmlDrawer.h"\
	".\third_party\inc\PPTooltip.h"\
	".\third_party\Inc\SkinProgress.h"\
	
# End Source File
# Begin Source File

SOURCE=src\stdafx.cpp
DEP_CPP_STDAF=\
	".\inc\stdafx.h"\
	
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;inc"
# Begin Group "third_party No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\third_party\inc\CeXDib.h
# End Source File
# Begin Source File

SOURCE=third_party\inc\DirDialog.h
# End Source File
# Begin Source File

SOURCE=.\third_party\inc\PPDrawManager.h
# End Source File
# Begin Source File

SOURCE=.\third_party\inc\PPHtmlDrawer.h
# End Source File
# Begin Source File

SOURCE=.\third_party\inc\PPTooltip.h
# End Source File
# Begin Source File

SOURCE=.\third_party\Inc\SkinProgress.h
# End Source File
# End Group
# Begin Source File

SOURCE=inc\RenameUtility.h
# End Source File
# Begin Source File

SOURCE=inc\RenameUtilityDlg.h
# End Source File
# Begin Source File

SOURCE=inc\Resource.h
# End Source File
# Begin Source File

SOURCE=inc\stdafx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;jpg;jpeg;jpe;manifest"
# Begin Source File

SOURCE=res\icon\RenameUtility.ico
# End Source File
# Begin Source File

SOURCE=res\RenameUtility.manifest
# End Source File
# Begin Source File

SOURCE=res\RenameUtility.rc
# End Source File
# Begin Source File

SOURCE=res\RenameUtility.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=ReadMe.txt
# End Source File
# End Target
# End Project
