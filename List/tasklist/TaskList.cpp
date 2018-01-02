//*******************************************************************
//* TASKLIST.CPP - CTaskList implementation                         *
//*                                                                 *
//*	Implements a priority based drop down task list using an	    *
//* ownerdrawn CComboBox. The listbox is sorted by priority level   *
//*														            *
//* October 06 / 2002										        *
//*														            *
//* Copyright PCSpectra 2002 (Free for any purpose, except to sell) *
//* Website: www.pcspectra.ca                                       *
//*														            *
//* Public methods:                                                 *
//* ===============                                                 *
//* AddTask() - Adds a task with a specified priority level to list *
//* GetTask() - Returns the indexed task text comment use           *
//*             GetPriority() to return the priority level          *
//*                                                                 *
//* SetCheck() - Set currently indexed item check state             *
//* GetCheck() - Returns check state of item at index               *
//*                                                                 *
//* SetColors() - Sets all priority colors                          *
//* GetColorLevelX() - Returns color for X priority level           *
//*                                                                 *
//* SetPriority() - Changes an items priority and "should" resort   *
//* GetPriority() - Returns an items current priority level         *
//*                                                                 *
//*                                                                 *
//* Notes:                                                          *
//* ======															*
//*	None   														    *
//*                                                                 *
//* History:														*
//*	========														*
//* Month dd/yyyy - None so far                             		*
//*******************************************************************

#include "stdafx.h"
#include "TaskList.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Global variable
// Namespace???
WNDPROC oldWndProc = NULL;

// Object construction

CTaskList::CTaskList()
{
	// Initialize priority colors with defaults
	m_clrLevel1 = RGB(000,128,000); // Green
	m_clrLevel2 = RGB(255,128,000); // Orange
	m_clrLevel3 = RGB(255,000,000); // Red

	m_hListBox = NULL; // No handle yet
}					 

// Control initialization

void CTaskList::PreSubclassWindow() 
{
	SetItemHeight(-1, 16);
	CComboBox::PreSubclassWindow();
}

BEGIN_MESSAGE_MAP(CTaskList, CComboBox)
	//{{AFX_MSG_MAP(CTaskList)
	ON_CONTROL_REFLECT(CBN_DROPDOWN, OnDropdown)
	ON_MESSAGE(WM_CTLCOLORLISTBOX, OnCtlColorListBox)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Control content management

void CTaskList::AddTask(UINT nLevel, CString strComment)
{
	CString temp;
	
	ASSERT((nLevel>0 && nLevel<4)); // Priority levels must be within 1 and 3

	// Determine level of priority
	if(nLevel==1) temp="c";
	if(nLevel==2) temp="b";
	if(nLevel==3) temp="a";
	
	temp += strComment; // Append comment onto priority level

	AddString(temp);
}

// Return task comment string

CString CTaskList::GetTask(UINT nIndex) const
{
	CString buff;
	
	GetLBText(nIndex, buff);
	
	return buff.Mid(1);
}

// Change item priority

void CTaskList::SetPriority(UINT nIndex, UINT nLevel)
{
	// Copy index items data into temp variables
	DWORD temp = GetItemData(nIndex);
		
	CString buff;
	GetLBText(nIndex, buff);

	// Remove old item from list
	DeleteString(nIndex);

	// Restore old item with changed priority
	SetItemData(nIndex, temp);
		
	// Determine which priority new item has
	if(nLevel==1) buff.SetAt(0, 'c');
	if(nLevel==2) buff.SetAt(0, 'b');
	if(nLevel==3) buff.SetAt(0, 'a');

	// Insert new item
	InsertString(nIndex, buff);
}

// Get an items current priority

UINT CTaskList::GetPriority(UINT nIndex) const
{ 
	CString buff;
	GetLBText(nIndex, buff);

	UINT nLevel = 0;

	switch(buff.GetAt(1)){
		case 'a': nLevel = 3; break;
		case 'b': nLevel = 2; break;
		case 'c': nLevel = 1; break;
	}

	return nLevel;
}


// Control drawing

void CTaskList::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	// Initialize some variables required for drawing
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	CRect rect(lpDIS->rcItem);

	int nIndex = lpDIS->itemID; // -1 = no item selected

	// No item is selected so don't draw inside combobox control
	if(nIndex<0) return;

	UINT nLen = GetLBTextLen(nIndex);

	// Allocate temp buffer to hold string and clear to zero
	LPSTR temp = new char[nLen+1];
	memset(temp, 0, nLen+1);
	
	// Extract string from listbox and store in temp buffer
	GetLBText(nIndex, temp);							   	

	// Copy temp buffer into CString for easier handling
	CString buff(temp);

	// Initialize DC
	pDC->SetBkMode(TRANSPARENT);	 
	
	// Construct bitmap object
	CBitmap bit;
	
	// Determine which bitmap to load from resources
	if(GetCheck(nIndex))
		bit.LoadBitmap(IDB_CHECKED);		
	else
		bit.LoadBitmap(IDB_UNCHECK);		
	
	// Create a memory DC thats compatible with current DC
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	// Select bitmap into memory DC
	// Store current DC object and restore later to avoid leaks
	CBitmap* pTempBit = memDC.SelectObject(&bit);			
	
	// Bit blit the bitmap onto screen
	pDC->BitBlt(rect.left, rect.top, 16, 16, &memDC, 0, 0, SRCCOPY);

	// Restore bitmap object to avoid leaks
	memDC.SelectObject(pTempBit);

	// Adjust rectangle for priority color code 
	rect.left+=18;

	CRect rcColor(rect); // Used to fill priority color code

	CSize size = pDC->GetTextExtent("Code");

	// Color rectangle is width of text above
	rcColor.right=rcColor.left+size.cx; 

	// Re-adjust item rectangle	add padding
	rect.left=rcColor.right+4;
	
	// Draw the color code based on priority level
	switch(buff.GetAt(0)){
		case 'a': // High
			pDC->SetTextColor(m_clrLevel3);
			pDC->DrawText("Code", rcColor, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
			break;
		case 'b': // Urgent
			pDC->SetTextColor(m_clrLevel2);
			pDC->DrawText("Code", rcColor, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
			break;
		case 'c': // Normal
			pDC->SetTextColor(m_clrLevel1);
			pDC->DrawText("Code", rcColor, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
			break;
	}

	// Draw the item in normal state
	pDC->SetTextColor(RGB(0,0,0));
	// Padd text ONLY!!!
	rect.DeflateRect(2,0,2,0);
	pDC->DrawText(buff.Mid(1), rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	rect.InflateRect(2,0,2,0); // Restore rectangle before item selection


	// Variables required for drawing item state properly
	UINT nState  = lpDIS->itemState;
	UINT nAction = lpDIS->itemAction;

	/*** Determine how to draw the current item ***/
	
	// The following code was borrowed (and used as a template) from a codeproject article 
	// Control Subclassing
	// Posted 8 Aug 2001
	// By Eric Sanchez 			

	// Used when an item needs to be selected
	if((nState & ODS_SELECTED) && (nAction & ODA_SELECT))
	{
		// Draws the highlighted rect	
		pDC->FillSolidRect(rect, GetSysColor(COLOR_HIGHLIGHT));
		pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
		rect.DeflateRect(2,0,2,0);
		pDC->DrawText(buff.Mid(1), rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	}
	
	// The item needs to be deselected
	if(!(nState & ODS_SELECTED) && (nAction & ODA_SELECT))
	{
		//We draw the background color	
		pDC->FillSolidRect(rect, GetSysColor(COLOR_WINDOW));
		pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
		rect.DeflateRect(2,0,2,0);
		pDC->DrawText(buff.Mid(1), rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	}

	// Item has the focus
	if((nAction & ODA_FOCUS) && (nState & ODS_FOCUS) && (nState & ODS_SELECTED))
	{
		// Item has the focus,
		pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
		pDC->FillSolidRect(rect, GetSysColor(COLOR_HIGHLIGHT));
		pDC->DrawFocusRect(rect);
		rect.DeflateRect(2,0,2,0);
		pDC->DrawText(buff.Mid(1), rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	}

	// Focus needs to be removed
	if((nAction & ODA_FOCUS) && !(nState & ODS_FOCUS) && (nState & ODS_SELECTED))
	{							 		
		pDC->FillSolidRect(rect, GetSysColor(COLOR_WINDOW));
		pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
		rect.DeflateRect(2,0,2,0);
		pDC->DrawText(buff.Mid(1), rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	}
	
	// Free up memory used by temp buffer
	delete[] temp;
}

// Helper functions

// The following code was borrowed from a codeproject article
// Setting the width of the dropdown list
// Posted 26 Mar 2000
// By Chris Maunder 
   
void CTaskList::RecalcDropWidth()
{
    // Reset the dropped width
    int nNumEntries = GetCount();
    int nWidth = 0;
    CString str;

    CClientDC dc(this);
    int nSave = dc.SaveDC();
    dc.SelectObject(GetFont());

	CSize size = dc.GetTextExtent("Code");
	
	int nIconWidth = 18+size.cx+4; // Added space for icons and color code bar 
								   // Item padding 2 pixels each side is also included

    int nScrollWidth = ::GetSystemMetrics(SM_CXVSCROLL)+nIconWidth;
	
    for (int i = 0; i < nNumEntries; i++)
    {
        GetLBText(i, str);
        int nLength = dc.GetTextExtent(str).cx + nScrollWidth;
        nWidth = max(nWidth, nLength);
    }
    
    // Add margin space to the calculations
    nWidth += dc.GetTextExtent("0").cx;

    dc.RestoreDC(nSave);
    SetDroppedWidth(nWidth);
}

// Subclass the drop down listbox

// The following code was borrowed from a codeproject article
// CheckComboBox Control
// Posted 25 Nov 1999
// By Magnus Egelberg, Lundalogik 
   
LRESULT CTaskList::OnCtlColorListBox(WPARAM wParam, LPARAM lParam)
{
	// If the listbox hasn't been subclassed yet, do so...
	if (!m_hListBox){
		
		// Copy window handle into temp variable
		HWND hWnd = (HWND)lParam;

		// Determine if window handle is valid 
		// Make sure it's not the combobox handle
		if(IsWindow(hWnd) && hWnd != m_hWnd){
			// Save the listbox handle
			m_hListBox = hWnd;
			
			// Do the subclassing
			oldWndProc = (WNDPROC)GetWindowLong(m_hListBox, GWL_WNDPROC);
			SetWindowLong(m_hListBox, GWL_WNDPROC, (LONG)ComboBoxListBoxProc);
		}
	}

	return DefWindowProc(WM_CTLCOLORLISTBOX, wParam, lParam);
}


LRESULT CTaskList::ComboBoxListBoxProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	// Used to determine whether to hide drop donw listbox or not
	static BOOL bHideList = TRUE;

	switch (nMsg)
	{
		// Check and Un-Check each item state as required
		case WM_LBUTTONDOWN: 
		{
			bHideList = TRUE; // Hide the list by default when mouse is released
							  // This assumes all mouse activity will be over item NOT check marks

			// Extract mouse coordinates from parameters
			CPoint pt(LOWORD(lParam), HIWORD(lParam));
			
			// Attach to CWnd derived control for easier handling
			CListBox* pControl = (CListBox*)CListBox::FromHandle(hWnd);
			ASSERT(pControl); 

			// Get the index of the currently selected item
			UINT nIndex = pControl->GetCurSel();
			
			// Determine if we should check/uncheck current item
			// Icon width = 18 pixels
			if(pt.x <= 18){
				bHideList=FALSE;
				
				// Change the current check state of item
				pControl->SetItemData(nIndex, !pControl->GetItemData(nIndex));
				
				// Trivial refresh
				// Invalidate();

				// Optimized refresh
				CRect rcItem;
				pControl->GetItemRect(nIndex, rcItem);
				pControl->InvalidateRect(rcItem);
			}

			// Break to default handler
			break;
		}
		case WM_LBUTTONUP: 
			if(bHideList)
				return CallWindowProc(oldWndProc, hWnd, nMsg, wParam, lParam);
			else
				return 0; // Ignore default processing 				
	} 

	// Default processing 
	return CallWindowProc(oldWndProc, hWnd, nMsg, wParam, lParam);
}
