// TitleBarButtonDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "TitleBarButton.h"
#include "TitleBarButtonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTitleBarButtonDlg Dialogfeld

CTitleBarButtonDlg::CTitleBarButtonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTitleBarButtonDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTitleBarButtonDlg)
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	m_bSwitch = TRUE;
	m_pCapBtn1 = new CCaptionButton;
	m_pCapBtn2 = new CCaptionButton;
	m_pCapBtn3 = new CCaptionButton;
}

void CTitleBarButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTitleBarButtonDlg)
	DDX_Control(pDX, IDB_ENABLE, m_btnEnable);
	DDX_Control(pDX, IDC_STATIC3, m_static3);
	DDX_Control(pDX, IDC_STATIC2, m_static2);
	DDX_Control(pDX, IDC_STATIC1, m_static1);
	DDX_Control(pDX, IDOK, m_btnOK);
	//}}AFX_DATA_MAP
}

// announce the user defined message:
DECLARE_USER_MESSAGE(WMU_HITCAPBUTTON)

BEGIN_MESSAGE_MAP(CTitleBarButtonDlg, CDialog)
	//{{AFX_MSG_MAP(CTitleBarButtonDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDB_ENABLE, OnBEnable)
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(WMU_HITCAPBUTTON, OnWMU_Hitcapbutton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTitleBarButtonDlg Nachrichten-Handler

BOOL CTitleBarButtonDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	// ZU ERLEDIGEN: Hier zusätzliche Initialisierung einfügen

	if(m_cfStatic1.CreatePointFont(90, "Arial"))
		{
			m_static1.SetFont(&m_cfStatic1);
			m_static2.SetFont(&m_cfStatic1);
			m_static3.SetFont(&m_cfStatic1);
		}
	
	// initialize the CCaptionButton - class 
	// with the handle of the window:
	CCaptionButton::InitCapBtn(m_hWnd);

	m_pCapBtn1->SetBmpID(1, IDB_LAMPOFF, IDB_LAMPON);
	m_pCapBtn2->SetBmpID(2, IDB_UNCHECKED, IDB_CHECKED, TRUE);
	m_pCapBtn3->SetBmpID(3, IDB_UP, IDB_DOWN);
		


return TRUE;
}


void CTitleBarButtonDlg::OnPaint() 
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


HCURSOR CTitleBarButtonDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CTitleBarButtonDlg::OnDestroy() 
{
	CDialog::OnDestroy();

if(m_pCapBtn1)	
	delete m_pCapBtn1;	
if(m_pCapBtn2)	
	delete m_pCapBtn2;	
if(m_pCapBtn3)	
	delete m_pCapBtn3;	
}

//////////////////////////////////////////////////////////////////////////////////////
				/*  ------------------------------------------- */
				/*     Functions for A BUTTON IN THE TITLEBAR
				/*  ------------------------------------------- */


// ****************** The functions for the buttons: ******************

/******************************************************************************
*	Message Name:		 WMU_HITCAPBUTTON
*	Inputs:
*		   WPARAM:		(UINT)wParam = No. of Button
*		   LPARAM:		(BOOL)lParam = Button state (Pressed=TRUE/Released=FALSE)
*
*	Result:	LRESULT
*			Logically void, 0, always
*
*	Effect:	 represents the # of the Button (if there is more than one) and the
*			 button state (pressed/released)
******************************************************************************/
LRESULT CTitleBarButtonDlg::OnWMU_Hitcapbutton(WPARAM wParam, LPARAM lParam)
{
	switch ((UINT)wParam) 
		{
		case 1:	// Button #1 has been hit:
				OnCapButton1((BOOL)lParam);
			break;
		case 2:	// Button #2 has been hit:
				OnCapButton2((BOOL)lParam);
			break;
		case 3:	// Button #3 has been hit:
				OnCapButton3((BOOL)lParam);
			break;
		default:	return 0;;
		}


return 0; // Allways return 0(LRESULT->void)
}




void CTitleBarButtonDlg::OnCapButton1(BOOL bBtnState)
{
	if(bBtnState)
		{
			SetWindowText("Light on");
			m_static1.SetWindowText("Rightmost Button is PUSHED");
		}
	else
		{
			SetWindowText("Light off");
			m_static1.SetWindowText("");
		}
}




void CTitleBarButtonDlg::OnCapButton2(BOOL bBtnState)
{
	if(bBtnState)
		{
			m_static2.SetWindowText("Middle Button is Checked");
		}
	else
		{	// if the button is released/unchecked/off:
			m_static2.SetWindowText("");
		}
}




void CTitleBarButtonDlg::OnCapButton3(BOOL bBtnState)
{
	if(bBtnState)
		{
			m_static3.SetWindowText("Leftmost Button is Checked");
		}
	else
		{	// if the button is released/unchecked/off:
			m_static3.SetWindowText("");
		}
}








void CTitleBarButtonDlg::OnBEnable() 
{
	if(m_bSwitch)
		{
			m_btnEnable.SetWindowText("Enable buttons in the caption");
			m_pCapBtn1->EnableButton(FALSE);
			m_pCapBtn2->EnableButton(FALSE);
			m_pCapBtn3->EnableButton(FALSE);
			m_bSwitch = FALSE;
		}
	else{
			m_btnEnable.SetWindowText("Disable buttons in the caption");
			m_pCapBtn1->EnableButton(TRUE);
			m_pCapBtn2->EnableButton(TRUE);
			m_pCapBtn3->EnableButton(TRUE);
			m_bSwitch = TRUE;
		}
	
}
