//////////////////////////////////////////////////////////////////////////
//PathDialog.h file
//
//Written by Nguyen Tan Hung <tanhung@yahoo.com>
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PathDialog.h"
#include <shlwapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_FOLDERTREE		0x3741
#define IDC_TITLE			0x3742
#define IDC_STATUSTEXT		0x3743
#define IDC_NEW_EDIT_PATH	0x3744


BEGIN_MESSAGE_MAP(CPathDialog, CWnd)
        ON_BN_CLICKED(IDOK, OnOK)
		ON_EN_CHANGE(IDC_NEW_EDIT_PATH, OnChangeEditPath)
END_MESSAGE_MAP()

void CPathDialog::OnOK()
{
	// get path name
	GetDlgItemText( IDC_NEW_EDIT_PATH, m_szPathName, MAX_PATH );

	// validate its existence
	if( ( ::GetFileAttributes( m_szPathName ) & FILE_ATTRIBUTE_DIRECTORY ) != 0 )
	{
		m_bGetSuccess = TRUE;
		EndDialog( m_hWnd, IDOK );
	}
	else
	{
		GetDlgItem( IDC_NEW_EDIT_PATH )->SetFocus();
	}
}

void CPathDialog::OnChangeEditPath()
{
	GetDlgItemText( IDC_NEW_EDIT_PATH,
					m_szPathName, 
					MAX_PATH );

	BOOL bEnableOKButton = ( lstrlen( m_szPathName ) > 0 );
	SendMessage( BFFM_ENABLEOK, 0, bEnableOKButton );
}
/////////////////////////////////////////////////////////////////////////////
// CPathDialog dialog
CPathDialog::CPathDialog(LPCTSTR lpszCaption, 
						 LPCTSTR lpszTitle, 
						 LPCTSTR lpszInitialPath, 
						 CWnd* pParent)
{
	m_hWnd = NULL;
    m_bParentDisabled = FALSE;

    // Get the true parent of the dialog
    m_pParentWnd = CWnd::GetSafeOwner( pParent );

	// reset buffers
	::ZeroMemory( m_lpszTitle, sizeof(lpszTitle) );
	::ZeroMemory( m_lpszCaption, sizeof(m_lpszCaption) );
	::ZeroMemory( m_lpszInitialPath, sizeof(m_lpszInitialPath) );
	::ZeroMemory( m_szPathName, sizeof(m_szPathName) );
	::ZeroMemory( &m_bi, sizeof(BROWSEINFO) );

	// get user specified caption
	if( lpszCaption != NULL )
	{
		StrCpy( m_lpszCaption, lpszCaption );
	}

	// get initial path
	if( lpszInitialPath != NULL )
	{
		StrCpy( m_lpszInitialPath, lpszInitialPath );
	}

	// get title
	if( lpszTitle != NULL )
	{
		StrCpy( m_lpszTitle, lpszTitle );
	}
	
	m_bi.hwndOwner = ( m_pParentWnd == NULL ) ? NULL : m_pParentWnd->GetSafeHwnd();
	m_bi.pszDisplayName = 0;
	m_bi.pidlRoot = 0;
	m_bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
	m_bi.lpfn = BrowseCallbackProc;
	m_bi.lpszTitle = m_lpszTitle;
}


/////////////////////////////////////////////////////////////////////////////
// CPathDialog message handlers

CString CPathDialog::GetPathName()
{
	return CString(m_szPathName);
}

int CALLBACK CPathDialog::BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM pData) 
{

	CPathDialog*  pDlg = (CPathDialog*)pData;

	switch(uMsg) 
	{
		case BFFM_INITIALIZED: 
		{
			RECT rc;
			HWND hEdit;
			HFONT hFont;

			if( pDlg->m_lpszCaption != NULL )
			{
				::SetWindowText( hwnd, pDlg->m_lpszCaption );
			}

			VERIFY( pDlg->SubclassWindow( hwnd ) );
			::ShowWindow( ::GetDlgItem( hwnd, IDC_STATUSTEXT ), SW_HIDE );

			::GetWindowRect( ::GetDlgItem( hwnd, IDC_FOLDERTREE ), &rc );
			rc.bottom = rc.top - 4;
			rc.top = rc.bottom - 23;
			::ScreenToClient( hwnd, (LPPOINT)&rc );
			::ScreenToClient( hwnd, ( (LPPOINT)&rc ) + 1 );
			hEdit = ::CreateWindowEx(	WS_EX_CLIENTEDGE,
										TEXT("EDIT"), 
										TEXT(""),
										WS_CHILD|WS_TABSTOP|WS_VISIBLE|ES_AUTOHSCROLL,
										rc.left, 
										rc.top, 
										rc.right - rc.left, 
										rc.bottom - rc.top, 
										hwnd, 
										NULL, 
										NULL, 
										NULL	);
			::SetWindowLong( hEdit, GWL_ID, IDC_NEW_EDIT_PATH );
			::ShowWindow( hEdit, SW_SHOW );

			hFont = (HFONT)::SendMessage( hwnd, WM_GETFONT, 0, 0 );
			::SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0) );

			// set initial path for display
			if( lstrlen( pDlg->m_lpszInitialPath ) == 0 )
			{
				::GetCurrentDirectory( MAX_PATH, pDlg->m_lpszInitialPath );
			}

			// wParam is TRUE since you are passing a path.
			// It would be FALSE if you were passing a pidl.
			::SendMessage( hwnd, BFFM_SETSELECTION, TRUE, (LPARAM)pDlg->m_lpszInitialPath );
			break;
		}
		case BFFM_SELCHANGED:
		{
			TCHAR szSelection[MAX_PATH];
			if( !::SHGetPathFromIDList( (LPITEMIDLIST)lParam, szSelection ) ) //||
//				szSelection[1] !=':' )
			{
				szSelection[0] = '\0';
				::SendMessage( hwnd, BFFM_ENABLEOK, 0, FALSE );
			}
			else
			{
				::SendMessage( hwnd, BFFM_ENABLEOK, 0, TRUE );
			}

			::SendMessage( hwnd, BFFM_SETSTATUSTEXT, 0, (LPARAM)szSelection );
			::SetWindowText( ::GetDlgItem( hwnd, IDC_NEW_EDIT_PATH ), szSelection );
			break;
		}
		default:
			break;
	}
	return 0;
}

int CPathDialog::DoModal() 
{
	LPITEMIDLIST	pidl;
	LPMALLOC		pMalloc;

	TCHAR szPathTemp[MAX_PATH] = { '\0' };
    m_bi.lpfn = BrowseCallbackProc;  // address of callback function
    m_bi.lParam = (LPARAM)this;      
	m_bi.pszDisplayName = szPathTemp;


	int iResult=-1;
	if( SUCCEEDED (SHGetMalloc( &pMalloc ) ) )
	{
//		if((m_pParentWnd!=NULL) && m_pParentWnd->IsWindowEnabled())
//		{
//		  m_pParentWnd->EnableWindow(FALSE);
//		  m_bParentDisabled = TRUE;
//		}
		m_bGetSuccess = FALSE;
		pidl = SHBrowseForFolder( &m_bi );
		if ( pidl != NULL) 
		{
			//not need do this because OnOK function did
			//bSucceeded = SHGetPathFromIDList(pidl, m_szPathName);
			// In C++: 
			pMalloc->Free( pidl );
			//In C:
			//pMalloc->lpVtbl->Free(pMalloc,pidl);
			//pMalloc->lpVtbl->Release(pMalloc);
		}

		if( m_bGetSuccess )
		{
			iResult = IDOK;
		}

		pMalloc->Release();
	}

    if( m_bParentDisabled && ( m_pParentWnd != NULL ) )
	{
		m_pParentWnd->EnableWindow( TRUE );
	}

    m_bParentDisabled = FALSE;

	return iResult;
}

