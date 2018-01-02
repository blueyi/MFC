# Microsoft Developer Studio Generated NMAKE File, Based on SpinnerTB.dsp
!IF "$(CFG)" == ""
CFG=SpinnerTB - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SpinnerTB - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SpinnerTB - Win32 Release" && "$(CFG)" != "SpinnerTB - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SpinnerTB.mak" CFG="SpinnerTB - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SpinnerTB - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SpinnerTB - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SpinnerTB - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\SpinnerTB.exe"


CLEAN :
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\SlideToolBar.obj"
	-@erase "$(INTDIR)\SpinnerTB.obj"
	-@erase "$(INTDIR)\SpinnerTB.res"
	-@erase "$(INTDIR)\SpinnerTBDoc.obj"
	-@erase "$(INTDIR)\SpinnerTBView.obj"
	-@erase "$(INTDIR)\SpinnerToolBar.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SpinnerTB.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\SpinnerTB.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SpinnerTB.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SpinnerTB.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\SpinnerTB.pdb" /machine:I386 /out:"$(OUTDIR)\SpinnerTB.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\SlideToolBar.obj" \
	"$(INTDIR)\SpinnerTB.obj" \
	"$(INTDIR)\SpinnerTBDoc.obj" \
	"$(INTDIR)\SpinnerTBView.obj" \
	"$(INTDIR)\SpinnerToolBar.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SpinnerTB.res"

"$(OUTDIR)\SpinnerTB.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SpinnerTB - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\SpinnerTB.exe"


CLEAN :
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\SlideToolBar.obj"
	-@erase "$(INTDIR)\SpinnerTB.obj"
	-@erase "$(INTDIR)\SpinnerTB.res"
	-@erase "$(INTDIR)\SpinnerTBDoc.obj"
	-@erase "$(INTDIR)\SpinnerTBView.obj"
	-@erase "$(INTDIR)\SpinnerToolBar.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SpinnerTB.exe"
	-@erase "$(OUTDIR)\SpinnerTB.ilk"
	-@erase "$(OUTDIR)\SpinnerTB.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\SpinnerTB.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SpinnerTB.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SpinnerTB.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\SpinnerTB.pdb" /debug /machine:I386 /out:"$(OUTDIR)\SpinnerTB.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\SlideToolBar.obj" \
	"$(INTDIR)\SpinnerTB.obj" \
	"$(INTDIR)\SpinnerTBDoc.obj" \
	"$(INTDIR)\SpinnerTBView.obj" \
	"$(INTDIR)\SpinnerToolBar.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SpinnerTB.res"

"$(OUTDIR)\SpinnerTB.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("SpinnerTB.dep")
!INCLUDE "SpinnerTB.dep"
!ELSE 
!MESSAGE Warning: cannot find "SpinnerTB.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SpinnerTB - Win32 Release" || "$(CFG)" == "SpinnerTB - Win32 Debug"
SOURCE=.\ChildFrm.cpp

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\MainFrm.cpp

"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SlideToolBar.cpp

"$(INTDIR)\SlideToolBar.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SpinnerTB.cpp

"$(INTDIR)\SpinnerTB.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SpinnerTBDoc.cpp

"$(INTDIR)\SpinnerTBDoc.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SpinnerTBView.cpp

"$(INTDIR)\SpinnerTBView.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SpinnerToolBar.cpp

"$(INTDIR)\SpinnerToolBar.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StdAfx.cpp

"$(INTDIR)\StdAfx.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SpinnerTB.rc

"$(INTDIR)\SpinnerTB.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

