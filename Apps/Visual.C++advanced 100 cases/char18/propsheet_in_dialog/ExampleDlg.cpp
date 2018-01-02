// ExampleDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "Example.h"
#include "CMyProperty.h"
#include "PropPage1.h"
#include "PropPage2.h"
#include "ExampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogfelddaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
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
		// Keine Nachrichten-Handler
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExampleDlg Dialogfeld

CExampleDlg::CExampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExampleDlg)
		// HINWEIS: Der Klassenassistent fügt hier Member-Initialisierung ein
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExampleDlg)
		// HINWEIS: Der Klassenassistent fügt an dieser Stelle DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExampleDlg, CDialog)
	//{{AFX_MSG_MAP(CExampleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExampleDlg 

BOOL CExampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	
	// IDM_ABOUTBOX 
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

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		
	
	// Create the CMyPropertysheet
	m_propertySheet.m_Rect.left = 100;	// set the position on the screen
	m_propertySheet.m_Rect.top = 100;
	m_propertySheet.m_Rect.right = 500;
	m_propertySheet.m_Rect.bottom = 300;
	m_propertySheet.m_nPages = -1;		// init this membervariable
	m_propertySheet.m_nActPage = 0;		// init this membervariable
	m_propertySheet.m_nCtrlID = 2000;	// control-id in the dialog

	// and create it on the screen
	m_propertySheet.Create (WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		m_propertySheet.m_Rect, this, m_propertySheet.m_nCtrlID);

	// Now add the dialogs page per page
	TC_ITEM Item;
	Item.mask = TCIF_TEXT;
	CMyPropertyPage *pPropPage;
	
	int nN;
	int	nPages = 2;	// in my example I have two pages
    for (nN = 0; nN < nPages; nN++) {
		
		pPropPage = new (CMyPropertyPage);	// new it
		
		// Create the tab and the dialog
		switch (nN) {
		case 0:	// page number 1 - a small example
			Item.pszText = "Page 1";
			pPropPage->m_strTitle = "&Page1";	// or get the title of m_fontPage - whatwever you want
			pPropPage->m_pDialogPage = (CMyPropDialog *) &m_propPage1;
			pPropPage->m_pDialogPage->Create (IDD_PROPPAGE1, &m_propertySheet);
			break;
		case 1:	// page number 2 - a small example
			Item.pszText = "Page 2";
			pPropPage->m_strTitle = "&Page2";	// or get the title of m_fontPage - whatwever you want
			pPropPage->m_pDialogPage = (CMyPropDialog *) &m_propPage2;
			pPropPage->m_pDialogPage->Create (IDD_PROPPAGE2, &m_propertySheet);
			break;
		}
				
		m_propertySheet.InsertItem (nN, &Item);	// this is fot CTabWnd
		pPropPage->m_hLocal = NULL;	// nothing is created on the fly
									// important information on delete!

		// add it to the array
		m_propertySheet.m_Dialogs.Add (pPropPage);
		m_propertySheet.m_nPages++;	// one more page


		// the size of CTabWnd is m_rect
		// the size of the dialog is smaller
		pPropPage->m_Rect.top = 30;	// above there must be enough place for the tab-control
		pPropPage->m_Rect.left = 10;	// border of 10 units is good
		pPropPage->m_Rect.bottom = m_propertySheet.m_Rect.bottom - m_propertySheet.m_Rect.top - 10;
		pPropPage->m_Rect.right = m_propertySheet.m_Rect.right - m_propertySheet.m_Rect.left - 10;

		// Only the 1. page should be active at startup
		if (nN > 0) {
			pPropPage->m_pDialogPage->SetWindowPos(NULL, pPropPage->m_Rect.left,
							pPropPage->m_Rect.top, 0, 0,
							SWP_HIDEWINDOW | SWP_NOSIZE); 
		}
		else {
			pPropPage->m_pDialogPage->SetWindowPos(NULL, pPropPage->m_Rect.left,
							pPropPage->m_Rect.top, 0, 0,
							SWP_SHOWWINDOW | SWP_NOSIZE);
		}
		// the class will handle the change of the tab-control
		// and synchronize activate-deactivate the dialogpages
		

		
	}
	
	return TRUE;  
}

void CExampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CExampleDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, während der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CExampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
