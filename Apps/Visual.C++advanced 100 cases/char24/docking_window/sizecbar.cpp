/////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 by Cristi Posea
// All rights reserved
//
// Distribute freely, except: don't remove my name from the source or
// documentation (don't take credit for my work), mark your changes
// (don't get me blamed for your possible bugs), don't alter or remove
// this notice.
// No warrantee of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc.,
// and I'll try to keep a version up to date.  I can be reached at:
//    cristi@gds.ro
/////////////////////////////////////////////////////////////////////////
//
// Acknowledgements:
//  o   Thanks to Harlan R. Seymour (harlan@hcube.com) for motivating me
//      to update this code. Also he prompted me to a bug durring 
//      the developement phase.
//  o   Thanks to Zafir Anjum (zafir@codeguru.com) for publishing this
//      code on his cool site (www.codeguru.com).
//  o   Some ideeas for the gripper came from the CToolBarEx flat toolbar
//      by Joerg Koenig (Joerg.Koenig@rhein-neckar.de). Also he inspired
//      me on writting this notice:) . Thanks, Joerg!
//  o   Thanks to Jakawan Ratiwanich (jack@alpha.fsec.ucf.edu) and to
//      Udo Schaefer(Udo.Schaefer@vcase.de) for the dwStyle bug fix under
//      VC++ 6.0.
//  o   Thanks to Microsoft developers for the MFC source code. After
//      all, most of this class code came from there.
//
/////////////////////////////////////////////////////////////////////////
//
// Usage:
// o    Derive your class from CSizingControlBar. Then create your child
//      controls/windows on it.
// o    Include your class header in Mainfrm.cpp and add a member 
//      variable to CMainFrame. In CMainFrame::OnCreate(), create the
//      control bar, enable it to dock, and so on... like a toolbar or
//      any control bar.
// o    More details at
//      http://www.codeguru.com/docking/docking_window.shtml or search
//      http://www.codeguru.com for my name if the article has moved.
//
/////////////////////////////////////////////////////////////////////////


// SizingControlBar.cpp : implementation file
//

#include "stdafx.h"
#include "afxpriv.h"    // for CDockContext
#include "sizecbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////
// CSizingControlBar

CSizingControlBar::CSizingControlBar()
{
    m_sizeMin = CSize(32, 32);
    m_sizeHorz = CSize(200, 200);
    m_sizeVert = CSize(200, 200);
    m_sizeFloat = CSize(200, 200);
    m_bTracking = FALSE;
    m_bInRecalcNC = FALSE;
    m_cxEdge = 5;
	m_bDragShowContent = FALSE;
}

CSizingControlBar::~CSizingControlBar()
{
}

BEGIN_MESSAGE_MAP(CSizingControlBar, CControlBar)
    //{{AFX_MSG_MAP(CSizingControlBar)
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_SETCURSOR()
    ON_WM_WINDOWPOSCHANGED()
    ON_WM_NCPAINT()
    ON_WM_NCLBUTTONDOWN()
    ON_WM_NCHITTEST()
    ON_WM_NCCALCSIZE()
    ON_WM_LBUTTONDOWN()
    ON_WM_CAPTURECHANGED()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_PAINT()
    ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////
// CSizingControlBar message handlers

BOOL CSizingControlBar::Create(LPCTSTR lpszWindowName, CWnd* pParentWnd,
                               CSize sizeDefault, BOOL bHasGripper,
                               UINT nID, DWORD dwStyle)
{
    ASSERT_VALID(pParentWnd);   // must have a parent
    ASSERT (!((dwStyle & CBRS_SIZE_FIXED)
        && (dwStyle & CBRS_SIZE_DYNAMIC)));

    // save the style
    SetBarStyle(dwStyle & CBRS_ALL);

    CString wndclass = ::AfxRegisterWndClass(CS_DBLCLKS,
        ::LoadCursor(NULL, IDC_ARROW),
        ::GetSysColorBrush(COLOR_BTNFACE), 0);

    dwStyle &= ~CBRS_ALL;
    dwStyle &= WS_VISIBLE | WS_CHILD;
    if (!CWnd::Create(wndclass, lpszWindowName, dwStyle, CRect(0,0,0,0),
        pParentWnd, nID))
        return FALSE;

    m_sizeHorz = sizeDefault;
    m_sizeVert = sizeDefault;
    m_sizeFloat = sizeDefault;

    m_bHasGripper = bHasGripper;
    m_cyGripper = m_bHasGripper ? 12 : 0;

    return TRUE;
}

BOOL CSizingControlBar::IsHorzDocked() const
{
    return (m_nDockBarID == AFX_IDW_DOCKBAR_TOP ||
        m_nDockBarID == AFX_IDW_DOCKBAR_BOTTOM);
}

BOOL CSizingControlBar::IsVertDocked() const
{
    return (m_nDockBarID == AFX_IDW_DOCKBAR_LEFT ||
        m_nDockBarID == AFX_IDW_DOCKBAR_RIGHT);
}

CSize CSizingControlBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
    CRect rc;

    m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_TOP)->GetWindowRect(rc);
    int nHorzDockBarWidth = bStretch ? 32767 : rc.Width() + 4;
    m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_LEFT)->GetWindowRect(rc);
    int nVertDockBarHeight = bStretch ? 32767 : rc.Height() + 4;

    if (bHorz)
        return CSize(nHorzDockBarWidth, m_sizeHorz.cy);
    else
        return CSize(m_sizeVert.cx, nVertDockBarHeight);
}

CSize CSizingControlBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{
    if (dwMode & (LM_HORZDOCK | LM_VERTDOCK))
    {
        if (nLength == -1)
            GetDockingFrame()->DelayRecalcLayout();
        return CControlBar::CalcDynamicLayout(nLength,dwMode);
    }

    if (dwMode & LM_MRUWIDTH)
        return m_sizeFloat;

    if (dwMode & LM_COMMIT)
    {
        m_sizeFloat.cx = nLength;
        return m_sizeFloat;
    }

    if (dwMode & LM_LENGTHY)
        return CSize(m_sizeFloat.cx,
            m_sizeFloat.cy = max(m_sizeMin.cy, nLength));
    else
        return CSize(max(m_sizeMin.cx, nLength), m_sizeFloat.cy);
}

void CSizingControlBar::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
    CControlBar::OnWindowPosChanged(lpwndpos);

    // Find on which side are we docked
    m_nDockBarID = GetParent()->GetDlgCtrlID();

    if (!m_bInRecalcNC)
    {
        m_bInRecalcNC = TRUE;

        // Force recalc the non-client area
        SetWindowPos(NULL, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE |
            SWP_NOACTIVATE | SWP_NOZORDER |
            SWP_FRAMECHANGED);

        m_bInRecalcNC = FALSE;
    }
}

BOOL CSizingControlBar::OnSetCursor(CWnd* pWnd, UINT nHitTest,
                                    UINT message) 
{
    if ((nHitTest != HTSIZE) || m_bTracking)
        return CControlBar::OnSetCursor(pWnd, nHitTest, message);

    if (IsHorzDocked())
        ::SetCursor(::LoadCursor(NULL, IDC_SIZENS));
    else
        ::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////
// Mouse Handling
//
void CSizingControlBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
    if (m_pDockBar != NULL)
    {
        // start the drag
        ASSERT(m_pDockContext != NULL);
        ClientToScreen(&point);
        m_pDockContext->StartDrag(point);
    }
    else
        CWnd::OnLButtonDown(nFlags, point);
}

void CSizingControlBar::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
    if (m_pDockBar != NULL)
    {
        // toggle docking
        ASSERT(m_pDockContext != NULL);
        m_pDockContext->ToggleDocking();
    }
    else
        CWnd::OnLButtonDblClk(nFlags, point);
}

void CSizingControlBar::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{
    if (m_bTracking) return;

    if ((nHitTest == HTSIZE) && !IsFloating())
        StartTracking();
    else    
        CControlBar::OnNcLButtonDown(nHitTest, point);
}

void CSizingControlBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
    if (m_bTracking)
        StopTracking(TRUE);

    CControlBar::OnLButtonUp(nFlags, point);
}

void CSizingControlBar::OnRButtonDown(UINT nFlags, CPoint point) 
{
    if (m_bTracking)
        StopTracking(FALSE);
	
	CControlBar::OnRButtonDown(nFlags, point);
}

void CSizingControlBar::OnMouseMove(UINT nFlags, CPoint point) 
{
    if (m_bTracking)
    {
		ASSERT (!IsFloating());
		CPoint pt = point;
		ClientToScreen(&pt);

		OnTrackUpdateSize(pt);
    }

    CControlBar::OnMouseMove(nFlags, point);
}

void CSizingControlBar::OnCaptureChanged(CWnd *pWnd) 
{
    if (m_bTracking && pWnd != this)
        StopTracking(FALSE); // cancel tracking

    CControlBar::OnCaptureChanged(pWnd);
}

void CSizingControlBar::OnNcCalcSize(BOOL bCalcValidRects,
                                     NCCALCSIZE_PARAMS FAR* lpncsp) 
{
    // Compute the rectangle of the mobile edge
    GetWindowRect(m_rectBorder);
    m_rectBorder.OffsetRect(-m_rectBorder.left, -m_rectBorder.top);
    m_rectBorder.DeflateRect(1, 1);
    
    m_rectGripper = m_rectBorder;
    m_rectGripper.DeflateRect(5, 5);
    m_rectGripper.right -= m_cxEdge;
    m_rectGripper.bottom -= m_cxEdge;
    CRect rc = lpncsp->rgrc[0];

    DWORD dwBorderStyle = m_dwStyle | CBRS_BORDER_ANY;

    switch(m_nDockBarID)
    {
    case AFX_IDW_DOCKBAR_TOP:
        dwBorderStyle &= ~CBRS_BORDER_BOTTOM;
        rc.DeflateRect(m_cyGripper + 2, 2, 2, m_cxEdge + 2);
        m_rectBorder.top = m_rectBorder.bottom - m_cxEdge;
        break;
    case AFX_IDW_DOCKBAR_BOTTOM:
        dwBorderStyle &= ~CBRS_BORDER_TOP;
        rc.DeflateRect(m_cyGripper + 2, m_cxEdge + 2, 2, 2);
        m_rectBorder.bottom = m_rectBorder.top + m_cxEdge;
        m_rectGripper.OffsetRect(0, m_cxEdge);
        break;
    case AFX_IDW_DOCKBAR_LEFT:
        dwBorderStyle &= ~CBRS_BORDER_RIGHT;
        rc.DeflateRect(2, m_cyGripper + 2, m_cxEdge + 2, 6);
        m_rectBorder.left = m_rectBorder.right - m_cxEdge;
        break;
    case AFX_IDW_DOCKBAR_RIGHT:
        dwBorderStyle &= ~CBRS_BORDER_LEFT;
        rc.DeflateRect(m_cxEdge + 2, m_cyGripper + 2, 2, 6);
        m_rectBorder.right = m_rectBorder.left + m_cxEdge;
        m_rectGripper.OffsetRect(m_cxEdge, 0);
        break;
    default:
        m_rectBorder.SetRectEmpty();
        break;
    }

    lpncsp->rgrc[0] = rc;

    SetBarStyle(dwBorderStyle);
}

void CSizingControlBar::OnNcPaint() 
{
    // get window DC that is clipped to the non-client area
    CWindowDC dc(this);
    CRect rectClient;
    GetClientRect(rectClient);
    CRect rectWindow;
    GetWindowRect(rectWindow);
    ScreenToClient(rectWindow);
    rectClient.OffsetRect(-rectWindow.left, -rectWindow.top);
    dc.ExcludeClipRect(rectClient);

    // draw borders in non-client area
    rectWindow.OffsetRect(-rectWindow.left, -rectWindow.top);
    DrawBorders(&dc, rectWindow);

    // erase parts not drawn
    dc.IntersectClipRect(rectWindow);

    // erase NC background the hard way
    HBRUSH hbr = (HBRUSH)GetClassLong(m_hWnd, GCL_HBRBACKGROUND);
    ::FillRect(dc.m_hDC, rectWindow, hbr);

    // paint the mobile edge
    dc.Draw3dRect(m_rectBorder, ::GetSysColor(COLOR_BTNHIGHLIGHT),
        ::GetSysColor(COLOR_BTNSHADOW));

    if (m_bHasGripper)
    {
        // paint the gripper
        CRect gripper = m_rectGripper;
        
        if (IsHorzDocked())
        {
            // gripper at left
            gripper.right = gripper.left + 3;
            dc.Draw3dRect(gripper, ::GetSysColor(COLOR_BTNHIGHLIGHT),
                ::GetSysColor(COLOR_BTNSHADOW));
            gripper.OffsetRect(3, 0);
            dc.Draw3dRect(gripper, ::GetSysColor(COLOR_BTNHIGHLIGHT),
                ::GetSysColor(COLOR_BTNSHADOW));
        }
        else if (IsVertDocked())
        {
            // gripper at top
            gripper.bottom = gripper.top + 3;
            dc.Draw3dRect(gripper, ::GetSysColor(COLOR_BTNHIGHLIGHT),
                ::GetSysColor(COLOR_BTNSHADOW));
            gripper.OffsetRect(0, 3);
            dc.Draw3dRect(gripper, ::GetSysColor(COLOR_BTNHIGHLIGHT),
                ::GetSysColor(COLOR_BTNSHADOW));
        }
    }

    ReleaseDC(&dc);
}

void CSizingControlBar::OnPaint() 
{
    // overridden to skip border painting based on clientrect
    CPaintDC dc(this);
}

LRESULT CSizingControlBar::OnNcHitTest(CPoint point) 
{
    if (IsFloating())
        return CControlBar::OnNcHitTest(point);

    CRect rc;
    GetWindowRect(rc);
    point.Offset(-rc.left, -rc.top);
    if (m_rectBorder.PtInRect(point))
        return HTSIZE;
    else
        return HTCLIENT;
}

/////////////////////////////////////////////////////////////////////////
// CSizingControlBar implementation helpers

void CSizingControlBar::StartTracking()
{
    SetCapture();

    // make sure no updates are pending
    RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_UPDATENOW);
	
	m_bDragShowContent = QueryDragFullWindows();
	
	if (!m_bDragShowContent)
	    m_pDockSite->LockWindowUpdate();

	m_sizeOld = IsHorzDocked() ? m_sizeHorz : m_sizeVert;

	CRect rect;
	GetWindowRect(&rect);
    m_ptOld = m_rectBorder.CenterPoint() + rect.TopLeft();

	m_sizeMax = CalcMaxSize();
    m_bTracking = TRUE;
    
	if (!m_bDragShowContent)
	    OnTrackInvertTracker();
}

void CSizingControlBar::StopTracking(BOOL bAccept)
{
	if (!m_bDragShowContent)
	{
		OnTrackInvertTracker();
	    m_pDockSite->UnlockWindowUpdate();
	}

    m_bTracking = FALSE;
    ReleaseCapture();
    
    if (!bAccept) // resize canceled?
	{
		// restore old size
		if (IsHorzDocked())
	        m_sizeHorz = m_sizeOld;
		else
			m_sizeVert = m_sizeOld;
	}

    m_pDockSite->DelayRecalcLayout();
}

void CSizingControlBar::OnTrackUpdateSize(CPoint& point)
{
	BOOL bHorz = IsHorzDocked();

    CSize sizeNew = m_sizeOld;
	
    if ((m_nDockBarID == AFX_IDW_DOCKBAR_TOP) ||
		(m_nDockBarID == AFX_IDW_DOCKBAR_LEFT))
        sizeNew += point - m_ptOld;
	else
        sizeNew -= point - m_ptOld;

	// check limits
  	sizeNew.cx = max(m_sizeMin.cx, sizeNew.cx);
  	sizeNew.cy = max(m_sizeMin.cy, sizeNew.cy);
  	sizeNew.cx = min(m_sizeMax.cx, sizeNew.cx);
  	sizeNew.cy = min(m_sizeMax.cy, sizeNew.cy);

    if ((sizeNew.cy == m_sizeHorz.cy) && bHorz ||
		(sizeNew.cx == m_sizeVert.cx) && !bHorz)
		return; // no size change

	if (!m_bDragShowContent)
		OnTrackInvertTracker();

    if (bHorz)
		m_sizeHorz = sizeNew;
	else
		m_sizeVert = sizeNew;

	if (!m_bDragShowContent)
		OnTrackInvertTracker();
	else
	    m_pDockSite->DelayRecalcLayout();
}

CSize CSizingControlBar::CalcMaxSize()
{
	// the control bar cannot grow with more than the size of 
	// remaining client area of the frame
	CRect rect;
	m_pDockSite->GetClientRect(&rect);
	CSize size = rect.Size();
	CWnd* pBar;
	if (IsHorzDocked())
	{
		if (pBar = m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_TOP))
		{
			pBar->GetWindowRect(&rect);
			size -= rect.Size();
		}
		if (pBar = m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_BOTTOM))
		{
			pBar->GetWindowRect(&rect);
			size -= rect.Size();
		}
		if (pBar = m_pDockSite->GetControlBar(AFX_IDW_STATUS_BAR))
		{
			pBar->GetWindowRect(&rect);
			size -= rect.Size();
		}
	}
	else
	{
		if (pBar = m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_LEFT))
		{
			pBar->GetWindowRect(&rect);
			size -= rect.Size();
		}
		if (pBar = m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_RIGHT))
		{
			pBar->GetWindowRect(&rect);
			size -= rect.Size();
		}
	}
	
	size -= CSize(4, 4);
    size += IsHorzDocked() ? m_sizeHorz : m_sizeVert;

	return size;
}

void CSizingControlBar::OnTrackInvertTracker()
{
    ASSERT_VALID(this);
    ASSERT(m_bTracking);

	CRect rect = m_rectBorder;
    CRect rectBar, rectFrame;
    GetWindowRect(rectBar);
    rect.OffsetRect(rectBar.TopLeft());
    m_pDockSite->GetWindowRect(rectFrame);
    rect.OffsetRect(-rectFrame.left, -rectFrame.top);

	switch (m_nDockBarID)
	{
	case AFX_IDW_DOCKBAR_TOP:
		rect.OffsetRect(0, m_sizeHorz.cy - m_sizeOld.cy); break;
	case AFX_IDW_DOCKBAR_BOTTOM:
		rect.OffsetRect(0, m_sizeOld.cy - m_sizeHorz.cy); break;
	case AFX_IDW_DOCKBAR_LEFT:
		rect.OffsetRect(m_sizeVert.cx - m_sizeOld.cx, 0); break;
	case AFX_IDW_DOCKBAR_RIGHT:
		rect.OffsetRect(m_sizeOld.cx - m_sizeVert.cx, 0); break;
	}
	if (IsVertDocked())
	    rect.bottom -= 4;
    rect.DeflateRect(1, 1);

    CDC *pDC = m_pDockSite->GetDCEx(NULL,
        DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);

    CBrush* pBrush = CDC::GetHalftoneBrush();
    HBRUSH hOldBrush = NULL;
    if (pBrush != NULL)
        hOldBrush = (HBRUSH)::SelectObject(pDC->m_hDC, pBrush->m_hObject);

    pDC->PatBlt(rect.left, rect.top,
		rect.Width(), rect.Height(), PATINVERT);

    if (hOldBrush != NULL)
        ::SelectObject(pDC->m_hDC, hOldBrush);

    m_pDockSite->ReleaseDC(pDC);
}

BOOL CSizingControlBar::QueryDragFullWindows() const
{
	TCHAR sDragfullWindows[2];
	DWORD cbDragfullWindows = sizeof(DWORD);
	DWORD dwType;
	HKEY hKey;
	BOOL bRet = FALSE;

	RegOpenKeyEx(HKEY_CURRENT_USER, _T("Control Panel\\desktop"),
		0, KEY_QUERY_VALUE, &hKey);

	if (!FAILED(RegQueryValueEx(hKey, _T("DragfullWindows"),
		NULL, &dwType, (LPBYTE)&sDragfullWindows, &cbDragfullWindows)))
		if (!_tcscmp(sDragfullWindows, _T("1")))
			bRet = TRUE;

	RegCloseKey(hKey);

	return bRet;
}
