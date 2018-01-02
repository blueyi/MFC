#include "StdAfx.h"
#include "TransparentDlg.h"
#include "resource.h"

CTransparentDlg::CTransparentDlg( UINT nIDTemplate, CWnd* pParentWnd /*= NULL*/, COLORREF transparentColour /*= RGB(255, 0, 255)*/ )
{
	m_TransparentColour = transparentColour;
	m_pBkDlg = NULL;
}

CTransparentDlg::~CTransparentDlg(void)
{
	if (NULL != m_pBkDlg)
	{
		delete m_pBkDlg;
		m_pBkDlg = NULL;
	}
	
}

BOOL CTransparentDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CTransparentDlg::OnInitDialog()
{

	m_pBkDlg = new CBkDlg(IDD_BKGROUND);

	ASSERT(m_pBkDlg);

	m_pBkDlg->Create(IDD_BKGROUND,AfxGetMainWnd());
	m_pBkDlg->ShowWindow(SW_NORMAL);	
	m_pBkDlg->getTransparentHwnd(&m_hWnd);	

	CDialog::OnInitDialog(); 

	m_Brush.CreateSolidBrush(m_TransparentColour);
	DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwStyle ^ 0x80000);
	::SetLayeredWindowAttributes(GetSafeHwnd(), m_TransparentColour, 0, 1);
 	::SetWindowPos(m_hWnd,  HWND_TOPMOST ,
		           0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	CRect rect;
	::GetWindowRect(m_pBkDlg->m_hWnd, &rect);
	::MoveWindow(m_hWnd, rect.left, rect.top, rect.Width(), rect.Height(), TRUE);	
	return TRUE;		
}
BEGIN_MESSAGE_MAP(CTransparentDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDCLOSE, &CTransparentDlg::OnBnClickedClose)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()

HBRUSH CTransparentDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if(nCtlColor == CTLCOLOR_DLG)
	{
		return m_Brush;
	}
	return CDialog::OnCtlColor(pDC,pWnd,nCtlColor);
}

void CTransparentDlg::OnClose()
{
	

	::SendMessage(m_pBkDlg->m_hWnd, WM_CLOSE, NULL, NULL);
	CDialog::OnClose();
	
}

void CTransparentDlg::SetTransparentColour( COLORREF transparentColour )
{
	m_TransparentColour = transparentColour;
	m_Brush.DeleteObject();
	m_Brush.CreateSolidBrush(m_TransparentColour);
	::SetLayeredWindowAttributes(GetSafeHwnd(), m_TransparentColour, 0, 1);//这句还可以测试画刷的颜色是否改变

}

void CTransparentDlg::OnDestroy()
{
	::SendMessage(m_pBkDlg->m_hWnd, WM_DESTROY, NULL, NULL);
	CDialog::OnDestroy();	

}

void CTransparentDlg::OnBnClickedClose()
{
	SendMessage(WM_CLOSE, 0, 0);
}

LRESULT CTransparentDlg::OnNcHitTest(CPoint point)
{
	return HTCLIENT;
}
