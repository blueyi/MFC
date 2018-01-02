# Microsoft Developer Studio Project File - Name="prjconverter" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=prjconverter - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "prjconverter.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "prjconverter.mak" CFG="prjconverter - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "prjconverter - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "prjconverter - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "prjconverter - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /tlb".\Debug\prjconverter.tlb" /win32
# ADD MTL /nologo /tlb".\Debug\prjconverter.tlb" /win32
# ADD BASE CPP /nologo /W3 /GX /ZI /Od /I "xmlparser" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /GZ /c
# ADD CPP /nologo /W3 /GX /ZI /Od /I "xmlparser" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib odbc32.lib odbccp32.lib msxml2.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib odbc32.lib odbccp32.lib msxml2.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "prjconverter - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE MTL /nologo /tlb".\Release\prjconverter.tlb" /win32
# ADD MTL /nologo /tlb".\Release\prjconverter.tlb" /win32
# ADD BASE CPP /nologo /W3 /GX /Ob1 /Gy /I "xmlparser" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /GF /c
# ADD CPP /nologo /W3 /GX /Ob1 /Gy /I "xmlparser" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /GF /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib msxml2.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib msxml2.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "prjconverter - Win32 Debug"
# Name "prjconverter - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CFile.h
# End Source File
# Begin Source File

SOURCE=.\CString.h
# End Source File
# Begin Source File

SOURCE=.\Folder.cpp
DEP_CPP_FOLDE=\
	".\Folder.h"\
	".\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\prjconverter.cpp
DEP_CPP_PRJCO=\
	".\CFile.h"\
	".\CString.h"\
	".\Folder.h"\
	".\slnprocess.h"\
	".\Templates.h"\
	
# End Source File
# Begin Source File

SOURCE=.\slnprocess.cpp
DEP_CPP_SLNPR=\
	".\CFile.h"\
	".\CString.h"\
	".\slnprocess.h"\
	".\symbols.h"\
	".\Templates.h"\
	".\vcprojconfiguration.h"\
	".\vcprojprocess.h"\
	{$(INCLUDE)}"msxml2.h"\
	
# End Source File
# Begin Source File

SOURCE=.\slnprocess.h
# End Source File
# Begin Source File

SOURCE=.\symbols.h
# End Source File
# Begin Source File

SOURCE=.\Templates.h
# End Source File
# Begin Source File

SOURCE=.\vcprojconfiguration.cpp
DEP_CPP_VCPRO=\
	".\CFile.h"\
	".\CString.h"\
	".\slnprocess.h"\
	".\symbols.h"\
	".\Templates.h"\
	".\vcprojconfiguration.h"\
	{$(INCLUDE)}"msxml2.h"\
	
# End Source File
# Begin Source File

SOURCE=.\vcprojconfiguration.h
# End Source File
# Begin Source File

SOURCE=.\vcprojprocess.cpp
DEP_CPP_VCPROJ=\
	".\CFile.h"\
	".\CString.h"\
	".\slnprocess.h"\
	".\symbols.h"\
	".\Templates.h"\
	".\vcprojconfiguration.h"\
	".\vcprojprocess.h"\
	{$(INCLUDE)}"msxml2.h"\
	
# End Source File
# Begin Source File

SOURCE=.\vcprojprocess.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Folder.h
# End Source File
# End Group
# End Target
# End Project
