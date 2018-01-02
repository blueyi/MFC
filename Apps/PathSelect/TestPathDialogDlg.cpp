// TestPathDialogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestPathDialog.h"
#include "TestPathDialogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestPathDialogDlg dialog

CTestPathDialogDlg::CTestPathDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestPathDialogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestPathDialogDlg)
	m_strPathName = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	::GetCurrentDirectory(MAX_PATH, m_strPathName.GetBuffer(MAX_PATH));
	m_strPathName.ReleaseBuffer();
}

void CTestPathDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestPathDialogDlg)
	DDX_Control(pDX, IDC_PATH, m_ctrlPathName);
	DDX_Text(pDX, IDC_PATH, m_strPathName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestPathDialogDlg, CDialog)
	//{{AFX_MSG_MAP(CTestPathDialogDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSER, OnBrowser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestPathDialogDlg message handlers

BOOL CTestPathDialogDlg::OnInitDialog()
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

void CTestPathDialogDlg::OnPaint() 
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
HCURSOR CTestPathDialogDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


#include "PathDialog.h"
void CTestPathDialogDlg::OnBrowser() 
{
	CString strPath;
	CString strYourCaption(_T("Your caption here..."));
	CString strYourTitle(_T("Your tilte here..."));

	m_ctrlPathName.GetWindowText(strPath);

	CPathDialog dlg(strYourCaption, strYourTitle, strPath);

	if(dlg.DoModal()==IDOK)
	{
		m_ctrlPathName.SetWindowText(dlg.GetPathName());
	}
}


void CTestPathDialogDlg::OnOK() 
{
	CString strPath;
	m_ctrlPathName.GetWindowText(strPath);

	if(CPathDialog::MakeSurePathExists(strPath)==0)
	{
		CDialog::OnOK();
	}
}
