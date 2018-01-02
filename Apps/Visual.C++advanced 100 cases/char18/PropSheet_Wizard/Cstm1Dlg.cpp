// cstm1dlg.cpp : implementation file
//

#include "stdafx.h"
#include "PropSheet Wizard.h"
#include "cstm1dlg.h"
#include "PropSheet Wizardaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg dialog


CCustom1Dlg::CCustom1Dlg()
	: CAppWizStepDlg(CCustom1Dlg::IDD)
{
	//{{AFX_DATA_INIT(CCustom1Dlg)
	m_aboutBox = TRUE;
	m_bitmapPages = TRUE;
	m_minimizeBox = TRUE;
	m_sendToTaskBar = TRUE;
	m_startOnTaskBar = TRUE;
	m_modal = 1;
	m_mfcDLL = 0;
	m_tooltips = TRUE;
	m_standardButtons = FALSE;
	//}}AFX_DATA_INIT
}


void CCustom1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom1Dlg)
	DDX_Control(pDX, IDC_CHECK_STANDARDBUTTONS, m_ctrlStandardButtons);
	DDX_Control(pDX, IDC_CHECK_START_ON_TASKBAR, m_ctrlStartOnTaskBar);
	DDX_Control(pDX, IDC_CHECK_SEND_TO_TASKBAR, m_ctrlSendToTaskBar);
	DDX_Control(pDX, IDC_CHECK_MINIMIZEBOX, m_ctrlMinimizeBox);
	DDX_Check(pDX, IDC_CHECK_ABOUT, m_aboutBox);
	DDX_Check(pDX, IDC_CHECK_BITMAP_PAGES, m_bitmapPages);
	DDX_Check(pDX, IDC_CHECK_MINIMIZEBOX, m_minimizeBox);
	DDX_Check(pDX, IDC_CHECK_SEND_TO_TASKBAR, m_sendToTaskBar);
	DDX_Check(pDX, IDC_CHECK_START_ON_TASKBAR, m_startOnTaskBar);
	DDX_Radio(pDX, IDC_RADIO_MODAL, m_modal);
	DDX_Radio(pDX, IDC_RADIO_DLL, m_mfcDLL);
	DDX_Check(pDX, IDC_CHECK_TOOLTIPS, m_tooltips);
	DDX_Check(pDX, IDC_CHECK_STANDARDBUTTONS, m_standardButtons);
	//}}AFX_DATA_MAP
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom1Dlg::OnDismiss()
{
	if (!UpdateData ())
		return (FALSE);

	DefineBoolMacro (_T ("MODAL"), !m_modal);
	DefineBoolMacro (_T ("ABOUT_BOX"), m_aboutBox);
	DefineBoolMacro (_T ("BITMAP_PAGES"), m_bitmapPages);
	DefineBoolMacro (_T ("STANDARD_BUTTONS"), m_modal && m_standardButtons);
	DefineBoolMacro (_T ("MINIMIZEBOX"), m_minimizeBox);
	DefineBoolMacro (_T ("SEND_TO_TASKBAR"), m_sendToTaskBar);
	DefineBoolMacro (_T ("START_ON_TASKBAR"), m_startOnTaskBar);
	DefineBoolMacro (_T ("TOOLTIPS"), m_tooltips);
	DefineBoolMacro (_T ("MFCDLL"), !m_mfcDLL);

	return (TRUE);	// return FALSE if the dialog shouldn't be dismissed
}

BOOL CCustom1Dlg::PreTranslateMessage (MSG* pMsg)
{
	// Let the ToolTip process this message.
	m_ctrlTooltip.RelayEvent (pMsg);

	return CAppWizStepDlg::PreTranslateMessage (pMsg);
}

BEGIN_MESSAGE_MAP(CCustom1Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom1Dlg)
	ON_BN_CLICKED(IDC_CHECK_MINIMIZEBOX, OnUpdateNeeded)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK_SEND_TO_TASKBAR, OnUpdateNeeded)
	ON_BN_CLICKED(IDC_CHECK_START_ON_TASKBAR, OnUpdateNeeded)
	ON_BN_CLICKED(IDC_RADIO_MODAL, OnUpdateNeeded)
	ON_BN_CLICKED(IDC_RADIO_MODELESS, OnUpdateNeeded)
	ON_BN_CLICKED(IDC_CHECK_ABOUT, OnUpdateNeeded)
	ON_BN_CLICKED(IDC_CHECK_BITMAP_PAGES, OnUpdateNeeded)
	ON_BN_CLICKED(IDC_CHECK_TOOLTIPS, OnUpdateNeeded)
	ON_BN_CLICKED(IDC_CHECK_STANDARDBUTTONS, OnUpdateNeeded)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg message handlers

void CCustom1Dlg::UpdateControls ()
{
	UpdateData ();
	m_ctrlStandardButtons.EnableWindow (m_modal);
	m_ctrlStandardButtons.ShowWindow (m_modal);
	m_ctrlMinimizeBox.EnableWindow (m_modal);
	m_ctrlMinimizeBox.ShowWindow (m_modal);
	m_ctrlSendToTaskBar.EnableWindow (m_modal && m_minimizeBox);
	m_ctrlSendToTaskBar.ShowWindow (m_modal);
	m_ctrlStartOnTaskBar.EnableWindow (m_modal && m_minimizeBox && m_sendToTaskBar);
	m_ctrlStartOnTaskBar.ShowWindow (m_modal);
}

BOOL CCustom1Dlg::OnInitDialog() 
{
	CAppWizStepDlg::OnInitDialog();

	// Create the ToolTip control.
	m_ctrlTooltip.Create (this);
	m_ctrlTooltip.Activate (TRUE);

	// TODO: Use one of the following forms to add controls:
	m_ctrlTooltip.AddTool (GetDlgItem (IDC_RADIO_MODAL), IDS_CUSTOM1_RADIO_MODAL_TIP);
	m_ctrlTooltip.AddTool (GetDlgItem (IDC_RADIO_MODELESS), IDS_CUSTOM1_RADIO_MODELESS_TIP);
	m_ctrlTooltip.AddTool (GetDlgItem (IDC_CHECK_ABOUT), IDS_CUSTOM1_CHECK_ABOUT_TIP);
	m_ctrlTooltip.AddTool (GetDlgItem (IDC_CHECK_BITMAP_PAGES), IDS_CUSTOM1_CHECK_BITMAP_PAGES_TIP);
	m_ctrlTooltip.AddTool (GetDlgItem (IDC_CHECK_TOOLTIPS), IDS_CUSTOM1_CHECK_TOOLTIPS_TIP);
	m_ctrlTooltip.AddTool (GetDlgItem (IDC_CHECK_STANDARDBUTTONS), IDS_CUSTOM1_CHECK_STANDARDBUTTONS_TIP);
	m_ctrlTooltip.AddTool (GetDlgItem (IDC_CHECK_MINIMIZEBOX), IDS_CUSTOM1_CHECK_MINIMIZEBOX_TIP);
	m_ctrlTooltip.AddTool (GetDlgItem (IDC_CHECK_SEND_TO_TASKBAR), IDS_CUSTOM1_CHECK_SEND_TO_TASKBAR_TIP);
	m_ctrlTooltip.AddTool (GetDlgItem (IDC_CHECK_START_ON_TASKBAR), IDS_CUSTOM1_CHECK_START_ON_TASKBAR_TIP);
	m_ctrlTooltip.AddTool (GetDlgItem (IDC_RADIO_DLL), IDS_CUSTOM1_RADIO_DLL_TIP);
	m_ctrlTooltip.AddTool (GetDlgItem (IDC_RADIO_STATICALLY), IDS_CUSTOM1_RADIO_STATICALLY_TIP);

	UpdateControls ();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

#define STEP1_LEFT				8
#define STEP1_TOP				42
#define STEP1_WIDTH				179
#define STEP1_HEIGHT			180

#define TOOLTIPS_LEFT			70
#define TOOLTIPS_TOP			139
#define TOOLTIPS_WIDTH			28
#define TOOLTIPS_HEIGHT			10

#define ABOUT_LEFT				14
#define ABOUT_TOP				68
#define ABOUT_WIDTH				70
#define ABOUT_HEIGHT			50

#define BMP_PAGES_LEFT			18
#define BMP_PAGES_TOP			71
#define BMP_PAGES_WIDTH			120
#define BMP_PAGES_HEIGHT		10

#define MINIMIZE_BOX_LEFT		157
#define MINIMIZE_BOX_TOP		59
#define MINIMIZE_BOX_WIDTH		15
#define MINIMIZE_BOX_HEIGHT		7

#define SEND_TO_TASKBAR_LEFT		23
#define SEND_TO_TASKBAR_TOP			282
#define SEND_TO_TASKBAR_WIDTH		160
#define SEND_TO_TASKBAR_HEIGHT		26

// Coordinates for yellow rectangle in dialog-box units
#define RIGHT_YELLOW_DLGU	124
#define BOTTOM_YELLOW_DLGU	197

void CCustom1Dlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CDC mdc;
	mdc.CreateCompatibleDC (&dc);
	
	CRect rect (0, 0, RIGHT_YELLOW_DLGU+1, BOTTOM_YELLOW_DLGU+1);
	MapDialogRect (&rect);
	dc.DPtoLP (&rect);
	CBitmap bmp, *ob;
	bmp.CreateCompatibleBitmap (&dc, rect.right, rect.bottom);
	ob = mdc.SelectObject (&bmp);
	PaintBackground (mdc, this);
	PaintBitmap ((m_standardButtons || !m_modal) ? IDB_STEP1_STANDARDBUTTONS : IDB_STEP1_NOSTANDARDBUTTONS, STEP1_LEFT, STEP1_TOP, STEP1_WIDTH, STEP1_HEIGHT, mdc);
	if (m_tooltips)
		PaintBitmap (IDB_TOOLTIPS, TOOLTIPS_LEFT, TOOLTIPS_TOP, TOOLTIPS_WIDTH, TOOLTIPS_HEIGHT, mdc);
	if (m_bitmapPages)
		PaintBitmap (IDB_BITMAP_PAGES, BMP_PAGES_LEFT, BMP_PAGES_TOP, BMP_PAGES_WIDTH, BMP_PAGES_HEIGHT, mdc);
	if (m_modal && m_minimizeBox)
		PaintBitmap (IDB_MINIMIZE_BOX, MINIMIZE_BOX_LEFT, MINIMIZE_BOX_TOP, MINIMIZE_BOX_WIDTH, MINIMIZE_BOX_HEIGHT, mdc);
	if (m_aboutBox)
		PaintBitmap (IDB_ABOUT, ABOUT_LEFT, ABOUT_TOP, ABOUT_WIDTH, ABOUT_HEIGHT, mdc);
	if (m_modal && m_minimizeBox)
	{
		if (m_sendToTaskBar)
			PaintBitmap (IDB_SEND_TO_TASKBAR, SEND_TO_TASKBAR_LEFT, SEND_TO_TASKBAR_TOP, SEND_TO_TASKBAR_WIDTH, SEND_TO_TASKBAR_HEIGHT, mdc);
		else
			PaintBitmap (IDB_NO_SEND_TO_TASKBAR, SEND_TO_TASKBAR_LEFT, SEND_TO_TASKBAR_TOP, SEND_TO_TASKBAR_WIDTH, SEND_TO_TASKBAR_HEIGHT, mdc);
	}
	dc.BitBlt (rect.left, rect.top, rect.Width (), rect.Height (), &mdc, rect.left, rect.top, SRCCOPY);
	mdc.SelectObject (ob);
}

void CCustom1Dlg::OnUpdateNeeded() 
{
	if (UpdateData ())
	{
		// Invalidate the portion of this dialog on which we draw the picture
		CRect rect (STEP1_LEFT, STEP1_TOP, SEND_TO_TASKBAR_LEFT + SEND_TO_TASKBAR_WIDTH, SEND_TO_TASKBAR_TOP + SEND_TO_TASKBAR_HEIGHT);
		InvalidateRect (rect, FALSE);
		RedrawWindow (rect, NULL, RDW_UPDATENOW);
		UpdateControls ();
	}
}
