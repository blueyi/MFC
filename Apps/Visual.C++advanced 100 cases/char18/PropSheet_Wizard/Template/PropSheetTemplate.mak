# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=PropSheetTemplate - Win32 Debug Modeless
!MESSAGE No configuration specified.  Defaulting to PropSheetTemplate - Win32\
 Debug Modeless.
!ENDIF 

!IF "$(CFG)" != "PropSheetTemplate - Win32 Release" && "$(CFG)" !=\
 "PropSheetTemplate - Win32 Debug" && "$(CFG)" !=\
 "PropSheetTemplate - Win32 Debug Modal" && "$(CFG)" !=\
 "PropSheetTemplate - Win32 Debug Modeless"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "PropSheetTemplate.mak"\
 CFG="PropSheetTemplate - Win32 Debug Modeless"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PropSheetTemplate - Win32 Release" (based on\
 "Win32 (x86) Application")
!MESSAGE "PropSheetTemplate - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "PropSheetTemplate - Win32 Debug Modal" (based on\
 "Win32 (x86) Application")
!MESSAGE "PropSheetTemplate - Win32 Debug Modeless" (based on\
 "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "PropSheetTemplate - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "PropSheetTemplate - Win32 Release"

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

ALL : "$(OUTDIR)\PropSheetTemplate.exe"

CLEAN : 
	-@erase "$(INTDIR)\LargePage.obj"
	-@erase "$(INTDIR)\MainSheet.obj"
	-@erase "$(INTDIR)\MediumPage.obj"
	-@erase "$(INTDIR)\PropSheetTemplate.obj"
	-@erase "$(INTDIR)\PropSheetTemplate.pch"
	-@erase "$(INTDIR)\PropSheetTemplate.res"
	-@erase "$(INTDIR)\SmallPage.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\PropSheetTemplate.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/PropSheetTemplate.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x418 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x418 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x418 /fo"$(INTDIR)/PropSheetTemplate.res" /d "NDEBUG" /d "_AFXDLL"\
 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/PropSheetTemplate.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/PropSheetTemplate.pdb" /machine:I386\
 /out:"$(OUTDIR)/PropSheetTemplate.exe" 
LINK32_OBJS= \
	"$(INTDIR)\LargePage.obj" \
	"$(INTDIR)\MainSheet.obj" \
	"$(INTDIR)\MediumPage.obj" \
	"$(INTDIR)\PropSheetTemplate.obj" \
	"$(INTDIR)\PropSheetTemplate.res" \
	"$(INTDIR)\SmallPage.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\PropSheetTemplate.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug"

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

ALL : "$(OUTDIR)\PropSheetTemplate.exe"

CLEAN : 
	-@erase "$(INTDIR)\LargePage.obj"
	-@erase "$(INTDIR)\MainSheet.obj"
	-@erase "$(INTDIR)\MediumPage.obj"
	-@erase "$(INTDIR)\PropSheetTemplate.obj"
	-@erase "$(INTDIR)\PropSheetTemplate.pch"
	-@erase "$(INTDIR)\PropSheetTemplate.res"
	-@erase "$(INTDIR)\SmallPage.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\PropSheetTemplate.exe"
	-@erase "$(OUTDIR)\PropSheetTemplate.ilk"
	-@erase "$(OUTDIR)\PropSheetTemplate.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/PropSheetTemplate.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x418 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x418 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x418 /fo"$(INTDIR)/PropSheetTemplate.res" /d "_DEBUG" /d "_AFXDLL"\
 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/PropSheetTemplate.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/PropSheetTemplate.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/PropSheetTemplate.exe" 
LINK32_OBJS= \
	"$(INTDIR)\LargePage.obj" \
	"$(INTDIR)\MainSheet.obj" \
	"$(INTDIR)\MediumPage.obj" \
	"$(INTDIR)\PropSheetTemplate.obj" \
	"$(INTDIR)\PropSheetTemplate.res" \
	"$(INTDIR)\SmallPage.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\PropSheetTemplate.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug Modal"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "PropShee"
# PROP BASE Intermediate_Dir "PropShee"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Modal"
# PROP Intermediate_Dir "Modal"
# PROP Target_Dir ""
OUTDIR=.\Modal
INTDIR=.\Modal

ALL : "$(OUTDIR)\PropSheetTemplate.exe"

CLEAN : 
	-@erase "$(INTDIR)\LargePage.obj"
	-@erase "$(INTDIR)\MainSheet.obj"
	-@erase "$(INTDIR)\MediumPage.obj"
	-@erase "$(INTDIR)\PropSheetTemplate.obj"
	-@erase "$(INTDIR)\PropSheetTemplate.pch"
	-@erase "$(INTDIR)\PropSheetTemplate.res"
	-@erase "$(INTDIR)\SmallPage.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\PropSheetTemplate.exe"
	-@erase "$(OUTDIR)\PropSheetTemplate.ilk"
	-@erase "$(OUTDIR)\PropSheetTemplate.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MODAL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /D "__MODAL" /Fp"$(INTDIR)/PropSheetTemplate.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Modal/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x418 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x418 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x418 /fo"$(INTDIR)/PropSheetTemplate.res" /d "_DEBUG" /d "_AFXDLL"\
 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/PropSheetTemplate.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/PropSheetTemplate.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/PropSheetTemplate.exe" 
LINK32_OBJS= \
	"$(INTDIR)\LargePage.obj" \
	"$(INTDIR)\MainSheet.obj" \
	"$(INTDIR)\MediumPage.obj" \
	"$(INTDIR)\PropSheetTemplate.obj" \
	"$(INTDIR)\PropSheetTemplate.res" \
	"$(INTDIR)\SmallPage.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\PropSheetTemplate.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug Modeless"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "PropShe0"
# PROP BASE Intermediate_Dir "PropShe0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Modeless"
# PROP Intermediate_Dir "Modeless"
# PROP Target_Dir ""
OUTDIR=.\Modeless
INTDIR=.\Modeless

ALL : "$(OUTDIR)\PropSheetTemplate.exe"

CLEAN : 
	-@erase "$(INTDIR)\LargePage.obj"
	-@erase "$(INTDIR)\MainSheet.obj"
	-@erase "$(INTDIR)\MediumPage.obj"
	-@erase "$(INTDIR)\PropSheetTemplate.obj"
	-@erase "$(INTDIR)\PropSheetTemplate.pch"
	-@erase "$(INTDIR)\PropSheetTemplate.res"
	-@erase "$(INTDIR)\SmallPage.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\PropSheetTemplate.exe"
	-@erase "$(OUTDIR)\PropSheetTemplate.ilk"
	-@erase "$(OUTDIR)\PropSheetTemplate.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "__MINIMIZE_ON_TASKBAR" /D "__MINIMIZEBOX" /D "__START_ON_TASKBAR" /D "__BITMAP_PAGES" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /D "__MINIMIZE_ON_TASKBAR" /D "__MINIMIZEBOX" /D\
 "__START_ON_TASKBAR" /D "__BITMAP_PAGES" /Fp"$(INTDIR)/PropSheetTemplate.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Modeless/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x418 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x418 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x418 /fo"$(INTDIR)/PropSheetTemplate.res" /d "_DEBUG" /d "_AFXDLL"\
 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/PropSheetTemplate.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/PropSheetTemplate.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/PropSheetTemplate.exe" 
LINK32_OBJS= \
	"$(INTDIR)\LargePage.obj" \
	"$(INTDIR)\MainSheet.obj" \
	"$(INTDIR)\MediumPage.obj" \
	"$(INTDIR)\PropSheetTemplate.obj" \
	"$(INTDIR)\PropSheetTemplate.res" \
	"$(INTDIR)\SmallPage.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\PropSheetTemplate.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "PropSheetTemplate - Win32 Release"
# Name "PropSheetTemplate - Win32 Debug"
# Name "PropSheetTemplate - Win32 Debug Modal"
# Name "PropSheetTemplate - Win32 Debug Modeless"

!IF  "$(CFG)" == "PropSheetTemplate - Win32 Release"

!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug"

!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug Modal"

!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug Modeless"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "PropSheetTemplate - Win32 Release"

!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug"

!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug Modal"

!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug Modeless"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PropSheetTemplate.cpp
DEP_CPP_PROPS=\
	".\LargePage.h"\
	".\MainSheet.h"\
	".\MediumPage.h"\
	".\PropSheetTemplate.h"\
	".\SmallPage.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PropSheetTemplate - Win32 Release"


"$(INTDIR)\PropSheetTemplate.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\PropSheetTemplate.pch"


!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug"


"$(INTDIR)\PropSheetTemplate.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\PropSheetTemplate.pch"


!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug Modal"


"$(INTDIR)\PropSheetTemplate.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\PropSheetTemplate.pch"


!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug Modeless"


"$(INTDIR)\PropSheetTemplate.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\PropSheetTemplate.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PropSheetTemplate - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/PropSheetTemplate.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\PropSheetTemplate.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/PropSheetTemplate.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\PropSheetTemplate.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug Modal"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /D "__MODAL" /Fp"$(INTDIR)/PropSheetTemplate.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\PropSheetTemplate.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug Modeless"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /D "__MINIMIZE_ON_TASKBAR" /D "__MINIMIZEBOX" /D\
 "__START_ON_TASKBAR" /D "__BITMAP_PAGES" /Fp"$(INTDIR)/PropSheetTemplate.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\PropSheetTemplate.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PropSheetTemplate.rc
DEP_RSC_PROPSH=\
	".\res\page1.bmp"\
	".\res\PropSheetTemplate.ico"\
	".\res\PropSheetTemplate.rc2"\
	

!IF  "$(CFG)" == "PropSheetTemplate - Win32 Release"


"$(INTDIR)\PropSheetTemplate.res" : $(SOURCE) $(DEP_RSC_PROPSH) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug"


"$(INTDIR)\PropSheetTemplate.res" : $(SOURCE) $(DEP_RSC_PROPSH) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug Modal"


"$(INTDIR)\PropSheetTemplate.res" : $(SOURCE) $(DEP_RSC_PROPSH) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug Modeless"


"$(INTDIR)\PropSheetTemplate.res" : $(SOURCE) $(DEP_RSC_PROPSH) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainSheet.cpp
DEP_CPP_MAINS=\
	".\LargePage.h"\
	".\MainSheet.h"\
	".\MediumPage.h"\
	".\PropSheetTemplate.h"\
	".\SmallPage.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PropSheetTemplate - Win32 Release"


"$(INTDIR)\MainSheet.obj" : $(SOURCE) $(DEP_CPP_MAINS) "$(INTDIR)"\
 "$(INTDIR)\PropSheetTemplate.pch"


!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug"


"$(INTDIR)\MainSheet.obj" : $(SOURCE) $(DEP_CPP_MAINS) "$(INTDIR)"\
 "$(INTDIR)\PropSheetTemplate.pch"


!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug Modal"


"$(INTDIR)\MainSheet.obj" : $(SOURCE) $(DEP_CPP_MAINS) "$(INTDIR)"\
 "$(INTDIR)\PropSheetTemplate.pch"


!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug Modeless"


"$(INTDIR)\MainSheet.obj" : $(SOURCE) $(DEP_CPP_MAINS) "$(INTDIR)"\
 "$(INTDIR)\PropSheetTemplate.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LargePage.cpp
DEP_CPP_LARGE=\
	".\LargePage.h"\
	".\PropSheetTemplate.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PropSheetTemplate - Win32 Release"


"$(INTDIR)\LargePage.obj" : $(SOURCE) $(DEP_CPP_LARGE) "$(INTDIR)"\
 "$(INTDIR)\PropSheetTemplate.pch"


!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug"


"$(INTDIR)\LargePage.obj" : $(SOURCE) $(DEP_CPP_LARGE) "$(INTDIR)"\
 "$(INTDIR)\PropSheetTemplate.pch"


!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug Modal"


"$(INTDIR)\LargePage.obj" : $(SOURCE) $(DEP_CPP_LARGE) "$(INTDIR)"\
 "$(INTDIR)\PropSheetTemplate.pch"


!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug Modeless"


"$(INTDIR)\LargePage.obj" : $(SOURCE) $(DEP_CPP_LARGE) "$(INTDIR)"\
 "$(INTDIR)\PropSheetTemplate.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MediumPage.cpp
DEP_CPP_MEDIU=\
	".\MediumPage.h"\
	".\PropSheetTemplate.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PropSheetTemplate - Win32 Release"


"$(INTDIR)\MediumPage.obj" : $(SOURCE) $(DEP_CPP_MEDIU) "$(INTDIR)"\
 "$(INTDIR)\PropSheetTemplate.pch"


!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug"


"$(INTDIR)\MediumPage.obj" : $(SOURCE) $(DEP_CPP_MEDIU) "$(INTDIR)"\
 "$(INTDIR)\PropSheetTemplate.pch"


!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug Modal"


"$(INTDIR)\MediumPage.obj" : $(SOURCE) $(DEP_CPP_MEDIU) "$(INTDIR)"\
 "$(INTDIR)\PropSheetTemplate.pch"


!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug Modeless"


"$(INTDIR)\MediumPage.obj" : $(SOURCE) $(DEP_CPP_MEDIU) "$(INTDIR)"\
 "$(INTDIR)\PropSheetTemplate.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SmallPage.cpp
DEP_CPP_SMALL=\
	".\PropSheetTemplate.h"\
	".\SmallPage.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PropSheetTemplate - Win32 Release"


"$(INTDIR)\SmallPage.obj" : $(SOURCE) $(DEP_CPP_SMALL) "$(INTDIR)"\
 "$(INTDIR)\PropSheetTemplate.pch"


!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug"


"$(INTDIR)\SmallPage.obj" : $(SOURCE) $(DEP_CPP_SMALL) "$(INTDIR)"\
 "$(INTDIR)\PropSheetTemplate.pch"


!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug Modal"


"$(INTDIR)\SmallPage.obj" : $(SOURCE) $(DEP_CPP_SMALL) "$(INTDIR)"\
 "$(INTDIR)\PropSheetTemplate.pch"


!ELSEIF  "$(CFG)" == "PropSheetTemplate - Win32 Debug Modeless"


"$(INTDIR)\SmallPage.obj" : $(SOURCE) $(DEP_CPP_SMALL) "$(INTDIR)"\
 "$(INTDIR)\PropSheetTemplate.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
