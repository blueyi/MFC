// MRUComboTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MRUComboTest.h"
#include "MRUComboTestDlg.h"
#include "MRUParamsDlg.h"

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
// CMRUComboTestDlg dialog

CMRUComboTestDlg::CMRUComboTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMRUComboTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMRUComboTestDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMRUComboTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMRUComboTestDlg)
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMRUComboTestDlg, CDialog)
	//{{AFX_MSG_MAP(CMRUComboTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDOK, OnGetSize)
	ON_BN_CLICKED(IDC_CHANGE_MRU, OnChangeMru)
	ON_BN_CLICKED(IDC_CLEAR_MRU, OnClearMru)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMRUComboTestDlg message handlers

BOOL CMRUComboTestDlg::OnInitDialog()
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
	
	// Combobox MRU initialization:

    m_combo.SetMRURegKey ( _T("Combobox MRU") );
    m_combo.SetMRUValueFormat ( _T("File #%d") );

    m_combo.SetAutoRefreshAfterAdd ( TRUE );
    m_combo.SetAutoSaveAfterAdd ( TRUE );

    m_combo.LoadMRU();
    m_combo.RefreshCtrl();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMRUComboTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMRUComboTestDlg::OnPaint() 
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
HCURSOR CMRUComboTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


/////////////////////////////////////////////////////////////////////////////
// CMRUComboTestDlg command message handlers


// Browse button -- brings up your standard file browse dialog.
void CMRUComboTestDlg::OnBrowse() 
{
CFileDialog dlg ( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
                  _T("All Files (*.*)|*.*|"), this );

    if ( IDOK == dlg.DoModal() )
        {
        m_combo.SetWindowText ( dlg.GetPathName() );
        }
}


// Get Size button -- gets the size of the file whose name is entered in the
// combobox.  If successful, the filename is added to the MRU list.
void CMRUComboTestDlg::OnGetSize() 
{
CFileFind find;
CString   cstrFile;

    m_combo.GetWindowText ( cstrFile );

    if ( find.FindFile ( cstrFile ) )
        {
        find.FindNextFile();
        SetDlgItemInt ( IDC_FILESIZE, find.GetLength(), FALSE );
        m_combo.AddToMRU ( cstrFile );
        }
    else
        {
        SetDlgItemText ( IDC_FILESIZE, _T("<error>") );
        }
}


// Clear MRU button -- removes all filenames from the MRU list.
void CMRUComboTestDlg::OnClearMru() 
{
    m_combo.EmptyMRU();
    m_combo.RefreshCtrl();
}


// Set MRU Params button -- brings up another dlg where you can change the
// parameters that CRecentFileList uses.
void CMRUComboTestDlg::OnChangeMru() 
{
CMRUParamsDlg dlg;

    dlg.m_cstrRegKey = m_combo.GetMRURegKey();
    dlg.m_cstrRegValue = m_combo.GetMRUValueFormat();
    dlg.m_nMRUSize = m_combo.GetMaxMRUSize();

    if ( IDOK == dlg.DoModal() )
        {
        m_combo.SetMRURegKey ( dlg.m_cstrRegKey );
        m_combo.SetMRUValueFormat ( dlg.m_cstrRegValue );
        m_combo.SetMaxMRUSize ( dlg.m_nMRUSize );

        m_combo.RefreshCtrl();
        }
}
