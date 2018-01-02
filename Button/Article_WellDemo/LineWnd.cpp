// LineWnd.cpp : implementation file
//
// Written by Chris Maunder (chrismaunder@codeguru.com)
// Extended by Alexander Bischofberger (bischofb@informatik.tu-muenchen.de)
// Copyright (c) 1998.
#include "stdafx.h"
#include <math.h>
#include "LinePicker.h"
#include "LineWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define INVALID_Line    -1

#define MAX_LineS      9

//#include "svizres.h"

LineTableEntry CSVizLineStyleWell::m_Lines[] = 
{
    { 0,    _T("Solid Line")          },
    { 1,    _T("Dash Line")             },
    { 2,    _T("Dot Line")		},

    { 3,    _T("Dash Dot Line")     },
    { 4,    _T("Dash Dot Dot Line")     },
    { 5,    _T("Dash Dot Dot Dot Line")        },

    { 6,    _T("Round Dot Line")     },
    { 7,    _T("Round Dash Dot Line")     },
    { 8,    _T("Round Dash Dot Dot Line")        }
    
};

/////////////////////////////////////////////////////////////////////////////
// CSVizLineStyleWell
IMPLEMENT_DYNCREATE(CSVizLineStyleWell, CSVizWellCtrl)

CSVizLineStyleWell::CSVizLineStyleWell()
{
}

/** Constructor
 * @param p A CPoint that specifies the left top corner of CSVizLineStyleWell
 * @param crLine Current Line style
 * @param pParentWnd A pointer to parent CWnd, usually is CLinkPicker
 */

CSVizLineStyleWell::CSVizLineStyleWell(CPoint p, int crLine, int n, CWnd* pParentWnd, DWORD dwStyle)
{
	Initialise ();

	m_style = dwStyle;

	m_nNumWells	   = n;

    m_pParent      = pParentWnd;

	if (IsPopupWnd())
	    Create(p,  pParentWnd,  WS_VISIBLE|WS_POPUP);
	else
	    Create(p,  pParentWnd,  WS_VISIBLE|WS_CHILD);
    // Find which cell (if any) corresponds to the initial colour
    FindCellFromWell(crLine);
}

void CSVizLineStyleWell::Initialise()
{
	CSVizWellCtrl::Initialise();
    m_nNumWells         = sizeof(m_Lines)/sizeof(LineTableEntry);
	m_nNumColumns		= 1;

    m_nBoxSize.cx        = 85;
    m_nBoxSize.cy        = 20;
    m_nMargin           = 3*::GetSystemMetrics(SM_CXEDGE);
    m_nCurrentSel       = INVALID_WELL;
    m_nChosenWellSel    = INVALID_WELL;
    m_pParent           = NULL;
}

CSVizLineStyleWell::~CSVizLineStyleWell()
{
}
/*
BOOL CSVizLineStyleWell::Create(CPoint p, int n, CWnd* pParentWnd, DWORD dwWinStyle)
{
    ASSERT(pParentWnd && ::IsWindow(pParentWnd->GetSafeHwnd()));
    m_pParent  = pParentWnd;

    // Get the class name and create the window
    CString szClassName = AfxRegisterWndClass(CS_CLASSDC|CS_SAVEBITS|CS_HREDRAW|CS_VREDRAW,
                                              0,
                                              (HBRUSH) (COLOR_BTNFACE+1), 
                                              0);

    if (!CWnd::CreateEx(0, szClassName, _T(""), WS_VISIBLE|WS_POPUP, 
                        p.x, p.y, 100, 100, // size updated soon
                        pParentWnd->GetSafeHwnd(), 0, NULL))
        return FALSE;
        
	SetPopupWnd(); //It is a popup windows.
	
    // Set the window size
    SetWindowSize();

    // Create the tooltips
    CreateToolTips();

	SetAutoDelete();  //It should destroy itself when selection is done;
	
    // Find which cell (if any) corresponds to the initial colour
    FindCellFromWell(n);

    // Capture all mouse events for the life of this window
    SetCapture();

    return TRUE;
}
*/
BEGIN_MESSAGE_MAP(CSVizLineStyleWell, CSVizWellCtrl)
    //{{AFX_MSG_MAP(CSVizLineStyleWell)
    ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSVizLineStyleWell implementation


void CSVizLineStyleWell::DrawCellContent(CDC* pDC, int nIndex, CRect rect, BYTE state)
{

	Graphics g(pDC->m_hDC);

	Pen pen(Color(255,0,0,0),3);

	pen.SetDashStyle((DashStyle)nIndex);

	g.DrawLine(&pen, rect.left,(rect.top+rect.bottom)/2,rect.right,(rect.top+rect.bottom)/2);
	
}



//! Handle the paint mesasge
void CSVizLineStyleWell::OnPaint() 
{
	CSVizWellCtrl::OnPaint();
}
