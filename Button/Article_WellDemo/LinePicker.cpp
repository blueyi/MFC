// LinePicker.cpp : implementation file
//

#include "stdafx.h"
#include "LineWnd.h"
#include "LinePicker.h"
//#include "svizres.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void AFXAPI DDX_LinePicker(CDataExchange *pDX, int nIDC, DashStyle &LineType)
{
    HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
    ASSERT (hWndCtrl != NULL);                
    
    CLinePicker* pLinePicker = (CLinePicker*) CWnd::FromHandle(hWndCtrl);
    if (pDX->m_bSaveAndValidate)
    {
        LineType = (DashStyle)pLinePicker->GetLine();
    }
    else // initializing
    {
        pLinePicker->SetLine((int)LineType);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CLinePicker

CLinePicker::CLinePicker()
{
    m_bTrackSelection = FALSE;
    m_bActive = FALSE;
	m_nNumLines = 5;
}

CLinePicker::~CLinePicker()
{
}

IMPLEMENT_DYNCREATE(CLinePicker, CButton)

BEGIN_MESSAGE_MAP(CLinePicker, CButton)
    //{{AFX_MSG_MAP(CLinePicker)
    ON_CONTROL_REFLECT_EX(BN_CLICKED, OnClicked)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
    ON_REGISTERED_MESSAGE(WELL_SELENDOK,     OnSelEndOK)
    ON_REGISTERED_MESSAGE(WELL_SELENDCANCEL, OnSelEndCancel)
    ON_REGISTERED_MESSAGE(WELL_SELCHANGED,    OnSelChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLinePicker message handlers

LONG CLinePicker::OnSelEndOK(UINT lParam, LONG /*wParam*/)
{
    int LineType = (int) lParam;
    m_bActive = FALSE;
    SetLine(LineType);

    CWnd *pParent = GetParent();
    if (pParent) {
        pParent->SendMessage(WELL_CLOSEUP, lParam, (WPARAM) GetDlgCtrlID());
        pParent->SendMessage(WELL_SELENDOK, lParam, (WPARAM) GetDlgCtrlID());
    }

    if (LineType != GetLine())
        if (pParent) pParent->SendMessage(WELL_SELCHANGED, lParam, (WPARAM) GetDlgCtrlID());

    return TRUE;
}

LONG CLinePicker::OnSelEndCancel(UINT lParam, LONG /*wParam*/)
{
    m_bActive = FALSE;
    SetLine((int) lParam);

    CWnd *pParent = GetParent();
    if (pParent) {
        pParent->SendMessage(WELL_CLOSEUP, lParam, (WPARAM) GetDlgCtrlID());
        pParent->SendMessage(WELL_SELENDCANCEL, lParam, (WPARAM) GetDlgCtrlID());
    }

    return TRUE;
}

LONG CLinePicker::OnSelChange(UINT lParam, LONG /*wParam*/)
{
    if (m_bTrackSelection) SetLine((int) lParam);

    CWnd *pParent = GetParent();
    if (pParent) pParent->SendMessage(WELL_SELCHANGED, lParam, (WPARAM) GetDlgCtrlID());

    return TRUE;
}

int CLinePicker::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CButton::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    SetWindowSize();    // resize appropriately
    return 0;
}

// On mouse click, create and show a CColourPopupWnd window for colour selection
BOOL CLinePicker::OnClicked()
{
    m_bActive = TRUE;
    CRect rect;
    GetWindowRect(rect);
    new CSVizLineStyleWell(CPoint(rect.left, rect.bottom),    // Point to display popup
                     GetLine(),  m_nNumLines,          // Selected colour
                     this,                              // parent
					 WELL_STYLE_OFFICE | WELL_STYLE_AUTODELETE | WELL_STYLE_POPUP
					 );

    CWnd *pParent = GetParent();
    
	
	if (pParent)
        pParent->SendMessage(WELL_DROPDOWN, (LPARAM)GetLine(), (WPARAM) GetDlgCtrlID());

    return TRUE;
}

void CLinePicker::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    ASSERT(lpDrawItemStruct);
    
    CDC*    pDC     = CDC::FromHandle(lpDrawItemStruct->hDC);
    CRect   rect    = lpDrawItemStruct->rcItem;
    UINT    state   = lpDrawItemStruct->itemState;
    //CString m_strText;

    CSize Margins(::GetSystemMetrics(SM_CXEDGE), ::GetSystemMetrics(SM_CYEDGE));

    // Draw Line
    if (m_bActive) state |= ODS_SELECTED;
    pDC->DrawFrameControl(&m_ArrowRect, DFC_SCROLL, DFCS_SCROLLDOWN  | 
                          ((state & ODS_SELECTED) ? DFCS_PUSHED : 0) |
                          ((state & ODS_DISABLED) ? DFCS_INACTIVE : 0));

    pDC->DrawEdge(rect, EDGE_SUNKEN, BF_RECT);

    // Must reduce the size of the "client" area of the button due to edge thickness.
    rect.DeflateRect(Margins.cx, Margins.cy);

    // Fill remaining area with colour
    rect.right -= m_ArrowRect.Width();
    pDC->FillSolidRect(rect, ::GetSysColor(COLOR_3DFACE));
 //center the Line
    rect.DeflateRect(2, 0);

	Graphics g(pDC->m_hDC);

	Pen pen(Color(255,0,0,0),3);

	pen.SetDashStyle((DashStyle)m_Line);

	g.DrawLine(&pen, rect.left,(rect.top+rect.bottom)/2,rect.right,(rect.top+rect.bottom)/2);
	

 
}

/////////////////////////////////////////////////////////////////////////////
// CLinePicker overrides

void CLinePicker::PreSubclassWindow() 
{
    ModifyStyle(0, BS_OWNERDRAW);        // Make it owner drawn
    CButton::PreSubclassWindow();
    SetWindowSize();                     // resize appropriately
}

/////////////////////////////////////////////////////////////////////////////
// CLinePicker attributes

int CLinePicker::GetLine()
{ 
    return m_Line;
}

void CLinePicker::SetLine(int LineType)
{ 
    m_Line=LineType;
}

/////////////////////////////////////////////////////////////////////////////
// CLinePicker implementation

void CLinePicker::SetWindowSize()
{
    // Get size dimensions of edges
    CSize MarginSize(::GetSystemMetrics(SM_CXEDGE), ::GetSystemMetrics(SM_CYEDGE));

    // Get size of dropdown Line
    int nLineWidth = max(::GetSystemMetrics(SM_CXHTHUMB), 5*MarginSize.cx);
    int nLineHeight = max(::GetSystemMetrics(SM_CYVTHUMB), 5*MarginSize.cy);
    CSize LineSize(max(nLineWidth, nLineHeight), max(nLineWidth, nLineHeight));

    // Get window size
    CRect rect;
    GetWindowRect(rect);

    CWnd* pParent = GetParent();
    if (pParent)
        pParent->ScreenToClient(rect);

    // Set window size at least as wide as 2 Lines, and as high as Line + margins
    int nWidth = max(rect.Width(), 2*LineSize.cx + 2*MarginSize.cx);
    MoveWindow(rect.left, rect.top, nWidth, LineSize.cy+2*MarginSize.cy, TRUE);

    // Get the new coords of this window
    GetWindowRect(rect);
    ScreenToClient(rect);

    // Get the rect where the Line goes, and convert to client coords.
    m_ArrowRect.SetRect(rect.right - LineSize.cx - MarginSize.cx, 
                        rect.top + MarginSize.cy, rect.right - MarginSize.cx,
                        rect.bottom - MarginSize.cy);
}

void CLinePicker::SetMaximumLines(int n = 9)
{
	m_nNumLines		  = n;
}
