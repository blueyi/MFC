// hovbuttDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hovbutt.h"
#include "hovbuttDlg.h"
#include "hoverbutton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHovbuttDlg dialog

CHovbuttDlg::CHovbuttDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHovbuttDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHovbuttDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHovbuttDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHovbuttDlg)
	DDX_Control(pDX, IDC_BUTTON4, m_button4);
	DDX_Control(pDX, IDC_BUTTON3, m_button3);
	DDX_Control(pDX, IDC_BUTTON2, m_button2);
	DDX_Control(pDX, IDC_BUTTON1, m_button1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHovbuttDlg, CDialog)
	//{{AFX_MSG_MAP(CHovbuttDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHovbuttDlg message handlers

BOOL CHovbuttDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Initialise the CBitmapButton with the images
	m_button4.LoadBitmaps(IDB_RBU, IDB_RBD, IDB_RBF, IDB_RBX);
	m_button3.LoadBitmaps(IDB_RBU, IDB_RBD, IDB_RBF, IDB_RBX);
	m_button2.LoadBitmaps(IDB_RBU, IDB_RBD, IDB_RBF, IDB_RBX);
	m_button1.LoadBitmaps(IDB_RBU, IDB_RBD, IDB_RBF, IDB_RBX);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_nSelected = 1;

	// Redraw the buttons in their various states
	RefreshButtons(m_nSelected);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

int CHovbuttDlg::RefreshButtons(int nSelected /*=0*/ )
{
	m_button1.SetButtonState(BUTTON_OFF);
	m_button2.SetButtonState(BUTTON_OFF);
	m_button3.SetButtonState(BUTTON_GREYED);
	m_button4.SetButtonState(BUTTON_OFF);

	switch(nSelected)
	{
	case 2:
		m_button2.SetButtonState(BUTTON_ON);
		break;
	case 3:
		m_button3.SetButtonState(BUTTON_ON);
		break;
	case 4:
		m_button4.SetButtonState(BUTTON_ON);
		break;
	default:
		m_button1.SetButtonState(BUTTON_ON);
		nSelected = 1;
		m_nSelected = nSelected;
		break;
	}

	return nSelected;
}

void CHovbuttDlg::OnButton1() 
{
	m_nSelected	= 1;
	RefreshButtons(m_nSelected);
	// Do some process (1)
}

void CHovbuttDlg::OnButton2() 
{
	m_nSelected	= 2;
	RefreshButtons(m_nSelected);
	// Do some process (2)
}

void CHovbuttDlg::OnButton3() 
{
	m_nSelected	= 3;
	RefreshButtons(m_nSelected);
	// Do some process (3)
}

void CHovbuttDlg::OnButton4() 
{
	m_nSelected	= 4;
	RefreshButtons(m_nSelected);
	// Do some process (4)
}
