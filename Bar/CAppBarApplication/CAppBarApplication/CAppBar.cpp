// AppBar.cpp : implementation file
//

#include "stdafx.h"
#include "AppBar.h"


// CAppBar dialog

IMPLEMENT_DYNAMIC(CAppBar, CDialog)

CAppBar::CAppBar(UINT ID, CWnd* pParent /*=NULL*/)
	: CDialog(ID, pParent),
	m_oldestPoint(0)
{
	m_pOptions = new OPTIONS;
	ASSERT (m_pOptions);
	m_bAppRegistered = FALSE;
	m_bMoving = FALSE;
	m_bHidden = FALSE;
	m_bLButionDown = FALSE;
	m_bFirstMouseMove = FALSE;
	m_nHotKeyID=0;

}

CAppBar::~CAppBar()
{

}


BEGIN_MESSAGE_MAP(CAppBar, CDialog)
	ON_WM_CREATE()
	ON_MESSAGE(WM_HOTKEY,OnHotKey) 
	ON_MESSAGE(APPBAR_CALLBACK,AppBarCallback) 
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_NCHITTEST()
	ON_WM_CLOSE()
END_MESSAGE_MAP()
BOOL CAppBar::OnInitDialog()
{
	CDialog::OnInitDialog();		
	Register ();
	MyRegisterHotKey(MOD_ALT,'D');
	SetSide (ABE_RIGHT);
	return TRUE;  
}


int CAppBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	POPTIONS pOptions;	
	InitCommonControls();	
	pOptions = (POPTIONS) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(OPTIONS));
	if (pOptions)
	{
		pOptions->uSide = ABE_RIGHT;
		DWORD dwUnits;
		dwUnits = GetDialogBaseUnits ();
		pOptions->cyHeight = (CY_DEFHEIGHT*HIWORD (dwUnits)) / 2;
		pOptions->cxWidth = (CX_DEFWIDTH*LOWORD (dwUnits)) / 2;
		pOptions->fHiding = m_bHidden;
		if (!SetAppbarData (pOptions))
		{
			ASSERT (FALSE);
		}
	}
	else
	{
		return FALSE;
	}

	return 0;
}

BOOL CAppBar::SetAppbarData( POPTIONS pOptions )
{
	if (!m_pOptions)
	{
		return FALSE;
	}
	m_pOptions->fHiding = pOptions->fHiding;
	m_pOptions->uSide = pOptions->uSide;
	m_pOptions->cxWidth = pOptions->cxWidth;
	m_pOptions->cyHeight = pOptions->cyHeight;
	return TRUE;

}

POPTIONS CAppBar::GetAppbarData()
{
	return m_pOptions;
}

BOOL CAppBar::Register()
{
	APPBARDATA abd;
	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = m_hWnd;
	abd.uCallbackMessage = APPBAR_CALLBACK;
	m_bAppRegistered = SHAppBarMessage (ABM_NEW, &abd);
	return m_bAppRegistered;
}

BOOL CAppBar::UnRegister()
{
	APPBARDATA abd;
	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = m_hWnd;
	m_bAppRegistered = !SHAppBarMessage(ABM_REMOVE, &abd);
	return !m_bAppRegistered;
}

BOOL CAppBar::SetSide( UINT uSide )
{
	APPBARDATA abd;
	RECT	   rc;
	POPTIONS   pOpt = GetAppbarData();	

	rc.top = 0;
	rc.left = 0;
	rc.right = GetSystemMetrics(SM_CXSCREEN);
	rc.bottom = GetSystemMetrics(SM_CYSCREEN);

	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = m_hWnd;

	switch (uSide)
	{	
	case ABE_LEFT:
		rc.right = rc.left + pOpt->cxWidth;
		break;
	case ABE_RIGHT:
		rc.left = rc.right - pOpt->cxWidth;
		break;
	}	
	QuerySetPos(uSide, &rc, &abd, TRUE);

	return TRUE;

}

void CAppBar::QueryPos( LPRECT lprc )
{
	POPTIONS pOpt;
	pOpt = GetAppbarData ();
	APPBARDATA abd;
	int iWidth = 0;
	abd.hWnd = m_hWnd;
	abd.cbSize = sizeof(APPBARDATA);
	abd.rc = *lprc;
	abd.uEdge = pOpt->uSide;
	iWidth =pOpt->cxWidth;	
	SHAppBarMessage(ABM_QUERYPOS, &abd);
	switch (abd.uEdge)
	{
	case ABE_LEFT:
		abd.rc.right = abd.rc.left + iWidth;
		break;

	case ABE_RIGHT:
		abd.rc.left = abd.rc.right - iWidth;
		break;
	}
	*lprc = abd.rc;	
}

void CAppBar::QuerySetPos( UINT uEdge, LPRECT lprc, PAPPBARDATA pabd, BOOL bMove )
{
	int iHeight = 0;
	int iWidth = 0;
	POPTIONS pOpt = GetAppbarData();	
	pabd->rc = *lprc;
	pabd->uEdge = uEdge;
	pOpt->uSide = uEdge;
	QueryPos(&(pabd->rc));

	SHAppBarMessage(ABM_SETPOS, pabd);
	if (bMove)
	{

		::MoveWindow(m_hWnd, pabd->rc.left, pabd->rc.top, 
			pabd->rc.right - pabd->rc.left,
			pabd->rc.bottom - pabd->rc.top, TRUE);

		CString s;
		s.Format(_T("!!%d,%d,%d,%d!!\n"),pabd->rc.left, pabd->rc.top, 
			pabd->rc.right - pabd->rc.left,
			pabd->rc.bottom - pabd->rc.top);
		TRACE(s);
	}	
	m_rcAppBar = pabd->rc;
}

LONG CAppBar::AppBarCallback(WPARAM wParam, LPARAM lParam )
{
	POPTIONS pOpt = GetAppbarData();
	switch (wParam) 
	{
		case ABN_STATECHANGE:
			TRACE(L"ABN_STATECHANGE\n");
			break;
		case ABN_FULLSCREENAPP:
	        TRACE(L"ABN_FULLSCREENAPP\n");
	        break;
		case ABN_POSCHANGED:	
			SetSide(pOpt->uSide);
			::MoveWindow(m_transparent_hwnd, m_rcAppBar.left, m_rcAppBar.top, m_rcAppBar.Width(), m_rcAppBar.Height(), TRUE);
			break;
	}

	return 0;
}

LONG CAppBar::OnHotKey( WPARAM wParam,LPARAM lParam )
{
	if (m_bHidden == FALSE)
	{
		ShowWindow(SW_HIDE);
		FromHandle(m_transparent_hwnd)->ShowWindow(SW_HIDE);

		m_bHidden = TRUE;
		UnRegister ();
	}
	else
	{
		ShowWindow(SW_SHOW);
		FromHandle(m_transparent_hwnd)->ShowWindow(SW_SHOW);
		m_bHidden = FALSE;		
		POPTIONS m_pOptions=GetAppbarData();
		Register ();	 
		SetSide(m_pOptions->uSide);
	}	
	return 0;

}

void CAppBar::OnDestroy()
{
	CDialog::OnDestroy();

}

void CAppBar::OnLButtonDown(UINT nFlags, CPoint point)
{

	POPTIONS pOpt = GetAppbarData();	
	m_uOriginSide = pOpt->uSide;
	m_bMoving = TRUE;
	CRect   rc; 
	GetWindowRect(&rc); 
	CRectTracker   rectTracker; 
	HDC   hdc   =   ::GetDC(NULL); 
	CDC*   pDC   =   CDC::FromHandle(hdc);	
	rectTracker.DrawTrackerRect(&rc,   NULL,   pDC,   NULL); 	
	ReleaseDC(pDC);
	m_bLButionDown = TRUE;
	m_bFirstMouseMove = TRUE;
	m_ptLast = point;
	ClientToScreen(&m_ptLast);
	m_rcLast = rc;
	m_oldestPoint.SetPoint(rc.left, rc.top);
	SetCapture();	
	CDialog::OnLButtonDown(nFlags, point);
}

void CAppBar::OnMouseMove(UINT nFlags, CPoint point)
{

	POINT ptCursor = {point.x, point.y};
	LONG cxScreen, cyScreen;	
	WORD horiz;
	POPTIONS pOpt = GetAppbarData();
	APPBARDATA abd;
	ClientToScreen(&ptCursor);
	HDC hdc = ::GetDC(NULL); 
	CDC* pDC = CDC::FromHandle(hdc);
	CRect rcwork;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcwork, 0);//得到除任务栏的区域
	int nMode = pDC->SetBkMode(TRANSPARENT);
	if (m_bLButionDown == TRUE )
	{
		if (m_bFirstMouseMove == FALSE)
		{	
			pDC->PatBlt(m_rcLast.left, m_rcLast.top, pOpt->cxWidth , 1, PATINVERT );
			pDC->PatBlt(m_rcLast.left, m_rcLast.top, 1, m_rcLast.Height()-1,PATINVERT );
			pDC->PatBlt(m_rcLast.left , m_rcLast.top +m_rcLast.Height(),
				pOpt->cxWidth , 1, PATINVERT );
			pDC->PatBlt(m_rcLast.left + pOpt->cxWidth, m_rcLast.top,
				1, m_rcLast.Height()-1,PATINVERT );
			m_rcLast.SetRect(CPoint(m_oldestPoint.x + ptCursor.x - m_ptLast.x , ptCursor.y - m_ptLast.y),
				CPoint(m_oldestPoint.x + ptCursor.x - m_ptLast.x + pOpt->cxWidth, rcwork.Height() + ptCursor.y - m_ptLast.y));
		}	
		pDC->PatBlt(m_rcLast.left, m_rcLast.top, m_rcLast.Width() , 1, PATINVERT );
		pDC->PatBlt(m_rcLast.left, m_rcLast.top, 1, m_rcLast.Height()-1,PATINVERT );	
		pDC->PatBlt(m_rcLast.left , m_rcLast.top +m_rcLast.Height(),
			pOpt->cxWidth , 1, PATINVERT );
		pDC->PatBlt(m_rcLast.left + pOpt->cxWidth, m_rcLast.top,
			1, m_rcLast.Height()-1,PATINVERT );	
		ReleaseDC(pDC); 
	}	

	pDC->SetBkMode(nMode);
	if (m_bFirstMouseMove == TRUE)
	{
		m_bFirstMouseMove = FALSE;
	}	

	cxScreen = GetSystemMetrics(SM_CXSCREEN);
	cyScreen = GetSystemMetrics(SM_CYSCREEN);
	if (ptCursor.x < (cxScreen / 2))
	{	
		horiz = ABE_LEFT;
	}
	else
	{	
		horiz = ABE_RIGHT;
	}
	m_rcAppBar.top = 0;
	m_rcAppBar.bottom = cyScreen;
	if (horiz == ABE_LEFT)
	{
		m_rcAppBar.left = 0;
		m_rcAppBar.right = m_rcAppBar.left + pOpt->cxWidth;
		pOpt->uSide = ABE_LEFT;
	}
	else
	{
		m_rcAppBar.right = cxScreen;
		m_rcAppBar.left = m_rcAppBar.right - pOpt->cxWidth;
		pOpt->uSide = ABE_RIGHT;
	}

	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = m_hWnd;

	QueryPos(&m_rcAppBar);
	MoveWindow(m_rcAppBar.left, m_rcAppBar.top, 
		m_rcAppBar.right - m_rcAppBar.left, 
		m_rcAppBar.bottom - m_rcAppBar.top, 
		TRUE);

	CDialog::OnMouseMove(nFlags, point);
}

void CAppBar::OnLButtonUp(UINT nFlags, CPoint point)
{

	APPBARDATA abd;
	POPTIONS pOpt = GetAppbarData();
	ReleaseCapture();	
	m_bLButionDown = FALSE;

	if (m_bFirstMouseMove == FALSE)
	{
		HDC hdc = ::GetDC(NULL); 
		CDC* pDC = CDC::FromHandle(hdc); 
		pDC->PatBlt(m_rcLast.left, m_rcLast.top, m_rcLast.Width() , 1, PATINVERT );
		pDC->PatBlt(m_rcLast.left, m_rcLast.top, 1, m_rcLast.Height()-1,PATINVERT );	
		pDC->PatBlt(m_rcLast.left , m_rcLast.top +m_rcLast.Height(),
			pOpt->cxWidth , 1, PATINVERT );
		pDC->PatBlt(m_rcLast.left + pOpt->cxWidth, m_rcLast.top,
			1, m_rcLast.Height()-1,PATINVERT );
		ReleaseDC(pDC); 
	}	

	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = m_hWnd;
	QuerySetPos(pOpt->uSide, &m_rcAppBar, &abd, FALSE);

	m_bMoving = FALSE;

	if (m_uOriginSide != pOpt->uSide)
	{
		FefreshDesktop();
		m_uOriginSide = pOpt ->uSide;
	}

	CDialog::OnLButtonUp(nFlags, point);
} 

LRESULT CAppBar::OnNcHitTest(CPoint point)
{
	return HTCLIENT;	
}

void CAppBar::FefreshDesktop()
{
	typedef void (__stdcall *PFN_UpdatePerUserSystemParameters)(DWORD dw1, BOOL bEnable);
	HMODULE hUser32Dll=LoadLibrary(_T("User32.dll"));
	if (hUser32Dll!=NULL)
	{
		PFN_UpdatePerUserSystemParameters fnUpdatePerUserSystemParameters=
			(PFN_UpdatePerUserSystemParameters)GetProcAddress(hUser32Dll,"UpdatePerUserSystemParameters");
		if (fnUpdatePerUserSystemParameters!=NULL)
		{
			fnUpdatePerUserSystemParameters(0,TRUE);
		}

		FreeLibrary(hUser32Dll);
	} 
}

void CAppBar::MyRegisterHotKey( UINT uNum1, UINT uNum2 )
{
	m_nHotKeyID = GlobalAddAtom(_T("普证"));
	BOOL m_isKeyRegistered = RegisterHotKey(GetSafeHwnd(), m_nHotKeyID, uNum1, uNum2);
	ASSERT(m_isKeyRegistered != FALSE);
}

void CAppBar::UnMyRegisterHotKey()
{
	UnregisterHotKey(GetSafeHwnd(),m_nHotKeyID);    
	GlobalDeleteAtom(m_nHotKeyID);
}
void CAppBar::getTransparentHwnd( HWND *hwnd )
{
	m_transparent_hwnd = *hwnd;
}



void CAppBar::OnClose()
{
	// TODO: Add your message handler code here and/or call default
if (NULL != m_pOptions)
	{	
		UnRegister();
		UnMyRegisterHotKey();
		delete m_pOptions;
		m_pOptions = NULL;
	}
	CDialog::OnClose();
		
}

LRESULT CAppBar::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	return CDialog::WindowProc(message, wParam, lParam);
}
