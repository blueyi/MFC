// ListCtrlDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ListCtrlDemo.h"
#include "ListCtrlDemoDlg.h"

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
// CListCtrlDemoDlg dialog

CListCtrlDemoDlg::CListCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CListCtrlDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListCtrlDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListCtrlDemoDlg)
	DDX_Control(pDX, IDC_COMBO_COLUMNINDEX, m_IndexCombo);
	DDX_Control(pDX, IDC_LIST1, m_NeuListCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CListCtrlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CListCtrlDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INSERT, OnButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_ADDCONTROLTEXT, OnButtonAddcontroltext)
	//}}AFX_MSG_MAP
	ON_NOTIFY(HDN_ENDTRACK, 0, OnEndtrack)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlDemoDlg message handlers

void GetColor(LPVOID * lpVoid)
{
	CWnd * pWnd = (CWnd *) lpVoid;
	pWnd->EnableWindow (!pWnd->IsWindowEnabled ());
}


BOOL CListCtrlDemoDlg::OnInitDialog()
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
	InitializeListCtrl();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CListCtrlDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CListCtrlDemoDlg::OnPaint() 
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
HCURSOR CListCtrlDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CListCtrlDemoDlg::OnEndtrack(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	NMHEADER * pHeade = (NMHEADER *) pNMHDR;
	m_NeuListCtrl.AdjustControlsAccordingToHeaderWidth (phdn);
	*pResult = 0;
} 
void CListCtrlDemoDlg::InitializeListCtrl()
{
	m_NeuListCtrl.InsertColumn(0, "Selected",LVCFMT_LEFT,90);
	m_NeuListCtrl.InsertColumn(1, "Graph", LVCFMT_LEFT,50);
	m_NeuListCtrl.InsertColumn(2, "Save", LVCFMT_LEFT,50);
		
	m_NeuListCtrl.InsertColumn(3, "Goal", LVCFMT_LEFT,60);
	m_NeuListCtrl.InsertColumn(4, "Play", LVCFMT_LEFT,75);
	
	CString strData;
	
	for(int i =0 ;i < 10 ;i++)
	{
		m_NeuListCtrl.InsertItem (i,strData);
		for(int ii =0 ;ii < 4 ;ii++)
		{
			strData.Format("%i:%i",i,ii);
			m_NeuListCtrl.SetItemText (i, ii, strData);
		}
	}
	m_NeuListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
}

void  pFuncShowColorDialog(LPVOID lpvoid) // pointer to window sending message
{
	CColorDialog dlg;
	dlg.DoModal ();
}

void CListCtrlDemoDlg::OnButtonInsert() 
{
	int i = m_IndexCombo.GetCurSel();
	if(i < 0)
		return ;
	switch(GetCheckedRadioButton(IDC_BUTTON,IDC_NONE))
	{
		case IDC_BUTTON:
			m_NeuListCtrl.SetItemControl(BUTTON,i);
			m_NeuListCtrl.AttachEvent_HandlerForItemControl(i,BN_CLICKED,pFuncShowColorDialog);
			break;
		case IDC_CHECKBOX:
			m_NeuListCtrl.SetItemControl(CHECKBOX,i);
			break;
		case IDC_COMBOBOX:
			m_NeuListCtrl.SetItemControl(COMBOBOX,i);
			break;
		case IDC_EDITBOX:
			m_NeuListCtrl.SetItemControl(EDITBOX,i);
			break;
		case IDC_LISTBOX:
			m_NeuListCtrl.SetItemControl(LISTBOX,i);
	}
	m_NeuListCtrl.MapControlsForSubItems();
	m_NeuListCtrl.ShowControls(TRUE);
	m_NeuListCtrl.EnableControls(TRUE);
}

void CListCtrlDemoDlg::OnButtonAddcontroltext() 
{
	CString strData;
	GetDlgItem(IDC_EDIT_ITEMTEXT)->GetWindowText(strData);
	int i = m_IndexCombo.GetCurSel();
	if(i < 0)
	{
		return ;
	}
	m_NeuListCtrl.AddToControlsData(i,strData);
	m_NeuListCtrl.MapControlsForSubItems();
	m_NeuListCtrl.ShowControls(TRUE);
	m_NeuListCtrl.EnableControls(TRUE);
}
