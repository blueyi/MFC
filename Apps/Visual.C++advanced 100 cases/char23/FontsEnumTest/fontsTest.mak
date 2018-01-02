# Microsoft Developer Studio Generated NMAKE File, Based on fontsTest.dsp
!IF "$(CFG)" == ""
CFG=fontsTest - Win32 Debug
!MESSAGE No configuration specified. Defaulting to fontsTest - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "fontsTest - Win32 Release" && "$(CFG)" !=\
 "fontsTest - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "fontsTest.mak" CFG="fontsTest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "fontsTest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "fontsTest - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "fontsTest - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\fontsTest.exe"

!ELSE 

ALL : "$(OUTDIR)\fontsTest.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\fontsTest.obj"
	-@erase "$(INTDIR)\fontsTest.pch"
	-@erase "$(INTDIR)\fontsTest.res"
	-@erase "$(INTDIR)\fontsTestDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\WizFontNamesComboBox.obj"
	-@erase "$(INTDIR)\WizFontScriptsComboBox.obj"
	-@erase "$(INTDIR)\WizFontsEnumerator.obj"
	-@erase "$(OUTDIR)\fontsTest.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\fontsTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\fontsTest.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\fontsTest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\fontsTest.pdb" /machine:I386 /out:"$(OUTDIR)\fontsTest.exe" 
LINK32_OBJS= \
	"$(INTDIR)\fontsTest.obj" \
	"$(INTDIR)\fontsTest.res" \
	"$(INTDIR)\fontsTestDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WizFontNamesComboBox.obj" \
	"$(INTDIR)\WizFontScriptsComboBox.obj" \
	"$(INTDIR)\WizFontsEnumerator.obj"

"$(OUTDIR)\fontsTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "fontsTest - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\fontsTest.exe"

!ELSE 

ALL : "$(OUTDIR)\fontsTest.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\fontsTest.obj"
	-@erase "$(INTDIR)\fontsTest.pch"
	-@erase "$(INTDIR)\fontsTest.res"
	-@erase "$(INTDIR)\fontsTestDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\WizFontNamesComboBox.obj"
	-@erase "$(INTDIR)\WizFontScriptsComboBox.obj"
	-@erase "$(INTDIR)\WizFontsEnumerator.obj"
	-@erase "$(OUTDIR)\fontsTest.exe"
	-@erase "$(OUTDIR)\fontsTest.ilk"
	-@erase "$(OUTDIR)\fontsTest.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\fontsTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\fontsTest.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\fontsTest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\fontsTest.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\fontsTest.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\fontsTest.obj" \
	"$(INTDIR)\fontsTest.res" \
	"$(INTDIR)\fontsTestDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WizFontNamesComboBox.obj" \
	"$(INTDIR)\WizFontScriptsComboBox.obj" \
	"$(INTDIR)\WizFontsEnumerator.obj"

"$(OUTDIR)\fontsTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(CFG)" == "fontsTest - Win32 Release" || "$(CFG)" ==\
 "fontsTest - Win32 Debug"
SOURCE=.\fontsTest.cpp

!IF  "$(CFG)" == "fontsTest - Win32 Release"

DEP_CPP_FONTS=\
	".\fontsTest.h"\
	".\fontsTestDlg.h"\
	".\StdAfx.h"\
	".\WizFontNamesComboBox.h"\
	".\WizFontScriptsComboBox.h"\
	".\WizFontsEnumerator.h"\
	

"$(INTDIR)\fontsTest.obj" : $(SOURCE) $(DEP_CPP_FONTS) "$(INTDIR)"\
 "$(INTDIR)\fontsTest.pch"


!ELSEIF  "$(CFG)" == "fontsTest - Win32 Debug"

DEP_CPP_FONTS=\
	".\fontsTest.h"\
	".\fontsTestDlg.h"\
	".\WizFontNamesComboBox.h"\
	".\WizFontsEnumerator.h"\
	

"$(INTDIR)\fontsTest.obj" : $(SOURCE) $(DEP_CPP_FONTS) "$(INTDIR)"\
 "$(INTDIR)\fontsTest.pch"


!ENDIF 

SOURCE=.\fontsTest.rc
DEP_RSC_FONTST=\
	".\res\fontsTest.ico"\
	".\res\fontsTest.rc2"\
	

"$(INTDIR)\fontsTest.res" : $(SOURCE) $(DEP_RSC_FONTST) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\fontsTestDlg.cpp

!IF  "$(CFG)" == "fontsTest - Win32 Release"

DEP_CPP_FONTSTE=\
	".\fontsTest.h"\
	".\fontsTestDlg.h"\
	".\StdAfx.h"\
	".\WizFontNamesComboBox.h"\
	".\WizFontScriptsComboBox.h"\
	".\WizFontsEnumerator.h"\
	

"$(INTDIR)\fontsTestDlg.obj" : $(SOURCE) $(DEP_CPP_FONTSTE) "$(INTDIR)"\
 "$(INTDIR)\fontsTest.pch"


!ELSEIF  "$(CFG)" == "fontsTest - Win32 Debug"

DEP_CPP_FONTSTE=\
	".\fontsTest.h"\
	".\fontsTestDlg.h"\
	".\WizFontNamesComboBox.h"\
	".\WizFontsEnumerator.h"\
	

"$(INTDIR)\fontsTestDlg.obj" : $(SOURCE) $(DEP_CPP_FONTSTE) "$(INTDIR)"\
 "$(INTDIR)\fontsTest.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "fontsTest - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\fontsTest.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\fontsTest.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "fontsTest - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\fontsTest.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\fontsTest.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\WizFontNamesComboBox.cpp

!IF  "$(CFG)" == "fontsTest - Win32 Release"

DEP_CPP_WIZFO=\
	".\fontsTest.h"\
	".\StdAfx.h"\
	".\WizFontNamesComboBox.h"\
	".\WizFontsEnumerator.h"\
	

"$(INTDIR)\WizFontNamesComboBox.obj" : $(SOURCE) $(DEP_CPP_WIZFO) "$(INTDIR)"\
 "$(INTDIR)\fontsTest.pch"


!ELSEIF  "$(CFG)" == "fontsTest - Win32 Debug"

DEP_CPP_WIZFO=\
	".\fontsTest.h"\
	".\WizFontNamesComboBox.h"\
	".\WizFontsEnumerator.h"\
	

"$(INTDIR)\WizFontNamesComboBox.obj" : $(SOURCE) $(DEP_CPP_WIZFO) "$(INTDIR)"\
 "$(INTDIR)\fontsTest.pch"


!ENDIF 

SOURCE=.\WizFontScriptsComboBox.cpp

!IF  "$(CFG)" == "fontsTest - Win32 Release"

DEP_CPP_WIZFON=\
	".\fontsTest.h"\
	".\StdAfx.h"\
	".\WizFontScriptsComboBox.h"\
	".\WizFontsEnumerator.h"\
	

"$(INTDIR)\WizFontScriptsComboBox.obj" : $(SOURCE) $(DEP_CPP_WIZFON)\
 "$(INTDIR)" "$(INTDIR)\fontsTest.pch"


!ELSEIF  "$(CFG)" == "fontsTest - Win32 Debug"

DEP_CPP_WIZFON=\
	".\fontsTest.h"\
	".\WizFontScriptsComboBox.h"\
	".\WizFontsEnumerator.h"\
	

"$(INTDIR)\WizFontScriptsComboBox.obj" : $(SOURCE) $(DEP_CPP_WIZFON)\
 "$(INTDIR)" "$(INTDIR)\fontsTest.pch"


!ENDIF 

SOURCE=.\WizFontsEnumerator.cpp

!IF  "$(CFG)" == "fontsTest - Win32 Release"

DEP_CPP_WIZFONT=\
	".\StdAfx.h"\
	".\WizFontsEnumerator.h"\
	

"$(INTDIR)\WizFontsEnumerator.obj" : $(SOURCE) $(DEP_CPP_WIZFONT) "$(INTDIR)"\
 "$(INTDIR)\fontsTest.pch"


!ELSEIF  "$(CFG)" == "fontsTest - Win32 Debug"

DEP_CPP_WIZFONT=\
	".\WizFontsEnumerator.h"\
	

"$(INTDIR)\WizFontsEnumerator.obj" : $(SOURCE) $(DEP_CPP_WIZFONT) "$(INTDIR)"\
 "$(INTDIR)\fontsTest.pch"


!ENDIF 


!ENDIF 

