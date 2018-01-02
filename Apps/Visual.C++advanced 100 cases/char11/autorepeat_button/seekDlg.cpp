// seekDlg.cpp : implementation file
//

#include "stdafx.h"
#include "seek.h"
#include "seekDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeekDlg dialog

CSeekDlg::CSeekDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSeekDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSeekDlg)
	m_value = 0;
	m_value2 = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSeekDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSeekDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSeekDlg, CDialog)
	//{{AFX_MSG_MAP(CSeekDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeekDlg message handlers

BOOL CSeekDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	myEdit.Create( WS_BORDER | WS_CHILD | WS_VISIBLE, CRect( 60, 60, 100, 80 ), this, 0 );
	myEdit2.Create( WS_BORDER | WS_CHILD | WS_VISIBLE, CRect( 10, 60, 50, 80 ), this, 1 );

	forwardBut.Create( ">>", WS_CHILD | WS_VISIBLE, CRect( 60, 10, 100, 30 ), this, IDC_FORWARD_BUTTON );
	forwardBut.SetParameters( myEdit.GetSafeHwnd(), 0, CSeekButton::FORWARD, 1, 0, 10);

	backwardBut.Create( "<<", WS_CHILD | WS_VISIBLE, CRect( 10, 10, 50, 30 ), this, IDC_BACKWARD_BUTTON );
	backwardBut.SetParameters( myEdit2.GetSafeHwnd(), -100, CSeekButton::BACKWARD, 2, -200, 0);

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSeekDlg::OnPaint() 
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
HCURSOR CSeekDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

