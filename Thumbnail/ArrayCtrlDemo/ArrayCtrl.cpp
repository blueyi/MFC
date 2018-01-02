/////////////////////////////////////////////////////////////////////////////
// 
// ArrayCtrl.cpp : implementation of the CArrayCtrl class
// 
//
// Using in MFC environment.
//
// Written by Adriano Asnaghi <aasnaghi@mail.tim.it>
// Version 1.0 2004.
//
// This code may be freely used in any way you desire. There is no
// copyright applied on it. If it is helpful for your application
// an email letting me know how you are using it would be nice as well. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author don't accepts liability for any damage or loss of business
// that this product may cause.
//
//        
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ArrayCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// service macros
//
#define IsOutOfBound(i)		((i<0) || (i>=m_nItemsCount))

/////////////////////////////////////////////////////////////////////////////
// CArrayCtrl

//-------------------------------------------------------------------------//
// Constructor                                                             //
//-------------------------------------------------------------------------//
CArrayCtrl::CArrayCtrl()
{
	WNDCLASS	wndcls;
	HINSTANCE	hInst = AfxGetInstanceHandle();

	// Register the window class if it has not already been registered.
	if( !(::GetClassInfo(hInst, ARRAYCTRL_CLASSNAME, &wndcls)) )
	{
		// otherwise we need to register a new class
		wndcls.style			= CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
		wndcls.lpfnWndProc		= ::DefWindowProc;
		wndcls.cbClsExtra		= 0;
		wndcls.cbWndExtra		= 0;
		wndcls.hInstance		= hInst;
		wndcls.hIcon			= NULL;
		wndcls.hCursor			= NULL;
		wndcls.hbrBackground	= (HBRUSH)NULL;
		wndcls.lpszMenuName		= NULL;
		wndcls.lpszClassName	= ARRAYCTRL_CLASSNAME;
		if( !AfxRegisterClass(&wndcls) ) AfxThrowResourceException();
	}

	// Initialize member variables
	m_bDrawable		= FALSE;
	m_pToolTip		= NULL;
	m_pVirtDC		= NULL;
	m_pDrawDC		= NULL;
	m_pFrameDC		= NULL;
	m_hCursor		= LoadCursor(NULL, IDC_ARROW);
	m_nID			= 0;
	m_dwStyle		= 0;
	m_nWidth		= 0;
	m_nHeight		= 0;
	m_nItemsCount	= 0;
	m_nItemW		= 0;
	m_nItemH		= 0;
	m_nColumns		= 0;
	m_nRows			= 0;
	m_nThickness	= 0;
	m_nGrid			= 0;
	m_nSelItem		= -1;
	m_nItemHit		= -1;
	m_nVertLineSize	= 0;
	m_nVertPageSize	= 0;
	m_nHorzLineSize	= 0;
	m_nHorzPageSize	= 0;
	m_nVertPos		= 0;
	m_nHorzPos		= 0;
	m_nVertMax		= 0;
	m_nHorzMax		= 0;
	m_dwUserData	= 0;
	m_lpItemVect	= NULL;
	m_crCtrlBg		= DEFAULT_BACKGROUND_COLOR;		
	m_crGrid		= DEFAULT_GRID_COLOR;
}

//-------------------------------------------------------------------------//
// Destroyer                                                               //
//-------------------------------------------------------------------------//
CArrayCtrl::~CArrayCtrl()
{
}

//-------------------------------------------------------------------------//
// Create method                                                           //
//-------------------------------------------------------------------------//
BOOL CArrayCtrl::Create(DWORD dwStyle, const CRect& rect, CWnd* pParentWnd, UINT nID, const CSize& ItemSize)
{
	CWnd*	pWnd = this;
	DWORD	dwExStyle;

	if( rect.IsRectEmpty() ) return FALSE;

	m_nItemW = ItemSize.cx;
	m_nItemH = ItemSize.cy;

	// separate windows and user control style
	m_dwStyle = dwStyle & CONTROL_MASK_BITS;
	dwStyle &= WINDOWS_MASK_BITS;

	// child and scrolling bars forced style
	dwStyle |= WS_CHILD | WS_VSCROLL | WS_HSCROLL;

	if( m_dwStyle & ACS_CLIENTEDGE ) dwExStyle = WS_EX_CLIENTEDGE;

	m_nID = nID;
	return pWnd->CreateEx(dwExStyle, ARRAYCTRL_CLASSNAME, NULL, dwStyle, rect, pParentWnd, nID, NULL);
}


BEGIN_MESSAGE_MAP(CArrayCtrl,CWnd)
	//{{AFX_MSG_MAP(CArrayCtrl)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
    ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
    ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CArrayCtrl message handlers

//-------------------------------------------------------------------------//
// Manages WM_CREATE message                                               //
//-------------------------------------------------------------------------//
int CArrayCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if( CWnd::OnCreate(lpCreateStruct) == -1 ) return -1;

	// Gridlines required? Yes, set default gridline thickness
	if( m_dwStyle & ACS_GRIDLINES ) m_nGrid = m_nThickness = 1;

	VdcCreate();
	VdcDraw();
	
	// Tooltip support required?
	if( m_dwStyle & ACS_TOOLTIP ) SetToolTip((m_dwStyle & ACS_TTBALLOON? TTS_BALLOON: 0));
	return 0;
}

//-------------------------------------------------------------------------//
// Manages WM_SIZE message                                                 //
//-------------------------------------------------------------------------//
void CArrayCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CRect		rcTool;

	m_nWidth = cx;
	m_nHeight = cy;
	VdcSetDrawable();
	m_pVirtDC->Resize(cx, cy);

	if( m_pToolTip )
	{
		GetClientRect(&rcTool);
		if( ::IsWindow(m_pToolTip->m_hWnd) ) m_pToolTip->SetToolRect(this, m_nID, &rcTool);
	}

	VdcUpdate();
}

//-------------------------------------------------------------------------//
// Manages WM_PAINT message                                                //
//-------------------------------------------------------------------------//
void CArrayCtrl::OnPaint() 
{
	CPaintDC dc(this);
	
	// simply copy virtual DC into window DC
	// this avoid troublesome flickering
	dc.BitBlt(0, 0, m_nWidth, m_nHeight, m_pVirtDC->GetDC(), 0, 0, SRCCOPY);	

	// Do not call CWnd::OnPaint() for painting messages
}

//-------------------------------------------------------------------------//
// Manages WM_VSCROLL message                                              //
//-------------------------------------------------------------------------//
void CArrayCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int			nNewVertPos;
	SCROLLINFO	si;

	switch( nSBCode ) 
	{
	// This code come from user invoked scroll method.
	// Then new position is 0. 
	case SB_TOP:
		nNewVertPos = 0; 
		break; 

	// This code come from user invoked scroll method.
	// Then new position is maximun minus view height. 
	case SB_BOTTOM:
		nNewVertPos = m_nVertMax - m_nHeight; 
		break; 

	// User clicked the shaft above the scroll box.
	// Then new position is one page before current position. 
	case SB_PAGEUP: 
		nNewVertPos = m_nVertPos - (m_nVertPageSize? m_nVertPageSize: m_nHeight); 
		break; 

	// User clicked the shaft below the scroll box. 
	// Then new position is one page after current position. 
	case SB_PAGEDOWN: 
		nNewVertPos = m_nVertPos + (m_nVertPageSize? m_nVertPageSize: m_nHeight); 
		break; 

	// User clicked the top arrow. 
	// Then new position is one line before current position. 
	case SB_LINEUP: 
		nNewVertPos = m_nVertPos - (m_nVertLineSize? m_nVertLineSize: m_nItemH + m_nGrid*2); 
		break; 

	// User clicked the bottom arrow. 
	// Then new position is one line after current position. 
	case SB_LINEDOWN: 
		nNewVertPos = m_nVertPos + (m_nVertLineSize? m_nVertLineSize: m_nItemH + m_nGrid*2); 
		break; 

	// User dragged the scroll box. 
	// Then new position must follow the scroll box position. 
	case SB_THUMBTRACK:
		nNewVertPos = nPos;
		break; 

	default: 
		nNewVertPos = m_nVertPos; 
	} 
 
	// New position must be between 0 and maximum virtual vertical height. 
	nNewVertPos = max(0, nNewVertPos); 
	nNewVertPos = min(m_nVertMax, nNewVertPos); 
 
	// If the current position does not change, do not scroll (sure!).
	if( nNewVertPos == m_nVertPos ) return; 

	// If new position plus pagesize exceed max virtual height, adjust it
	if( (nNewVertPos + m_nHeight) > m_nVertMax ) nNewVertPos = m_nVertMax - m_nHeight + 1; 
	if( nNewVertPos < 0 ) nNewVertPos = 0;

	// Finally, set the new scroll value
	m_nVertPos = nNewVertPos; 

	// Reset the scroll bar to reflect new position
	si.cbSize = sizeof(si); 
	si.fMask  = SIF_POS; 
	si.nPos   = nNewVertPos;
	SetScrollInfo(SB_VERT, &si, TRUE);
	VdcDraw();
}

//-------------------------------------------------------------------------//
// Manages WM_HSCROLL message                                              //
//-------------------------------------------------------------------------//
void CArrayCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int			nNewHorzPos;
	SCROLLINFO	si;

	switch( nSBCode ) 
	{ 
	// This code come from user invoked scroll method.
	// Then new position is 0. 
	case SB_LEFT:
		nNewHorzPos = 0; 
		break; 

	// This code come from user invoked scroll method.
	// Then new position is maximun minus one view width. 
	case SB_RIGHT:
		nNewHorzPos = m_nHorzMax - m_nWidth; 
		break; 

	// User clicked the shaft left the scroll box. 
	// Then new position is one page before current position. 
	case SB_PAGEUP: 
		nNewHorzPos = m_nHorzPos - (m_nHorzPageSize? m_nHorzPageSize: m_nWidth); 
		break; 

	// User clicked the shaft right the scroll box. 
	// Then new position is one page after current position. 
	case SB_PAGEDOWN: 
		nNewHorzPos = m_nHorzPos + (m_nHorzPageSize? m_nHorzPageSize: m_nWidth); 
		break; 

	// User clicked the left arrow. 
	// Then new position is one line before current position. 
	case SB_LINEUP: 
		nNewHorzPos = m_nHorzPos - (m_nHorzLineSize? m_nHorzLineSize: m_nItemW); 
		break; 

	// User clicked the right arrow. 
	// Then new position is one line after current position. 
	case SB_LINEDOWN: 
		nNewHorzPos = m_nHorzPos + (m_nHorzLineSize? m_nHorzLineSize: m_nItemW); 
		break; 

	// User dragged the scroll box. 
	// Then new position must follow the scroll box position. 
	case SB_THUMBTRACK:
		nNewHorzPos = nPos;
		break; 

	default: 
		nNewHorzPos = m_nHorzPos; 
	} 
 
	// New position must be between 0 and the virtual horizontal width. 
	nNewHorzPos = max(0, nNewHorzPos); 
	nNewHorzPos = min(m_nHorzMax, nNewHorzPos); 
 
	// If the current position does not change, do not scroll (sure!).
	if( nNewHorzPos == m_nHorzPos ) return; 
 
	// If new position plus pagesize exceed max virtual height, adjust it
	if( (nNewHorzPos + m_nWidth) > m_nHorzMax ) nNewHorzPos = m_nHorzMax - m_nWidth + 1; 
	if( nNewHorzPos < 0 ) nNewHorzPos = 0;

	// Finally, set the new scroll value
	m_nHorzPos = nNewHorzPos; 

	// Reset the scroll bar to reflect new position
	si.cbSize = sizeof(si); 
	si.fMask  = SIF_POS; 
	si.nPos   = nNewHorzPos;
	SetScrollInfo(SB_HORZ, &si, TRUE);
	VdcDraw();
}

//-------------------------------------------------------------------------//
// Manages WM_LBUTTONDOWN message                                          //
//-------------------------------------------------------------------------//
void CArrayCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	int				nOldSelItem;
	ACITEMACTIVATE	acia;

	ASSERT(::IsWindow(m_hWnd));

	// save old selected item
	nOldSelItem = m_nSelItem;
	// get new item selected (if any)
	m_nSelItem = HitTest(&point);
	// redraw this items
	VdcRedraw(nOldSelItem, m_nSelItem);

	// Prepare notification message structure
	ZeroMemory(&acia, sizeof(ACITEMACTIVATE));
	acia.hdr.hwndFrom	= m_hWnd;
	acia.hdr.idFrom		= m_nID;
	acia.hdr.code		= ACN_CLICK;
	acia.pControl		= this;
	acia.nItem			= m_nSelItem;
	acia.dwState		= (m_nSelItem<0? ACIS_NORMAL: ACIS_SELECTED);
	acia.ptAction		= point;
	acia.nRow			= GetRowIndex();
	acia.nColumn		= GetColumnIndex();
	acia.nKeyFlags		= nFlags;
	acia.dwParam		= GetItemData(m_nSelItem);
	// notify to parent window
	::SendMessage(::GetParent(m_hWnd), WM_NOTIFY, m_nID, (LPARAM)&acia);
}

//-------------------------------------------------------------------------//
// Manages WM_RBUTTONDOWN message                                          //
//-------------------------------------------------------------------------//
void CArrayCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	int				nOldSelItem;
	ACITEMACTIVATE	acia;

	ASSERT(::IsWindow(m_hWnd));

	// save old selected item
	nOldSelItem = m_nSelItem;
	// get new item selected (if any)
	m_nSelItem = HitTest(&point);
	// redraw this items
	VdcRedraw(nOldSelItem, m_nSelItem);

	// Prepare notification message structure
	ZeroMemory(&acia, sizeof(ACITEMACTIVATE));
	acia.hdr.hwndFrom	= m_hWnd;
	acia.hdr.idFrom		= ::GetWindowLong(m_hWnd, GWL_ID);
	acia.hdr.code		= ACN_RCLICK;
	acia.pControl		= this;
	acia.nItem			= m_nSelItem;
	acia.dwState		= (m_nSelItem<0? ACIS_NORMAL: ACIS_SELECTED);
	acia.ptAction		= point;
	acia.nRow			= GetRowIndex();
	acia.nColumn		= GetColumnIndex();
	acia.nKeyFlags		= nFlags;
	acia.dwParam		= GetItemData(m_nSelItem);
	// notify to parent window
	::SendMessage(::GetParent(m_hWnd), WM_NOTIFY, m_nID, (LPARAM)&acia);
}

//-------------------------------------------------------------------------//
// Manages WM_LBUTTONDBLCLK message                                        //
//-------------------------------------------------------------------------//
void CArrayCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	int				nOldSelItem;
	ACITEMACTIVATE	acia;

	ASSERT(::IsWindow(m_hWnd));

	// save old selected item
	nOldSelItem = m_nSelItem;
	// get new item selected (if any)
	m_nSelItem = HitTest(&point);
	// redraw this items
	VdcRedraw(nOldSelItem, m_nSelItem);

	// Prepare notification message structure
	ZeroMemory(&acia, sizeof(ACITEMACTIVATE));
	acia.hdr.hwndFrom	= m_hWnd;
	acia.hdr.idFrom		= m_nID;
	acia.hdr.code		= ACN_DBCLICK;
	acia.pControl		= this;
	acia.nItem			= m_nSelItem;
	acia.dwState		= (m_nSelItem<0? ACIS_NORMAL: ACIS_SELECTED);
	acia.ptAction		= point;
	acia.nRow			= GetRowIndex();
	acia.nColumn		= GetColumnIndex();
	acia.nKeyFlags		= nFlags;
	acia.dwParam		= GetItemData(m_nSelItem);
	// notify to parent window
	::SendMessage(::GetParent(m_hWnd), WM_NOTIFY, m_nID, (LPARAM)&acia);
}

//-------------------------------------------------------------------------//
// Manages WM_ERASEBACKGROUND message                                      //
//-------------------------------------------------------------------------//
BOOL CArrayCtrl::OnEraseBkgnd(CDC *pDC)
{
	// simply copy virtual DC into window DC
	pDC->BitBlt(0, 0, m_nWidth, m_nHeight, m_pVirtDC->GetDC(), 0, 0, SRCCOPY);	
	// none further action 
	return 1;
}

//-------------------------------------------------------------------------//
// Manages WM_MOUSEMOVE message                                            //
//-------------------------------------------------------------------------//
void CArrayCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	int		nItemUnderPointer;

	::SetCursor(m_hCursor);
	if( m_pToolTip != NULL )
	{
		if( ::IsWindow(m_pToolTip->m_hWnd) )
		{
			nItemUnderPointer = HitTest((CPoint*)&point);
			// if no item is under pointer or this item is not the active tooltip item... 
			if( (nItemUnderPointer < 0) || (nItemUnderPointer != m_nItemHit) )
			{
				// ... then disable tooltip
				m_pToolTip->Activate(FALSE);        
			}
			// if item is valid ...
			if( nItemUnderPointer >= 0 )
			{
				// ... then enable tooltip
				m_pToolTip->Activate(TRUE);
				// and set to current
				m_nItemHit = nItemUnderPointer;
			}
		}
	}
    CWnd::OnMouseMove(nFlags, point);
}

//-------------------------------------------------------------------------//
// Implement the PreTranslateMessage() method                              //
// This must be done to relay event to tooltip control                     //
//-------------------------------------------------------------------------//
BOOL CArrayCtrl::PreTranslateMessage(MSG *pMsg)
{
	if( m_pToolTip != NULL )
	{
		if( ::IsWindow(m_pToolTip->m_hWnd) && (pMsg->hwnd == m_hWnd) )
		{
			switch(pMsg->message)
			{
			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_MBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_MBUTTONUP:
			case WM_RBUTTONUP:
			case WM_MOUSEMOVE:
				m_pToolTip->Activate (TRUE);
				m_pToolTip->RelayEvent(pMsg);
				break;
			}
		}
	}
	return CWnd::PreTranslateMessage(pMsg);
}

//-------------------------------------------------------------------------//
// Manages ToolTip notification message                                    //
//-------------------------------------------------------------------------//
BOOL CArrayCtrl::OnToolTipText(UINT nId, NMHDR *pNMHDR, LRESULT *pResult)
{
	// need to handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA*	pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW*	pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	UINT			nID = pNMHDR->idFrom;
	int				nItem;
	POINT			point;
	ACTOOLTIPINFO	actti;
	TCHAR			szTipText[MAX_PATH];

	// manage only if NEEDTEXT is required
	if( (pNMHDR->code == TTN_NEEDTEXTA) || (pNMHDR->code == TTN_NEEDTEXTW) )
	{
		// pointer coordinates are relative to screen
		// the convert them
		::GetCursorPos(&point);
		ScreenToClient(&point);
		nItem = HitTest((CPoint*)&point);
		szTipText[0] = NIL;
		if( nItem >= 0 )
		{	
			ASSERT(::IsWindow(m_hWnd));
			// Prepare notification message structure to pass request
			// to parent window
			ZeroMemory(&actti, sizeof(ACTOOLTIPINFO));
			actti.hdr.hwndFrom	= m_hWnd;
			actti.hdr.idFrom	= m_nID;
			actti.hdr.code		= ACN_NEEDTIPTEXT;
			actti.pControl		= this;
			actti.lpszTipText	= TPTR(szTipText);
			actti.nItem			= nItem;
			actti.nColumn		= GetColumnIndex(nItem);
			actti.nRow			= GetRowIndex(nItem);
			actti.dwState		= GetItemState(nItem);
			actti.dwParam		= GetItemData(nItem);
			// notify to parent window
			::SendMessage(::GetParent(m_hWnd), WM_NOTIFY, m_nID, (LPARAM)&actti);
		}
		if( pNMHDR->code == TTN_NEEDTEXTA ) lstrcpyn(pTTTA->szText, CTPTR(szTipText), sizeof(pTTTA->szText));
		else _mbstowcsz(pTTTW->szText, CTPTR(szTipText), sizeof(pTTTW->szText));
	}
	*pResult = 0;
	return TRUE;
}

//-------------------------------------------------------------------------//
// Manages WM_DESTROY message                                              //
//-------------------------------------------------------------------------//
void CArrayCtrl::OnDestroy() 
{
	CWnd ::OnDestroy();

	if( (m_dwStyle & ACS_TOOLTIP) && m_pToolTip )
	{
		if( ::IsWindow(m_pToolTip->m_hWnd) ) m_pToolTip->DelTool(this, m_nID);
	}
	// delete all objects
	if( m_nItemsCount ) RemoveAllItems();
	VdcDelete();
}


/////////////////////////////////////////////////////////////////////////////
// CArrayCtrl service methods

//-------------------------------------------------------------------//
// Activate/Disactivate control                                      //
//-------------------------------------------------------------------//
void CArrayCtrl::Activate(BOOL bFlag)
{
	ASSERT(::IsWindow(m_hWnd));

	if( bFlag == FALSE )
	{
		m_dwStyle |= ACS_NOREDRAW;
		ShowWindow(SW_HIDE);
		return;
	}
	m_dwStyle &= ~ACS_NOREDRAW;
	ShowWindow(SW_SHOW);
	VdcUpdate();
	return;
}


//-------------------------------------------------------------------//
// Activate a tooltip control                                        //
//-------------------------------------------------------------------//
void CArrayCtrl::SetToolTip(DWORD ttstyle)
{
	CRect		rc;

	m_pToolTip = new CToolTipCtrl;
	if( m_pToolTip->Create(this, ttstyle) )
	{
		GetClientRect(&rc);
		m_pToolTip->AddTool(this, LPSTR_TEXTCALLBACK, &rc, m_nID);
		if( m_nItemsCount ) m_pToolTip->Activate(TRUE);
	}
}

//-------------------------------------------------------------------//
// Set the tooltip colors                                            //
//-------------------------------------------------------------------//
void CArrayCtrl::SetTipColor(COLORREF crBkg, COLORREF crTxt)
{
	if( m_pToolTip != NULL )
	{
		if( crBkg != CLR_NONE ) m_pToolTip->SetTipBkColor(crBkg);
		if( crTxt != CLR_NONE ) m_pToolTip->SetTipTextColor(crTxt);
	}
}

//-------------------------------------------------------------------//
// Set the control's cursor handle                                   //
//-------------------------------------------------------------------//
void CArrayCtrl::SetCursor(HCURSOR hCursor)
{
	if( hCursor == NULL ) m_hCursor = LoadCursor(NULL, IDC_ARROW);
	else m_hCursor = hCursor;
}

//-------------------------------------------------------------------//
// Set the number of columns or rows to be fixed                     //
//-------------------------------------------------------------------//
void CArrayCtrl::SetDimension(int num, int obj)
{
	switch( obj )
	{
	case ACDT_COLUMNS:
		// columns must be fixed
		if( (m_dwStyle & ACS_FIXEDROW) )
		{
			// if previous fixed object was rows then reset it
			m_nRows = 0;
			m_dwStyle &= ~ACS_FIXEDROW;
		}
		// if columns count is 0 the reset it
		if( num ) m_dwStyle |= ACS_FIXEDCOL;
		else m_dwStyle &= ~ACS_FIXEDCOL;
		m_nColumns = num;
		break;
	case ACDT_ROWS:
		// rows must be fixed
		if( (m_dwStyle & ACS_FIXEDCOL) )
		{
			// if previous fixed object was columns then reset it
			m_nColumns = 0;
			m_dwStyle &= ~ACS_FIXEDCOL;
		}
		if( num ) m_dwStyle |= ACS_FIXEDROW;
		else m_dwStyle &= ~ACS_FIXEDROW;
		m_nRows = num;
		break;
	default:
		return;
	}

	VdcUpdate();
}

//-------------------------------------------------------------------//
// Get the number of fixed columns or rows                           //
//-------------------------------------------------------------------//
int CArrayCtrl::GetDimension(int* dimtype)
{
	if( (m_dwStyle & ACS_FIXEDCOL) )
	{
		*dimtype = ACDT_COLUMNS;
		return m_nColumns;
	}
	if( (m_dwStyle & ACS_FIXEDROW) )
	{
		*dimtype = ACDT_ROWS;
		return m_nRows;
	}
	*dimtype = ACDT_NODIMS;
	return 0;
}

//-------------------------------------------------------------------//
// Get the row index of a given item                                 //
//-------------------------------------------------------------------//
int	CArrayCtrl::GetRowIndex(int nItem)
{
	if( IsOutOfBound(nItem) || !m_nColumns ) return -1; 
	return (nItem/m_nColumns);
}

//-------------------------------------------------------------------//
// Get the column index of a given item                              //
//-------------------------------------------------------------------//
int	CArrayCtrl::GetColumnIndex(int nItem)
{
	if( IsOutOfBound(nItem) || !m_nColumns ) return -1; 
	return (nItem%m_nColumns);
}

//----------------------------------------------------------------------------------//
// Change the items count                               						    //
//----------------------------------------------------------------------------------//
void CArrayCtrl::SetItemCount(int nItems)
{
	if( m_nItemsCount ) RemoveAllItems();
	if( !nItems ) return;
	m_nItemsCount = nItems;
	AllocateVector();
	m_nSelItem = -1;
	if( m_dwStyle & ACS_NOREDRAW ) return;
	VdcSetDrawable();
	VdcUpdate();
	if( (m_dwStyle & ACS_TOOLTIP) && (m_nItemsCount) && m_pToolTip ) m_pToolTip->Activate(TRUE);
}

//-------------------------------------------------------------------//
// Resize the item                                                   //
//-------------------------------------------------------------------//
void CArrayCtrl::SetItemSize(int width, int height)
{
	// no null values are permitted
	if( !width || !height ) return;

	// set the members values
	m_nItemW = width;
	m_nItemH = height;

	m_pDrawDC->Resize(width, height);
	if( m_pFrameDC ) m_pFrameDC->Resize(width + m_nThickness*2, height + m_nThickness*2);

	// update control to reflect changes
	VdcSetDrawable();
	VdcUpdate();
}

//-------------------------------------------------------------------//
// Get the item size                                                 //
//-------------------------------------------------------------------//
void CArrayCtrl::GetItemSize(CSize* pSize)
{
	pSize->cx = m_nItemW;
	pSize->cy = m_nItemH;
}

//----------------------------------------------------------------------------------//
// Set or reset resize availability                                                 //
//----------------------------------------------------------------------------------//
void CArrayCtrl::SetRedraw(BOOL bDraw)
{
	if( bDraw == FALSE )
	{
		m_dwStyle |= ACS_NOREDRAW;
		return;
	}
	m_dwStyle &= ~ACS_NOREDRAW;
	VdcSetDrawable();
	VdcUpdate();
	if( (m_dwStyle & ACS_TOOLTIP) && (m_nItemsCount) && m_pToolTip ) m_pToolTip->Activate(TRUE);
}

//----------------------------------------------------------------------------------//
// Add an item to control                                                           //
// Item will be added at specified position of the vector                           //
//----------------------------------------------------------------------------------//
void CArrayCtrl::AddItem(int nItem, LPARAM dwData)
{
	LPARAM*		lpNewVect;
	int			nInsertPos;

	// if no data will be associated to item, this call don't make sense.
	// may be, has user forgotten the USERDATA bit? Shell we assume as default?
	// We think that user is aware of what is doing. 
	if( m_dwStyle & ACS_USERDATA )
	{
		// Resize items vector
		lpNewVect = new LPARAM[m_nItemsCount+1];
		ASSERT(lpNewVect);
		// default insert position
		nInsertPos = m_nItemsCount;
		if( m_lpItemVect )
		{
			// add to bottom?
			if( (nItem == ACAI_BOTTOM) || (nItem == m_nItemsCount) )
			{
				::BoundsCopy(lpNewVect, 0, m_lpItemVect, 0, m_nItemsCount); 
			}
			// add to top?
			else if( nItem == ACAI_TOP )
			{
				::BoundsCopy(lpNewVect, 1, m_lpItemVect, 0, m_nItemsCount); 
				nInsertPos = 0;
			}
			else
			{
				if( IsOutOfBound(nItem) ) return;
				::BoundsCopy(lpNewVect, 0, m_lpItemVect, 0, nItem+1);
				::BoundsCopy(lpNewVect, nItem+2, m_lpItemVect, nItem+1, m_nItemsCount);
				nInsertPos = nItem + 1;
 			}
			delete [] m_lpItemVect;
		}
		lpNewVect[nInsertPos] = dwData;
		m_lpItemVect = lpNewVect;
	}
	m_nItemsCount++;
	if( m_dwStyle & ACS_NOREDRAW ) return;
	VdcSetDrawable();
	VdcUpdate();
	if( (m_dwStyle & ACS_TOOLTIP) && (m_nItemsCount) && m_pToolTip ) m_pToolTip->Activate(TRUE);
}

//----------------------------------------------------------------------------------//
// Set user data on a given item                                                    //
//----------------------------------------------------------------------------------//
LPARAM CArrayCtrl::SetItemData(int nItem, LPARAM dwData)
{
	LPARAM	dwOldData;

	if( !(m_dwStyle & ACS_USERDATA) ) return 0;
	if( IsOutOfBound(nItem) ) return 0;
	if( m_lpItemVect == NULL ) AllocateVector();
	dwOldData = m_lpItemVect[nItem];
	m_lpItemVect[nItem] = dwData;
	return dwOldData;
}

//----------------------------------------------------------------------------------//
// Get user data of a given item                                                    //
//----------------------------------------------------------------------------------//
LPARAM CArrayCtrl::GetItemData(int nItem)
{
	if( !(m_dwStyle & ACS_USERDATA) ) return 0;
	if( IsOutOfBound(nItem) ) return 0;
	if( m_lpItemVect == NULL ) return 0;
	return m_lpItemVect[nItem];
}

//----------------------------------------------------------------------------------//
// Remove an item from control                                                      //
//----------------------------------------------------------------------------------//
void CArrayCtrl::RemoveItem(int nItem)
{
	ACITEMINFO	mcii;

	if( IsOutOfBound(nItem) ) return;

	// Prepare notification message structure
	ZeroMemory(&mcii, sizeof(ACITEMINFO));
	mcii.hdr.hwndFrom	= m_hWnd;
	mcii.hdr.idFrom		= m_nID;
	mcii.hdr.code		= ACN_DELETEITEM;
	mcii.pControl		= this;
	mcii.pDC			= NULL;
	mcii.nWidth			= 0;
	mcii.nHeight		= 0;
	mcii.nItem			= nItem;
	mcii.nRow			= 0;
	mcii.nColumn		= 0;
	mcii.dwState		= ACIS_NORMAL;
	mcii.dwParam		= GetItemData(nItem);
	::SendMessage(::GetParent(m_hWnd), WM_NOTIFY, m_nID, (LPARAM)&mcii);

	if( m_dwStyle & ACS_USERDATA )
	{
		if( nItem < m_nItemsCount-1 )
		{
			::BoundsCopy(m_lpItemVect, nItem, m_lpItemVect, nItem+1, m_nItemsCount);
		}
	}
	--m_nItemsCount;
	if( m_nItemsCount )
	{
		m_nSelItem = -1;
		VdcUpdate();
		return;
	}
	m_nColumns = m_nRows = 0;
	m_nHorzMax = m_nVertMax = 0;
	m_nVertPos = m_nHorzPos = 0;
	m_bDrawable = FALSE;
	if( m_lpItemVect ) delete [] m_lpItemVect;
	m_lpItemVect = NULL;
	m_pVirtDC->Erase();
	VdcInvalidate();
}

//----------------------------------------------------------------------------------//
// Remove all items from control                                                    //
//----------------------------------------------------------------------------------//
void CArrayCtrl::RemoveAllItems()
{
	int			i;
	ACITEMINFO	mcii;

	for(i=0; i<m_nItemsCount; i++)
	{
		// Prepare notification message structure
		ZeroMemory(&mcii, sizeof(ACITEMINFO));
		mcii.hdr.hwndFrom	= m_hWnd;
		mcii.hdr.idFrom		= m_nID;
		mcii.hdr.code		= ACN_DELETEITEM;
		mcii.pControl		= this;
		mcii.pDC			= NULL;
		mcii.nWidth			= 0;
		mcii.nHeight		= 0;
		mcii.nItem			= i;
		mcii.nRow			= 0;
		mcii.nColumn		= 0;
		mcii.dwState		= ACIS_NORMAL;
		mcii.dwParam		= GetItemData(i);
		::SendMessage(::GetParent(m_hWnd), WM_NOTIFY, m_nID, (LPARAM)&mcii);
	}

	if( m_lpItemVect ) delete [] m_lpItemVect;
	m_lpItemVect = NULL;
	m_nItemsCount = 0;
	m_nColumns = m_nRows = 0;
	m_nHorzMax = m_nVertMax = 0;
	m_nVertPos = m_nHorzPos = 0;
	m_bDrawable = FALSE;
	VdcSetScroll();
	m_pVirtDC->Erase();
	VdcInvalidate();
}

//----------------------------------------------------------------------------------//
// Get item state                                                                   //
//----------------------------------------------------------------------------------//
DWORD CArrayCtrl::GetItemState(int nItem)
{
	DWORD		dwState = 0;

	dwState = (nItem==m_nSelItem?ACIS_SELECTED: ACIS_NORMAL);
	dwState |= (IsVisible(nItem)==TRUE? ACIS_VISIBLE: ACIS_HIDDEN);
	return dwState;
}

//----------------------------------------------------------------------------------//
// User ask to drawing a specific item                                              //
//----------------------------------------------------------------------------------//
void CArrayCtrl::DrawItem(int nItem)
{
	CRect		rcView;

	if( IsOutOfBound(nItem) ) return;
	rcView.SetRect(0, 0, m_nWidth, m_nHeight);
	VdcItemDraw(&rcView, nItem);
	VdcInvalidate();
}

//----------------------------------------------------------------------------------//
// Verify if mouse is over an element (CPoint coordinate)                           //
//----------------------------------------------------------------------------------//
int CArrayCtrl::HitTest(CPoint* pPoint)
{
	return HitTest(pPoint->x, pPoint->y);
}

//----------------------------------------------------------------------------------//
// Verify if mouse is over an element (x and y coordinate)                          //
//----------------------------------------------------------------------------------//
int CArrayCtrl::HitTest(int x, int y)
{
	int			nCol, nRow, nItem;

	// Note. Coordinates must be relative to control's client area.

	// check presence of some values
	if( m_bDrawable == FALSE ) return -1;
	if( (y < 0) || (y > m_nHeight) ) return -1;
	if( (x < 0) || (x > m_nWidth) ) return -1;

	// get column index 
	nCol = (x - m_nGrid + m_nHorzPos)/(m_nItemW + m_nGrid);
	if( nCol >= m_nColumns ) return -1;

	// get row index 
	nRow = (y - m_nGrid + m_nVertPos)/(m_nItemH + m_nGrid);
	if( nRow >= m_nRows ) return -1;

	nItem = nRow * m_nColumns + nCol;
	if( nItem < m_nItemsCount ) return nItem;
	return -1;
}

//-------------------------------------------------------------------//
// Check if an item lie into visible view                            //
//-------------------------------------------------------------------//
BOOL CArrayCtrl::IsVisible(int nItem)
{
	int			x, y;

	ASSERT(::IsWindow(m_hWnd));
	if( IsOutOfBound(nItem) ) return FALSE;
	if( m_bDrawable == FALSE ) return FALSE;

	x = GetColumnIndex(nItem) * (m_nItemW + m_nGrid);
	y = GetRowIndex(nItem) * (m_nItemH + m_nGrid);

	if( y > (m_nVertPos + m_nHeight) ) return FALSE;
	if( (y + m_nItemH) < m_nVertPos ) return FALSE;
	if( x > (m_nHorzPos + m_nWidth) ) return FALSE;
	if( (x + m_nItemW) < m_nHorzPos ) return FALSE;
	return TRUE;
}

//----------------------------------------------------------------------------------//
// Change the background brush                                                      //
//----------------------------------------------------------------------------------//
void CArrayCtrl::SetBkColor(COLORREF crBack)
{
	if( crBack == CLR_NONE ) return;
	m_pVirtDC->SetColor(crBack);
	m_pDrawDC->SetColor(crBack);
	m_crCtrlBg = crBack;
	VdcDraw();
}

//----------------------------------------------------------------------------------//
// Change the gridline brush                                                        //
//----------------------------------------------------------------------------------//
void CArrayCtrl::SetGridColor(COLORREF crGrid)
{
	if( crGrid != CLR_NONE )
	{
		if( m_pFrameDC ) m_pFrameDC->SetColor(crGrid);
		m_crGrid = crGrid;
	}
	VdcDraw();
}

//----------------------------------------------------------------------------------//
// Change the background and gridline brush together                                //
//----------------------------------------------------------------------------------//
void CArrayCtrl::SetColors(COLORREF crBack, COLORREF crGrid)
{
	// CLR_NONE is a Windows define that indicates NO COLOR SPECIFIED
	if( crBack != CLR_NONE )
	{
		m_pVirtDC->SetColor(crBack);
		m_pDrawDC->SetColor(crBack);
		m_crCtrlBg = crBack;
	}
	if( crGrid != CLR_NONE )
	{
		if( m_pFrameDC ) m_pFrameDC->SetColor(crGrid);
		m_crGrid = crGrid;
	}
	VdcDraw();
}

//----------------------------------------------------------------------------------//
// Activate or disactivate gridlines                                                //
//----------------------------------------------------------------------------------//
void CArrayCtrl::SetGridLines(BOOL bActive)
{
	if( bActive == TRUE )
	{
		if( (m_dwStyle & ACS_GRIDLINES) ) return;
		m_dwStyle |= ACS_GRIDLINES;
		m_nGrid = m_nThickness;
	}
	else
	{
		if( (m_dwStyle & ACS_GRIDLINES) == 0 ) return;
		m_dwStyle &= ~ACS_GRIDLINES;
		m_nGrid = 0;
	}
	VdcDraw();
}

//----------------------------------------------------------------------------------//
// Set the grid lines thickness                                                     //
//----------------------------------------------------------------------------------//
void CArrayCtrl::SetGridThickness(int nThickness)
{
	if( !nThickness ) return;
	m_nThickness = nThickness;
	m_pFrameDC->Resize(m_nItemW+m_nThickness*2, m_nItemH+m_nThickness*2);
	m_nGrid = m_nThickness;
	VdcDraw();
}

//----------------------------------------------------------------------------------//
// Set scroll position                                                              //
//----------------------------------------------------------------------------------//
void CArrayCtrl::Scroll(UINT nSBVers, UINT nSBCode)
{
	switch( nSBVers )
	{
	case SB_HORZ: HorzScroll(nSBCode); break;
	case SB_VERT: VertScroll(nSBCode); break;
	}
}

//----------------------------------------------------------------------------------//
// Set scroll at specific position                                                  //
//----------------------------------------------------------------------------------//
void CArrayCtrl::Scroll(UINT nSBVers, UINT nSBCode, UINT nPos)
{
	switch( nSBVers )
	{
	case SB_HORZ: HorzScroll(nSBCode, nPos); break;
	case SB_VERT: VertScroll(nSBCode, nPos); break;
	}
}

//----------------------------------------------------------------------------------//
// Set vertical scroll position                                                     //
//----------------------------------------------------------------------------------//
void CArrayCtrl::VertScroll(UINT nSBCode)
{
	switch( nSBCode )
	{
	case SB_TOP:
	case SB_BOTTOM:
	case SB_PAGEUP: 
	case SB_PAGEDOWN: 
	case SB_LINEUP: 
	case SB_LINEDOWN: 
		OnVScroll(nSBCode, 0, NULL);
		break;
	}
}

//----------------------------------------------------------------------------------//
// Set vertical scroll at specific position                                         //
//----------------------------------------------------------------------------------//
void CArrayCtrl::VertScroll(UINT nSBCode, UINT nPos)
{
	UINT		i;

	switch( nSBCode )
	{
	case SB_PAGEUP: 
	case SB_PAGEDOWN: 
	case SB_LINEUP: 
	case SB_LINEDOWN: 
		for(i=0; i<nPos; i++) OnVScroll(nSBCode, 0, NULL);
		break;
	case SB_THUMBPOSITION:
		OnVScroll(SB_THUMBTRACK, nPos, NULL);
		break; 
	}
}

//----------------------------------------------------------------------------------//
// Set horizontal scroll position                                                   //
//----------------------------------------------------------------------------------//
void CArrayCtrl::HorzScroll(UINT nSBCode)
{
	switch( nSBCode )
	{
	case SB_LEFT:
	case SB_RIGHT:
	case SB_PAGEUP: 
	case SB_PAGEDOWN: 
	case SB_LINEUP: 
	case SB_LINEDOWN: 
		OnHScroll(nSBCode, 0, NULL);
		break;
	}
}

//----------------------------------------------------------------------------------//
// Set horizontal scroll at specific position                                       //
//----------------------------------------------------------------------------------//
void CArrayCtrl::HorzScroll(UINT nSBCode, UINT nPos)
{
	UINT		i;

	switch( nSBCode )
	{
	case SB_PAGEUP: 
	case SB_PAGEDOWN: 
	case SB_LINEUP: 
	case SB_LINEDOWN: 
		for(i=0; i<nPos; i++) OnHScroll(nSBCode, 0, NULL);
		break;
	case SB_THUMBPOSITION:
		OnHScroll(SB_THUMBTRACK, nPos, NULL);
	}
}

//----------------------------------------------------------------------------------//
// Set scroll line and page amount                                                  //
//----------------------------------------------------------------------------------//
void CArrayCtrl::SetScrollSize(int nScrollVersus, int nScrollObj, int nSize)
{
	switch( nScrollVersus )
	{
	case SB_VERT:
		switch( nScrollObj )
		{
		case ACSO_LINE:
			if( (nSize < 0) || (nSize >= m_nVertPageSize) ) break;
			m_nVertLineSize = nSize;
			break;
		case ACSO_PAGE:
			if( (nSize < 0) || (nSize >= m_nVertMax ) ) break;
			m_nVertPageSize = nSize;
			break;
		}
		break;
	case SB_HORZ:
		switch( nScrollObj )
		{
		case ACSO_LINE:
			if( (nSize < 0) || (nSize >= m_nHorzPageSize) ) break;
			m_nHorzLineSize = nSize;
			break;
		case ACSO_PAGE:
			if( (nSize < 0) || (nSize >= m_nHorzMax ) ) break;
			m_nHorzPageSize = nSize;
			break;
		}
		break;
	}
}

//----------------------------------------------------------------------------------//
// Get scroll line and page amount                                                  //
//----------------------------------------------------------------------------------//
int CArrayCtrl::GetScrollSize(int nScrollVersus, int nScrollObj)
{
	switch( nScrollVersus )
	{
	case SB_VERT:
		switch( nScrollObj )
		{
		case ACSO_LINE: return (m_nVertLineSize? m_nVertLineSize: m_nItemH);
		case ACSO_PAGE: return (m_nVertPageSize? m_nVertPageSize: m_nHeight);
		}
		break;
	case SB_HORZ:
		switch( nScrollObj )
		{
		case ACSO_LINE: return (m_nHorzLineSize? m_nHorzLineSize: m_nItemW);
		case ACSO_PAGE: return (m_nHorzPageSize? m_nHorzPageSize: m_nWidth);
		}
		break;
	}
	return 0;
}

//----------------------------------------------------------------------------------//
// Ensure item visibility                                                           //
//----------------------------------------------------------------------------------//
void CArrayCtrl::EnsureVisible(int nItem)
{
	int		nItemPosX, nItemPosY;

	if( IsOutOfBound(nItem) ) return;

	nItemPosX = (GetColumnIndex(nItem) + m_nGrid)*m_nItemW;
	nItemPosY = (GetRowIndex(nItem) + m_nGrid)*m_nItemH;

	OnVScroll(SB_THUMBTRACK, nItemPosY, NULL);
	OnHScroll(SB_THUMBTRACK, nItemPosX, NULL);
}

//-------------------------------------------------------------------------//
// Select an item (like left button click but without notification)        //
//-------------------------------------------------------------------------//
void CArrayCtrl::SelectItem(int nItem)
{
	int				nOldSelItem;
	ACITEMACTIVATE	acia;

	// if no items, no action
	if( !m_nItemsCount || IsOutOfBound(nItem) || (nItem == m_nSelItem) ) return;

	// save old selected item
	nOldSelItem = m_nSelItem;
	// make new item selected
	m_nSelItem = nItem;
	// redraw this items
	VdcRedraw(nOldSelItem, m_nSelItem);
}

//-------------------------------------------------------------------------//
// Activate an item (like double clicked)                                  //
//-------------------------------------------------------------------------//
void CArrayCtrl::ActivateItem(int nItem)
{
	int				nOldSelItem;
	CPoint			point(0,0);
	ACITEMACTIVATE	acia;

	// if no items, no action
	if( !m_nItemsCount ) return;
	if( IsOutOfBound(nItem) ) return;
	if( nItem != m_nSelItem )
	{
		// save old selected item
		nOldSelItem = m_nSelItem;
		// make new item selected
		m_nSelItem = nItem;
		// redraw this items
		VdcRedraw(nOldSelItem, m_nSelItem);
	}

	// Prepare notification message structure
	ZeroMemory(&acia, sizeof(ACITEMACTIVATE));
	acia.hdr.hwndFrom	= m_hWnd;
	acia.hdr.idFrom		= m_nID;
	acia.hdr.code		= ACN_DBCLICK;
	acia.nItem			= m_nSelItem;
	acia.dwState		= ACIS_SELECTED;
	acia.ptAction		= point;
	acia.nRow			= GetRowIndex();
	acia.nColumn		= GetColumnIndex();
	acia.nKeyFlags		= 0;
	acia.dwParam		= GetItemData(m_nSelItem);
	// notify to parent window
	::SendMessage(::GetParent(m_hWnd), WM_NOTIFY, m_nID, (LPARAM)&acia);
}

/////////////////////////////////////////////////////////////////////////////
// CArrayCtrl private methods

//-------------------------------------------------------------------//
// Allocate a new data items vector                                  //
//-------------------------------------------------------------------//
void CArrayCtrl::AllocateVector()
{
	int		i;

	if( m_dwStyle & ACS_USERDATA )
	{
		m_lpItemVect = new LPARAM[m_nItemsCount];
		ASSERT(m_lpItemVect);
		for(i=0; i<m_nItemsCount; i++) m_lpItemVect[i] = (LPARAM)0;
	}
}

//-------------------------------------------------------------------//
// Create an OffScreen DC (memory dc) and related objects            //
//-------------------------------------------------------------------//
void CArrayCtrl::VdcCreate()
{
	int			nThick;
	CRect		rcCtrl;

	// get control's client area size
	GetClientRect(&rcCtrl);
	m_nWidth = rcCtrl.Width();
	m_nHeight = rcCtrl.Height();
	
	// Create primary offscreen DC
	m_pVirtDC = new CMemDC(m_nWidth, m_nHeight, m_crCtrlBg);

	// Create item draw offscreen DC.
	// This DC will be passed to parent window for items paint
	// and then blitted to virtual DC. This is done for safety's sake
	// and also because user will operate with real coordinate (0,0,width,height)
	m_pDrawDC = new CMemDC(m_nItemW, m_nItemH, m_crCtrlBg);

	// Create frame offscreen DC.
	// This DC will be used if grid are required
	if( (m_dwStyle & ACS_GRIDLINES) )
	{
		nThick = m_nThickness * 2;
		if( m_nThickness ) m_pFrameDC = new CMemDC(m_nItemW + nThick, m_nItemH + nThick, m_crGrid);
	}
	VdcUpdate();
}

//-------------------------------------------------------------------//
// Force control redraw unless NOREDRAW was specified                //
//-------------------------------------------------------------------//
void CArrayCtrl::VdcInvalidate()
{
	if( m_dwStyle & ACS_NOREDRAW ) return;
	InvalidateRect(NULL, FALSE);
	UpdateWindow();
}

//-------------------------------------------------------------------//
// Group frequently calling functions into one update function       //
//-------------------------------------------------------------------//
void CArrayCtrl::VdcUpdate()
{
	if( m_dwStyle & ACS_NOREDRAW ) return;
	VdcSetDimensions();
	VdcSetScroll();
	VdcDraw();
}

//-------------------------------------------------------------------//
// Compute rows and columns occurrence                               //
//-------------------------------------------------------------------//
void CArrayCtrl::VdcSetDimensions()
{
	if( !m_nItemsCount ) return;
	// if columns are fixed, compute the number of rows
	if( m_dwStyle & ACS_FIXEDCOL )
	{
		m_nRows = m_nItemsCount/m_nColumns + (m_nItemsCount%m_nColumns? 1: 0);
		return;
	}
	// if rows are fixed, compute the number of columns
	if( m_dwStyle & ACS_FIXEDROW )
	{
		m_nColumns = m_nItemsCount/m_nRows + (m_nItemsCount%m_nRows? 1: 0);
		return;
	}

	// else, columns and rows are'nt fixed, 
	// hence we obtain their numbers from control's width and items count;
	// we assumed that columns must be fitted on control's width
	m_nColumns = m_nWidth/(m_nItemW + m_nGrid);
	if( m_nColumns == 0 ) m_nColumns = 1;
	m_nRows = m_nItemsCount/m_nColumns + (m_nItemsCount%m_nColumns? 1: 0);
}

//-------------------------------------------------------------------//
// Set informatiuon of scrolling bars                                //
//-------------------------------------------------------------------//
void CArrayCtrl::VdcSetScroll()
{
	SCROLLINFO	si;

	// set scroll extension
	m_nHorzMax = m_nColumns * (m_nItemW + m_nGrid) + m_nGrid;
	m_nVertMax = m_nRows * (m_nItemH + m_nGrid) + m_nGrid;

	if( m_nVertMax < m_nHeight ) m_nVertPos = 0;
	else
	{
		while( m_nVertPos > m_nVertMax ) m_nVertPos -= m_nVertLineSize;
		if( m_nVertPos < 0 ) m_nVertPos = 0;
	}
	if( m_nHorzMax < m_nWidth ) m_nHorzPos = 0;
	else
	{
		while( m_nHorzPos > m_nHorzMax ) m_nHorzPos -= m_nHorzLineSize;
		if( m_nHorzPos < 0 ) m_nHorzPos = 0;
	}

	// set vertical scrolling information 
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
	si.nPage = m_nHeight;
	si.nMin = 0;
	si.nMax = m_nVertMax;
	si.nPos = m_nVertPos;
	SetScrollInfo(SB_VERT, &si, TRUE);

	// set horizontal scrolling information 
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
	si.nPage = m_nWidth;
	si.nMin = 0;
	si.nMax = m_nHorzMax;
	si.nPos = m_nHorzPos;
	SetScrollInfo(SB_HORZ, &si, TRUE);
}

//-------------------------------------------------------------------//
// Delete the VirtualDC and related objects                          //
//-------------------------------------------------------------------//
void CArrayCtrl::VdcDelete()
{
	if( m_pFrameDC ) delete m_pFrameDC;
	delete m_pDrawDC;
	delete m_pVirtDC;
}

//-------------------------------------------------------------------//
// Paint old and new selection items on VDC                          //
//-------------------------------------------------------------------//
void CArrayCtrl::VdcRedraw(int nOldItem, int nNewItem)
{
	CRect		rcView;

	ASSERT(::IsWindow(m_hWnd));
	if( m_bDrawable == FALSE ) return;
	// if old item and new item are the same, don't paint
	if( nOldItem == nNewItem ) return;
	rcView.SetRect(m_nHorzPos, m_nVertPos, m_nHorzPos + m_nWidth, m_nVertPos + m_nHeight);
	VdcItemDraw(&rcView, nOldItem);
	VdcItemDraw(&rcView, nNewItem);
	VdcInvalidate();
}

//-------------------------------------------------------------------//
// Draw whole view                                                   //
//-------------------------------------------------------------------//
void CArrayCtrl::VdcDraw()
{
	int			i;
	CRect		rcView;

	ASSERT(::IsWindow(m_hWnd));
	m_pVirtDC->Erase();
	if( m_bDrawable == TRUE )
	{
		rcView.SetRect(m_nHorzPos, m_nVertPos, m_nHorzPos + m_nWidth, m_nVertPos + m_nHeight);
		for(i=0; i<m_nItemsCount; i++) VdcItemDraw(&rcView, i);
	}
	VdcInvalidate();
}

//-------------------------------------------------------------------//
// Draw a single item on VDC                                         //
//-------------------------------------------------------------------//
void CArrayCtrl::VdcItemDraw(CRect* prcView, int nItem)
{
	CMemDC*		pSrcDC;
	int			x, y;
	int			nRow, nCol, nGbord;
	CRect		rcResult, rcItem;
	ACITEMINFO	mcii;

	if( nItem < 0 ) return;

	nCol = GetColumnIndex(nItem);
	nRow = GetRowIndex(nItem);
	nGbord = m_nGrid * 2;

	// set the item rectangle
	x = nCol * (m_nItemW + m_nGrid);
	y = nRow * (m_nItemH + m_nGrid);
	rcItem.SetRect(x, y, x + m_nItemW + nGbord, y + m_nItemH + nGbord);

	// intersect view and item rectangles
	// if no intersection (result is 0) don't need to be draw
	if( rcResult.IntersectRect(prcView, &rcItem) == 0 ) return;

	// item lie into view (totally or partially), then draw it

	m_pDrawDC->Erase();

	// Prepare notification message structure
	ZeroMemory(&mcii, sizeof(ACITEMINFO));
	mcii.hdr.hwndFrom	= m_hWnd;
	mcii.hdr.idFrom		= m_nID;
	mcii.hdr.code		= ACN_DRAWITEM;
	mcii.pControl		= this;
	mcii.pDC			= m_pDrawDC->GetDC();
	mcii.nWidth			= m_nItemW;
	mcii.nHeight		= m_nItemH;
	mcii.nItem			= nItem;
	mcii.nRow			= nRow;
	mcii.nColumn		= nCol;
	mcii.dwState		= (nItem==m_nSelItem? ACIS_SELECTED: ACIS_NORMAL) | ACIS_VISIBLE;
	mcii.dwParam		= GetItemData(nItem);
	::SendMessage(::GetParent(m_hWnd), WM_NOTIFY, m_nID, (LPARAM)&mcii);

	// blit intersection rectangle from temp frame DC to virtual DC
	pSrcDC = m_pDrawDC;
	if( m_nGrid )
	{
		pSrcDC = m_pFrameDC;
		pSrcDC->Copy(m_nGrid, m_nGrid, m_nItemW, m_nItemH, m_pDrawDC, 0, 0);
	}
	m_pVirtDC->Copy(rcResult.left - m_nHorzPos, rcResult.top - m_nVertPos, rcResult.Width(), rcResult.Height(), 
						pSrcDC, rcResult.left - rcItem.left, rcResult.top - rcItem.top);
}

//-------------------------------------------------------------------//
// Check if control can or cannot draw its items                     //
//-------------------------------------------------------------------//
void CArrayCtrl::VdcSetDrawable()
{
	// if any of control's properties are null, others quantities are really null
	// hence drawing is not possible
	m_bDrawable = FALSE;
	if( !m_nItemsCount || !m_nItemW || !m_nItemH || !m_nWidth || !m_nHeight ) return;
	m_bDrawable = TRUE;
}

//-------------------------------------------------------------------//
// Copy vectors using bounds                                         //
//-------------------------------------------------------------------//
void BoundsCopy(LPARAM* pDst, int nDstBegin, LPARAM* pSrc, int nSrcBegin, int nSrcEnd)
{
	int		i, k;

	for(i=nSrcBegin,k=0; i<nSrcEnd; i++,k++) pDst[nDstBegin+k] = pSrc[i];
}

