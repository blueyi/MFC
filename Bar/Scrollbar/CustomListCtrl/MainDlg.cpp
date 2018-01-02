// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "MainDlg.h"

LRESULT CMainDlg::OnInitDialog
	(
		UINT /*uMsg*/, 
		WPARAM /*wParam*/, 
		LPARAM /*lParam*/, 
		BOOL& /*bHandled*/
	)
{

#ifdef _WIN32_WCE

	SHINITDLGINFO sid;

	sid.dwMask = SHIDIM_FLAGS;  // This is the only allowed value.
	sid.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;  // Make the DB full screen.
	sid.hDlg = m_hWnd;  // Handle to the dialog box.

	const BOOL rb = SHInitDialog( &sid );
	_ASSERT( rb == TRUE );

	AtlCreateEmptyMenuBar( m_hWnd, true );

	SetForegroundWindow( m_hWnd );

#else

	// center the dialog on the screen
	CenterWindow();

#endif // _WIN32_WCE

	// set icons
	HICON hIcon = (HICON)::LoadImage
		(
			_Module.GetResourceInstance(), 
			MAKEINTRESOURCE(IDR_MAINFRAME), 
			IMAGE_ICON, 
			::GetSystemMetrics(SM_CXICON), 
			::GetSystemMetrics(SM_CYICON), 
			LR_DEFAULTCOLOR
		);
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = (HICON)::LoadImage
		(
			_Module.GetResourceInstance(), 
			MAKEINTRESOURCE(IDR_MAINFRAME), 
			IMAGE_ICON, 
			::GetSystemMetrics(SM_CXSMICON), 
			::GetSystemMetrics(SM_CYSMICON), 
			LR_DEFAULTCOLOR
		);
	SetIcon(hIconSmall, FALSE);

	// Background
	m_Back.LoadBitmap( IDB_CAT );

	// Background brush
	CRect clientRect;
	GetClientRect( clientRect );
	m_BackBrush = GetBkBrush( clientRect );

	// List view
#ifdef _WIN32_WCE
	CRect listRect( CPoint( 10, 30 ), CSize( 160, 160 ) );
#else
	CRect listRect( CPoint( 10, 30 ), CSize( 200, 160 ) );
#endif // _WIN32_WCE
	m_ListCtrl.Create
		( 
			m_hWnd, 
			listRect,
			NULL,
			WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | WS_GROUP
		);
	m_ListBrush = GetBkBrush( listRect );

	// Insert some sample items
	for ( int n = 0; n < 100; ++n )
	{
		CString str;
		str.Format( _T( "Item %d" ), n);
		m_ListCtrl.InsertItem( n, str );
	}

	// Scrollbar
#ifdef _WIN32_WCE
	CRect scrollbarRect( CPoint( 180, 20 ), CSize( 25, 180 ) );
#else
	CRect scrollbarRect( CPoint( 220, 20 ), CSize( 25, 180 ) );
#endif // _WIN32_WCE
	m_Scrollbar.Create
		( 
			m_hWnd, 
			scrollbarRect, 
			NULL, 
			WS_VISIBLE | WS_CHILD | SBS_VERT | WS_GROUP
		);
	m_ScrollbarBrush = GetBkBrush( scrollbarRect );

	// Link the controls to each other
	m_ListCtrl.setVScrollbar( m_Scrollbar );
	m_Scrollbar.setBuddy( m_ListCtrl );

	// Get radio button's brushes
	CRect radioRect;

	CButton radioCustom = GetDlgItem( IDC_CUSTOM );
	_ASSERT( radioCustom != NULL );
	radioCustom.GetWindowRect( radioRect );
	ScreenToClient( radioRect );
	m_RadioCustomBrush = GetBkBrush( radioRect );

	CButton radioStandard = GetDlgItem( IDC_STANDARD );
	_ASSERT( radioStandard != NULL );
	radioStandard.GetWindowRect( radioRect );
	ScreenToClient( radioRect );
	m_RadioStandardBrush = GetBkBrush( radioRect );

	// Select radio button "Custom"
	radioCustom.SetCheck( BST_CHECKED );

	m_ListCtrl.SelectItem( 0 );
	m_ListCtrl.SetFocus();

	return TRUE;
}


LRESULT CMainDlg::OnOK
	(
		WORD /*wNotifyCode*/, 
		WORD wID, 
		HWND /*hWndCtl*/, 
		BOOL& /*bHandled*/
	)
{
	// TODO: Add validation code 
	EndDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnCancel
	(
		WORD /*wNotifyCode*/, 
		WORD wID, 
		HWND /*hWndCtl*/, 
		BOOL& /*bHandled*/
	)
{
	EndDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnDestroy
	(
		UINT /*uMsg*/, 
		WPARAM /*wParam*/, 
		LPARAM /*lParam*/, 
		BOOL& /*bHandled*/
	)
{
	//return CDialogImpl<CMainDlg>::OnDestroy( uMsg, wParam, lParam, bHandled );
	return 0;
}


LRESULT CMainDlg::OnCtlColor
	(
		UINT /*uMsg*/, 
		WPARAM wParam, 
		LPARAM lParam, 
		BOOL& /*bHandled*/
	)
{
	HWND hWnd = ( HWND ) lParam;

	HBRUSH hBrush = NULL;

	if ( hWnd == m_hWnd )
	{
		// Dialog itself
		_ASSERT( m_BackBrush != NULL );
		hBrush = m_BackBrush;
	}
	else if ( hWnd == m_Scrollbar )
	{
		// Scrollbar
		_ASSERT( m_ScrollbarBrush != NULL );
		hBrush = m_ScrollbarBrush;
	}
	else if ( hWnd == m_ListCtrl )
	{
		// List control
		_ASSERT( m_ListBrush != NULL );
		hBrush = m_ListBrush;
	}
	else if ( hWnd == GetDlgItem( IDC_CUSTOM ) )
	{
		// Radio button
		CDCHandle dc = ( HDC ) wParam;
		dc.SetBkMode( TRANSPARENT );
		_ASSERT( m_RadioCustomBrush != NULL );
		hBrush = m_RadioCustomBrush;
	}
	else if ( hWnd == GetDlgItem( IDC_STANDARD ) )
	{
		// Radio button
		CDCHandle dc = ( HDC ) wParam;
		dc.SetBkMode( TRANSPARENT );
		_ASSERT( m_RadioStandardBrush != NULL );
		hBrush = m_RadioStandardBrush;
	}

	return ( LRESULT ) hBrush;
}


HBRUSH CMainDlg::GetBkBrush( const CRect& rect )
{
	// Determine dimension of back bitmap 
	_ASSERT( GetObjectType( m_Back ) == OBJ_BITMAP );
	CSize bmpSize;
	m_Back.GetSize( bmpSize );
	CRect backRect( CPoint( 0, 0 ), bmpSize );

	// To be sure the background bitmap is large enough
#ifdef _DEBUG
	CRect unitedRect;
	unitedRect.UnionRect( backRect, rect );
	_ASSERT( unitedRect == backRect );
#endif // _DEBUG

	CClientDC dc( m_hWnd );

	// Memory DC and bitmap for the whole image
	CDC memDC = CreateCompatibleDC( dc );
	_ASSERT( memDC != NULL );

	// Memory DC and bitmap for the part
	CDC memPartDC = CreateCompatibleDC( dc );
	_ASSERT( memPartDC != NULL );
	CBitmap bitmapPart = CreateCompatibleBitmap( dc, rect.Width(), rect.Height() );
	_ASSERT( bitmapPart != NULL );

	// Select the appropriate bitmaps
	HBITMAP prevBitmap = memDC.SelectBitmap( m_Back );
	HBITMAP prevPartBitmap = memPartDC.SelectBitmap( bitmapPart );

	// Copy the required part of back bitmap
	memPartDC.BitBlt( 0, 0, rect.Width(), rect.Height(), memDC, rect.left, rect.top, SRCCOPY );

	// Deselect the appropriate bitmaps
	memDC.SelectBitmap( prevBitmap );
	memPartDC.SelectBitmap( prevPartBitmap );

	// Create brush
	HBRUSH hBrush = CreatePatternBrush( bitmapPart );
	_ASSERT( hBrush != NULL );

	return hBrush;
}


LRESULT CMainDlg::OnVScroll
	(
		UINT /*uMsg*/, 
		WPARAM wParam, 
		LPARAM lParam, 
		BOOL& /*bHandled*/ 
	)
{
	LRESULT res = TRUE;

	if ( m_ListCtrl != NULL )
	{
		res = m_ListCtrl.SendMessage( WM_VSCROLL, wParam, lParam );
	}

	return res;
}


LRESULT CMainDlg::OnCustom
	(
		WORD /*wNotifyCode*/, 
		WORD /*wID*/, 
		HWND /*hWndCtl*/, 
		BOOL& /*bHandled*/
	)
{
	// Use custom scrollbar
	m_ListCtrl.setVScrollbar( m_Scrollbar );
	m_Scrollbar.setBuddy( m_ListCtrl );

	return 0;
}


LRESULT CMainDlg::OnStandard
	(
		WORD /*wNotifyCode*/, 
		WORD /*wID*/, 
		HWND /*hWndCtl*/, 
		BOOL& /*bHandled*/
	)
{
	// Use standard scrollbar
	HWND hScrollbar = GetDlgItem( IDC_SCROLLBAR1 );
	m_ListCtrl.setVScrollbar( hScrollbar );
	m_Scrollbar.setBuddy( NULL );

	return 0;
}

