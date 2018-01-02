// TreeDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TreeDemo.h"
#include "TreeDemoDlg.h"
#include ".\treedemodlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTreeDemoDlg dialog

CTreeDemoDlg::CTreeDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTreeDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTreeDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_ctrlTree);
}

BEGIN_MESSAGE_MAP(CTreeDemoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTreeDemoDlg message handlers

BOOL CTreeDemoDlg::OnInitDialog()
{
	HTREEITEM	hItem = NULL;
	HTREEITEM	hRoot = NULL;
	HTREEITEM	hChild = NULL;
	CString		strLabel;
	CRect		rTemp;
	//

	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// A partial scrollbar to give us our gripper...
	this->GetClientRect( rTemp );
	rTemp.left = rTemp.right - ::GetSystemMetrics(SM_CXVSCROLL);
	rTemp.top = rTemp.bottom - ::GetSystemMetrics(SM_CYVSCROLL);
	m_ScrollGripper.Create( WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | SBS_SIZEBOX | SBS_SIZEGRIP | SBS_SIZEBOXBOTTOMRIGHTALIGN, rTemp, this, (UINT) IDC_STATIC );

	// Hook up a sample image list
	m_ILTree.Create( IDB_BITMAP1, 16, 0, RGB(255,0,255) );
	m_ctrlTree.SetImageList( &m_ILTree, TVSIL_NORMAL );

	// Plug some sample items into the tree
	hItem = m_ctrlTree.InsertItem( _T("Root Item"), 0, 0, TVI_ROOT );
	hRoot = hItem;
	hItem = m_ctrlTree.InsertItem( _T("1st Child of root item"), hRoot );
	m_ctrlTree.InsertItem( _T("2nd Child of root item"), hRoot );
	hItem = m_ctrlTree.InsertItem( _T("Further Nested child item"), hItem );
	for ( int i = 1; i <= 100; i++ )
	{
		strLabel.Format( _T("Leaf item number #%03d"), i );
		hChild = m_ctrlTree.InsertItem( strLabel, 0, 0, hItem );
		m_ctrlTree.SetCheck( hChild, i % 2 );
	}// end of loop
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTreeDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTreeDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTreeDemoDlg::OnSize(UINT nType, int cx, int cy)
{
	CRect	rCtrl;
	CRect	rDlg;
	CRect	rCtrlOrig;
	//

	CDialog::OnSize(nType, cx, cy);

	// Get dialog's client rectangle...
	this->GetClientRect( rDlg );

	// Move the pseudo gripper if appropriate...
	if ( ::IsWindow(m_ScrollGripper.m_hWnd) )
	{
		rCtrl = rDlg;
		rCtrl.left = rCtrl.right - ::GetSystemMetrics(SM_CXVSCROLL);
		rCtrl.top = rCtrl.bottom - ::GetSystemMetrics(SM_CYVSCROLL);
		m_ScrollGripper.GetWindowRect( rCtrlOrig );
		this->ScreenToClient( rCtrlOrig );
		if ( rCtrlOrig != rCtrl )
			m_ScrollGripper.MoveWindow( rCtrl );
	}
	
	if ( ::IsWindow(m_ctrlTree.m_hWnd) )
	{
		m_ctrlTree.GetWindowRect( rCtrlOrig );
		this->ScreenToClient( rCtrlOrig );
		
		rCtrl = rCtrlOrig;
		rCtrl.right = rDlg.right - rCtrl.left;
		rCtrl.bottom = rDlg.bottom - rCtrl.top;
		if ( rCtrlOrig != rCtrl )
			m_ctrlTree.MoveWindow( rCtrl );
	}
}
