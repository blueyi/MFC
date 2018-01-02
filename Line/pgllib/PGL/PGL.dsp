# Microsoft Developer Studio Project File - Name="PGL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=PGL - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PGL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PGL.mak" CFG="PGL - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PGL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "PGL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/PGL", BAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PGL - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /Ob2 /I "../AlgoTools/" /I "../IGfx" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_PGL_DLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 AlgoTools.lib IGfx.lib gdiplus.lib /nologo /subsystem:windows /dll /machine:I386 /nodefaultlib:"libcmt" /nodefaultlib:"libc" /out:"../bin/PGL.dll" /implib:"../lib/PGL.lib" /libpath:"../lib"
# SUBTRACT LINK32 /pdb:none /incremental:yes

!ELSEIF  "$(CFG)" == "PGL - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../AlgoTools/" /I "../IGfx" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_PGL_DLL" /Yu"stdafx.h" /FD /I /PGL/" /GZ " /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 AlgoToolsd.lib IGfxd.lib gdiplus.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"libcd" /out:"../bin/PGLd.dll" /implib:"../lib/PGLd.lib" /pdbtype:sept /libpath:"..\lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "PGL - Win32 Release"
# Name "PGL - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\PGL.cpp
# End Source File
# Begin Source File

SOURCE=.\PGL.def

!IF  "$(CFG)" == "PGL - Win32 Release"

!ELSEIF  "$(CFG)" == "PGL - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PGL.rc
# End Source File
# Begin Source File

SOURCE=.\PGLAllPropsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLAxe.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLAxe2DPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLColor.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLd.def

!IF  "$(CFG)" == "PGL - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "PGL - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PGLFont.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLGlobal.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLGraph.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLGraphBitDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLGraphDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLGraphDlgList.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLGraphView.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLLegend.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLLine.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLLine2D.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLLine2DLOD.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLLine2DLODPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLLine2DPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLLineHor.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLLinePropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLLineVer.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLMap.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLMapPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLMapVector.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLMapVectorPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLMapZ.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLMapZPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLMouse.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLObject.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLObjectManager.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLObjectPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLPie.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLRegion.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLRegionPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLText.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLTextPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLUtility.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLView.cpp
# End Source File
# Begin Source File

SOURCE=.\PGLView2D.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Pgl\PGL.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLAllPropsDlg.h
# End Source File
# Begin Source File

SOURCE=.\PGL\PGLAxe.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLAxe2DPropPage.h
# End Source File
# Begin Source File

SOURCE=.\PGL\PGLColor.h
# End Source File
# Begin Source File

SOURCE=.\PGL\PGLDef.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLFont.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLGlobal.h
# End Source File
# Begin Source File

SOURCE=.\PGL\PGLGraph.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLGraphBitDlg.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLGraphDlg.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLGraphDlgList.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLGraphView.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLLegend.h
# End Source File
# Begin Source File

SOURCE=.\PGL\PGLLine.h
# End Source File
# Begin Source File

SOURCE=.\PGL\PGLLine2D.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLLine2DLOD.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLLine2DLODPropPage.h
# End Source File
# Begin Source File

SOURCE=.\PGL\PGLLine2DPropPage.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLLineHor.h
# End Source File
# Begin Source File

SOURCE=.\PGL\PGLLinePropPage.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLLineVer.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLMap.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLMapPropPage.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLMapVector.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLMapVectorPropPage.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLMapZ.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLMapZPropPage.h
# End Source File
# Begin Source File

SOURCE=.\PGL\PGLMouse.h
# End Source File
# Begin Source File

SOURCE=.\PGL\PGLObject.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLObjectManager.h
# End Source File
# Begin Source File

SOURCE=.\PGL\PGLObjectPropPage.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLPie.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLRegion.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLRegionPropPage.h
# End Source File
# Begin Source File

SOURCE=.\PGL\PGLResource.h
# End Source File
# Begin Source File

SOURCE=.\PGL\PGLText.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLTextPropPage.h
# End Source File
# Begin Source File

SOURCE=.\Pgl\PGLUtility.h
# End Source File
# Begin Source File

SOURCE=.\PGL\PGLView.h
# End Source File
# Begin Source File

SOURCE=.\PGL\PGLView2D.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Res\map.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PGL.rc2
# End Source File
# Begin Source File

SOURCE=.\Res\pgl_axe2.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pgl_grap.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pgl_line.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pgl_line2D.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pgl_line2Dlod.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pgl_mapv.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pgl_mapz.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pgl_objmg.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pgl_regi.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pgl_select.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pgl_text.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pglmapgrid.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\introdoc.txt
# End Source File
# End Target
# End Project
