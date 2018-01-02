# Microsoft Developer Studio Project File - Name="qqlike" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=qqlike - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "qqlike.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qqlike.mak" CFG="qqlike - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qqlike - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "qqlike - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "qqlike - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "qqlike - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "qqlike - Win32 Release"
# Name "qqlike - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\listboxex.cpp
# End Source File
# Begin Source File

SOURCE=.\qqlike.cpp
# End Source File
# Begin Source File

SOURCE=.\qqlike.rc
# End Source File
# Begin Source File

SOURCE=.\ringeditex.cpp
# End Source File
# Begin Source File

SOURCE=.\ringtrackbarex.cpp
# End Source File
# Begin Source File

SOURCE=.\tabex.cpp
# End Source File
# Begin Source File

SOURCE=.\wndclient.cpp
# End Source File
# Begin Source File

SOURCE=.\wndqqbutton.cpp
# End Source File
# Begin Source File

SOURCE=.\wnduioption.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\global.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\adj_hue.bmp
# End Source File
# Begin Source File

SOURCE=.\res\adj_lum.bmp
# End Source File
# Begin Source File

SOURCE=.\res\adj_sum.bmp
# End Source File
# Begin Source File

SOURCE=.\res\adj_thumb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\adj_trans.bmp
# End Source File
# Begin Source File

SOURCE=.\res\arrbtn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bkg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\busy.ico
# End Source File
# Begin Source File

SOURCE=.\res\caption.gif
# End Source File
# Begin Source File

SOURCE=.\res\hide.ico
# End Source File
# Begin Source File

SOURCE=.\res\hoverbtn.gif
# End Source File
# Begin Source File

SOURCE=.\res\leave.ico
# End Source File
# Begin Source File

SOURCE=.\res\listarr.gif
# End Source File
# Begin Source File

SOURCE=.\res\listtile.gif
# End Source File
# Begin Source File

SOURCE=.\res\lock.ico
# End Source File
# Begin Source File

SOURCE=.\res\mail.gif
# End Source File
# Begin Source File

SOURCE=.\res\menubkg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\menusel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ncbtnadj.gif
# End Source File
# Begin Source File

SOURCE=.\res\ncbuttons.gif
# End Source File
# Begin Source File

SOURCE=.\res\offline.ico
# End Source File
# Begin Source File

SOURCE=.\res\online.ico
# End Source File
# Begin Source File

SOURCE=.\res\qme.ico
# End Source File
# Begin Source File

SOURCE=.\res\qq.ico
# End Source File
# Begin Source File

SOURCE=.\res\qqbtn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\searchbar.gif
# End Source File
# Begin Source File

SOURCE=.\res\sidebtnstate.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sidebtnstatebig.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sidetool.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stop.ico
# End Source File
# Begin Source File

SOURCE=.\res\tabbkg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tabicon.gif
# End Source File
# Begin Source File

SOURCE=.\res\toolbot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbot1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tooltop.gif
# End Source File
# Begin Source File

SOURCE=.\res\tooltr.gif
# End Source File
# Begin Source File

SOURCE=.\res\uicolor.bmp
# End Source File
# Begin Source File

SOURCE=.\res\uidefault.bmp
# End Source File
# Begin Source File

SOURCE=.\res\uitatoo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\uitatoo_none.bmp
# End Source File
# Begin Source File

SOURCE=.\res\user.gif
# End Source File
# Begin Source File

SOURCE=.\res\users.gif
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\caption.png
# End Source File
# Begin Source File

SOURCE=.\res\fox.png
# End Source File
# Begin Source File

SOURCE=.\res\girl.png
# End Source File
# Begin Source File

SOURCE=.\res\qq.png
# End Source File
# Begin Source File

SOURCE=.\res\sea.png
# End Source File
# Begin Source File

SOURCE=.\res\tree.png
# End Source File
# Begin Source File

SOURCE=.\res\wall.png
# End Source File
# End Target
# End Project
