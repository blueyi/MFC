// ListBoxCHDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ListBoxCHDemo.h"
#include "ListBoxCHDemoDlg.h"

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
// CListBoxCHDemoDlg dialog

CListBoxCHDemoDlg::CListBoxCHDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CListBoxCHDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListBoxCHDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListBoxCHDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListBoxCHDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CListBoxCHDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CListBoxCHDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GET_SEL_INDEX, OnGetSelIndex)
	ON_CBN_SELCHANGE(IDC_SEL_COLOR_COMBO, OnSelchangeSelColorCombo)
	ON_CBN_SELCHANGE(IDC_BG_COLOR_COMBO, OnSelchangeBgColorCombo)
	ON_CBN_SELCHANGE(IDC_TEXT_COLOR_COMBO, OnSelchangeTextColorCombo)
	ON_BN_CLICKED(IDC_EDGE_CHECK, OnEdgeCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListBoxCHDemoDlg message handlers

BOOL CListBoxCHDemoDlg::OnInitDialog()
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

	// attach dialog template to the CWnd object
	m_ListBox.SubclassDlgItem(IDC_ICON_LIST,this);
	// add item 
	m_ListBox.AddItem("MFC",AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	m_ListBox.AddItem("Computer",AfxGetApp()->LoadIcon(IDI_PC));
	m_ListBox.AddItem("CD-ROM",AfxGetApp()->LoadIcon(IDI_CDROM));
	m_ListBox.AddItem("Hard Disk",AfxGetApp()->LoadIcon(IDI_HD));
	m_ListBox.AddItem("Floppy",AfxGetApp()->LoadIcon(IDI_FLOPPY));
	m_ListBox.AddItem("Net Drive",AfxGetApp()->LoadIcon(IDI_NETDRIVE));
	m_ListBox.AddItem("Install",AfxGetApp()->LoadIcon(IDI_INSTALL));
	m_ListBox.AddItem("Net Group",AfxGetApp()->LoadIcon(IDI_NETGROUP));
	m_ListBox.AddItem("Net Work",AfxGetApp()->LoadIcon(IDI_NETWORK));
	m_ListBox.AddItem("Port",AfxGetApp()->LoadIcon(IDI_PORT));

	m_ListBox.AddItem("Printer",AfxGetApp()->LoadIcon(IDI_PRINTER));
	m_ListBox.AddItem("Scanner",AfxGetApp()->LoadIcon(IDI_SCANNER));
	m_ListBox.AddItem("Card",AfxGetApp()->LoadIcon(IDI_CARD));
	m_ListBox.AddItem("Tool",AfxGetApp()->LoadIcon(IDI_TOOL));
	m_ListBox.AddItem("Mouse",AfxGetApp()->LoadIcon(IDI_MOUSE));
	m_ListBox.SetCurSel(0);	// set default selected index 

	((CButton *) GetDlgItem(IDC_EDGE_CHECK))->SetCheck(TRUE);
	((CComboBox *) GetDlgItem(IDC_BG_COLOR_COMBO))->SetCurSel(6);
	((CComboBox *) GetDlgItem(IDC_SEL_COLOR_COMBO))->SetCurSel(1);
	((CComboBox *) GetDlgItem(IDC_TEXT_COLOR_COMBO))->SetCurSel(6);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CListBoxCHDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CListBoxCHDemoDlg::OnPaint() 
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
HCURSOR CListBoxCHDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CListBoxCHDemoDlg::OnGetSelIndex() 
{
	// TODO: Add your control notification handler code here
	CString str;
	
	str.Format("%d",m_ListBox.GetCurSel());
	SetDlgItemText(IDC_SEL_INDEX,str);
}

void CListBoxCHDemoDlg::OnSelchangeSelColorCombo() 
{
	// TODO: Add your control notification handler code here
	CComboBox* pCombo = (CComboBox *) GetDlgItem(IDC_SEL_COLOR_COMBO);
	switch(pCombo->GetCurSel())
	{
	case 0:	//red
		m_ListBox.SetSelColor(RGB(255,0,0));
		m_ListBox.Invalidate();
		break;
	case 1: // green
		m_ListBox.SetSelColor(RGB(0,255,0));
		m_ListBox.Invalidate();
		break;
	case 2: // blue
		m_ListBox.SetSelColor(RGB(0,0,255));
		m_ListBox.Invalidate();
		break;
	case 3: // yellow
		m_ListBox.SetSelColor(RGB(255,255,0));
		m_ListBox.Invalidate();
		break;
	case 4: // Magenta
		m_ListBox.SetSelColor(RGB(255,0,255));
		m_ListBox.Invalidate();
		break;
	case 5: // Cyan
		m_ListBox.SetSelColor(RGB(0, 255, 255));
		m_ListBox.Invalidate();
		break;
	case 6: // white
		m_ListBox.SetSelColor(RGB(255, 255, 255));
		m_ListBox.Invalidate();
		break;
	case 7: // black
		m_ListBox.SetSelColor(RGB(0, 0, 0));
		m_ListBox.Invalidate();
		break;
	}
}

void CListBoxCHDemoDlg::OnSelchangeBgColorCombo() 
{
	// TODO: Add your control notification handler code here
	CComboBox* pCombo = (CComboBox *) GetDlgItem(IDC_BG_COLOR_COMBO);
	switch(pCombo->GetCurSel())
	{
	case 0:	//red
		m_ListBox.SetBgColor(RGB(255,0,0));
		m_ListBox.Invalidate();
		break;
	case 1: // green
		m_ListBox.SetBgColor(RGB(0,255,0));
		m_ListBox.Invalidate();
		break;
	case 2: // blue
		m_ListBox.SetBgColor(RGB(0,0,255));
		m_ListBox.Invalidate();
		break;
	case 3: // yellow
		m_ListBox.SetBgColor(RGB(255,255,0));
		m_ListBox.Invalidate();
		break;
	case 4: // magenta
		m_ListBox.SetBgColor(RGB(255,0,255));
		m_ListBox.Invalidate();
		break;
	case 5: // cyan
		m_ListBox.SetBgColor(RGB(0, 255, 255));
		m_ListBox.Invalidate();
		break;
	case 6: // white
		m_ListBox.SetBgColor(RGB(255, 255, 255));
		m_ListBox.Invalidate();
		break;
	case 7: // black
		m_ListBox.SetBgColor(RGB(0, 0, 0));
		m_ListBox.Invalidate();
		break;
	}	
}

void CListBoxCHDemoDlg::OnSelchangeTextColorCombo() 
{
	// TODO: Add your control notification handler code here
	CComboBox* pCombo = (CComboBox *) GetDlgItem(IDC_TEXT_COLOR_COMBO);
	switch(pCombo->GetCurSel())
	{
	case 0:	//red
		m_ListBox.SetTextColor(RGB(255,0,0));
		m_ListBox.Invalidate();
		break;
	case 1: // green
		m_ListBox.SetTextColor(RGB(0,255,0));
		m_ListBox.Invalidate();
		break;
	case 2: // blue
		m_ListBox.SetTextColor(RGB(0,0,255));
		m_ListBox.Invalidate();
		break;
	case 3: // yellow
		m_ListBox.SetTextColor(RGB(255,255,0));
		m_ListBox.Invalidate();
		break;
	case 4: // magenta
		m_ListBox.SetTextColor(RGB(255,0,255));
		m_ListBox.Invalidate();
		break;
	case 5: // cyan
		m_ListBox.SetTextColor(RGB(0, 255, 255));
		m_ListBox.Invalidate();
		break;
	case 6: // white
		m_ListBox.SetTextColor(RGB(255, 255, 255));
		m_ListBox.Invalidate();
		break;
	case 7: // black
		m_ListBox.SetTextColor(RGB(0, 0, 0));
		m_ListBox.Invalidate();
		break;
	}		
}

void CListBoxCHDemoDlg::OnEdgeCheck() 
{
	// TODO: Add your control notification handler code here
	m_ListBox.EnableEdge(((CButton *) GetDlgItem(IDC_EDGE_CHECK))->GetCheck());
	m_ListBox.Invalidate();
}
