// IconLBDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IconLBDemo.h"
#include "IconLBDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIconLBDemoDlg dialog

CIconLBDemoDlg::CIconLBDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIconLBDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIconLBDemoDlg)
	m_Str = _T("Hello World");
	m_Img = 0;
	m_Check = TRUE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIconLBDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIconLBDemoDlg)
	DDX_Control(pDX, IDC_CHANGEICON, m_ChangeIcon);
	DDX_Control(pDX, IDC_ICONLISTBOX, m_ListBox);
	DDX_Text(pDX, IDC_NAME, m_Str);
	DDX_Text(pDX, IDC_IMAGE_NUM, m_Img);
	DDV_MinMaxInt(pDX, m_Img, 0, 19);
	DDX_Check(pDX, IDC_IMG_LIST, m_Check);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIconLBDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CIconLBDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_INSERT, OnInsert)
	ON_BN_CLICKED(IDC_CHANGEICON, OnChangeicon)
	ON_BN_CLICKED(IDC_IMG_LIST, OnCheckImageList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIconLBDemoDlg message handlers

BOOL CIconLBDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	InitImageLists();	
	m_ListBox.SetImageList(&m_imgNormal);
	
	for(int i = 0; i < 20 ; i++ )
		m_ListBox.AddString( "Hello World" , i );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIconLBDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIconLBDemoDlg::OnPaint() 
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
HCURSOR CIconLBDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CIconLBDemoDlg::InitImageLists()
{

	CBitmap bmp;
	// normal tree images
	m_imgNormal.Create(16,
				 15,
				 TRUE,
				 20,	// number of initial images
				 20);

	ASSERT(m_imgNormal.m_hImageList);

	bmp.LoadBitmap(IDB_LB_IMG);
	m_imgNormal.Add( &bmp, RGB(255,255,255));
	bmp.DeleteObject();
}


void CIconLBDemoDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData())
	{
		if(!m_Str.IsEmpty())
			m_ListBox.AddString(m_Str,m_Img);
		else
			AfxMessageBox("Enter a String!");
	}
}

void CIconLBDemoDlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	int iSel = m_ListBox.GetCurSel();
	if( iSel != LB_ERR )
		m_ListBox.DeleteString( iSel );
	else
		AfxMessageBox("Select an Item in the List Box!");

}

void CIconLBDemoDlg::OnInsert() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData())
	{
		if( m_Str.IsEmpty() )
		{
			AfxMessageBox("Enter a String!");
			return;
		}
		int iSel = m_ListBox.GetCurSel();
		if( iSel != LB_ERR )
			m_ListBox.InsertString(iSel, m_Str , m_Img);
		else
			AfxMessageBox("Select an Item in the List Box!");
	}
}

void CIconLBDemoDlg::OnChangeicon() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData())
	{
		int iSel = m_ListBox.GetCurSel();
		if(iSel != LB_ERR )
			m_ListBox.SetItemImage(iSel,m_Img);
		else
			AfxMessageBox("Select an Item in the List Box!");
	}
}

void CIconLBDemoDlg::OnCheckImageList() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData())
	{
		if( m_Check )
			m_ListBox.SetImageList(&m_imgNormal);
		else
			m_ListBox.SetImageList();
		m_ListBox.RedrawWindow();
	}
	else
	{
		((CButton *)GetDlgItem(IDC_IMG_LIST))->SetCheck(m_Check);
	}
}
