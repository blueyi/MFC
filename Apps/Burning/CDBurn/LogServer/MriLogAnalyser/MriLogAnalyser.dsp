# Microsoft Developer Studio Project File - Name="MriLogAnalyser" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MriLogAnalyser - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MriLogAnalyser.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MriLogAnalyser.mak" CFG="MriLogAnalyser - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MriLogAnalyser - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MriLogAnalyser - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MriLogAnalyser - Win32 Release"

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
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"..\..\..\Build\Bin/MriLogAnalyser.exe"

!ELSEIF  "$(CFG)" == "MriLogAnalyser - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\..\Build\BinDebug/MriLogAnalyser.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MriLogAnalyser - Win32 Release"
# Name "MriLogAnalyser - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Chart.cpp
# End Source File
# Begin Source File

SOURCE=.\DataManager.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MriLogAnalyser.cpp
# End Source File
# Begin Source File

SOURCE=.\MriLogAnalyser.rc
# End Source File
# Begin Source File

SOURCE=.\MriLogAnalyserDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\MriLogAnalyserView.cpp
# End Source File
# Begin Source File

SOURCE=.\SetQueryingConditionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowLogRecordGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UGC\UGCBType.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\UGCell.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\UGCelTyp.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\UGCnrBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\UGCTarrw.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\UGCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\UGCTsarw.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\UGDLType.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\UGDrgDrp.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\UGDrwHnt.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\UGDtaSrc.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\UGEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\ugexcel.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\ugformat.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\uggdinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\UGGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\UGHint.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\ughscrol.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\ugLstBox.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\UGMemMan.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\UGMultiS.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\ugprint.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\ugptrlst.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\ugsidehd.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\ugtab.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\UGTopHdg.cpp
# End Source File
# Begin Source File

SOURCE=.\UGC\ugvscrol.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DataManager.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MriLogAnalyser.h
# End Source File
# Begin Source File

SOURCE=.\MriLogAnalyserDoc.h
# End Source File
# Begin Source File

SOURCE=.\MriLogAnalyserView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SetQueryingConditionDlg.h
# End Source File
# Begin Source File

SOURCE=.\ShowLogRecordGrid.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\MriLogAnalyser.ico
# End Source File
# Begin Source File

SOURCE=.\res\MriLogAnalyser.rc2
# End Source File
# Begin Source File

SOURCE=.\res\MriLogAnalyserDoc.ico
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
