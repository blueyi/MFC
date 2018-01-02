// sampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sample.h"
#include "sampleDlg.h"
#include "EditList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


char *Product[] = 
{
"Ball", 
"Deordorant",
"Pin",
"Net"
};

char *Price[] = 
{
"12.00$",	//	"Ball", 
"13.50$",	//	"Deordorant"
"2.00$",	//	"Pin",
"100.00$",	//	"Net"
};

char *ID[] = 
{
"VV120",	//	"Ball", 
"CC321",	//	"Deordorant"
"BGTY6",	//	"Pin",
"XCDCD",	//	"Net"
};

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
// CSampleDlg dialog

CSampleDlg::CSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSampleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSampleDlg)
	DDX_Control(pDX, IDC_LIST, m_cList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSampleDlg, CDialog)
	//{{AFX_MSG_MAP(CSampleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDADD, OnAdd)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg message handlers

BOOL CSampleDlg::OnInitDialog()
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
	BuildList();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSampleDlg::OnPaint() 
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
HCURSOR CSampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// this function is sent to CEditList 
// there it is used to determine which type of ctrl to create 
// when cell is being edited
static int _List_Type( int col )
{
	if ( col == 0 )
		return CEditList::eCombo;
	if ( col == 4)
		return CEditList::eSlider;
	// else :
	return CEditList::eEdit;
}

void CSampleDlg::BuildList()
{
	m_cList.SetExtendedStyle( m_cList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

	// determine the columns 
	m_cList.InsertColumn( 0, "Product");
	m_cList.InsertColumn( 1, "ID");
	m_cList.InsertColumn( 2, "Price");
	m_cList.InsertColumn( 3, "Amount");
	m_cList.InsertColumn( 4, "Slider");
	
	m_cList.SetColumnWidth( 0, 100);
	m_cList.SetColumnWidth( 1, 50);
	m_cList.SetColumnWidth( 2, 70);
	m_cList.SetColumnWidth( 3, 70);
	m_cList.SetColumnWidth( 4, 70);

	// set functionality of list according to column
	m_cList.SetColumnType ( (fGetType)_List_Type );	

	// insert string elements  for the ComboBox : 
	for ( int i=0 ; i < 4 ; i++)
		m_cList.m_strList.AddTail( Product[i]);

	// insert a dummy row
	InsertEmpty();


}




void CSampleDlg::InsertEmpty()
{
	int num = m_cList.GetItemCount();

	m_cList.InsertItem( num, "..." );
}

void CSampleDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	InsertEmpty();	
}

void CSampleDlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
    int     iItem = pNMListView->iItem;
    int     iSubItem = pNMListView->iSubItem;
	
	// retrieve the ProductName & load corresponding cells with 
	// ProductPrice and ProductID
	CString sProductName = m_cList.GetItemText( iItem, 0 ); 
	
	for ( int i = 0 ;  i < 4; i++)
	{
		if ( sProductName == Product[i] )
		{
			
			m_cList.SetItemText( iItem, ePrice, Price[i]);
			m_cList.SetItemText( iItem, eID, ID[i]);
			break;
		}
	}
	
	
	*pResult = 0;
}



