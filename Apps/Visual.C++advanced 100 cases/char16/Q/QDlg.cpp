// QDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Q.h"
#include "QDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQDlg dialog

CQDlg::CQDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	for (int  i = 0; i < 5; i++)
		m_pCombo[i] = new CQComboBox(Line, NULL, i);
}

CQDlg::~CQDlg()
{
	for (int  i = 0; i < 5; i++)
		delete m_pCombo[i];
}


void CQDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQDlg)
	DDX_Control(pDX, IDC_EDIT_TEXT, m_edit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CQDlg, CDialog)
	//{{AFX_MSG_MAP(CQDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQDlg message handlers

typedef TCHAR (*RNDSTR) (CString* pString);

TCHAR RandomLimited(CString* pString)
{
        return (TCHAR)pString->GetAt(((BYTE)rand()) %
pString->GetLength());
}

TCHAR RandomUnLimited(CString* pString)
{
        return (TCHAR)(BYTE)rand();
}

CString RandomString(int nLength = 16, CString sWhat = _T("0123456789"))
{
        RNDSTR f = sWhat.IsEmpty() ? RandomUnLimited : RandomLimited;
        CString result;
        for (int i = 0; i < nLength; i++)
                result += f(&sWhat);
        return result;
}

BOOL CQDlg::OnInitDialog()
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

	for (int i = 0; i < 5 ; i++)
	{
		int n = 5000 + rand() % 1000;
		for (int j = 0; j < n; j++)
			m_arItems[i].Add(RandomString());
	}
	
	for (i = 0; i < 5; i++)
	{
		m_pCombo[i]->SubclassDlgItem(IDC_CUSTOM1 + i,this);
		m_pCombo[i]->SetCountItems(m_arItems[i].GetSize());
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CQDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CQDlg::OnPaint() 
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
HCURSOR CQDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

CStringArray CQDlg::m_arItems[5];
LPCTSTR CQDlg::Line(int iLine, LPARAM& lParamItem, LPARAM lParam)
{
	if (iLine < m_arItems[lParam].GetSize())
		return m_arItems[lParam][iLine];
	return NULL;
}


LRESULT CQDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	UINT m_nLoaded = RegisterWindowMessage(_T("QCBN_LOADED"));
	if (message == m_nLoaded)
	{
		CQComboBox* pCombo = ((CQComboBox*)CWnd::FromHandle((HWND)wParam));
		CString text; text.Format(_T("QCombo ID = %i\r\n"), pCombo->GetDlgCtrlID());
		text += pCombo->m_QuickLoader.GetListNodes() + _T("\r\n");
		CString oldText;
		m_edit.GetWindowText(oldText);
		oldText = text + oldText;
		m_edit.SetWindowText(oldText);
	}
	
	return CDialog::WindowProc(message, wParam, lParam);
}
