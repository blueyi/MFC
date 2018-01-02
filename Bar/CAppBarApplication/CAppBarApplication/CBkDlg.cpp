#include "StdAfx.h"
#include "BkDlg.h"

CBkDlg::CBkDlg( UINT nIDTemplate, CWnd* pParentWnd /*= NULL*/, BYTE bAlpha /*= 128*/, COLORREF bkColour /*= RGB(0,0,0)*/ )
       :CAppBar(nIDTemplate, pParentWnd)
{
	m_bAlpha = bAlpha;
	m_BkColour = bkColour;

	m_transparent_hwnd = NULL;
}

CBkDlg::~CBkDlg(void)
{
	m_transparent_hwnd = NULL;
}

BOOL CBkDlg::OnInitDialog()
{
	CAppBar::OnInitDialog();

	DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwStyle ^ 0x80000);
	::SetLayeredWindowAttributes(m_hWnd, 0, m_bAlpha , LWA_ALPHA);	
	::SetWindowPos(m_hWnd,  HWND_TOPMOST ,
		0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	Invalidate(TRUE);

	return TRUE; 	
}

BOOL CBkDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	return CAppBar::PreTranslateMessage(pMsg);
}


BEGIN_MESSAGE_MAP(CBkDlg, CAppBar)
	ON_WM_ERASEBKGND()
	ON_WM_NCHITTEST()
	ON_WM_MOVE()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

BOOL CBkDlg::OnEraseBkgnd(CDC* pDC)
{
	RECT rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect, m_BkColour);	

	return TRUE;
}

LRESULT CBkDlg::OnNcHitTest(CPoint point)
{
	return CAppBar::OnNcHitTest(point);
}

void CBkDlg::OnMove(int x, int y)
{
	CRect rect;
	GetWindowRect(&rect);
	::MoveWindow(m_transparent_hwnd,rect.left, rect.top, rect.Width(), rect.Height(), TRUE);

	CAppBar::OnMove(x, y);	
}

void CBkDlg::getTransparentHwnd( HWND *hwnd )
{
	m_transparent_hwnd = *hwnd;
	CAppBar::getTransparentHwnd(hwnd);
}

void CBkDlg::SetAlpha( BYTE bAlpha )
{
	m_bAlpha = bAlpha;
	::SetLayeredWindowAttributes(m_hWnd, m_bAlpha, m_bAlpha , LWA_ALPHA);
}

void CBkDlg::SetColor( COLORREF bkColour )
{
	m_BkColour =bkColour;	
	Invalidate(TRUE);
	UpdateWindow();
}


void CBkDlg::OnSetFocus(CWnd* pOldWnd)
{
	CAppBar::OnSetFocus(pOldWnd);
	
}

void CBkDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CAppBar::OnLButtonUp(nFlags, point);
	::SendMessage(m_transparent_hwnd, WM_SETFOCUS, 0, 0);

}

void CBkDlg::OnDestroy()
{
	CAppBar::OnDestroy();
	
}

void CBkDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CAppBar::OnClose();
}
