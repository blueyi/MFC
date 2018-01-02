// WndEx.cpp : implementation file
//

#include "stdafx.h"
#include "WndEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWndEx

CWndEx::CWndEx()
{
}

CWndEx::~CWndEx()
{
}


BEGIN_MESSAGE_MAP(CWndEx, CWnd)
	//{{AFX_MSG_MAP(CWndEx)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWndEx message handlers
BOOL CWndEx::CreateEx(DWORD dwExStyle,CString strWindowName,DWORD dwStyle,CRect rect,CWnd* pwndParent)
{
	HCURSOR hCursor = AfxGetApp()->LoadStandardCursor (IDC_ARROW);
	HBRUSH hBrush = (HBRUSH)(COLOR_WINDOW+1);
	HICON hIcon = NULL;

	CString strClassName;
	strClassName = AfxRegisterWndClass(CS_DBLCLKS,hCursor,hBrush,hIcon);
	
	int x = rect.left ;
	int y = rect.top ;
	int nWidth = rect.Width();
	int nHeight = rect.Height();
	HWND hWndParent = pwndParent->m_hWnd;

	return CWnd::CreateEx(dwExStyle,strClassName,strWindowName,dwStyle,x,y,nWidth,nHeight,hWndParent,NULL);

}
BOOL CWndEx::CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CWnd::CreateEx (dwExStyle,lpszClassName,lpszWindowName,dwStyle,rect,pParentWnd,nID);
}

BOOL CWndEx::Create(CString strWindowName,DWORD dwStyle,CRect rect,CWnd* pwndParent)
{
	return CreateEx(NULL,strWindowName,dwStyle,rect,pwndParent);
}

