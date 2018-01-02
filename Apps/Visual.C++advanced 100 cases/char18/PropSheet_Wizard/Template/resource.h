//{{NO_DEPENDENCIES}}
// Microsoft Developer Studio generated include file.
// Used by PropSheetTemplate.rc
//

$$IF(ABOUT_BOX)
#define IDM_ABOUTBOX                    0x0010
#define IDD_ABOUTBOX                    100
#define IDS_ABOUTBOX                    101
$$ENDIF	//ABOUT_BOX
#define IDS_TITLE                       100
$$IF(SEND_TO_TASKBAR)
#define IDS_SENDTOTASKBAR               102
#define ID_ICON_RESTORE                 10000
#define ID_ICON_SHUTDOWN                10001
$$ENDIF	//SEND_TO_TASKBAR
$$BEGINLOOP(NUM_PAGES)
#define $$PAGE_ID$$                     $$PAGE_VAL$$
#define $$PAGE_BMP$$                    $$PAGE_VAL$$
$$ENDLOOP	//NUM_PAGES
#define IDR_MAINFRAME                   128

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        131
#define _APS_NEXT_COMMAND_VALUE         32773
#define _APS_NEXT_CONTROL_VALUE         1000
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
