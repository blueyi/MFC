// MainSheet.cpp : implementation file
//

#include "stdafx.h"
#include "$$Root$$.h"
#include "MainSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

$$IF(ABOUT_BOX)
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

$$IF(TOOLTIPS)
	virtual BOOL PreTranslateMessage (MSG* pMsg);
$$ENDIF	//TOOLTIPS

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
$$IF(TOOLTIPS)
	virtual BOOL OnInitDialog();
$$ELSE
		// NOTE: the ClassWizard will add member functions here
$$ENDIF	//TOOLTIPS
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

$$IF(TOOLTIPS)
protected:
	CToolTipCtrl m_tooltip;
$$ENDIF	//TOOLTIPS
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
$$ENDIF	//ABOUT_BOX

$$IF(TOOLTIPS)
BOOL CAboutDlg::PreTranslateMessage (MSG* pMsg)
{
	// Let the ToolTip process this message.
	m_tooltip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Create the ToolTip control.
	m_tooltip.Create (this);
	m_tooltip.Activate (TRUE);

	// TODO: Use one of the following forms to add controls:
	// m_tooltip.AddTool (GetDlgItem (IDC_<name>), <string-table-id>);
	// m_tooltip.AddTool (GetDlgItem (IDC_<name>), _T ("<text>"));

	return TRUE;
}
$$ENDIF	//TOOLTIPS

/////////////////////////////////////////////////////////////////////////////
// CMainSheet

CMainSheet::CMainSheet()
: CPropertySheet (IDS_TITLE)
{
	// Add the property pages
$$BEGINLOOP(NUM_PAGES)
	AddPage (&$$PAGE_VAR$$);
$$ENDLOOP	//NUM_PAGES

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

$$IF(BITMAP_PAGES)
	m_imgTabBmps.Create ($$PAGE_FIRST_BMP$$, 10, 1, RGB (0x00, 0x00, 0xFF));
	for (int i = 1;i < $$NUM_PAGES$$;i++)
	{
		CBitmap bmp;
		bmp.LoadBitmap ($$PAGE_FIRST_BMP$$ + i);
		m_imgTabBmps.Add (&bmp, RGB (0x00, 0x00, 0xFF));
	}
$$ENDIF	//BITMAP_PAGES
}

CMainSheet::~CMainSheet()
{
}


BEGIN_MESSAGE_MAP(CMainSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CMainSheet)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
$$IF(ABOUT_BOX)
	ON_COMMAND(IDM_ABOUTBOX, OnAboutbox)
$$ENDIF	//ABOUT_BOX
$$IF(SEND_TO_TASKBAR)
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(WM_ICONNOTIFY, OnIconNotify)
	ON_COMMAND(ID_ICON_SHUTDOWN, OnIconShutdown)
	ON_COMMAND(ID_ICON_RESTORE, OnIconRestore)
$$ENDIF	//SEND_TO_TASKBAR
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainSheet message handlers

BOOL CMainSheet::OnInitDialog() 
{
$$IF(!MODAL)
$$IF(STANDARD_BUTTONS)
	m_bModeless = FALSE;
$$ENDIF	//STANDARD_BUTTONS
$$ENDIF	//MODAL

	CPropertySheet::OnInitDialog();

$$IF(ABOUT_BOX)
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}
$$ENDIF	//ABOUT_BOX

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

$$IF(BITMAP_PAGES)
	GetTabControl ()->SetImageList (&m_imgTabBmps);
	TC_ITEM tci = {TCIF_IMAGE};
	for (tci.iImage = 0;tci.iImage < $$NUM_PAGES$$;tci.iImage++)
		GetTabControl ()->SetItem (tci.iImage, &tci);
$$ENDIF	//BITMAP_PAGES

$$IF(TOOLTIPS)
	// Create the ToolTip control.
	m_tooltip.Create (this);
	m_tooltip.Activate (TRUE);

	// TODO: Use one of the following forms to add controls:
	// m_tooltip.AddTool (GetDlgItem (IDC_<name>), <string-table-id>);
	// m_tooltip.AddTool (GetDlgItem (IDC_<name>), _T ("<text>"));
$$ENDIF	//TOOLTIPS

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMainSheet::PostNcDestroy() 
{
	CPropertySheet::PostNcDestroy();

	delete this;
}

void CMainSheet::OnSysCommand(UINT nID, LPARAM lParam) 
{
$$IF(ABOUT_BOX)
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
$$IF(MODAL)
		CPropertySheet::OnSysCommand (nID, lParam);
$$ELSE
		switch (nID)
		{
		case SC_CLOSE:
			DestroyWindow ();
			break;
		default:
			CPropertySheet::OnSysCommand (nID, lParam);
			break;
		}
$$ENDIF	//MODAL
	}
$$ELSE
$$IF(MODAL)
	CPropertySheet::OnSysCommand (nID, lParam);
$$ELSE
	switch (nID)
	{
	case SC_CLOSE:
		DestroyWindow ();
		break;
	default:
		CPropertySheet::OnSysCommand (nID, lParam);
		break;
	}
$$ENDIF	//MODAL
$$ENDIF	//ABOUT_BOX
}

// If you add a minimize button to your property sheet, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.


void CMainSheet::OnPaint() 
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
		CPropertySheet::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.

HCURSOR CMainSheet::OnQueryDragIcon() 
{
	return (HCURSOR (m_hIcon));
}

BOOL CMainSheet::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (HIWORD (wParam) == BN_CLICKED)
	{
		switch (LOWORD (wParam))
		{
		case IDOK:
			PressButton (PSBTN_OK);
$$IF(!MODAL)
			DestroyWindow ();
$$ENDIF	//MODAL
			return (TRUE);
		case 0x3021:	// Apply
			PressButton (PSBTN_APPLYNOW);
			return (TRUE);
		case IDCANCEL:
			PressButton (PSBTN_CANCEL);
$$IF(!MODAL)
			DestroyWindow ();
$$ENDIF	//MODAL
			return (TRUE);
		case IDHELP:
			PressButton (PSBTN_HELP);
			return (TRUE);
		}
	}
	return CPropertySheet::OnCommand(wParam, lParam);
}

$$IF(ABOUT_BOX)
void CMainSheet::OnAboutbox() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
$$ENDIF	//ABOUT_BOX

$$IF(SEND_TO_TASKBAR)
void CMainSheet::OnSize(UINT nType, int cx, int cy) 
{
	CPropertySheet::OnSize(nType, cx, cy);

	NOTIFYICONDATA nid = {sizeof (nid), GetSafeHwnd (), 100, NIF_ICON|NIF_MESSAGE|NIF_TIP, WM_ICONNOTIFY, m_hIcon};
	CString niTip;
	niTip.LoadString (IDS_TITLE);
	strcpy (nid.szTip, niTip);
	switch (nType)
	{
	case SIZE_MINIMIZED:
		ShowWindow (SW_HIDE);
		Shell_NotifyIcon (NIM_ADD, &nid);
$$IF(START_ON_TASKBAR)
		AfxGetApp ()->WriteProfileInt (_T ("StartUp"), _T ("StartOnTaskBar"), TRUE);
$$ENDIF	//START_ON_TASKBAR
		break;
	case SIZE_RESTORED:
		Shell_NotifyIcon (NIM_DELETE, &nid);
$$IF(START_ON_TASKBAR)
		AfxGetApp ()->WriteProfileInt (_T ("StartUp"), _T ("StartOnTaskBar"), FALSE);
$$ENDIF	//START_ON_TASKBAR
		static BOOL bFirst = TRUE;
		if (bFirst && GetTabControl () != NULL)
		{
			bFirst = FALSE;

			CWnd *pTab = GetTabControl ();
			CRect rTab;
			pTab->GetWindowRect (rTab);

$$IF(STANDARD_BUTTONS)
			SetWindowPos (NULL, rTab.left - 9, rTab.top - 29, rTab.Width () + 18, rTab.Height () + 68, SWP_NOACTIVATE|SWP_NOZORDER);
$$ELSE
			SetWindowPos (NULL, rTab.left - 9, rTab.top - 29, rTab.Width () + 18, rTab.Height () + 35, SWP_NOACTIVATE|SWP_NOZORDER);
$$ENDIF	//STANDARD_BUTTONS
		}
		break;
	}
}

LRESULT CMainSheet::OnIconNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 100)
	{
		switch (lParam)
		{
		case WM_LBUTTONDBLCLK:
			PostMessage (WM_COMMAND, ID_ICON_RESTORE);
			break;
		case WM_RBUTTONDOWN:
			{
				CMenu menu;
				menu.LoadMenu (IDR_MAINFRAME);
				CPoint pt;
				::GetCursorPos (&pt);
				menu.GetSubMenu (0)->TrackPopupMenu (TPM_RIGHTALIGN|TPM_RIGHTBUTTON, pt.x, pt.y, this);
			}
			break;
		}
	}
	return (0);
}

void CMainSheet::OnIconShutdown() 
{
	NOTIFYICONDATA nid = {sizeof (nid), GetSafeHwnd (), 100, NIF_ICON|NIF_MESSAGE|NIF_TIP, WM_ICONNOTIFY, m_hIcon};
	CString niTip;
	niTip.LoadString (IDS_TITLE);
	strcpy (nid.szTip, niTip);
	Shell_NotifyIcon (NIM_DELETE, &nid);
	DestroyWindow ();
}

void CMainSheet::OnIconRestore() 
{
	ShowWindow (SW_RESTORE);
}

$$ENDIF	//SEND_TO_TASKBAR

$$IF(TOOLTIPS)
BOOL CMainSheet::PreTranslateMessage(MSG* pMsg)
{
	// Let the ToolTip process this message.
	m_tooltip.RelayEvent (pMsg);

	return CPropertySheet::PreTranslateMessage (pMsg);
}
$$ENDIF	//TOOLTIPS
