# Microsoft Developer Studio Project File - Name="XPBtn_Scroll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=XPBtn_Scroll - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XPBtn_Scroll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XPBtn_Scroll.mak" CFG="XPBtn_Scroll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XPBtn_Scroll - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "XPBtn_Scroll - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XPBtn_Scroll - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "XPBtn_Scroll - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"XPBtn_Scroll.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "XPBtn_Scroll - Win32 Release"
# Name "XPBtn_Scroll - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\_command.cpp
# End Source File
# Begin Source File

SOURCE=.\_hscroll.cpp
# End Source File
# Begin Source File

SOURCE=.\_vscroll.cpp
# End Source File
# Begin Source File

SOURCE=.\_xpcmdbutton.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\XPBtn_Scroll.cpp
# End Source File
# Begin Source File

SOURCE=.\XPBtn_Scroll.rc
# End Source File
# Begin Source File

SOURCE=.\XPBtn_ScrollDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\_command.h
# End Source File
# Begin Source File

SOURCE=.\_hscroll.h
# End Source File
# Begin Source File

SOURCE=.\_vscroll.h
# End Source File
# Begin Source File

SOURCE=.\_xpcmdbutton.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\XPBtn_Scroll.h
# End Source File
# Begin Source File

SOURCE=.\XPBtn_ScrollDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\XPBtn_Scroll.ico
# End Source File
# Begin Source File

SOURCE=.\res\XPBtn_Scroll.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section XPBtn_Scroll : {E9C81C23-08E9-4305-A5DB-F86B3F7B2489}
# 	2:5:Class:C_Command
# 	2:10:HeaderFile:_command1.h
# 	2:8:ImplFile:_command1.cpp
# End Section
# Section XPBtn_Scroll : {9076B41A-F995-44DA-9B9F-8601255C7D48}
# 	2:21:DefaultSinkHeaderFile:_xpcmdbutton.h
# 	2:16:DefaultSinkClass:C_xpcmdbutton
# End Section
# Section XPBtn_Scroll : {3C214D38-1EF9-4296-B3B3-656893643AE6}
# 	2:21:DefaultSinkHeaderFile:_command1.h
# 	2:16:DefaultSinkClass:C_Command
# End Section
# Section XPBtn_Scroll : {0AA9F4E4-AE6A-465D-A770-FD84C3606E9E}
# 	2:5:Class:C_VScroll
# 	2:10:HeaderFile:_vscroll.h
# 	2:8:ImplFile:_vscroll.cpp
# End Section
# Section XPBtn_Scroll : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section XPBtn_Scroll : {B2BE9818-ED59-43E2-99EA-B0C0A23D247D}
# 	2:5:Class:C_HScroll
# 	2:10:HeaderFile:_hscroll.h
# 	2:8:ImplFile:_hscroll.cpp
# End Section
# Section XPBtn_Scroll : {193A209F-16A6-410B-B9AD-5DEC573F7C58}
# 	2:5:Class:C_xpcmdbutton
# 	2:10:HeaderFile:_xpcmdbutton.h
# 	2:8:ImplFile:_xpcmdbutton.cpp
# End Section
# Section XPBtn_Scroll : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture1.h
# 	2:8:ImplFile:picture1.cpp
# End Section
# Section XPBtn_Scroll : {B2135337-D9E9-4226-BB5E-071034B83303}
# 	2:21:DefaultSinkHeaderFile:_hscroll.h
# 	2:16:DefaultSinkClass:C_HScroll
# End Section
# Section XPBtn_Scroll : {83F9408C-91B9-420E-A642-64CD206AA1EB}
# 	2:21:DefaultSinkHeaderFile:_vscroll.h
# 	2:16:DefaultSinkClass:C_VScroll
# End Section
