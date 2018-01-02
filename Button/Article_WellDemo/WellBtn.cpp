////////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2002, SVizSoft, All rights reserved.
//
// FILE:     CSVizWellCtrl.cpp
//			$Revision: 1.3 $
//			$Date: 2002/11/14 02:43:11 $
//			$Author: tzhu $ of last update
//
// CREATOR:    Tao Zhu
//
// DESCRIPTION
//    Class implementation for class CSVizWellCtrl.
//
/////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "wellbtn.h"
#include "memdc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT WELL_SELCHANGED		= ::RegisterWindowMessage (_T("SVIZ_WELL_SELCHANGE"));
UINT WELL_DROPDOWN			= ::RegisterWindowMessage (_T("SVIZ_WELL_DROPDOWN"));
UINT WELL_CLOSEUP			= ::RegisterWindowMessage (_T("SVIZ_WELL_CLOSEUP"));
UINT WELL_SELENDOK			= ::RegisterWindowMessage (_T("SVIZ_WELL_SELOK"));
UINT WELL_SELENDCANCEL		= ::RegisterWindowMessage (_T("SVIZ_WELL_SELCANCLE"));
UINT CPW_SELCHANGED			= ::RegisterWindowMessage (_T("SVIZ_COLORWELL_SELCHANGE"));

/////////////////////////////////////////////////////////////////////////////
// CSVizWellCtrl

IMPLEMENT_DYNCREATE(CSVizWellCtrl, CButton)

/////////////////////////////////////////////////////////////////////////////
// CSVizWellCtrl
CSVizWellCtrl::CSVizWellCtrl()
{
	m_style				= 0;
	m_count				= 0;
}
 
CSVizWellCtrl::CSVizWellCtrl(DWORD dwStyle)
{
	m_style				= 0;
	m_count				= 0;
	m_style				= dwStyle;
}
 

void CSVizWellCtrl::Initialise()
{
 	m_count				= 0;
    m_nNumWells         = 1;
	m_nNumColumns       = 1;
    m_nNumRows          = 1;
    m_nBoxSize.cx       = 18;
    m_nBoxSize.cy       = 18;
    m_nMargin           = ::GetSystemMetrics(SM_CXEDGE);
    m_nCurrentSel       = INVALID_WELL;
    m_nChosenWellSel    = INVALID_WELL;
    m_pParent           = NULL;
    m_crWell            = m_crInitialWell = 0;
	m_foreColor			= Color(255, 0, 0, 255);
	m_backColor         = Color(255, 0, 255,0);
    // Create the font
    NONCLIENTMETRICS ncm;
    ncm.cbSize = sizeof(NONCLIENTMETRICS);
    VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0));
    m_Font.CreateFontIndirect(&(ncm.lfMessageFont));
}

CSVizWellCtrl::~CSVizWellCtrl()
{
}

BEGIN_MESSAGE_MAP(CSVizWellCtrl, CButton)
    //{{AFX_MSG_MAP(CSVizWellCtrl)
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_KEYDOWN()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////


BOOL CSVizWellCtrl::Create(CPoint p, CWnd* pParentWnd, DWORD dwWinStyle)
{
    ASSERT(pParentWnd && ::IsWindow(pParentWnd->GetSafeHwnd()));
    m_pParent  = pParentWnd;

    // Get the class name and create the window
    CString szClassName = AfxRegisterWndClass(CS_CLASSDC|CS_SAVEBITS|CS_HREDRAW|CS_VREDRAW,
                                              0,
                                              (HBRUSH) (COLOR_BTNFACE+1), 
                                              0);

    if (!CWnd::CreateEx(0, szClassName, _T(""), dwWinStyle, 
                        p.x, p.y, 100, 100, // size updated soon
                        pParentWnd->GetSafeHwnd(), 0, NULL))
        return FALSE;
     
	
    return TRUE;
}

//! Create tooltips for the control
void CSVizWellCtrl::CreateToolTips()
{
    // Create the tool tip
    if (!m_ToolTip.Create(this)) return;

    // Add a tool for each cell
    for (int i = 0; i < m_nNumWells; i++)
    {
        CRect rect;
        if (!GetCellRect(i, rect)) continue;
            m_ToolTip.AddTool(this, GetWellName(i), rect, 1);
    }
}

/** Change the selection.
 *
 * If an arrow key is pressed, change the selection. If escape pressed, cancel the selection and close
 * window, if return or space is pressed, confirm the selection and close the window.
 *
 * @param nChar Char that pressed (VK_DOWN, VK_UP, VK_RIGHT, VK_LEFT, VK_ESCAPE, VK_RETURN, VK_SPACE)
 */
void CSVizWellCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    int row = GetRow(m_nCurrentSel),
        col = GetColumn(m_nCurrentSel);

    if (nChar == VK_DOWN) 
    {
        row++;
        if (GetIndex(row,col) < 0)
        {
			row = col = 0;
        }
		ChangeSelection(GetIndex(row, col));
    }

    if (nChar == VK_UP) 
    {
        if (row > 0) 
			row--;
        else /* row == 0 */
        {
            row = GetRow(m_nNumWells-1); 
            col = GetColumn(m_nNumWells-1); 
        }
        ChangeSelection(GetIndex(row, col));
    }

    if (nChar == VK_RIGHT) 
    {
		if (col < m_nNumColumns-1) 
            col++;
        else 
        { 
            col = 0; 
			row++;
        }

        if (GetIndex(row,col) == INVALID_WELL)
        {
            row = col = 0;
        }

        ChangeSelection(GetIndex(row, col));
    }

    if (nChar == VK_LEFT) 
    {
		if (col > 0) col--;
        else /* col == 0 */
        {
            if (row > 0) { row--; col = m_nNumColumns-1; }
            else 
            {
                row = GetRow(m_nNumWells-1); 
                col = GetColumn(m_nNumWells-1); 
            }
        }
        ChangeSelection(GetIndex(row, col));
    }

    if (nChar == VK_ESCAPE) 
    {
        m_crWell = m_crInitialWell;
        EndSelection(WELL_SELENDCANCEL);
        return;
    }

    if (nChar == VK_RETURN || nChar == VK_SPACE)
    {
        EndSelection(WELL_SELENDOK);
        return;
    }

    CButton::OnKeyDown(nChar, nRepCnt, nFlags);
}


/** Change the selection accoding to the mouse position
 * @param point Position of mouse
 */
void CSVizWellCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
    int nNewSelection = INVALID_WELL;

    // Translate points to be relative raised window edge
    point.x -= m_nMargin;
    point.y -= m_nMargin;

   // Get the row and column
    nNewSelection = GetIndex(point.y / m_nBoxSize.cy, point.x / m_nBoxSize.cx);

    // In range? If not, default and exit
    if (nNewSelection < 0 || nNewSelection >= m_nNumWells)
    {
        CButton::OnMouseMove(nFlags, point);
        return;
    }

    // OK - we have the row and column of the current selection (may be CUSTOM_BOX_VALUE)
    // Has the row/col selection changed? If yes, then redraw old and new cells.
    if (nNewSelection != m_nCurrentSel)
        ChangeSelection(nNewSelection);

    CButton::OnMouseMove(nFlags, point);
}

/** End the selection, when mouse Lbutton is up
 *
 * If mouse is in the control, confirm the selection. if mouse is outside of
 * the well control, cancel the selection.
 * @param point Position of mouse
 */
void CSVizWellCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{    
	
	if (!GetSafeHwnd())
		return;
	

	CButton::OnLButtonUp(nFlags, point);


    DWORD pos = GetMessagePos();
    if (IsPopupWnd())
		point = CPoint(LOWORD(pos), HIWORD(pos));
	else {
		point.x += m_WindowRect.left;
		point.y += m_WindowRect.top;
	}
    if (m_WindowRect.PtInRect(point))
        EndSelection(WELL_SELENDOK);
    else {
		if (IsInPropList()) {
			m_count++;
			if (m_count>1) {
				EndSelection(WELL_SELENDCANCEL);
			}
		}
		else
			EndSelection(WELL_SELENDCANCEL);

	}
	
    	
}

/////////////////////////////////////////////////////////////////////////////
// CSVizWellCtrl implementation

/** Get the index from row and col number
 * @param row Row number
 * @param col Column number
 * @return The index if row and col is in the range of well control, otherwise INVALID_WELL.
 */
int CSVizWellCtrl::GetIndex(int row, int col) const
{ 
    if (row < 0 || col < 0 || row >= m_nNumRows || col >= m_nNumColumns)
        return INVALID_WELL;
    else
    {
        if (row*m_nNumColumns + col >= m_nNumWells)
            return INVALID_WELL;
        else
            return row*m_nNumColumns + col;
    }
}

/** Get the row from Index
 * @param Index Index of well
 * @return The row number coresponding to the well index if index is in the range of well control, otherwise INVALID_WELL.
 */
int CSVizWellCtrl::GetRow(int nIndex) const               
{ 
	if (nIndex < 0 || nIndex >= m_nNumWells)
        return INVALID_WELL;
    else
        return nIndex / m_nNumColumns; 
}

/** Get the coloumn from Index
 * @param Index Index of well
 * @return The coloumn number coresponding to the well index if index is in the range of well control, otherwise INVALID_WELL.
 */
int CSVizWellCtrl::GetColumn(int nIndex) const            
{ 
	if (nIndex < 0 || nIndex >= m_nNumWells)
        return INVALID_WELL;
    else
        return nIndex % m_nNumColumns; 
}

void CSVizWellCtrl::FindCellFromWell(int crWell)
{
    for (int i = 0; i < m_nNumWells; i++)
    {
        if (i == crWell)
        {
            m_nChosenWellSel = i;
            return;
        }
    }

    m_nChosenWellSel = INVALID_WELL;
}

//! Gets the dimensions of the cell given by (row,col)
BOOL CSVizWellCtrl::GetCellRect(int nIndex, const LPRECT& rect)
{

    if (nIndex < 0 || nIndex >= m_nNumWells)
        return FALSE;

    rect->left = GetColumn(nIndex) * m_nBoxSize.cx + m_nMargin;
    rect->top  = GetRow(nIndex) * m_nBoxSize.cy + m_nMargin;

   
	rect->right = rect->left + m_nBoxSize.cx;
    rect->bottom = rect->top + m_nBoxSize.cy;

    return TRUE;
}

/** Set the the appropriate size and position of this window
 *
 * precondition :column nubmer is already defined and well control is created.
 */

void CSVizWellCtrl::SetWindowSize()
{
	ASSERT (m_nNumColumns);
	if (m_nNumColumns ==0) return;

    m_nNumRows = m_nNumWells / m_nNumColumns;
    if (m_nNumWells % m_nNumColumns) m_nNumRows++;

     // Get the current window position, and set the new size
    CRect rect;

	if (IsPopupWnd()){
		GetWindowRect(rect); 
		m_WindowRect.SetRect(rect.left, rect.top, 
							 rect.left + m_nNumColumns*m_nBoxSize.cx + 2*m_nMargin,
							 rect.top  + m_nNumRows*m_nBoxSize.cy + 2*m_nMargin);


	   // Need to check it'll fit on screen: Too far right?
		CSize ScreenSize(::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN));
		if (m_WindowRect.right > ScreenSize.cx)
			m_WindowRect.OffsetRect(-(m_WindowRect.right - ScreenSize.cx), 0);

		// Too far left?
		if (m_WindowRect.left < 0)
			m_WindowRect.OffsetRect( -m_WindowRect.left, 0);

		// Bottom falling out of screen?
		if (m_WindowRect.bottom > ScreenSize.cy)
		{
			if (m_pParent)
				m_pParent->GetWindowRect(m_ParentRect);
			m_WindowRect.OffsetRect(0, -(m_ParentRect.Height() + m_WindowRect.Height()));
		}
	}
	else {
     // Get the current window position, and set the new size
		CRect rect1;
		GetWindowRect(rect);
		GetParent()->GetWindowRect(rect1);
		int x = rect.left - rect1.left;
		int y = rect.top - rect1.top;

		m_WindowRect.SetRect(x,y, 
							 x+m_nNumColumns*m_nBoxSize.cx + 2*m_nMargin,
							  y+ m_nNumRows*m_nBoxSize.cy + 2*m_nMargin);



	}
    // Set the window size and position
    MoveWindow(m_WindowRect, TRUE);
}

/** Invoked when selection changed. 
 * 
 * Redraw the last selected item and newly select item. Send the WELL_SELCHANGEBT message to parent
 * @param nIndex The new selection. 
 */void CSVizWellCtrl::ChangeSelection(int nIndex)
{
    CClientDC dc(this);        // device context for drawing

    if ((m_nCurrentSel >= 0 && m_nCurrentSel < m_nNumWells))
    {
        // Set Current selection as invalid and redraw old selection (this way
        // the old selection will be drawn unselected)
        int OldSel = m_nCurrentSel;
        m_nCurrentSel = INVALID_WELL;
        DrawCell(&dc, OldSel);
    }

    // Set the current selection as row/col and draw (it will be drawn selected)
    m_nCurrentSel = nIndex;
    DrawCell(&dc, m_nCurrentSel);

    // Store the current hatch
    m_crWell = m_nCurrentSel;
	m_pParent->SendMessage(WELL_SELCHANGED, (WPARAM) m_crWell, (LPARAM) GetDlgCtrlID());
}

/** Invoked when selection finished. 
 *  @param nMessage The last message the well ctrl sends to parment. 
 *
 */

void CSVizWellCtrl::EndSelection(UINT nMessage)
{
    ReleaseCapture();

    // If custom text selected, perform a custom hatch selection
    if (nMessage == WELL_SELENDCANCEL)
        m_crWell = m_crInitialWell;

	if (m_pParent)
		m_pParent->SendMessage(nMessage, (WPARAM) m_crWell, (LPARAM) GetDlgCtrlID());

	if (IsPopupWnd()){ 
		DestroyWindow();
		if (IsAutoDelete())
			delete this;

	}
}

/** Draw a single cell
 * @param pDC A pointer to DC to draw
 * @param nIndex The index of cell to draw
 */
void CSVizWellCtrl::DrawCell(CDC* pDC, int nIndex)
{
    CRect rect;
    if (!GetCellRect(nIndex, rect)) return;

	if (GetDrawStyle() == WELL_STYLE_OFFICE){ //office 2000 like style
		pDC->FillSolidRect(rect, RGB(255,255,255));
		if (m_nCurrentSel == nIndex) {
			pDC->FillSolidRect(rect, RGB(50,50,50));
			CRect rect1 = rect;
			rect1.DeflateRect(1,1);
			pDC->FillSolidRect(rect1, RGB(180,180,220));
		}
		else if (m_nChosenWellSel == nIndex){
			pDC->FillSolidRect(rect, RGB(50,50,50));
			CRect rect1 = rect;
			rect1.DeflateRect(1,1);
			pDC->FillSolidRect(rect1, RGB(200,200,240));
		}
	}
	else{ //traditional style
		if (m_nChosenWellSel == nIndex && m_nCurrentSel != nIndex)
			pDC->FillSolidRect(rect, ::GetSysColor(COLOR_3DHILIGHT));
		else
			pDC->FillSolidRect(rect, ::GetSysColor(COLOR_3DFACE));
		if (m_nCurrentSel == nIndex) 
			pDC->DrawEdge(rect, BDR_RAISEDINNER, BF_RECT);
		else if (m_nChosenWellSel == nIndex)
			pDC->DrawEdge(rect, BDR_SUNKENOUTER, BF_RECT);

	}

    rect.DeflateRect(m_nMargin+1, m_nMargin+1);
    // Draw the cell hatch
	DrawCellContent(pDC, nIndex, rect, WELL_STATE_NORMAL);

}

/** Draw a single cell content
 *
 * This is the virtual function that all the classes derived from CSVizWellCtrl have to 
 * implement. It allows customerly draw the item.
 *
 * @param pDC A pointer to DC to draw
 * @param nIndex The index of cell to draw
 * @param rect The rectangle of cell
 * @state state The state of cell. Not used in SViz version 1.0
 */
void CSVizWellCtrl::DrawCellContent(CDC* pDC, int nIndex, CRect rect,BYTE state)
{
	return;
}

void CSVizWellCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	  CDC  *pdrawDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	  CMemDC memDC(pdrawDC);
	  CDC  *pDC = &memDC;
	
	//CDC*    pDC     = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect = lpDrawItemStruct->rcItem;

	//rect.InflateRect(1,1);

	pDC->FillSolidRect(rect, RGB(0, 0, 0 ));
	rect.DeflateRect(1,1);
	pDC->FillSolidRect(rect, ::GetSysColor(COLOR_3DFACE));
    // Draw hatch cells
    for (int i = 0; i < m_nNumWells; i++)
        DrawCell(pDC, i);
	//CButon::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

//! Handle the paint mesasge
void CSVizWellCtrl::OnPaint() 
{

    CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect(rect);

	if (GetDrawStyle() == WELL_STYLE_OFFICE){
		dc.FillSolidRect(rect,RGB(50,50,50));
		rect.DeflateRect(1,1);
		dc.FillSolidRect(rect,RGB(255,255,255));
	}
	else
		dc.DrawEdge(rect, EDGE_RAISED, BF_RECT);

    for (int i = 0; i < m_nNumWells; i++)
        DrawCell(&dc, i);
    
	CButton::OnPaint();
}
/** Auto Deletion itself when windows is destoyed.
 *
 */
void CSVizWellCtrl::OnNcDestroy() 
{
    CButton::OnNcDestroy();
	if (IsAutoDelete())
		delete this;
}
//!Destroy the Well Ctrl when activate other application.

void CSVizWellCtrl::OnActivateApp(BOOL bActive, HTASK hTask) 
{
	CButton::OnActivateApp(bActive, hTask);

	if (!GetSafeHwnd())
		return;

	// If Deactivating App, cancel this selection
	if (!bActive)
		 EndSelection(WELL_SELENDCANCEL);
}

void CSVizWellCtrl::SetAutoDelete(bool b){
	if (b)
		m_style = m_style|WELL_STYLE_AUTODELETE;
	else
		m_style = m_style&(0xFFFFFFFF^WELL_STYLE_AUTODELETE);
}

void CSVizWellCtrl::SetPopupWnd(bool b){
	if (b)
		m_style = m_style|WELL_STYLE_POPUP;
	else
		m_style = m_style&(0xFFFFFFFF^WELL_STYLE_POPUP);
}
void CSVizWellCtrl::SetInPropList   (bool b){
	if (b)
		m_style = m_style|WELL_STYLE_INPROPLIST;
	else
		m_style = m_style&(0xFFFFFFFF^WELL_STYLE_INPROPLIST);
}
// For tooltips
BOOL CSVizWellCtrl::PreTranslateMessage(MSG* pMsg) 
{
    if (m_ToolTip.GetSafeHwnd())
		m_ToolTip.RelayEvent(pMsg);

    return CButton::PreTranslateMessage(pMsg);
}

int CSVizWellCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CButton::OnCreate(lpCreateStruct) == -1)
        return -1;
    
	if (lpCreateStruct->style & WS_POPUP)
		SetPopupWnd(TRUE); //It is a popup windows.
	
    // Set the window size
    SetWindowSize();

    // Create the tooltips
    CreateToolTips();
	
    // Capture all mouse events for the life of this window if it is a popup
    if(IsPopupWnd())
		SetCapture();
    
	return 0;
}
