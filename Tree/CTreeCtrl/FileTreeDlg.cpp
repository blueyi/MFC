// FileTreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileTree.h"
#include "FileTreeDlg.h"

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
// CFileTreeDlg dialog

CFileTreeDlg::CFileTreeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileTreeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileTreeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileTreeDlg)
	DDX_Control(pDX, IDC_TREE1, m_Tree);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileTreeDlg, CDialog)
	//{{AFX_MSG_MAP(CFileTreeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileTreeDlg message handlers

BOOL CFileTreeDlg::OnInitDialog()
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
	AddFile( "成绩表", NULL );
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFileTreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFileTreeDlg::OnPaint() 
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
HCURSOR CFileTreeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFileTreeDlg::AddFile(CString StrPath, HTREEITEM faItem )
				//StrPath为传递过来的目录层次，本次函数调用中搜索的文件都是它的下一层的。
				//faItem为传递过来的Tree节点，本次函数调用中添加的Tree节点都是它的子节点。
{
	CFileFind OneFile;
	CString FName, DirName;
	BOOL BeWorking; 
	HTREEITEM NewItem;	

	DirName = StrPath+"\\*.*";
	BeWorking = OneFile.FindFile( DirName );
	while ( BeWorking ) {  		//BeWorking非零，指找了文件或目录

		//查找同级的目录
		BeWorking = OneFile.FindNextFile();

		if ( OneFile.IsDirectory() && !OneFile.IsDots() )      //如果查找的结果是目录又不是".."或"."
		{	
			//向Tree1中添加目录;
			DirName = OneFile.GetFilePath();
			FName = OneFile.GetFileTitle(); 
			//IDC_TREE1
			NewItem = m_Tree.InsertItem( FName, faItem );    //NewItem取得节点，其目的是为了下一层中
											 //添加节点方便，递归时把它传过去。
			//进入下一层递归调用。
			AddFile(DirName, NewItem);
		}

		//退出递归时，到了这里！！！
		if ( !OneFile.IsDirectory() && !OneFile.IsDots() )     //如果查找结果是文件
		{
			//向Tree1中添加文件
			FName = OneFile.GetFileTitle();			 //注意这里用的是GetFileTitle,因为
											 //这里是添加文件。
			m_Tree.InsertItem( FName, faItem );
		}

		
		//BeWorking = OneFile.FindNextFile();

	}// end of while
	
	OneFile.Close();								//记着用完CFileFild实例要关闭
}
