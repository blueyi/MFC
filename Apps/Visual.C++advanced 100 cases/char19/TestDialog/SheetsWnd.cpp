/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 7/19/98 11:29:37 AM
  Comments: SheetsWnd.cpp : implementation file
 ************************************/

#include "stdafx.h"
#include "SheetsWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DEFAULTFORMATDRAWTEXT DT_CENTER | DT_VCENTER | DT_SINGLELINE

/////////////////////////////////////////////////////////////////////////////
// CSheetsWnd

#define unknown _T("Sheet")
#define LRB 6

CSheetsWnd::CSheetsWnd()
{
	m_wndProcParent = NULL;
	m_DrawRect.SetRectEmpty();
	m_nHorzScroll = 0;
	m_nMaxHorzScroll = 0;
}

CSheetsWnd::~CSheetsWnd()
{
}


BEGIN_MESSAGE_MAP(CSheetsWnd, CWnd)
	//{{AFX_MSG_MAP(CSheetsWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSheetsWnd message handlers

// Function name	: WindowProcParent
// Description	    : 
// Return type		: LRESULT CALLBACK 
// Argument         :  HWND hwnd
// Argument         : UINT uMsg
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
LRESULT CALLBACK WindowProcParent( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch (uMsg)
	{
		case WM_DESTROY:
			{
				CSheetsWnd::RestoreWndProc(hwnd);
				break;
			}
		case WM_SIZE:
			{
				CSheetsWnd::Resize(hwnd);
				return NULL;
			}
		case WM_PARENTNOTIFY:
			{
				CSheetsWnd::GetWndSheet(hwnd)->Invalidate();
				break;
			}

	}
	return CallWindowProc(CSheetsWnd::GetWndSheet(hwnd)->m_wndProcParent, hwnd, uMsg, wParam, lParam );
}

// Function name	: CSheetsWnd::GetRect
// Description	    : Return the wished rect of this object
// Return type		: CRect 
// Argument         : CWnd* pWndParent
CRect CSheetsWnd::GetRect(CWnd* pWndParent)
{
	CRect rect; pWndParent->GetClientRect(rect);
	rect.top = rect.bottom - GetSystemMetrics(SM_CYVTHUMB);
	return rect;
}

// Function name	: CSheetsWnd::GetRect
// Description	    : Return the wished rect of this object
// Return type		: CRect 
// Argument         : HWND hWndParent
CRect CSheetsWnd::GetRect(HWND hWndParent)
{
	return GetRect(CWnd::FromHandle(hWndParent));
}

// Function name	: CSheetsWnd::Attach
// Description	    : Create object as child of pWndParent with rgbBackground
// Return type		: BOOL 
// Argument         : CWnd * pWndParent
// Argument         : COLORREF rgbBackground
BOOL CSheetsWnd::Attach(CWnd * pWndParent, COLORREF rgbBackground)
{
	ASSERT (pWndParent && IsWindow(pWndParent->m_hWnd));
	CRect rect = GetRect(pWndParent);
	m_brBackground.CreateSolidBrush(rgbBackground);
	ASSERT(pWndParent->GetDlgItem(IDTHIS) == NULL);
	BOOL bResult = Create(AfxRegisterWndClass(0,AfxGetApp()->LoadStandardCursor(IDC_ARROW),(HBRUSH)m_brBackground,0), _T(""), WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, rect, pWndParent, IDTHIS);
	if (bResult)
		m_wndProcParent = (WNDPROC)SetWindowLong(pWndParent->m_hWnd, GWL_WNDPROC, (long)WindowProcParent);
	return bResult;
}

// Function name	: CSheetsWnd::GetWndSheet
// Description	    : Return pointer to sheet window
// Return type		: CSheetsWnd* 
// Argument         : HWND hWndParent
CSheetsWnd* CSheetsWnd::GetWndSheet(HWND hWndParent)
{
	return (CSheetsWnd*)CWnd::FromHandle(::GetDlgItem(hWndParent, IDTHIS));
}

// Function name	: CSheetsWnd::RestoreWndProc
// Description	    : When parent of this object become to be destroyed then restore window procedure
// Return type		: void 
// Argument         : HWND hWndParent
void CSheetsWnd::RestoreWndProc(HWND hWndParent)
{
	SetWindowLong(hWndParent, GWL_WNDPROC, (long)((CSheetsWnd*)CWnd::FromHandle(::GetDlgItem(hWndParent, IDTHIS)))->m_wndProcParent);
}

// Function name	: CSheetsWnd::Resize
// Description	    : All childs of parent, without this must be resized
// Return type		: void 
// Argument         : HWND hWndParent
void CSheetsWnd::Resize(HWND hWndParent)
{
	CSheetsWnd* pThis = GetWndSheet(hWndParent);
	CRect rect = pThis->GetRect(hWndParent);
	pThis->MoveWindow(rect);
	rect.bottom = rect.top; rect.top = 0;
	CWnd* pChild = pThis->GetFirstView();
	while (pChild)
	{
		pChild->MoveWindow(rect);
		pChild = pThis->GetNextView();
	}
	pThis->GetClientRect(rect);
	pThis->m_DrawRect.right = rect.right;
			
}

// Function name	: CSheetsWnd::GetFirstView
// Description	    : Get first view from object parent
// Return type		: CWnd* 
CWnd* CSheetsWnd::GetFirstView()
{
	m_pViewFind = GetParent()->GetWindow(GW_CHILD);
	while (m_pViewFind && m_pViewFind->m_hWnd == m_hWnd)
		m_pViewFind = m_pViewFind->GetWindow(GW_HWNDNEXT);
	return m_pViewFind;
}

// Function name	: CSheetsWnd::GetNextView
// Description	    : Get next view from object parent
// Return type		: CWnd* 
CWnd* CSheetsWnd::GetNextView()
{
	if (m_pViewFind)
	{
		m_pViewFind = m_pViewFind->GetWindow(GW_HWNDNEXT);
		while (m_pViewFind && m_pViewFind->m_hWnd == m_hWnd)
			m_pViewFind = m_pViewFind->GetWindow(GW_HWNDNEXT);
		return m_pViewFind;
	}
	return NULL;
}

// Function name	: CSheetsWnd::GetViewTitle
// Description	    : Return the default window title
// Return type		: CString 
// Argument         : CWnd * pView
CString CSheetsWnd::GetViewTitle(CWnd * pView)
{
	CString result; pView->GetWindowText(result);
	if (result.IsEmpty())
		result = unknown;
	return result;
}

// Function name	: CSheetsWnd::GetActiveView
// Description	    : Return the first active view
// Return type		: CWnd* 
CWnd* CSheetsWnd::GetActiveView()
{
	CWnd* pWnd = GetFirstView();
	while (pWnd)
		if (pWnd->IsWindowVisible())
			return pWnd;
		else
			pWnd = GetNextView();

	return pWnd;
}

// Function name	: CSheetsWnd::OnCreate
// Description	    : Create a new things.
// Return type		: int 
// Argument         : LPCREATESTRUCT lpCreateStruct
int CSheetsWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect rect; GetClientRect(rect);
	m_font.CreateFont(-rect.Height() * 8 / 10, 0, 0, 0, FW_LIGHT, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Arial"));
	CSize sxy(2 * rect.Height(), rect.Height());
	m_btns.Create(WS_CHILD | WS_VISIBLE | SBS_HORZ, CRect(CPoint(rect.left, rect.top), sxy), this, IDBTNS);
	rect.left += sxy.cx + 2;
	m_DrawRect = rect;
	return 0;
}

// Function name	: CSheetsWnd::OnPaint
// Description	    : Paint the pages 
// Return type		: void 
void CSheetsWnd::OnPaint() 
{
	CPaintDC dcThis(this);

	Draw(&dcThis);
	
}

// Function name	: CSheetsWnd::OnEraseBkgnd
// Description	    : 
// Return type		: BOOL 
// Argument         : CDC* pDC
BOOL CSheetsWnd::OnEraseBkgnd(CDC* pDC) 
{
	Draw(pDC);
	pDC->ExcludeClipRect(m_DrawRect);
	CBrush* pOldBrush = pDC->SelectObject(&m_brBackground);
	CRect rect;
	pDC->GetClipBox(&rect);     // Erase the area needed
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);
	return TRUE;
}

// Function name	: CSheetsWnd::Draw
// Description	    : Draw the pages of object
// Return type		: void 
// Argument         : CDC * pDC
void CSheetsWnd::Draw(CDC * pDC)
{
	if (!m_DrawRect.IsRectNull())
	{
		CDC dc; CBitmap bitmap;
		if (dc.CreateCompatibleDC(pDC))
			if (bitmap.CreateCompatibleBitmap(pDC, m_DrawRect.Width(), m_DrawRect.Height()))
			{
				dc.SelectObject(&bitmap);

				CBrush* pOldBrush = dc.SelectObject(&m_brBackground);
				dc.PatBlt(0,0, m_DrawRect.Width(), m_DrawRect.Height(), PATCOPY);
				dc.SelectObject(pOldBrush);

				CFont* pOldFont = dc.SelectObject(&m_font);
				dc.SetBkMode(TRANSPARENT);
				CWnd *pActiveView = GetActiveView(), *pView = GetFirstView();;
				CRgn rgnActive;
				CRect rtActive;
				int cxB = LRB, cx = m_nHorzScroll + cxB;
				m_nMaxHorzScroll = 0;
				while (pView)
				{
					CString title = GetViewTitle(pView);
					CRect rt(cx,0,0,0);
					dc.DrawText(title, rt, DEFAULTFORMATDRAWTEXT | DT_CALCRECT);
					rt.top = 0; rt.bottom = m_DrawRect.Height();
					rt.left -= 4; rt.right += 4;
					CPoint pPage[4];
					 pPage[0] = CPoint(rt.left  - cxB, 0);
					 pPage[1] = CPoint(rt.right + cxB, 0);
					 pPage[2] = CPoint(rt.BottomRight());
					 pPage[3] = CPoint(rt.left, rt.bottom);
					CRgn rgn; rgn.CreatePolygonRgn(pPage, 4, WINDING);
					dc.FillRgn(&rgn, &m_brBackground);
					dc.FrameRgn(&rgn, &CBrush(RGB(0,0,0)), 1, 1);
					dc.DrawText(title, rt, DEFAULTFORMATDRAWTEXT);
					if ((pActiveView) && (pView->m_hWnd == pActiveView->m_hWnd))
					{
						rgnActive.CreatePolygonRgn(pPage, 4, ALTERNATE);
						rtActive = rt;
					}
					pView = GetNextView();
					int next = rt.Width() + 6;
					cx += next;
					m_nMaxHorzScroll += next;
				}
				if (pActiveView)
				{
					dc.FillRgn(&rgnActive, &CBrush(RGB(255,255,255)));
					dc.FrameRgn(&rgnActive, &CBrush(RGB(0,0,0)), 1, 1);
					dc.DrawText(GetViewTitle(pActiveView), rtActive, DEFAULTFORMATDRAWTEXT);
				}
				dc.SelectObject(pOldFont);
				pDC->BitBlt(m_DrawRect.left, m_DrawRect.top, m_DrawRect.Width(), m_DrawRect.Height(), &dc, 0,0, SRCCOPY);
			}
	}
}

// Function name	: CSheetsWnd::OnHScroll
// Description	    : Left right buttons
// Return type		: void 
// Argument         : UINT nSBCode
// Argument         : UINT nPos
// Argument         : CScrollBar* pScrollBar
void CSheetsWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (pScrollBar->m_hWnd == m_btns.m_hWnd)
	{
		int nCX = 0;
		switch (nSBCode)
		{
			case SB_LINELEFT:
			case SB_LINERIGHT:
				{
					nCX = (nSBCode == SB_LINELEFT ? 1 : - 1) * 16;
					break;
				}
		}
		int n = m_nHorzScroll + nCX;
		if ( n <= 0)
			if (abs(n) < m_nMaxHorzScroll)
		{
			m_nHorzScroll = n;	
			Invalidate();
		}
	}
	
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

// Function name	: CSheetsWnd::OnLButtonDown
// Description	    : 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CSheetsWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_DrawRect.PtInRect(point))
		if (CWnd* pView = GetViewFromPoint(point))
		{
			CWnd* pOldActiveView = GetActiveView();
			if (!pOldActiveView || (pOldActiveView && pOldActiveView->m_hWnd != pView->m_hWnd))
			{
				pView->SetWindowPos(0,0,0,0,0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );
				if (pOldActiveView)
					pOldActiveView->SetWindowPos(0,0,0,0,0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_HIDEWINDOW);
				Invalidate();
			}
		}

	CWnd::OnLButtonDown(nFlags, point);
}

// Function name	: CSheetsWnd::GetViewFromPoint
// Description	    : Return pointer to view s.t. page of view contain point
// Return type		: CWnd* 
// Argument         : CPoint point
CWnd* CSheetsWnd::GetViewFromPoint(CPoint point)
{
	if (m_DrawRect.PtInRect(point))
	{
		CWnd* pChild = GetFirstView();
		CDC* pDC = GetDC();
		pDC->SetViewportOrg(m_DrawRect.TopLeft());
		CFont* pOldFont = pDC->SelectObject(&m_font);
		int cxB = LRB, cx = cxB;
		int aPointX = -m_nHorzScroll + point.x - m_DrawRect.left;
		while (pChild)
		{
			CRect rt(cx,0,0,0);
			pDC->DrawText(GetViewTitle(pChild), rt, DEFAULTFORMATDRAWTEXT | DT_CALCRECT);
			rt.top = 0; rt.bottom = m_DrawRect.Height();
			if ((aPointX > cx - LRB) && (aPointX  <= cx + rt.Width() + LRB))
				break;
			pChild = GetNextView();
			int next = rt.Width() + 6 + LRB;
			cx += next;
		}
		pDC->SelectObject(pOldFont);
		ReleaseDC(pDC);
		return pChild;
	}
	return NULL;
}
