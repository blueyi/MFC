// ListSubclassDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ListSubclass.h"
#include "ListSubclassDlg.h"

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
// CListSubclassDlg dialog

CListSubclassDlg::CListSubclassDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CListSubclassDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListSubclassDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListSubclassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListSubclassDlg)
	DDX_Control(pDX, IDC_TextColor, m_TextColor);
	DDX_Control(pDX, IDC_BkColor, m_BkColor);
	DDX_Control(pDX, IDC_Names, m_names);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CListSubclassDlg, CDialog)
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_CREATE()
	//{{AFX_MSG_MAP(CListSubclassDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_INSERT, OnInsert)
	ON_LBN_DBLCLK(IDC_TextColor, OnDblclkTextColor)
	ON_LBN_DBLCLK(IDC_BkColor, OnDblclkBkColor)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_DISABLED, OnDisabled)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListSubclassDlg message handlers

BOOL CListSubclassDlg::OnInitDialog()
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
	m_names.SetBkColor(RGB(128,0,0));
	m_names.SetTextColor(RGB(0,235,0),RGB(0,0,0));	//m_names.SetBkPattern(IDB_Pattern);	

	m_TextColor.AddString("Highlight Clr");
	m_TextColor.AddString("Text Color");

m_BkColor.AddString("Background");
m_BkColor.AddString("Highlight Clr");
	BkColor=RGB(128,0,0);
	TextColor=RGB(0,235,0);
	HColor=GetSysColor(COLOR_HIGHLIGHT);
	HTextClr=GetSysColor(COLOR_HIGHLIGHTTEXT);
//	for (int red = 0; red <= 255; red += 255)
//		for (int green = 0; green <= 255; green += 255)
//			for (int blue = 0; blue <= 255; blue += 255)
//				m_names.AddString((LPCSTR)RGB(red, green, blue));
	// TODO: Add extra initialization here

m_names.AddItem(IDB_HAPPY,"Clown Happy");
m_names.AddItem(IDB_SAD,"Clown Sad");
m_names.AddItem(IDB_RED,"Red");
m_names.AddItem(BLANK_BMP,"OOPS. Icon Gone");
m_names.AddItem(NO_BMP_ITEM,"Normal Text");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CListSubclassDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CListSubclassDlg::OnPaint() 
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
HCURSOR CListSubclassDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CListSubclassDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString str;
	GetDlgItem(IDC_NewText)->GetWindowText(str);
	UINT sel;
	if(IsDlgButtonChecked(IDC_NORMAL))sel=NO_BMP_ITEM;
	 else {
	sel=((CComboBox*)GetDlgItem(IDC_BMPS))->GetCurSel();
	if (sel==0)sel=	IDB_HAPPY;
	else if (sel==1) sel=IDB_RED;
	else if (sel==2)sel=IDB_SAD;
	else sel=BLANK_BMP;
	 }
	 m_names.AddItem(sel,str);
}

void CListSubclassDlg::OnInsert() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString str;
	GetDlgItem(IDC_NewText)->GetWindowText(str);
	UINT sel;
	if(IsDlgButtonChecked(IDC_NORMAL))sel=NO_BMP_ITEM;
	 else {
	sel=((CComboBox*)GetDlgItem(IDC_BMPS))->GetCurSel();
	if (sel==0)sel=	IDB_HAPPY;
	else if (sel==1) sel=IDB_RED;
	else if (sel==2)sel=IDB_SAD;
	else sel=BLANK_BMP;
	 }
	 m_names.InsertItem(m_names.GetCurSel(),sel,str);	
}



BOOL CListSubclassDlg::DrawScrolls(CDC *pDC)
{
return FALSE;
}

BOOL CListSubclassDlg::OnQueryNewPalette()
{
	// CG: This function was added by the Palette Support component

	if (m_pPalette == NULL)
		return FALSE;
	
	// BLOCK
	{
		CClientDC dc(this);
		CPalette* pOldPalette = dc.SelectPalette(m_pPalette,
			GetCurrentMessage()->message == WM_PALETTECHANGED);
		UINT nChanged = dc.RealizePalette();
		dc.SelectPalette(pOldPalette, TRUE);

		if (nChanged == 0)
			return FALSE;
	}
	
	Invalidate();
	
	return TRUE;
}

void CListSubclassDlg::OnPaletteChanged(CWnd* pFocusWnd)
{
	// CG: This function was added by the Palette Support component

	if (pFocusWnd == this || IsChild(pFocusWnd))
		return;
	
	OnQueryNewPalette();
}

CPalette* CListSubclassDlg::SetPalette(CPalette* pPalette)
{
	// CG: This function was added by the Palette Support component

	// Call this function when the palette changes.  It will
	// realize the palette in the foreground to cause the screen
	// to repaint correctly.  All calls to CDC::SelectPalette in
	// painting code should select palettes in the background.

	CPalette* pOldPalette = m_pPalette;
	m_pPalette = pPalette;
	OnQueryNewPalette();
	return pOldPalette;
}

int CListSubclassDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// CG: This function was added by the Palette Support component

	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pPalette = NULL;
	return 0;
}

void CListSubclassDlg::OnDblclkTextColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	dlg.DoModal();

	if	(m_TextColor.GetCurSel()==0)HTextClr=dlg.GetColor();
else TextColor=dlg.GetColor();
m_names.SetTextColor(TextColor,HTextClr);

}

void CListSubclassDlg::OnDblclkBkColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	dlg.DoModal();

	if	(m_BkColor.GetCurSel()==0)BkColor=dlg.GetColor();
else HColor=dlg.GetColor();

m_names.SetBkColor(BkColor,HColor);
}

void CListSubclassDlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	m_names.DeleteString(m_names.GetCurSel());
}

void CListSubclassDlg::OnDisabled() 
{
	// TODO: Add your control notification handler code here
	if (IsDlgButtonChecked(IDC_DISABLED))m_names.EnableWindow(FALSE);
	else m_names.EnableWindow(TRUE);
}

