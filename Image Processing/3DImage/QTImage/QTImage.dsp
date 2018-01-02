# Microsoft Developer Studio Project File - Name="QTImage" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=QTImage - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "QTImage.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "QTImage.mak" CFG="QTImage - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "QTImage - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "QTImage - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "QTImage - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include" /I "..\include\utildll" /I "D:\Software\Xtk\Include" /I "E:\Library\vtk\vtkLib\include\vtk-5.6" /I "..\include\mri" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_XTP_STATICLINK" /FR /FD /Zm500 /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 msimg32.lib triMath.lib MRISeriesDLL.lib snmpapi.lib opengl32.lib glu32.lib vtkexpat.lib vtksys.lib vtkCommon.lib vtkftgl.lib vtkzlib.lib vtkfreetype.lib vtkftgl.lib vtkMFC.lib vtkWidgets.lib vtkHybrid.lib vtkRendering.lib vtkio.lib vtkGraphics.lib vtkImaging.lib vtkpng.lib vtklibxml2.lib vtkjpeg.lib vtktiff.lib vtkFiltering.lib vtkDICOMParser.lib vtkVolumeRendering.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\LibR" /libpath:"D:\Software\Xtk\LibR" /libpath:"E:\Library\vtk\vtkLib\libR"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy release\QTImage.exe ..\BinR
# End Special Build Tool

!ELSEIF  "$(CFG)" == "QTImage - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\include\utildll" /I "..\include\mri" /I "G:\XinAo\Tps\Include\VTK" /I "G:\XinAo\Tps\Include\xtk" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_XTP_STATICLINK" /D "_XTPLIB_NOAUTOLINK" /FR /FD /GZ /Zm500 /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ToolkitPro1121vc60DSD.lib msimg32.lib triMathD.lib MRISeriesDLLD.lib snmpapi.lib opengl32.lib glu32.lib vtkexpat.lib vtksys.lib vtkCommon.lib vtkftgl.lib vtkzlib.lib vtkfreetype.lib vtkftgl.lib vtkMFC.lib vtkWidgets.lib vtkHybrid.lib vtkRendering.lib vtkio.lib vtkGraphics.lib vtkImaging.lib vtkpng.lib vtklibxml2.lib vtkjpeg.lib vtktiff.lib vtkFiltering.lib vtkDICOMParser.lib vtkVolumeRendering.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/QTImageD.exe" /pdbtype:sept /libpath:"..\LibD" /libpath:"D:\Software\Xtk\LibD" /libpath:"E:\Library\vtk\vtkLib\libD"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy debug\QTImageD.exe ..\BinD
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "QTImage - Win32 Release"
# Name "QTImage - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Ctrler2D.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgContourLine.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMPR.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPixelEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgScaleCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSegment.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSR.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSRCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSRView.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVR.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawSeries.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageViewer.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageViewerManager.cpp
# End Source File
# Begin Source File

SOURCE=.\LineChartCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\LUT.cpp
# End Source File
# Begin Source File

SOURCE=.\MemDC.cpp
# End Source File
# Begin Source File

SOURCE=.\MeshReader.cxx
# End Source File
# Begin Source File

SOURCE=.\MeshWriter.cxx
# End Source File
# Begin Source File

SOURCE=.\Points2Mesh.cpp
# End Source File
# Begin Source File

SOURCE=.\QTImage.cpp
# End Source File
# Begin Source File

SOURCE=.\QTImage.rc
# End Source File
# Begin Source File

SOURCE=.\QTImageDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ROI.cpp
# End Source File
# Begin Source File

SOURCE=.\ROIManager.cpp
# End Source File
# Begin Source File

SOURCE=.\SeriesList.cpp
# End Source File
# Begin Source File

SOURCE=.\SeriesListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\SeriesManager.cpp
# End Source File
# Begin Source File

SOURCE=.\SeriesShower.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Viewer2D.cpp
# End Source File
# Begin Source File

SOURCE=.\VRCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\VRView.cpp
# End Source File
# Begin Source File

SOURCE=.\vtkPowerCrustSurfaceReconstruction.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Ctrler2D.h
# End Source File
# Begin Source File

SOURCE=.\DlgContourLine.h
# End Source File
# Begin Source File

SOURCE=.\DlgMPR.h
# End Source File
# Begin Source File

SOURCE=.\DlgPixelEdit.h
# End Source File
# Begin Source File

SOURCE=.\DlgScaleCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DlgSegment.h
# End Source File
# Begin Source File

SOURCE=.\DlgSR.h
# End Source File
# Begin Source File

SOURCE=.\DlgSRCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DlgSRView.h
# End Source File
# Begin Source File

SOURCE=.\DlgVR.h
# End Source File
# Begin Source File

SOURCE=.\DrawSeries.h
# End Source File
# Begin Source File

SOURCE=.\ImageViewer.h
# End Source File
# Begin Source File

SOURCE=.\ImageViewerManager.h
# End Source File
# Begin Source File

SOURCE=.\LineChartCtrl.h
# End Source File
# Begin Source File

SOURCE=.\LUT.h
# End Source File
# Begin Source File

SOURCE=.\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\MeshReader.h
# End Source File
# Begin Source File

SOURCE=.\MeshWriter.h
# End Source File
# Begin Source File

SOURCE=.\Points2Mesh.h
# End Source File
# Begin Source File

SOURCE=.\QTImage.h
# End Source File
# Begin Source File

SOURCE=.\QTImageDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ROI.h
# End Source File
# Begin Source File

SOURCE=.\ROIManager.h
# End Source File
# Begin Source File

SOURCE=.\SeriesList.h
# End Source File
# Begin Source File

SOURCE=.\SeriesListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\SeriesManager.h
# End Source File
# Begin Source File

SOURCE=.\SeriesShower.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Viewer2D.h
# End Source File
# Begin Source File

SOURCE=.\VRCtrl.h
# End Source File
# Begin Source File

SOURCE=.\VRView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\AutoSeg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Brush.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Cross.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Manual.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Mesh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\QTImage.ico
# End Source File
# Begin Source File

SOURCE=.\res\QTImage.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
