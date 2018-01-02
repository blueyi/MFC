# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=TreeList - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to TreeList - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TreeList - Win32 Release" && "$(CFG)" !=\
 "TreeList - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Treelist.mak" CFG="TreeList - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TreeList - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TreeList - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "TreeList - Win32 Release"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "TreeList - Win32 Release"

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

ALL : "$(OUTDIR)\Treelist.exe"

CLEAN : 
	-@erase ".\Release\Treelist.exe"
	-@erase ".\Release\ViewList.obj"
	-@erase ".\Release\Treelist.pch"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\TreeList.obj"
	-@erase ".\Release\ViewTree.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\Doc.obj"
	-@erase ".\Release\TreeList.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Treelist.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/TreeList.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Treelist.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Treelist.pdb" /machine:I386 /out:"$(OUTDIR)/Treelist.exe" 
LINK32_OBJS= \
	"$(INTDIR)/ViewList.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/TreeList.obj" \
	"$(INTDIR)/ViewTree.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/Doc.obj" \
	"$(INTDIR)/TreeList.res"

"$(OUTDIR)\Treelist.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TreeList - Win32 Debug"

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

ALL : "$(OUTDIR)\Treelist.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\Treelist.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\Treelist.exe"
	-@erase ".\Debug\Doc.obj"
	-@erase ".\Debug\ViewTree.obj"
	-@erase ".\Debug\ViewList.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\TreeList.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\TreeList.res"
	-@erase ".\Debug\Treelist.ilk"
	-@erase ".\Debug\Treelist.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Treelist.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/TreeList.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Treelist.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Treelist.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Treelist.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Doc.obj" \
	"$(INTDIR)/ViewTree.obj" \
	"$(INTDIR)/ViewList.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/TreeList.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/TreeList.res"

"$(OUTDIR)\Treelist.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "TreeList - Win32 Release"
# Name "TreeList - Win32 Debug"

!IF  "$(CFG)" == "TreeList - Win32 Release"

!ELSEIF  "$(CFG)" == "TreeList - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\TreeList.cpp
DEP_CPP_TREEL=\
	".\Stdafx.h"\
	".\Treelist.h"\
	".\Mainfrm.h"\
	".\Doc.h"\
	".\Viewtree.h"\
	

"$(INTDIR)\TreeList.obj" : $(SOURCE) $(DEP_CPP_TREEL) "$(INTDIR)"\
 "$(INTDIR)\Treelist.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "TreeList - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Treelist.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Treelist.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "TreeList - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Treelist.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Treelist.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\Stdafx.h"\
	".\Treelist.h"\
	".\Mainfrm.h"\
	".\Doc.h"\
	".\Viewtree.h"\
	".\Viewlist.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Treelist.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Doc.cpp
DEP_CPP_DOC_C=\
	".\Stdafx.h"\
	".\Treelist.h"\
	".\Mainfrm.h"\
	".\Doc.h"\
	".\Viewlist.h"\
	".\Viewtree.h"\
	

"$(INTDIR)\Doc.obj" : $(SOURCE) $(DEP_CPP_DOC_C) "$(INTDIR)"\
 "$(INTDIR)\Treelist.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TreeList.rc
DEP_RSC_TREELI=\
	".\res\Doc.ico"\
	".\res\TreeList.ico"\
	".\res\Cd.bmp"\
	".\res\Desktop.bmp"\
	".\res\Fixed.bmp"\
	".\res\FoldCls.bmp"\
	".\res\FoldOpen.bmp"\
	".\res\FoldOpn2.bmp"\
	".\res\Remote.bmp"\
	".\res\Remove.bmp"\
	".\RES\Computer.bmp"\
	".\res\ToolBar.bmp"\
	".\res\Doc.bmp"\
	".\res\TreeList.rc2"\
	

"$(INTDIR)\TreeList.res" : $(SOURCE) $(DEP_RSC_TREELI) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ViewTree.cpp
DEP_CPP_VIEWT=\
	".\Stdafx.h"\
	".\Treelist.h"\
	".\Doc.h"\
	".\Viewtree.h"\
	".\Viewlist.h"\
	".\Mainfrm.h"\
	

"$(INTDIR)\ViewTree.obj" : $(SOURCE) $(DEP_CPP_VIEWT) "$(INTDIR)"\
 "$(INTDIR)\Treelist.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ViewList.cpp
DEP_CPP_VIEWL=\
	".\Stdafx.h"\
	".\Treelist.h"\
	".\Doc.h"\
	".\Viewtree.h"\
	".\Viewlist.h"\
	".\Mainfrm.h"\
	

"$(INTDIR)\ViewList.obj" : $(SOURCE) $(DEP_CPP_VIEWL) "$(INTDIR)"\
 "$(INTDIR)\Treelist.pch"


# End Source File
# End Target
# End Project
################################################################################
