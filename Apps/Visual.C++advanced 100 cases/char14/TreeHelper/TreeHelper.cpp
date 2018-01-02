// TreeHelper.cpp : implementation file
//

#include "stdafx.h"

#include "TreeHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	ID_KILLTIMER	3333
#define	ID_KILLTIMER_TIMEOUT	1000 // 1 sec/ Line
/////////////////////////////////////////////////////////////////////////////
// CTreeHelper

CTreeHelper::CTreeHelper(UINT nBitmapID/*= 0*/)
{
	m_pFocusWnd = NULL;
	m_pimagelist = NULL;
	m_nBitmapID = nBitmapID;
}

CTreeHelper::~CTreeHelper()
{
	if ( m_pimagelist )
		delete m_pimagelist;
}


BEGIN_MESSAGE_MAP(CTreeHelper, CTreeCtrl)
	//{{AFX_MSG_MAP(CTreeHelper)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeHelper message handlers


void CTreeHelper::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect rct;
	GetClientRect( &rct );
	rct.InflateRect( rct.Width() /4, rct.Height() /4 );
	if ( rct.PtInRect( point ) == FALSE )
	{
		DestroyWindow();
		return;
	}
	else
	{
		KillTimer( ID_KILLTIMER );
		SetTimer( ID_KILLTIMER, ID_KILLTIMER_TIMEOUT*GetCount(), NULL );
	}
	
	CTreeCtrl::OnMouseMove(nFlags, point);
}



BOOL CTreeHelper::DestroyWindow() 
{
	ReleaseCapture();
	if ( m_pFocusWnd )
		m_pFocusWnd->SetFocus();

	BOOL bRet = CTreeCtrl::DestroyWindow();
	return bRet ;
}


void CTreeHelper::OnLButtonDown(UINT nFlags, CPoint point) 
{
}

void CTreeHelper::OnRButtonDown(UINT nFlags, CPoint point) 
{
}


void	CTreeHelper::ShowTree( CString* i_psPfad, LPCTSTR i_psSeparator, CWnd* pParent, CPoint* i_pPoint )
{
	if ( ::IsWindow( m_hWnd ) )
		return ;

	if ( i_psPfad == NULL  || i_psSeparator == NULL )
	{
		DestroyWindow();
		delete this;
		return;
	}

	if ( i_psPfad->IsEmpty() || *i_psSeparator  == '\0' )
	{
		DestroyWindow();
		delete this;
		return;
	}

	int pos = i_psPfad->Find( i_psSeparator );
	if ( 	pos <= 0 )
	{
		DestroyWindow();
		delete this;
		return;
	}

	CWnd* pMain = CWnd::GetDesktopWindow();

	CRect rctWnd;
	pParent->GetWindowRect( &rctWnd );
	m_pFocusWnd = GetFocus();

	pMain->ScreenToClient( &rctWnd );

	CPoint ptParent( i_pPoint->x + rctWnd.left -3, i_pPoint->y + rctWnd.top -3 );
	CRect rct( ptParent.x, ptParent.y, ptParent.x + 500, ptParent.y+ 300);

	Create( WS_BORDER|TVS_HASLINES | TVS_NOTOOLTIPS  , rct, pMain, -1 );
	if ( m_pimagelist )
	{
		SetImageList( m_pimagelist, TVSIL_NORMAL);
		SetImageList( m_pimagelist, TVSIL_STATE);
	}

	CString sAktToken;
	CString sPfad( *i_psPfad);
	int iLenPfadSeparator = strlen( i_psSeparator);

	int indent = GetIndent();
	HTREEITEM hParentItem = TVI_ROOT;
	int length[100];
	int idx = 0;
	CDC *pDc = GetDC();

	while ( pos > 0 )
	{
		sAktToken = 	sPfad.Left( pos );
		sPfad = sPfad.Right( sPfad.GetLength() - pos - iLenPfadSeparator );
		HTREEITEM newItem = InsertItem( sAktToken,  hParentItem );

		if ( m_pimagelist )
		{
			SetItemImage ( newItem, 0, 0 );
		}
		length[idx++] = pDc->GetTextExtent( sAktToken).cx;

		pos =  sPfad.Find( i_psSeparator );
		if ( pos < 0 )
		{
			newItem = InsertItem( sPfad,  newItem );
			if ( m_pimagelist )
			{
				SetItemImage ( newItem, 1, 1 );
			}
			length[idx++] = pDc->GetTextExtent( sPfad ).cx;
		}
		hParentItem = newItem;
	}

	int maxL = 0;
	int len = 0;
	for ( int nLines = 0; nLines < idx ; nLines++ )
	{
		len = length[nLines] + (nLines+1) * indent;
		maxL = len > maxL ? len : maxL;
	}

	CRect wndRect;
	Expand (hParentItem, TVE_EXPAND);
	SetItemState(  hParentItem, TVIS_SELECTED , 0 );
	Select( hParentItem, TVGN_CARET );
	GetItemRect( hParentItem, &wndRect, TRUE );

	wndRect.top = 0;
	wndRect.left = 0;
	wndRect.right = (wndRect.right > maxL)? wndRect.right : maxL;
	wndRect.right +=indent;
	wndRect.bottom += 20;

	MoveWindow( rct.left, rct.top, wndRect.right, wndRect.bottom , FALSE );
	SetWindowPos( &wndTopMost ,0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
	DWORD style = GetWindowLong( m_hWnd, GWL_EXSTYLE ); 
	SetWindowLong( m_hWnd, GWL_EXSTYLE, style | WS_EX_TOPMOST );//|WS_EX_TOOLWINDOW
	SetCapture();
	SetFocus();
	ShowWindow( SW_SHOW );
	SetTimer( ID_KILLTIMER, ID_KILLTIMER_TIMEOUT*nLines, NULL );
}

int CTreeHelper::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if ( m_nBitmapID > 0 )
	{
		m_pimagelist = new CImageList();
		CBitmap bmp;
		bmp.LoadBitmap ( m_nBitmapID);

		BITMAP 	bm;						//	BITMAP struct 
		bmp.GetBitmap( &bm ); //	fill bitmapstruct 

		bm.bmWidth /= 2;

		m_pimagelist ->Create (m_nBitmapID, bm.bmWidth , 1, RGB( 255, 0, 255 )); // magentafarbener hintergrund
	}
	
	return 0;
}

void CTreeHelper::PostNcDestroy() 
{
	CTreeCtrl::PostNcDestroy();
	delete this;
}



void CTreeHelper::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if ( nIDEvent == ID_KILLTIMER )
	{
		KillTimer( ID_KILLTIMER );
		DestroyWindow();
		return;
	}
	CTreeCtrl::OnTimer(nIDEvent);
}

void CTreeHelper::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	KillTimer( ID_KILLTIMER );
	SetTimer( ID_KILLTIMER, ID_KILLTIMER_TIMEOUT*GetCount(), NULL );
	CTreeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}
