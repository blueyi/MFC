// StdioFileTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StdioFileEx.h"
#include "StdioFileTest.h"
#include "StdioFileTestDlg.h"

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
// CStdioFileTestDlg dialog

CStdioFileTestDlg::CStdioFileTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStdioFileTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStdioFileTestDlg)
	m_sFilePath = _T("");
	m_sIsUnicode = _T("");
	m_sSizeInChars = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStdioFileTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStdioFileTestDlg)
	DDX_Control(pDX, IDC_BUTTON_COPYASUNICODE, m_buttonCopyAsUnicode);
	DDX_Control(pDX, IDC_BUTTON_COPYASANSI, m_buttonCopyAsAnsi);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_editText);
	DDX_Control(pDX, IDC_STATIC_SIZECHARS, m_staticSizeChars);
	DDX_Control(pDX, IDC_STATIC_ISUNICODE, m_staticIsUnicode);
	DDX_Control(pDX, IDC_EDIT_FILE, m_editFilePath);
	DDX_Control(pDX, IDC_COMBO_FILECHARSET, m_comboFileCodePage);
	DDX_Text(pDX, IDC_EDIT_FILE, m_sFilePath);
	DDX_Text(pDX, IDC_STATIC_ISUNICODE, m_sIsUnicode);
	DDX_Text(pDX, IDC_STATIC_SIZECHARS, m_sSizeInChars);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStdioFileTestDlg, CDialog)
	//{{AFX_MSG_MAP(CStdioFileTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_EN_CHANGE(IDC_EDIT_FILE, OnChangeEditFile)
	ON_BN_CLICKED(IDC_BUTTON_COPYASANSI, OnButtonCopyAsAnsi)
	ON_BN_CLICKED(IDC_BUTTON_COPYASUNICODE, OnButtonCopyAsUnicode)
	ON_CBN_SELCHANGE(IDC_COMBO_FILECHARSET, OnSelChangeComboFileCharset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStdioFileTestDlg message handlers

BOOL CStdioFileTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	UINT nCurrentCodePage;

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
	
	m_buttonCopyAsUnicode.EnableWindow(FALSE);
	m_buttonCopyAsAnsi.EnableWindow(FALSE);

	// Get current locale code page
	nCurrentCodePage = CStdioFileEx::GetCurrentLocaleCodePage();

	// Fill the combo box with strings and our map with strings and code page IDs
	AddCodePage(_T("United States"), 437, nCurrentCodePage);
	AddCodePage(_T("Arabic"), 1256, nCurrentCodePage);
	AddCodePage(_T("Greek"), 737, nCurrentCodePage);
	AddCodePage(_T("Baltic"), 1257, nCurrentCodePage);
	AddCodePage(_T("Multilingual (Latin I)"), 850, nCurrentCodePage);
	AddCodePage(_T("Slavic (Latin II)"), 852, nCurrentCodePage);
	AddCodePage(_T("Thai"), 874, nCurrentCodePage);
	AddCodePage(_T("Japanese"), 932, nCurrentCodePage);
	AddCodePage(_T("Chinese (PRC, Singapore)"), 936, nCurrentCodePage);
	AddCodePage(_T("Korean"), 949, nCurrentCodePage);
	AddCodePage(_T("Chinese (Taiwan, Hong Kong)"), 950, nCurrentCodePage);
	AddCodePage(_T("Hebrew"), 1255, nCurrentCodePage);
	AddCodePage(_T("Windows 3.1 US (ANSI)"), 1252, nCurrentCodePage);
	AddCodePage(_T("Windows 3.1 Greek"), 1253, nCurrentCodePage);
	AddCodePage(_T("UTF-8"), CP_UTF8, nCurrentCodePage);

	// Add current as "unknown" if we didn't find it
	if (m_sCurrentCPDesc.IsEmpty())
	{
		AddCodePage(_T("Unknown"), nCurrentCodePage, nCurrentCodePage);
	}

	// Select the current locale in the combo
	m_comboFileCodePage.SetCurSel(m_comboFileCodePage.FindString(-1, m_sCurrentCPDesc));

	// Disable combo and label for now
	m_comboFileCodePage.EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_FILECODEPAGE)->EnableWindow(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStdioFileTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CStdioFileTestDlg::OnPaint() 
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
HCURSOR CStdioFileTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int CStdioFileTestDlg::GetUserFileSelection(CString& sSelectedFile)
{
	// Launch file dialog to select log file
	int nResponse;

	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, NULL, this);

	// Show dialog
	nResponse = fileDlg.DoModal();

	if (nResponse == IDOK)
	{
		sSelectedFile = fileDlg.GetPathName();
	}

	return nResponse;
}

void CStdioFileTestDlg::OnButtonBrowse() 
{
	// Get user file
	if (GetUserFileSelection(m_sFilePath) == IDOK)
	{
		m_editFilePath.SetWindowText(m_sFilePath);
	}
}

void CStdioFileTestDlg::OnChangeEditFile() 
{
	m_buttonCopyAsUnicode.EnableWindow(!m_sFilePath.IsEmpty());
	m_buttonCopyAsAnsi.EnableWindow(!m_sFilePath.IsEmpty());

	if (m_sFilePath.IsEmpty())
		return;

	// Read the file
	ReadSelectedFile(GetSelectedCodePage());
}

void CStdioFileTestDlg::ReadSelectedFile(IN const UINT nCodePage)
{
	int				nCharCount = 0;
	CStdioFileEx	fileEx;
	CString			sText, sLine;

	// Set the code page. Will not make any difference for Unicode-Unicode or ANSI-ANSI using the
	// same code page
	fileEx.SetCodePage(nCodePage);

	// Open file
	if (fileEx.Open(m_sFilePath, CFile::modeRead | CFile::typeText))
	{
		// Is file unicode?
		m_sIsUnicode = fileEx.IsFileUnicodeText() ? _T("Yes") : _T("No");
		m_staticIsUnicode.SetWindowText(m_sIsUnicode);

		nCharCount = fileEx.GetCharCount();

		// Convert to string, set in static control
		m_sSizeInChars.Format(_T("%d"), nCharCount);
		m_staticSizeChars.SetWindowText(m_sSizeInChars);

		// Read first 15 lines
		for (short nLineCount = 0; nLineCount < 16 && fileEx.ReadString(sLine); nLineCount++)
		{
			sText += sLine + sNEWLINE;
		}

		// Set lines in edit
		m_editText.SetWindowText(sText);

		// Disable buttons accordingly
		if (fileEx.IsFileUnicodeText())
		{
			m_buttonCopyAsUnicode.EnableWindow(FALSE);
			m_buttonCopyAsAnsi.EnableWindow(TRUE);
			m_comboFileCodePage.EnableWindow(FALSE);
			GetDlgItem(IDC_STATIC_FILECODEPAGE)->EnableWindow(FALSE);
		}
		else
		{
			m_buttonCopyAsAnsi.EnableWindow(FALSE);
			m_buttonCopyAsUnicode.EnableWindow(TRUE);
			m_comboFileCodePage.EnableWindow(TRUE);
			GetDlgItem(IDC_STATIC_FILECODEPAGE)->EnableWindow(TRUE);
		}

		fileEx.Close();
	}
}


void CStdioFileTestDlg::OnButtonCopyAsAnsi() 
{
	MakeCopy(false);
}

void CStdioFileTestDlg::OnButtonCopyAsUnicode() 
{
	MakeCopy(true);
}

void CStdioFileTestDlg::MakeCopy(IN const bool bAsUnicode)
{
	ASSERT(!m_sFilePath.IsEmpty());

	CString			sFilePathOut, sLine;
	CStdioFileEx	fileExOut;
	CStdioFileEx	fileEx;
	UINT				nWriteFlags = CFile::modeCreate | CFile::modeWrite | CFile::typeText;

	// Get user file path...
	GetUserFileSelection(sFilePathOut);

	// Set correct flags
	if (bAsUnicode)
	{
		nWriteFlags |= CStdioFileEx::modeWriteUnicode;
	}

	// Open file
	if (fileEx.Open(m_sFilePath, CFile::modeRead | CFile::typeText))
	{
		if (fileExOut.Open(sFilePathOut, nWriteFlags))
		{
			// Read file
			while (fileEx.ReadString(sLine))
			{
				fileExOut.WriteString(sLine + sNEWLINE);
			}

			fileExOut.Close();
		}

		fileEx.Close();
	}
}

void CStdioFileTestDlg::AddCodePage(IN const CString& sDesc,IN const UINT nCodePage,IN const UINT nCurrentCP)
{
	CString	sCPDesc = sDesc;
	_TCHAR	szBuffer[64];

	_itot(nCodePage, szBuffer, 10);

	// Add code page to desc
	sCPDesc += (CString)_T(" - ") + (CString)szBuffer;

	// Add "(this locale)" if current locale code page
	if (nCodePage == nCurrentCP)
	{
		sCPDesc += _T(" (this locale)");

		// Store it so we know we found it
		m_sCurrentCPDesc = sCPDesc;
	}

	// Add to map
	m_mapCodePageDescsToCodePages.SetAt(sCPDesc, (void*)nCodePage);

	// Add to combo
	m_comboFileCodePage.AddString(sCPDesc);
}

void CStdioFileTestDlg::OnSelChangeComboFileCharset() 
{
	// Re-read the file with the specified charset
	ReadSelectedFile(GetSelectedCodePage());
}

UINT CStdioFileTestDlg::GetSelectedCodePage()
{
	CString	sText;
	void*		pVoidCodePage;
	int		nSel = m_comboFileCodePage.GetCurSel();

	if (nSel > -1)
	{
		m_comboFileCodePage.GetLBText(nSel, sText);

		if (m_mapCodePageDescsToCodePages.Lookup(sText, pVoidCodePage))
		{
			return (UINT)pVoidCodePage;
		}
	}
	
	return CStdioFileEx::GetCurrentLocaleCodePage();
}
