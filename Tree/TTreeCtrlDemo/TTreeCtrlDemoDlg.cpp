// TTreeCtrlDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TTreeCtrlDemo.h"
#include "TTreeCtrlDemoDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


TTipItemData::TTipItemData()
{
	strTool = "";
	pos = NULL;
};
CString TTipItemData::GetToolTipString()
{
	return strTool;
};

/////////////////////////////////////////////////////////////////////////////
// CTTreeCtrlDemoDlg dialog

CTTreeCtrlDemoDlg::CTTreeCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTTreeCtrlDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTTreeCtrlDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTTreeCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTTreeCtrlDemoDlg)
	DDX_Control(pDX, IDC_TREE1, m_Tree);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTTreeCtrlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CTTreeCtrlDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTTreeCtrlDemoDlg message handlers

BOOL CTTreeCtrlDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	HTREEITEM level1,level2;
	


	TTipItemData* p ; 
	p  = new TTipItemData;
	p->strTool = "is ran";
	
	level1= m_Tree.InsertItem("");
	m_Tree.SetItemText(level1,"First Name");
	m_Tree.SetItemData(level1,DWORD(p));
 

	p  = new TTipItemData;
	p->strTool = "is wainstein";
	level2= m_Tree.InsertItem("");
	m_Tree.SetItemText(level2,"Last Name");
	m_Tree.SetItemData(level2,DWORD(p));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTTreeCtrlDemoDlg::OnPaint() 
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
HCURSOR CTTreeCtrlDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
