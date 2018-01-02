// TreeHelperTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"

#include "TreeHelperTestDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeHelperTestDlg dialog

CTreeHelperTestDlg::CTreeHelperTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTreeHelperTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTreeHelperTestDlg)
	m_sSeparator1 = _T(",");
	m_sSeparator2 = _T("\\");
	m_sEdit1 = _T("Ebene 1,Ebene 2,Ebene 3,Ebene 4,Ebene 5,Letzte Ebene");
	m_sEdit2 = _T("C:\\Winnt\\System32\\Unterverzeichnis\\Noch ein Unterverzeichnis\\Datei.dat");
	m_bBitmap2 = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTreeHelperTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTreeHelperTestDlg)
	DDX_Control(pDX, IDC_EDIT2, m_oEdit2);
	DDX_Control(pDX, IDC_EDIT1, m_oEdit1);
	DDX_Text(pDX, IDC_SEPARATOR1, m_sSeparator1);
	DDX_Text(pDX, IDC_SEPARATOR2, m_sSeparator2);
	DDX_Text(pDX, IDC_EDIT1, m_sEdit1);
	DDX_Text(pDX, IDC_EDIT2, m_sEdit2);
	DDX_Check(pDX, IDC_CHECK1, m_bBitmap2);
	//}}AFX_DATA_MAP

	if ( pDX->m_bSaveAndValidate )
	{
		m_oEdit1.SetHelperFlags( m_sSeparator1, IDB_TREEICONS + m_bBitmap2 );
		m_oEdit2.SetHelperFlags( m_sSeparator2 );
	}

}

BEGIN_MESSAGE_MAP(CTreeHelperTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTreeHelperTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeHelperTestDlg message handlers

BOOL CTreeHelperTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTreeHelperTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

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
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTreeHelperTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
