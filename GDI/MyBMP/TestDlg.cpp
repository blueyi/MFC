// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD,pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
	m_bmpName = _T("");
	m_colorG = 0;
	m_colorB = 0;
	m_colorR = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_colorR = 255;
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	DDX_Text(pDX, IDC_BMPNAME, m_bmpName);
	DDX_Text(pDX, IDC_COLOR_G, m_colorG);
	DDV_MinMaxByte(pDX, m_colorG, 0, 255);
	DDX_Text(pDX, IDC_COLOR_B, m_colorB);
	DDV_MinMaxByte(pDX, m_colorB, 0, 255);
	DDX_Text(pDX, IDC_COLOR_R, m_colorR);
	DDV_MinMaxByte(pDX, m_colorR, 0, 255);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_BMP, OnOpenBmp)
	ON_BN_CLICKED(IDC_BMP_ORIGIN, OnBmpOrigin)
	ON_BN_CLICKED(IDC_BMP_STRETCH, OnBmpStretch)
	ON_BN_CLICKED(IDC_BMP_TILE, OnBmpTile)
	ON_BN_CLICKED(IDC_BACK_BMP, OnBackBmp)
	ON_BN_CLICKED(IDC_BACK_COLORED, OnBackColored)
	ON_BN_CLICKED(IDC_BACK_NORMAL, OnBackNormal)
	ON_EN_CHANGE(IDC_COLOR_B, OnChangeColorB)
	ON_EN_KILLFOCUS(IDC_COLOR_B, OnKillfocusColorB)
	ON_EN_CHANGE(IDC_COLOR_G, OnChangeColorG)
	ON_EN_KILLFOCUS(IDC_COLOR_G, OnKillfocusColorG)
	ON_EN_CHANGE(IDC_COLOR_R, OnChangeColorR)
	ON_EN_KILLFOCUS(IDC_COLOR_R, OnKillfocusColorR)
	ON_BN_CLICKED(IDC_SHOW_DLG, OnShowDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CButton * pButton;
	pButton = (CButton *) GetDlgItem(IDC_BACK_NORMAL);
	pButton->SetCheck(1);
	pButton = (CButton *) GetDlgItem(IDC_BMP_ORIGIN);
	pButton->SetCheck(1);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlg::OnPaint() 
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
		SetButtons();
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestDlg::OnOpenBmp() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE);
	if(dlg.DoModal()==IDOK)
		m_bmpName = dlg.GetPathName();
	UpdateData(FALSE);
	if( (m_bmpName.GetLength()>0)&&m_showDlg.LoadBmp(m_bmpName) )
	{
		m_showDlg.SetBackStyle(BACK_STYLE_BITMAP);
		m_showDlg.SetBmpStyle(BMP_STYLE_ORIGIN);
	}
}
void CTestDlg::SetButtons()
{
	GetDlgItem(IDC_BMPNAME)->EnableWindow( m_showDlg.GetBackStyle() == BACK_STYLE_BITMAP );
	GetDlgItem(IDC_OPEN_BMP)->EnableWindow( m_showDlg.GetBackStyle() == BACK_STYLE_BITMAP );
	GetDlgItem(IDC_BMP_STYLE)->EnableWindow( m_showDlg.GetBackStyle() == BACK_STYLE_BITMAP );
	GetDlgItem(IDC_COLOR_R)->EnableWindow( m_showDlg.GetBackStyle() == BACK_STYLE_COLORED );
	GetDlgItem(IDC_COLOR_G)->EnableWindow( m_showDlg.GetBackStyle() == BACK_STYLE_COLORED );
	GetDlgItem(IDC_COLOR_B)->EnableWindow( m_showDlg.GetBackStyle() == BACK_STYLE_COLORED );
	GetDlgItem(IDC_BMP_ORIGIN)->EnableWindow( m_showDlg.GetBackStyle() == BACK_STYLE_BITMAP );
	GetDlgItem(IDC_BMP_STRETCH)->EnableWindow( m_showDlg.GetBackStyle() == BACK_STYLE_BITMAP );
	GetDlgItem(IDC_BMP_TILE)->EnableWindow( m_showDlg.GetBackStyle() == BACK_STYLE_BITMAP );
	((CButton*)GetDlgItem(IDC_BMP_ORIGIN))->SetCheck( 
		m_showDlg.GetBmpStyle() == BMP_STYLE_ORIGIN);
	((CButton*)GetDlgItem(IDC_BMP_STRETCH))->SetCheck( 
		m_showDlg.GetBmpStyle() == BMP_STYLE_STRETCH);
	((CButton*)GetDlgItem(IDC_BMP_TILE))->SetCheck( 
		m_showDlg.GetBmpStyle() == BMP_STYLE_TILE);
}

void CTestDlg::OnBackNormal() 
{
	// TODO: Add your control notification handler code here
	m_showDlg.SetBackStyle(BACK_STYLE_NORMAL);
	Invalidate();
}
void CTestDlg::OnBackBmp() 
{
	// TODO: Add your control notification handler code here
	m_showDlg.SetBackStyle(BACK_STYLE_BITMAP);
	Invalidate();
}
void CTestDlg::OnBackColored() 
{
	// TODO: Add your control notification handler code here
	m_showDlg.SetBackStyle(BACK_STYLE_COLORED);
	m_showDlg.SetBackBrush(RGB(m_colorR,m_colorG,m_colorB));
	Invalidate();
}

void CTestDlg::OnBmpOrigin() 
{
	// TODO: Add your control notification handler code here
	if( (m_bmpName.GetLength()>0)&&m_showDlg.LoadBmp(m_bmpName) )
	{
		m_showDlg.SetBackStyle(BACK_STYLE_BITMAP);
		m_showDlg.SetBmpStyle(BMP_STYLE_ORIGIN);
	}
	((CButton*)GetDlgItem(IDC_BACK_BMP))->SetCheck(1);
}
void CTestDlg::OnBmpStretch() 
{
	// TODO: Add your control notification handler code here
	if( (m_bmpName.GetLength()>0)&&m_showDlg.LoadBmp(m_bmpName) )
	{
		m_showDlg.SetBackStyle(BACK_STYLE_BITMAP);
		m_showDlg.SetBmpStyle(BMP_STYLE_STRETCH);
	}
	((CButton*)GetDlgItem(IDC_BACK_BMP))->SetCheck(1);
}
void CTestDlg::OnBmpTile() 
{
	// TODO: Add your control notification handler code here
	if( (m_bmpName.GetLength()>0)&&m_showDlg.LoadBmp(m_bmpName) )
	{
		m_showDlg.SetBackStyle(BACK_STYLE_BITMAP);
		m_showDlg.SetBmpStyle(BMP_STYLE_TILE);
	}
	((CButton*)GetDlgItem(IDC_BACK_BMP))->SetCheck(1);
}

void CTestDlg::OnChangeColorB() 
{
	UpdateData(TRUE);
	m_showDlg.SetBackBrush(RGB(m_colorR,m_colorG,m_colorB));
}

void CTestDlg::OnKillfocusColorB() 
{
	UpdateData(TRUE);
	m_showDlg.SetBackBrush(RGB(m_colorR,m_colorG,m_colorB));
}

void CTestDlg::OnChangeColorG() 
{
	UpdateData(TRUE);
	m_showDlg.SetBackBrush(RGB(m_colorR,m_colorG,m_colorB));
}

void CTestDlg::OnKillfocusColorG() 
{
	UpdateData(TRUE);
	m_showDlg.SetBackBrush(RGB(m_colorR,m_colorG,m_colorB));
}

void CTestDlg::OnChangeColorR() 
{
	UpdateData(TRUE);
	m_showDlg.SetBackBrush(RGB(m_colorR,m_colorG,m_colorB));
}

void CTestDlg::OnKillfocusColorR() 
{
	UpdateData(TRUE);
	m_showDlg.SetBackBrush(RGB(m_colorR,m_colorG,m_colorB));
}

void CTestDlg::OnShowDlg() 
{
	// TODO: Add your control notification handler code here
	m_showDlg.DoModal();
}
