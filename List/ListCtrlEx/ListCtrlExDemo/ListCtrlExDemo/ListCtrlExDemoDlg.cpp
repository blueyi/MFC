// ListCtrlExDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ListCtrlExDemo.h"
#include "ListCtrlExDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CListCtrlExDemoDlg dialog




CListCtrlExDemoDlg::CListCtrlExDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CListCtrlExDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListCtrlExDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CListCtrlExDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CListCtrlExDemoDlg message handlers

BOOL CListCtrlExDemoDlg::OnInitDialog()
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

	m_list.ModifyStyle(0, LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() |LVS_EX_FULLROWSELECT );

	m_list.InsertColumn(0, _T("Normal Text"), 100, ListCtrlEx::Normal, LVCFMT_CENTER, ListCtrlEx::SortByDigit);
	m_list.InsertColumn(1, _T("Check Box"), 100, ListCtrlEx::CheckBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_list.InsertColumn(2, _T("Edit Box"), 100, ListCtrlEx::EditBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_list.InsertColumn(3, _T("Combo Box"), 100, ListCtrlEx::ComboBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_list.InsertColumn(4, _T("Radio Box"), 100, ListCtrlEx::RadioBox, LVCFMT_CENTER, ListCtrlEx::SortByString);
	m_list.InsertColumn(5, _T("Progress Bar"), 100, ListCtrlEx::Progress, LVCFMT_CENTER, ListCtrlEx::SortByString);

	for (int i=0; i <20; ++i)
	{
		CString strItem;
		strItem.Format(_T("%d"), i+1);
		int nRow = m_list.InsertItem(m_list.GetItemCount(), strItem);
		
		int nSubCnt =m_list.GetColumnCount() -1;
		for (int j = 1; j <= nSubCnt; ++j)
		{
			CString sub;
			sub.Format(_T("sub item %d %d"), nRow, j);
			m_list.SetItemText(nRow, j, sub);
			if(ListCtrlEx::ComboBox == m_list.GetColumnType(j))
			{
				ListCtrlEx::CStrList strlist;
				strlist.push_back(sub);
				CString str; 
				str.Format(_T("some other %d, %d"), nRow, j); 
				strlist.push_back(str);
				m_list.SetCellStringList(nRow, j, strlist);
			}
			else if (ListCtrlEx::Progress == m_list.GetColumnType(j))
			{
				m_list.SetCellProgressMaxValue(nRow, j, 100*j);
				m_list.SetCellProgressValue(nRow, j, 100*nRow);
				
			}
			m_list.SetCellEnabled(nRow, j, (nRow != j));
		}
	}

	m_list.SetShowProgressPercent(TRUE);
	m_list.SetSupportSort(TRUE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CListCtrlExDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CListCtrlExDemoDlg::OnPaint()
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
HCURSOR CListCtrlExDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

