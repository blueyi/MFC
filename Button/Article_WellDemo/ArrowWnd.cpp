// ArrowWnd.cpp : implementation file
//
// Written by Chris Maunder (chrismaunder@codeguru.com)
// Extended by Alexander Bischofberger (bischofb@informatik.tu-muenchen.de)
// Copyright (c) 1998.
#include "stdafx.h"
#include <math.h>
#include "ArrowPicker.h"
#include "ArrowWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_ARROWS      9

#include "resource.h"

ArrowTableEntry CSVizArrowWell::m_Arrows[] = 
{
    { 0,    _T("No Arrow")          },
    { 1,    _T("Arrow")             },
    { 2,    _T("Open Arrow")		},

    { 3,    _T("Stealth Arrow")     },
    { 4,    _T("Diamond Arrow")     },
    { 5,    _T("Oval Arrow")        },
    
    { 6,    _T("Square Arrow")      },
    { 7,    _T("Up Stealth Arrow")  },
    { 8,    _T("Low Stealth Arrow") }
};

/////////////////////////////////////////////////////////////////////////////
// CSVizArrowWell
IMPLEMENT_DYNCREATE(CSVizArrowWell, CSVizWellCtrl)

CSVizArrowWell::CSVizArrowWell()
{
}

CSVizArrowWell::CSVizArrowWell(CPoint p, int crArrow, CWnd* pParentWnd, DWORD dwStyle) : CSVizWellCtrl()
{

	Initialise ();
	m_style = dwStyle;

	if (IsPopupWnd()) 
		Create(p, pParentWnd, WS_VISIBLE|WS_POPUP);
	else
		Create(p, pParentWnd, WS_VISIBLE|WS_CHILD);
    // Find which cell (if any) corresponds to the initial colour
    FindCellFromWell(crArrow);
}

void CSVizArrowWell::Initialise()
{
	CSVizWellCtrl::Initialise();

  	SetDrawStyle(WELL_STYLE_CLASSIC);
    m_nNumWells       = sizeof(m_Arrows)/sizeof(ArrowTableEntry);
	m_nNumColumns     = 3;

	m_nBoxSize.cx     = 30;
	m_nBoxSize.cy	  = 30;

    ASSERT(m_nNumWells <= MAX_ARROWS);
    if (m_nNumWells > MAX_ARROWS)
        m_nNumWells = MAX_ARROWS;

//    m_crArrow = m_crInitialArrow = 1; //Standard Arrow
	m_image.Create( IDB_SVIZ_ARROWS, 22, 0, RGB(255,0,0) );

}

CSVizArrowWell::~CSVizArrowWell()
{
}

/*BOOL CSVizArrowWell::Create(CPoint p, int crArrow, CWnd* pParentWnd)
{
	//Dont call the CSVizWellCtrl::Create();

    ASSERT(pParentWnd && ::IsWindow(pParentWnd->GetSafeHwnd()));
    ASSERT(pParentWnd->IsKindOf(RUNTIME_CLASS(CArrowPicker)));
    m_pParent  = pParentWnd;
//    m_crArrow = m_crInitialArrow = crArrow;

    // Get the class name and create the window
    CString szClassName = AfxRegisterWndClass(CS_CLASSDC|CS_SAVEBITS|CS_HREDRAW|CS_VREDRAW,
                                              0,
                                              (HBRUSH) (COLOR_BTNFACE+1), 
                                              0);

    if (!CWnd::CreateEx(0, szClassName, _T(""), WS_VISIBLE|WS_POPUP, 
                        p.x, p.y, 100, 100, // size updated soon
                        pParentWnd->GetSafeHwnd(), 0, NULL))
        return FALSE;

	SetPopupWnd(); //It is a popup windows. Set it BEFORE  SetWindowSize();
	
    // Set the window size
    SetWindowSize();

    // Create the tooltips
    CreateToolTips();

	SetAutoDelete();  //It should destroy itself when selection is done;
	

    // Find which cell (if any) corresponds to the initial colour
    FindCellFromWell(crArrow);

    // Capture all mouse events for the life of this window
    SetCapture();

    return TRUE;
}
*/
BEGIN_MESSAGE_MAP(CSVizArrowWell, CSVizWellCtrl)
    //{{AFX_MSG_MAP(CSVizArrowWell)
    ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSVizArrowWell implementation

void CSVizArrowWell::DrawCellContent(CDC* pDC, int nIndex, CRect rect, BYTE)
{
    rect.DeflateRect(3, 3);
    
	POINT pt;
	pt.x=rect.left;
	pt.y=rect.top;
    m_image.Draw( pDC, nIndex, pt, ILD_TRANSPARENT );

}

//! Handle the paint mesasge
void CSVizArrowWell::OnPaint() 
{
	CSVizWellCtrl::OnPaint();
}
