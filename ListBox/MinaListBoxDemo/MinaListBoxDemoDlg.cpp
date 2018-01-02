// MinaListBoxDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MinaListBoxDemo.h"
#include "MinaListBoxDemoDlg.h"

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
// CMinaListBoxDemoDlg dialog

CMinaListBoxDemoDlg::CMinaListBoxDemoDlg(CWnd* pParent /*=NULL*/)
: CDialog(CMinaListBoxDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMinaListBoxDemoDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMinaListBoxDemoDlg::DoDataExchange(CDataExchange* pDX)
{	
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMinaListBoxDemoDlg)
	DDX_Control(pDX, IDC_LIST_OWNER_DRAW, m_OwnerListBox);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMinaListBoxDemoDlg, CDialog)
//{{AFX_MSG_MAP(CMinaListBoxDemoDlg)
ON_WM_SYSCOMMAND()
ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMinaListBoxDemoDlg message handlers

BOOL CMinaListBoxDemoDlg::OnInitDialog()
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
	
	// Set the icon for this dialog. The framework does this automatically
	// When the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Adding Icons and the Names of the Icons to the list box
	m_OwnerListBox.Add("Cafe", AfxGetApp()->LoadIcon(IDI_CAFE));
	m_OwnerListBox.Add("Printer", AfxGetApp()->LoadIcon(IDI_PRINTER));
	m_OwnerListBox.Add("Rose", AfxGetApp()->LoadIcon(IDI_ROSE));
	m_OwnerListBox.Add("Monitor", AfxGetApp()->LoadIcon(IDI_MONITOR));
    m_OwnerListBox.Add("Cafe", AfxGetApp()->LoadIcon(IDI_CAFE));
    m_OwnerListBox.Add("Printer", AfxGetApp()->LoadIcon(IDI_PRINTER));
    m_OwnerListBox.Add("Rose", AfxGetApp()->LoadIcon(IDI_ROSE));
    m_OwnerListBox.Add("Monitor", AfxGetApp()->LoadIcon(IDI_MONITOR));

    m_OwnerListBox.Add("Cafe", AfxGetApp()->LoadIcon(IDI_CAFE));
    m_OwnerListBox.Add("Printer", AfxGetApp()->LoadIcon(IDI_PRINTER));
    m_OwnerListBox.Add("Rose", AfxGetApp()->LoadIcon(IDI_ROSE));
    m_OwnerListBox.Add("Monitor", AfxGetApp()->LoadIcon(IDI_MONITOR));

	
	// Set the Text and the Icon Postion to draw them inside the list box
	m_OwnerListBox.SetTextPosition(COwnerDrawListBox::ITEM_LEFT);
	m_OwnerListBox.SetIconPosition(COwnerDrawListBox::ITEM_RIGHT);	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMinaListBoxDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMinaListBoxDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMinaListBoxDemoDlg::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
	m_OwnerListBox.Destroy();
}

void CMinaListBoxDemoDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();

	m_OwnerListBox.Destroy();
}
