# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=tab - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to tab - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "tab - Win32 Release" && "$(CFG)" != "tab - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "tab.mak" CFG="tab - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tab - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "tab - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "tab - Win32 Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "tab - Win32 Release"

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
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\tab.exe" "$(OUTDIR)\tab.bsc"

CLEAN : 
	-@erase ".\Release\tab.bsc"
	-@erase ".\Release\tab.sbr"
	-@erase ".\Release\tab.pch"
	-@erase ".\Release\MainFrm.sbr"
	-@erase ".\Release\splitterTabWnd.sbr"
	-@erase ".\Release\StdAfx.sbr"
	-@erase ".\Release\tabView.sbr"
	-@erase ".\Release\viewTwo.sbr"
	-@erase ".\Release\tabDoc.sbr"
	-@erase ".\Release\wndTab.sbr"
	-@erase ".\Release\tab.exe"
	-@erase ".\Release\tabDoc.obj"
	-@erase ".\Release\wndTab.obj"
	-@erase ".\Release\tab.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\splitterTabWnd.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\tabView.obj"
	-@erase ".\Release\viewTwo.obj"
	-@erase ".\Release\tab.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/tab.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x41d /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x41d /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x41d /fo"$(INTDIR)/tab.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/tab.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/tab.sbr" \
	"$(INTDIR)/MainFrm.sbr" \
	"$(INTDIR)/splitterTabWnd.sbr" \
	"$(INTDIR)/StdAfx.sbr" \
	"$(INTDIR)/tabView.sbr" \
	"$(INTDIR)/viewTwo.sbr" \
	"$(INTDIR)/tabDoc.sbr" \
	"$(INTDIR)/wndTab.sbr"

"$(OUTDIR)\tab.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/tab.pdb" /machine:I386 /out:"$(OUTDIR)/tab.exe" 
LINK32_OBJS= \
	"$(INTDIR)/tabDoc.obj" \
	"$(INTDIR)/wndTab.obj" \
	"$(INTDIR)/tab.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/splitterTabWnd.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/tabView.obj" \
	"$(INTDIR)/viewTwo.obj" \
	"$(INTDIR)/tab.res"

"$(OUTDIR)\tab.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "tab - Win32 Debug"

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
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\tab.exe" "$(OUTDIR)\tab.bsc"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\tab.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\tab.bsc"
	-@erase ".\Debug\tab.sbr"
	-@erase ".\Debug\wndTab.sbr"
	-@erase ".\Debug\MainFrm.sbr"
	-@erase ".\Debug\tabView.sbr"
	-@erase ".\Debug\viewTwo.sbr"
	-@erase ".\Debug\tabDoc.sbr"
	-@erase ".\Debug\splitterTabWnd.sbr"
	-@erase ".\Debug\StdAfx.sbr"
	-@erase ".\Debug\tab.exe"
	-@erase ".\Debug\splitterTabWnd.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\tab.obj"
	-@erase ".\Debug\wndTab.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\tabView.obj"
	-@erase ".\Debug\viewTwo.obj"
	-@erase ".\Debug\tabDoc.obj"
	-@erase ".\Debug\tab.res"
	-@erase ".\Debug\tab.ilk"
	-@erase ".\Debug\tab.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/tab.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x41d /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x41d /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x41d /fo"$(INTDIR)/tab.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/tab.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/tab.sbr" \
	"$(INTDIR)/wndTab.sbr" \
	"$(INTDIR)/MainFrm.sbr" \
	"$(INTDIR)/tabView.sbr" \
	"$(INTDIR)/viewTwo.sbr" \
	"$(INTDIR)/tabDoc.sbr" \
	"$(INTDIR)/splitterTabWnd.sbr" \
	"$(INTDIR)/StdAfx.sbr"

"$(OUTDIR)\tab.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/tab.pdb" /debug /machine:I386 /out:"$(OUTDIR)/tab.exe" 
LINK32_OBJS= \
	"$(INTDIR)/splitterTabWnd.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/tab.obj" \
	"$(INTDIR)/wndTab.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/tabView.obj" \
	"$(INTDIR)/viewTwo.obj" \
	"$(INTDIR)/tabDoc.obj" \
	"$(INTDIR)/tab.res"

"$(OUTDIR)\tab.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "tab - Win32 Release"
# Name "tab - Win32 Debug"

!IF  "$(CFG)" == "tab - Win32 Release"

!ELSEIF  "$(CFG)" == "tab - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "tab - Win32 Release"

!ELSEIF  "$(CFG)" == "tab - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\tab.cpp
DEP_CPP_TAB_C=\
	".\StdAfx.h"\
	".\tab.h"\
	".\MainFrm.h"\
	".\tabDoc.h"\
	".\tabView.h"\
	".\splitterTabWnd.h"\
	

"$(INTDIR)\tab.obj" : $(SOURCE) $(DEP_CPP_TAB_C) "$(INTDIR)"\
 "$(INTDIR)\tab.pch"

"$(INTDIR)\tab.sbr" : $(SOURCE) $(DEP_CPP_TAB_C) "$(INTDIR)"\
 "$(INTDIR)\tab.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "tab - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/tab.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\tab.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "tab - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/tab.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\tab.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "tab - Win32 Release"

DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\tab.h"\
	".\viewTwo.h"\
	".\tabView.h"\
	".\MainFrm.h"\
	".\splitterTabWnd.h"\
	
NODEP_CPP_MAINF=\
	".\cs"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\tab.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\tab.pch"


!ELSEIF  "$(CFG)" == "tab - Win32 Debug"

DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\tab.h"\
	".\viewTwo.h"\
	".\tabView.h"\
	".\MainFrm.h"\
	".\splitterTabWnd.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\tab.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\tab.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\tabDoc.cpp
DEP_CPP_TABDO=\
	".\StdAfx.h"\
	".\tab.h"\
	".\tabDoc.h"\
	

"$(INTDIR)\tabDoc.obj" : $(SOURCE) $(DEP_CPP_TABDO) "$(INTDIR)"\
 "$(INTDIR)\tab.pch"

"$(INTDIR)\tabDoc.sbr" : $(SOURCE) $(DEP_CPP_TABDO) "$(INTDIR)"\
 "$(INTDIR)\tab.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tabView.cpp
DEP_CPP_TABVI=\
	".\StdAfx.h"\
	".\tab.h"\
	".\tabDoc.h"\
	".\tabView.h"\
	

"$(INTDIR)\tabView.obj" : $(SOURCE) $(DEP_CPP_TABVI) "$(INTDIR)"\
 "$(INTDIR)\tab.pch"

"$(INTDIR)\tabView.sbr" : $(SOURCE) $(DEP_CPP_TABVI) "$(INTDIR)"\
 "$(INTDIR)\tab.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\tab.rc
DEP_RSC_TAB_R=\
	".\res\tab.ico"\
	".\res\tabDoc.ico"\
	".\res\tab.rc2"\
	

"$(INTDIR)\tab.res" : $(SOURCE) $(DEP_RSC_TAB_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\wndTab.cpp
DEP_CPP_WNDTA=\
	".\StdAfx.h"\
	".\tab.h"\
	".\wndTab.h"\
	

"$(INTDIR)\wndTab.obj" : $(SOURCE) $(DEP_CPP_WNDTA) "$(INTDIR)"\
 "$(INTDIR)\tab.pch"

"$(INTDIR)\wndTab.sbr" : $(SOURCE) $(DEP_CPP_WNDTA) "$(INTDIR)"\
 "$(INTDIR)\tab.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\splitterTabWnd.cpp

!IF  "$(CFG)" == "tab - Win32 Release"

DEP_CPP_SPLIT=\
	".\StdAfx.h"\
	".\tab.h"\
	".\tabView.h"\
	".\splitterTabWnd.h"\
	
NODEP_CPP_SPLIT=\
	".\cy"\
	

"$(INTDIR)\splitterTabWnd.obj" : $(SOURCE) $(DEP_CPP_SPLIT) "$(INTDIR)"\
 "$(INTDIR)\tab.pch"

"$(INTDIR)\splitterTabWnd.sbr" : $(SOURCE) $(DEP_CPP_SPLIT) "$(INTDIR)"\
 "$(INTDIR)\tab.pch"


!ELSEIF  "$(CFG)" == "tab - Win32 Debug"

DEP_CPP_SPLIT=\
	".\StdAfx.h"\
	".\tab.h"\
	".\tabView.h"\
	".\splitterTabWnd.h"\
	

"$(INTDIR)\splitterTabWnd.obj" : $(SOURCE) $(DEP_CPP_SPLIT) "$(INTDIR)"\
 "$(INTDIR)\tab.pch"

"$(INTDIR)\splitterTabWnd.sbr" : $(SOURCE) $(DEP_CPP_SPLIT) "$(INTDIR)"\
 "$(INTDIR)\tab.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\viewTwo.cpp
DEP_CPP_VIEWT=\
	".\StdAfx.h"\
	".\tab.h"\
	".\viewTwo.h"\
	

"$(INTDIR)\viewTwo.obj" : $(SOURCE) $(DEP_CPP_VIEWT) "$(INTDIR)"\
 "$(INTDIR)\tab.pch"

"$(INTDIR)\viewTwo.sbr" : $(SOURCE) $(DEP_CPP_VIEWT) "$(INTDIR)"\
 "$(INTDIR)\tab.pch"


# End Source File
# End Target
# End Project
################################################################################
