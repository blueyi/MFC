#if !defined (COMM_CONTROL_H_INCLUDED)
#define COMM_CONTROL_H_INCLUDED

// Only needed for versions prior to Visual C++ 6.0
#if _MSC_VER < 1200

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
///  ====================== Toolbar Control =============================
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

#if !defined (TB_SETEXTENDEDSTYLE)
#define TB_SETEXTENDEDSTYLE (WM_USER+84)
#endif

#if !defined (TB_SETHOTIMAGELIST)
#define TB_SETHOTIMAGELIST (WM_USER+52) 
#endif

#if !defined (TB_SETIMAGELIST)
#define TB_SETIMAGELIST (WM_USER+48)
#endif

#if !defined (TBSTYLE_TRANSPARENT)
#define TBSTYLE_TRANSPARENT 0x8000
#endif

#if !defined (TBSTYLE_AUTOSIZE)
#define TBSTYLE_AUTOSIZE 0x0010
#endif

#if !defined (TBSTYLE_EX_DRAWDDARROWS)
#define TBSTYLE_EX_DRAWDDARROWS 0x00000001
#endif

#if !defined (TBSTYLE_FLAT)
#define TBSTYLE_FLAT 0x0800
#endif

#if !defined (CBRS_GRIPPER)
#define CBRS_GRIPPER 0x00400000L
#endif
////======================  End Toolbar Control ==========================================

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
///  ====================== Pager Control =============================
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

#define PGM_FIRST               0x1400		// Pager control messages
#define PGN_FIRST               (0U-900U)   // Pager Control

#define ICC_PAGESCROLLER_CLASS 0x00001000   // page scroller

#ifndef NOPAGESCROLLER

//Pager Class Name
#define WC_PAGESCROLLERW           L"SysPager"
#define WC_PAGESCROLLERA           "SysPager"

#ifdef UNICODE
#define WC_PAGESCROLLER          WC_PAGESCROLLERW
#else
#define WC_PAGESCROLLER          WC_PAGESCROLLERA
#endif


//---------------------------------------------------------------------------------------
// Pager Control Styles
//---------------------------------------------------------------------------------------
#define PGS_VERT                0x00000000
#define PGS_HORZ                0x00000001
#define PGS_AUTOSCROLL          0x00000002
#define PGS_DRAGNDROP           0x00000004


//---------------------------------------------------------------------------------------
// Pager Button State
//---------------------------------------------------------------------------------------
//The scroll can be in one of the following control State 
#define  PGF_INVISIBLE   0      // Scroll button is not visible
#define  PGF_NORMAL      1      // Scroll button is in normal state
#define  PGF_GRAYED      2      // Scroll button is in grayed state
#define  PGF_DEPRESSED   4      // Scroll button is in depressed state
#define  PGF_HOT         8      // Scroll button is in hot state


// The following identifiers specifies the button control 
#define PGB_TOPORLEFT       0
#define PGB_BOTTOMORRIGHT   1

//---------------------------------------------------------------------------------------
// Pager Control  Messages
//---------------------------------------------------------------------------------------
#define PGM_SETCHILD            (PGM_FIRST + 1)  // lParam == hwnd
#define Pager_SetChild(hwnd, hwndChild) \
        (void)SNDMSG((hwnd), PGM_SETCHILD, 0, (LPARAM)(hwndChild))

#define PGM_RECALCSIZE          (PGM_FIRST + 2)
#define Pager_RecalcSize(hwnd) \
        (void)SNDMSG((hwnd), PGM_RECALCSIZE, 0, 0)

#define PGM_FORWARDMOUSE        (PGM_FIRST + 3)
#define Pager_ForwardMouse(hwnd, bForward) \
        (void)SNDMSG((hwnd), PGM_FORWARDMOUSE, (WPARAM)(bForward), 0)

#define PGM_SETBKCOLOR          (PGM_FIRST + 4)
#define Pager_SetBkColor(hwnd, clr) \
        (COLORREF)SNDMSG((hwnd), PGM_SETBKCOLOR, 0, (LPARAM)clr)

#define PGM_GETBKCOLOR          (PGM_FIRST + 5)
#define Pager_GetBkColor(hwnd) \
        (COLORREF)SNDMSG((hwnd), PGM_GETBKCOLOR, 0, 0)

#define PGM_SETBORDER          (PGM_FIRST + 6)
#define Pager_SetBorder(hwnd, iBorder) \
        (int)SNDMSG((hwnd), PGM_SETBORDER, 0, (LPARAM)iBorder)

#define PGM_GETBORDER          (PGM_FIRST + 7)
#define Pager_GetBorder(hwnd) \
        (int)SNDMSG((hwnd), PGM_GETBORDER, 0, 0)

#define PGM_SETPOS              (PGM_FIRST + 8)
#define Pager_SetPos(hwnd, iPos) \
        (int)SNDMSG((hwnd), PGM_SETPOS, 0, (LPARAM)iPos)

#define PGM_GETPOS              (PGM_FIRST + 9)
#define Pager_GetPos(hwnd) \
        (int)SNDMSG((hwnd), PGM_GETPOS, 0, 0)

#define PGM_SETBUTTONSIZE       (PGM_FIRST + 10)
#define Pager_SetButtonSize(hwnd, iSize) \
        (int)SNDMSG((hwnd), PGM_SETBUTTONSIZE, 0, (LPARAM)iSize)

#define PGM_GETBUTTONSIZE       (PGM_FIRST + 11)
#define Pager_GetButtonSize(hwnd) \
        (int)SNDMSG((hwnd), PGM_GETBUTTONSIZE, 0,0)

#define PGM_GETBUTTONSTATE      (PGM_FIRST + 12)
#define Pager_GetButtonState(hwnd, iButton) \
        (DWORD)SNDMSG((hwnd), PGM_GETBUTTONSTATE, 0, (LPARAM)iButton)

#define PGM_GETDROPTARGET       CCM_GETDROPTARGET
#define Pager_GetDropTarget(hwnd, ppdt) \
        (void)SNDMSG((hwnd), PGM_GETDROPTARGET, 0, (LPARAM)ppdt)

//---------------------------------------------------------------------------------------
//Pager Control Notification Messages
//---------------------------------------------------------------------------------------


// PGN_SCROLL Notification Message

#define PGN_SCROLL          (PGN_FIRST-1)

#define PGF_SCROLLUP        1
#define PGF_SCROLLDOWN      2
#define PGF_SCROLLLEFT      4
#define PGF_SCROLLRIGHT     8


//Keys down
#define PGK_SHIFT           1
#define PGK_CONTROL         2
#define PGK_MENU            4


// This structure is sent along with PGN_SCROLL notifications
typedef struct {
    NMHDR hdr;
    WORD fwKeys;            // Specifies which keys are down when this notification is send
    RECT rcParent;          // Contains Parent Window Rect
    int  iDir;              // Scrolling Direction
    int  iXpos;             // Horizontal scroll position
    int  iYpos;             // Vertical scroll position
    int  iScroll;           // [in/out] Amount to scroll
}NMPGSCROLL, *LPNMPGSCROLL;


// PGN_CALCSIZE Notification Message

#define PGN_CALCSIZE        (PGN_FIRST-2)

#define PGF_CALCWIDTH       1
#define PGF_CALCHEIGHT      2

typedef struct {
    NMHDR   hdr;
    DWORD   dwFlag;
    int     iWidth;
    int     iHeight;
}NMPGCALCSIZE, *LPNMPGCALCSIZE;

#endif // NOPAGESCROLLER

////======================  End Pager Control ==========================================

#endif // _MSC_VER < 1200

#endif // !defined (COMM_CONTROL_H_INCLUDED)