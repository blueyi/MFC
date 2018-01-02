// MacCheckBox.cpp : implementation file
//
// CMacCheckBox class, version 1.0
//
//	Copyright (c) 1999 Paul Meidinger (pmmeidinger@yahoo.com)
//
//
// Feel free to modifiy and/or distribute this file, but
// do not remove this header.
//
// I would appreciate a notification of any bugs discovered or 
// improvements that could be made.
//
// This file is provided "as is" with no expressed or implied warranty.
//


#include "stdafx.h"
#include "MacCheckBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMacCheckBox

//-------------------------------------------------------------------
//
CMacCheckBox::CMacCheckBox()
//
// Return Value:	None.
//
// Parameters	:	None.
//
// Remarks		:	Standard constructor.
//
{
	m_bChecked = FALSE;
	m_bMouseDown = FALSE;
	GetColors();
}	// CMacCheckBox

//-------------------------------------------------------------------
//
CMacCheckBox::~CMacCheckBox()
//
// Return Value:	None.
//
// Parameters	:	None.
//
// Remarks		:	Destructor. Does nothing.
//
{
}	// ~CMacCheckBox


BEGIN_MESSAGE_MAP(CMacCheckBox, CButton)
	//{{AFX_MSG_MAP(CMacCheckBox)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMacCheckBox message handlers

//-------------------------------------------------------------------
//
void CMacCheckBox::PreSubclassWindow() 
//
// Return Value:	None.
//
// Parameters	:	None.
//
// Remarks		:	This member function is called by the framework to 
//						allow other necessary subclassing to occur before the 
//						window is subclassed. Adds the BS_OWNERDRAW style.
//
{
	CButton::PreSubclassWindow();
	ModifyStyle(0, BS_OWNERDRAW);
}	// PreSubclassWindow

//-------------------------------------------------------------------
//
void CMacCheckBox::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
//
// Return Value:	None.
//
// Parameters	:	lpDIS - A long pointer to a DRAWITEMSTRUCT structure.
//
// Remarks		:	Called by the framework when a visual aspect of an 
//						owner-drawn button has changed.
//
{
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	CRect rectItem(lpDIS->rcItem);
	CRect rectClip;
	pDC->GetClipBox(rectClip);

  	UINT nState = lpDIS->itemState;
	UINT nStyle = GetStyle();
	BOOL bDisabled = BOOL(nState & ODS_DISABLED);

	// Determine the rect for the check mark.
	CRect rectCheck;
	int nHeight = 12;
	int nAdjust = (rectItem.Height() - nHeight) >> 1;
	if (nStyle & BS_LEFTTEXT)
		rectCheck.SetRect(rectItem.right - nHeight, rectItem.top + nAdjust, 
								rectItem.right, rectItem.top + nHeight + nAdjust);
	else
		rectCheck.SetRect(rectItem.left, rectItem.top + nAdjust, 
								rectItem.left + nHeight, rectItem.top + nHeight + nAdjust);

	int nSaveDC = pDC->SaveDC();

	pDC->SelectStockObject(NULL_BRUSH);
	pDC->FillSolidRect(rectClip, m_crFace);

	DrawCheckMark(pDC, rectCheck, nStyle, nState);

	// Don't draw more than is necessary.
	if (rectClip != rectItem)
		return;

	// Determine the rect for the text.
	if (nStyle & BS_LEFTTEXT)
		rectItem.left = lpDIS->rcItem.left + 2;
	else
		rectItem.left += nHeight + 5;
	rectItem.top++;

	CString sText;
	GetWindowText(sText);
	pDC->SetBkMode(TRANSPARENT);

	CSize size = pDC->GetTextExtent(sText);
  	rectItem.right = rectItem.left + size.cx + (nStyle & BS_LEFTTEXT ? 2 : -5);
	rectItem.top = (rectItem.Height() - size.cy) >> 1;
	rectItem.bottom = rectItem.top + size.cy;

	// Draw the text.
	if (bDisabled)
		pDC->DrawState(rectItem.TopLeft(), rectItem.Size(), sText, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
	else
		pDC->DrawText(sText, rectItem, DT_LEFT);

	// Draw the focus rect.
	rectItem.InflateRect(1, 1, 0, 2);

	if (nState & ODS_FOCUS)
		pDC->DrawFocusRect(rectItem); 

	pDC->RestoreDC(nSaveDC);
}	// DrawItem

//-------------------------------------------------------------------
//
void CMacCheckBox::DrawCheckMark(CDC *pDC, CRect rect, UINT nStyle, UINT nState)
//
// Return Value:	None.
//
// Parameters	:	pDC - A pointer to the DC to draw on.
//						rect - The check mark's rectangle.
//						nStyle - The button's style.
//						nState - The button's state.
//
// Remarks		:	Draws the check mark.
//
{
	CBrush br(nState & ODS_DISABLED ? m_crShadow : m_crDkShadow);
	pDC->FrameRect(rect, &br);
	rect.DeflateRect(1, 1);

	// Draw a 3D rect if the button's not flat.
	if (!(nStyle & BS_FLAT))
	{
		if (m_bMouseDown)
			pDC->Draw3dRect(rect, m_crLiteShadow, m_crHilight);
		else
			pDC->Draw3dRect(rect, m_crHilight, m_crLiteShadow);

		pDC->SetPixel(CPoint(rect.right - 1, rect.top), m_crFace);
		pDC->SetPixel(CPoint(rect.left, rect.bottom - 1), m_crFace);
	}

	// Draw the check mark.
	if (m_bChecked)
	{
		CPen penDkShadow(PS_SOLID, 1, (nState & ODS_DISABLED ? m_crShadow: m_crDkShadow));
		CPen *pOldPen = (CPen *)pDC->SelectObject(&penDkShadow);
		pDC->MoveTo(rect.left + 1, rect.top + 4);
		pDC->LineTo(rect.left + 4, rect.top + 7);
		pDC->LineTo(rect.left + 12,rect.top - 1);

		pDC->MoveTo(rect.left + 2, rect.top + 4);
		pDC->LineTo(rect.left + 4, rect.top + 6);
		pDC->LineTo(rect.left + 10, rect.top + 0);

		// If not flat, draw the check mark's shadow
		if (!(nStyle & BS_FLAT) && !(nState & ODS_DISABLED))
		{
			CPen pen3DShadow(PS_SOLID, 1, m_crShadow);
			pDC->SelectObject(&pen3DShadow);
			pDC->MoveTo(rect.left + 4, rect.top + 8);
			pDC->LineTo(rect.left + 9, rect.top + 3);
			pDC->LineTo(rect.left + 9, rect.top + 5);

			CPen penLiteShadow(PS_SOLID, 1, m_crLiteShadow);
			pDC->SelectObject(&penLiteShadow);
			pDC->MoveTo(rect.left + 2, rect.top + 6);
			pDC->LineTo(rect.left + 4, rect.top + 8);
			pDC->MoveTo(rect.left + 5, rect.top + 8);
			pDC->LineTo(rect.left + 9, rect.top + 4);

			pDC->SetPixel(rect.left + 11, rect.top + 1, m_crShadow);
			pDC->SetPixel(rect.left + 12, rect.top + 1, m_crLiteShadow);
			pDC->SetPixel(rect.left + 11, rect.top + 2, m_crLiteShadow);
		}

		pDC->SelectObject(pOldPen);
	}	// if checked
}	// DrawCheck

//-------------------------------------------------------------------
//
void CMacCheckBox::OnLButtonUp(UINT /*nFlags*/, CPoint point) 
//
// Return Value:	None.
//
// Parameters	:	nFlags - Indicates whether various virtual keys are down. 
//						point - Specifies the x- and y-coordinate of the cursor. 
//							These coordinates are always relative to the upper-left 
//							corner of the window.
//
// Remarks		:	The framework calls this member function when the user 
//						releases the left mouse button. Checks to see if the mouse
//						was released over the button. If so, check it.
//
{
	ReleaseCapture();

	if (!(GetStyle() & BS_AUTOCHECKBOX))
		return;

	CRect rect;
	GetClientRect(rect);

	if (rect.PtInRect(point))
		m_bChecked = !m_bChecked;

	m_bMouseDown = FALSE;

	RedrawCheck();
}	// OnLButtonUp

//-------------------------------------------------------------------
//
void CMacCheckBox::OnLButtonDown(UINT /*nFlags*/, CPoint /*point*/) 
//
// Return Value:	None.
//
// Parameters	:	nFlags - Indicates whether various virtual keys are down. 
//						point - Specifies the x- and y-coordinate of the cursor. 
//							These coordinates are always relative to the upper-left 
//							corner of the window.
//
// Remarks		:	The framework calls this member function when the user 
//						presses the left mouse button. Sets focus to this button,
//						captures the mouse, and redraws the check.
//
{
	m_bMouseDown = TRUE;
	SetFocus();
	SetCapture();
	RedrawCheck();
}	// OnLButtonDown 

//-------------------------------------------------------------------
//
void CMacCheckBox::OnLButtonDblClk(UINT /*nFlags*/, CPoint point) 
//
// Return Value:	None.
//
// Parameters	:	nFlags - Indicates whether various virtual keys are down.
//						point - Specifies the x- and y-coordinate of the cursor. 
//							These coordinates are always relative to the upper-left
//							 corner of the window.
//
// Remarks		:	The framework calls this member function when the user 
//						double-clicks the left mouse button. The WM_LBUTTONDOWN
//						message is sent to simulate a single click.
//
{
	SendMessage(WM_LBUTTONDOWN, 0, MAKELPARAM(point.x, point.y));	
}	// OnLButtonDblClk

//-------------------------------------------------------------------
//
void CMacCheckBox::OnMouseMove(UINT /*nFlags*/, CPoint point) 
//
// Return Value:	None.
//
// Parameters	:	nFlags - Indicates whether various virtual keys are down. 
//						point - Specifies the x- and y-coordinate of the cursor. 
//							These coordinates are always relative to the upper-left 
//							corner of the window.
//
// Remarks		:	The framework calls this member function when the 
//						mouse cursor moves. Checks to see if the mouse is over
//						the button, and redraws the check if it is, but wasn't previously.
//
{
	if (GetCapture() != this)
		return;

	BOOL bWasMouseDown = m_bMouseDown;

	CRect rect;
	GetClientRect(rect);
	m_bMouseDown = rect.PtInRect(point);

	if (bWasMouseDown != m_bMouseDown)
		RedrawCheck();
}	// OnMouseMove

//-------------------------------------------------------------------
//
void CMacCheckBox::OnKeyUp(UINT nChar, UINT /*nRepCnt*/, UINT /*nFlags*/) 
//
// Return Value:	None.
//
// Parameters	:	nChar - Specifies the virtual-key code of the given key.
//						nRepCnt - Repeat count (the number of times the keystroke
//							is repeated as a result of the user holding down the key).
//						nFlags - Specifies the scan code, key-transition code, previous 
//							key state, and context code
//
// Remarks		:	The framework calls this member function when a nonsystem 
//						key is released. Checks/unchecks the button when the space bar
//						is pressed.
//
{		
	if (nChar == VK_SPACE)
	{
		m_bMouseDown = FALSE;
		m_bChecked = !m_bChecked;
		RedrawCheck();
	}
}	// OnKeyUp

//-------------------------------------------------------------------
//
void CMacCheckBox::OnKeyDown(UINT nChar, UINT /*nRepCnt*/, UINT /*nFlags*/) 
//
// Return Value:	None.
//
// Parameters	:	nChar - Specifies the virtual-key code of the given key.
//						nRepCnt - Repeat count (the number of times the keystroke 
//							is repeated as a result of the user holding down the key).
//						nFlags - Specifies the scan code, key-transition code, 
//							previous key state, and context code
//
// Remarks		:	The framework calls this member function when a 
//						nonsystem key is pressed.
//
{
	if (nChar == VK_SPACE)
	{
		m_bMouseDown = TRUE;
		RedrawCheck();
	}
}	// OnKeyDown

//-------------------------------------------------------------------
//
void CMacCheckBox::SetCheck(int nCheck)
//
// Return Value:	None.
//
// Parameters	:	nCheck - Specifies the check state (checked or unchecked,
//							there is no indeterminate state). 
//
// Remarks		:	Sets or resets the check state of a radio button or check box.
//
{
	BOOL bWasChecked = m_bChecked;

	m_bChecked = nCheck;

	if (m_bChecked != bWasChecked)
		RedrawCheck();
}	// SetCheck

//-------------------------------------------------------------------
//
int CMacCheckBox::GetCheck() const
//
// Return Value:	1 if checked, 0 otherwise.
//
// Parameters	:	None.
//
// Remarks		:	Retrieves the check state of the radio button.
//
{
	return m_bChecked;
}	// GetCheck

//-------------------------------------------------------------------
//
void CMacCheckBox::RedrawCheck()
//
// Return Value:	None.
//
// Parameters	:	None.
//
// Remarks		:	Redraws the check part of the button.
//
{
	CRect rect;
	GetClientRect(rect);
	int nHeight = 12;
	int nAdjust = (rect.Height() - nHeight) >> 1;
	CRect rectCheck;
	// The +2 adjustment is needed because the check mark extends 
	// two pixels beyond the right side of 12x12 square of the check box.
	if (GetStyle() & BS_LEFTTEXT)
		rectCheck.SetRect(rect.right - nHeight, rect.top + nAdjust, 
								rect.right + 2, rect.top + nHeight + nAdjust);
	else
		rectCheck.SetRect(rect.left, rect.top + nAdjust, 
								rect.left + nHeight + 2, rect.top + nHeight + nAdjust);

	InvalidateRect(rectCheck);
}	// RedrawCheck

//-------------------------------------------------------------------
//
void CMacCheckBox::GetColors()
//
// Return Value:	None.
//
// Parameters	:	None.
//
// Remarks		:	Sets the COLORREF member variables.
//
{
	m_crFace = ::GetSysColor(COLOR_3DFACE);
	m_crShadow = ::GetSysColor(COLOR_3DSHADOW);
	m_crHilight = ::GetSysColor(COLOR_3DHILIGHT);
	m_crDkShadow	 = ::GetSysColor(COLOR_3DDKSHADOW);

	// Create some intermediate colors. This is done by averaging two colors.
	BYTE byRedDark = GetRValue(m_crShadow);
	BYTE byRedLite = GetRValue(m_crFace);
	BYTE byGreenDark = GetGValue(m_crShadow);
	BYTE byGreenLite = GetGValue(m_crFace);
	BYTE byBlueDark = GetBValue(m_crShadow);
	BYTE byBlueLite = GetBValue(m_crFace);

	m_crLiteShadow = RGB(byRedLite + ((byRedDark - byRedLite) >> 1),
										 byGreenLite + ((byGreenDark - byGreenLite) >> 1),
										 byBlueLite + ((byBlueDark - byBlueLite) >> 1));
}	// GetColors
