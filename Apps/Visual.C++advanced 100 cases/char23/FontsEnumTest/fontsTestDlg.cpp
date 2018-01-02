// fontsTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "fontsTest.h"
#include "fontsTestDlg.h"

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
// CFontsTestDlg dialog

CFontsTestDlg::CFontsTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFontsTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFontsTestDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFontsTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFontsTestDlg)
	DDX_Control(pDX, IDC_SAMPLEBOX, m_SampleBox);
	DDX_Control(pDX, IDC_UNDERLINE_CHECK, m_Underline);
	DDX_Control(pDX, IDC_ITALIC_CHECK, m_Italic);
	DDX_Control(pDX, IDC_COMBO_SIZE, m_SizeCombo);
	DDX_Control(pDX, IDC_COMBO_SCRIPT, m_ScriptCombo);
	DDX_Control(pDX, IDC_BOLD_CHECK, m_bold);
	DDX_Control(pDX, IDC_COMBO1, m_FontNamesCombo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFontsTestDlg, CDialog)
	//{{AFX_MSG_MAP(CFontsTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BOLD_CHECK, OnBoldCheck)
	ON_CBN_SELCHANGE(IDC_COMBO_SIZE, OnSelchangeComboSize)
	ON_CBN_SELCHANGE(IDC_COMBO_SCRIPT, OnSelchangeComboScript)
	ON_BN_CLICKED(IDC_ITALIC_CHECK, OnItalicCheck)
	ON_BN_CLICKED(IDC_UNDERLINE_CHECK, OnUnderlineCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontsTestDlg message handlers

BOOL CFontsTestDlg::OnInitDialog()
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
	m_Fonts.Enumerate(this);
	m_FontNamesCombo.Initialize(m_Fonts);
	Update4NewFontName();
	FontChanged();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFontsTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFontsTestDlg::OnPaint() 
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
HCURSOR CFontsTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFontsTestDlg::OnSelchangeCombo1() 
{
	Update4NewFontName();
	FontChanged();
}

void CFontsTestDlg::OnBoldCheck() 
{
	FontChanged();
}

void CFontsTestDlg::OnSelchangeComboSize() 
{
	FontChanged();
}

void CFontsTestDlg::OnSelchangeComboScript() 
{
	FontChanged();
}

void CFontsTestDlg::OnItalicCheck() 
{
	FontChanged();
}

void CFontsTestDlg::OnUnderlineCheck() 
{
	FontChanged();
}

void CFontsTestDlg::FontChanged()
{
	BOOL it = (m_Italic.GetCheck() == 1);
	BOOL bl = (m_bold.GetCheck() == 1);
	BOOL un = (m_Underline.GetCheck() == 1);
	CString str;
	const CWizFontsEnumerator::Font* font = m_FontNamesCombo.GetCurrentFont(m_Fonts);
	if (NULL == font)
	{
		ASSERT(0);
		return;
	}
	str = font->Name();
	int pp_size = m_SizeCombo.GetCurrentSize();
	if (pp_size < 0)
	{
		ASSERT(0);
		return;
	}

	//m_Edit.SetFont (str, pp_size, it, bl, un);
	m_SampleBox.SetFont (str, pp_size, it, bl, un);
}

void CFontsTestDlg::Update4NewFontName()
{
	const CWizFontsEnumerator::Font* font = m_FontNamesCombo.GetCurrentFont(m_Fonts);
	if (NULL == font)
	{
		ASSERT(0);
		return;
	}

	m_ScriptCombo.Initialize(font);
	m_SizeCombo.Initialize(font);

	int be = 0, ie = 0, ue = 0, bc = 0, ic = 0, uc = 0;

	if (!font->MustBeRegular())
		{
		if (font->CanBeBold())
			{
			if (font->MustBeBold())
				bc = 1;
			else
				be = 1;
			}
		if (font->CanBeItalics())
			{
			if (font->MustBeItalics())
				ic = 1;
			else
				ie = 1;
			}
		if (font->CanBeUnderline())
			{
			if (font->MustBeUnderline())
				uc = 1;
			else
				ue = 1;
			}

		}

	m_bold.EnableWindow(be);
	m_Italic.EnableWindow(ie);
	m_Underline.EnableWindow(ue);

	m_bold.SetCheck (bc);
	m_Italic.SetCheck (ic);
	m_Underline.SetCheck (uc);
}

