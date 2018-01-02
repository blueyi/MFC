# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=PushPinDemo - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to PushPinDemo - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "PushPinDemo - Win32 Release" && "$(CFG)" !=\
 "PushPinDemo - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "pushpindemo.mak" CFG="PushPinDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PushPinDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PushPinDemo - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "PushPinDemo - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PushPinDemo - Win32 Release"

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

ALL : "$(OUTDIR)\pushpindemo.exe"

CLEAN : 
	-@erase "$(INTDIR)\PushPin.obj"
	-@erase "$(INTDIR)\PushPinDemo.obj"
	-@erase "$(INTDIR)\pushpindemo.pch"
	-@erase "$(INTDIR)\PushPinDemo.res"
	-@erase "$(INTDIR)\PushPinDemoDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\pushpindemo.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/pushpindemo.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x1809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1809 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x1809 /fo"$(INTDIR)/PushPinDemo.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/pushpindemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/pushpindemo.pdb" /machine:I386 /out:"$(OUTDIR)/pushpindemo.exe"\
 
LINK32_OBJS= \
	"$(INTDIR)\PushPin.obj" \
	"$(INTDIR)\PushPinDemo.obj" \
	"$(INTDIR)\PushPinDemo.res" \
	"$(INTDIR)\PushPinDemoDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\pushpindemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "PushPinDemo - Win32 Debug"

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

ALL : "$(OUTDIR)\pushpindemo.exe"

CLEAN : 
	-@erase "$(INTDIR)\PushPin.obj"
	-@erase "$(INTDIR)\PushPinDemo.obj"
	-@erase "$(INTDIR)\pushpindemo.pch"
	-@erase "$(INTDIR)\PushPinDemo.res"
	-@erase "$(INTDIR)\PushPinDemoDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\pushpindemo.exe"
	-@erase "$(OUTDIR)\pushpindemo.ilk"
	-@erase "$(OUTDIR)\pushpindemo.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/pushpindemo.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x1809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1809 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x1809 /fo"$(INTDIR)/PushPinDemo.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/pushpindemo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/pushpindemo.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/pushpindemo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\PushPin.obj" \
	"$(INTDIR)\PushPinDemo.obj" \
	"$(INTDIR)\PushPinDemo.res" \
	"$(INTDIR)\PushPinDemoDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\pushpindemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "PushPinDemo - Win32 Release"
# Name "PushPinDemo - Win32 Debug"

!IF  "$(CFG)" == "PushPinDemo - Win32 Release"

!ELSEIF  "$(CFG)" == "PushPinDemo - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\PushPinDemo.cpp
DEP_CPP_PUSHP=\
	".\PushPin.h"\
	".\PushPinDemo.h"\
	".\PushPinDemoDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\PushPinDemo.obj" : $(SOURCE) $(DEP_CPP_PUSHP) "$(INTDIR)"\
 "$(INTDIR)\pushpindemo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PushPinDemoDlg.cpp
DEP_CPP_PUSHPI=\
	".\PushPin.h"\
	".\PushPinDemo.h"\
	".\PushPinDemoDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\PushPinDemoDlg.obj" : $(SOURCE) $(DEP_CPP_PUSHPI) "$(INTDIR)"\
 "$(INTDIR)\pushpindemo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PushPinDemo - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/pushpindemo.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\pushpindemo.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "PushPinDemo - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/pushpindemo.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\pushpindemo.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PushPinDemo.rc
DEP_RSC_PUSHPIN=\
	".\res\pinned.bmp"\
	".\res\pinnede.bmp"\
	".\res\pushpin2.ico"\
	".\res\pushpin2.rc2"\
	".\res\unpinned.bmp"\
	".\res\unpinnede.bmp"\
	

"$(INTDIR)\PushPinDemo.res" : $(SOURCE) $(DEP_RSC_PUSHPIN) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PushPin.cpp
DEP_CPP_PUSHPIN_=\
	".\PushPin.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\PushPin.obj" : $(SOURCE) $(DEP_CPP_PUSHPIN_) "$(INTDIR)"\
 "$(INTDIR)\pushpindemo.pch"


# End Source File
# End Target
# End Project
################################################################################
