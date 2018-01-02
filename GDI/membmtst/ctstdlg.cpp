// ctstdlg.cpp : implementation file
//

#include "stdafx.h"
#include "membmtst2.h"
#include "ctstdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//string conts
#define STR_RESNAME_PFX _T("BMP Name: ")
#define STR_RESID_PFX _T("BMP ResID: ")

CStringList CTstDlg::m_slstBmpResNames;

/////////////////////////////////////////////////////////////////////////////
// CTstDlg dialog

CTstDlg::CTstDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTstDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTstDlg)
	m_iBmpUsage = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTstDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTstDlg)
	DDX_Control(pDX, IDC_RESBMPSELECTOR, m_cbxBmpResSelector);
	DDX_Radio(pDX, IDC_BMPUSAGE, m_iBmpUsage);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTstDlg, CDialog)
	//{{AFX_MSG_MAP(CTstDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_RESBMPSELECTOR, OnSelchangeResbmpselector)
	ON_BN_CLICKED(IDC_BMPUSAGE, OnBmpusage)
	ON_BN_CLICKED(IDC_RADIO2, OnBmpusage)
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTstDlg message handlers

BOOL CTstDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	PopulateBmpResourceSelector();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTstDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if(IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();

		if( !m_iBmpUsage ) // actually if it equals to 0
			m_Bitmap.Draw( dc, 20, 200 );
	}
}

BOOL CTstDlg::OnEraseBkgnd( CDC* pDC )
{
	if( m_iBmpUsage && m_Bitmap ) // actually if it equals to 1
	{
		CRect rClient;
		GetClientRect( rClient );
		m_Bitmap.Fill( *pDC, rClient.left, rClient.top, rClient.right, rClient.bottom );
		return TRUE;
	}
	else //otherwise do ordinary backgroud drawing
		return CDialog::OnEraseBkgnd( pDC );
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTstDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CALLBACK CTstDlg::EnumBmpResNames( HMODULE hModule, LPCTSTR lpszType, LPTSTR lpszName, LPARAM lParam )
{
	if( lpszType == MAKEINTRESOURCE(RT_BITMAP) )
	{
		CString strTmp;

		if( (ULONG)lpszName & 0xFFFF0000 ) //actual name
			strTmp.Format( STR_RESNAME_PFX _T("%s"), lpszName );
		else //integer ID in lpsz
			strTmp.Format( STR_RESID_PFX _T("%u"), (ULONG)lpszName );

		m_slstBmpResNames.AddTail( strTmp );
	}

	return TRUE;
}

void CTstDlg::PopulateBmpResourceSelector()
{
	//clear string list first
	m_slstBmpResNames.RemoveAll();
	
	//enumerate all bitmap resources in current module
	EnumResourceNames( NULL, RT_BITMAP, EnumBmpResNames, NULL);

	//assign string list to combo list
	m_cbxBmpResSelector.ResetContent();
	
	POSITION posCur = m_slstBmpResNames.GetHeadPosition();
	while( posCur != NULL )
	{
		CString strTmp = m_slstBmpResNames.GetNext(posCur);
		int iIdx = m_cbxBmpResSelector.AddString( strTmp );
		
		//set data to bmp id if this item is resource id
		if( strTmp.Find(STR_RESID_PFX) >= 0 )
		{
			strTmp = strTmp.Right( strTmp.GetLength() - _tcsclen(STR_RESID_PFX) );
			LPSTR strStop;
			DWORD dwResID = _tcstoul(strTmp, &strStop, 10);
			m_cbxBmpResSelector.SetItemData( iIdx, dwResID );
		}
	}
}

void CTstDlg::OnSelchangeResbmpselector() 
{
	// upload new bitmap and redraw it
	UpdateBitmap();	
}

void CTstDlg::OnBmpusage() 
{
	CDataExchange dataEx( this, TRUE );

	//get radiogroup data
	int iTmp;
	DDX_Radio(&dataEx, IDC_BMPUSAGE, iTmp);

	if( iTmp != m_iBmpUsage ) //eliminate unneeded updates
	{
		m_iBmpUsage = iTmp;

		//force repaint entire window
		Invalidate();
	}
}

void CTstDlg::UpdateBitmap()
{
	m_Bitmap.Cleanup();
	//if selected item contains data - use it, otherwise use name part
	int iIdx = m_cbxBmpResSelector.GetCurSel();
	if( iIdx != CB_ERR )
	{
		DWORD dwData = m_cbxBmpResSelector.GetItemData(iIdx);
		HINSTANCE hInst = (HINSTANCE)GetWindowLong( GetSafeHwnd(), GWL_HINSTANCE );
		if( dwData )
			m_Bitmap.Create(hInst, dwData);
		else
		{
		  CString strTmp;
			m_cbxBmpResSelector.GetLBText(iIdx, strTmp);
			//extract actual bitmap resource name from selection string
			m_Bitmap.Create(hInst, strTmp.Right(strTmp.GetLength() - _tcsclen(STR_RESNAME_PFX)) );
		}
	}

	Invalidate();
}

