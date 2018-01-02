// CButtonST_Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "CButtonST_demo.h"
#include "CButtonST_Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonST_Dlg dialog

CButtonST_Dlg::CButtonST_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CButtonST_Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CButtonST_Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CButtonST_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CButtonST_Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_ZIP256, m_btnZip256);
}

BEGIN_MESSAGE_MAP(CButtonST_Dlg, CDialog)
	//{{AFX_MSG_MAP(CButtonST_Dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonST_Dlg message handlers

BOOL CButtonST_Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
		
	//wb add down
	// Create the ZIP 256 colors button
	// Don't subclass twice! This is already done by DoDataExchange
	//  m_btnZip256.SubclassDlgItem(IDC_ZIP256, this);
	m_btnZip256.SetIcon(IDI_ZIPSMALL256, IDI_ZIP256); // 32x32 icon

	// Create the Hand 256 colors button
	m_btnHand256.SubclassDlgItem(IDC_HAND256, this);
	m_btnHand256.SetIcon(IDI_HAND256); 

	// Create the Lamp 256 colors button
	m_btnLamp256.SubclassDlgItem(IDC_LAMP256, this);
	m_btnLamp256.SetIcon(IDI_LAMP256, IDI_LAMP2); 
	// Don't draw border for this button
	m_btnLamp256.DrawBorder(FALSE);

	// Create the CD-Gold 256 colors button
	m_btnCDGold256.SubclassDlgItem(IDC_CDGOLD256, this);
	m_btnCDGold256.SetIcon(IDI_CDGOLD256); 
	// Don't draw border for this button
	m_btnCDGold256.DrawBorder(FALSE);

	// Create the OkBor 16 colors button
	m_btnOkBor16.SubclassDlgItem(IDC_OKBOR16, this);
	m_btnOkBor16.SetIcon(IDI_OKBOR16, IDI_OKBOR2);
	m_btnOkBor16.SetActiveBgColor(RGB(220,220,220));

	// Create the CancelBor 16 colors button
	m_btnCancelBor16.SubclassDlgItem(IDC_CANCELBOR16, this);
	m_btnCancelBor16.SetIcon(IDI_CANCELBOR16, IDI_CANCELBOR2);
	m_btnCancelBor16.SetActiveBgColor(RGB(220,220,220));

	// Create the Screw 16 colors button
	m_btnScrew16.SubclassDlgItem(IDC_SCREW16, this);
	m_btnScrew16.SetIcon(IDI_SCREW16);

	// Set some color effect
	m_btnScrew16.SetActiveFgColor(RGB(255,0,0));
	m_btnScrew16.SetInactiveFgColor(RGB(0,255,0));

	// Create the Exit 16 colors button
	m_btnExit16.SubclassDlgItem(IDOK, this);
	m_btnExit16.SetIcon(IDI_EXIT16);
	// Draw this button as a standard button
	m_btnExit16.SetFlat(FALSE);
	// Assign a custom cursor
	m_btnExit16.SetBtnCursor(IDC_HAND);

	// Create the About 16 colors button
	COLORREF crStandard = m_btnExit16.GetInactiveBgColor();

	// Write class version
	CString sVersion;
	sVersion.Format("Test for MFC class: CButtonST v%s", CButtonST::GetVersionC());
	SetWindowText(sVersion);
		//wb add up
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}


