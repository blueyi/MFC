@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by TREELIST.HPJ. >"hlp\treelist.hm"
echo. >>"hlp\treelist.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\treelist.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\treelist.hm"
echo. >>"hlp\treelist.hm"
echo // Prompts (IDP_*) >>"hlp\treelist.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\treelist.hm"
echo. >>"hlp\treelist.hm"
echo // Resources (IDR_*) >>"hlp\treelist.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\treelist.hm"
echo. >>"hlp\treelist.hm"
echo // Dialogs (IDD_*) >>"hlp\treelist.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\treelist.hm"
echo. >>"hlp\treelist.hm"
echo // Frame Controls (IDW_*) >>"hlp\treelist.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\treelist.hm"
REM -- Make help for Project TREELIST


echo Building Win32 Help files
start /wait hcrtf -x "hlp\treelist.hpj"
echo.
if exist Debug\nul copy "hlp\treelist.hlp" Debug
if exist Debug\nul copy "hlp\treelist.cnt" Debug
if exist Release\nul copy "hlp\treelist.hlp" Release
if exist Release\nul copy "hlp\treelist.cnt" Release
echo.


