// Property.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "KeyHook.h"
#include "Property.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyDlg dialog

CPropertyDlg::CPropertyDlg()
	: CPropertyPage(CPropertyDlg::IDD)
{
	//{{AFX_DATA_INIT(CPropertyDlg)
	//}}AFX_DATA_INIT

	m_wKey = AfxGetApp()->GetProfileInt("", "wKey", 192);
	m_wMod = AfxGetApp()->GetProfileInt("", "wMod", HOTKEYF_CONTROL);
	m_nWidth = AfxGetApp()->GetProfileInt("", "nWidth", 40);
	m_nFactor = AfxGetApp()->GetProfileInt("", "nFactor", 4);
	m_bNoPersist = AfxGetApp()->GetProfileInt("", "bNoPersist", FALSE);
	KHSetZoomParams(m_nWidth, m_nWidth, m_wKey, m_wMod,
		DEFAULT_ZOOM_RATE, m_nFactor, !m_bNoPersist);
}

void CPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyDlg)
	DDX_Control(pDX, IDC_WIDTH_SPIN, m_widthSpin);
	DDX_Control(pDX, IDC_FACTOR_SPIN, m_factorSpin);
	DDX_Control(pDX, IDC_HOTKEY, m_hotKey);
	DDX_Text(pDX, IDC_FACTOR, m_nFactor);
	DDV_MinMaxUInt(pDX, m_nFactor, 2, 6);
	DDX_Text(pDX, IDC_WIDTH, m_nWidth);
	DDV_MinMaxUInt(pDX, m_nWidth, 20, 60);
	DDX_Check(pDX, IDC_CHECK_PERSIST, m_bNoPersist);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPropertyDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CPropertyDlg)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_CHECK_PERSIST, OnPropertyChanged)
	ON_EN_CHANGE(IDC_FACTOR, OnPropertyChanged)
	ON_EN_CHANGE(IDC_WIDTH, OnPropertyChanged)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CPropertyDlg::OnSetActive()
{
	m_wKey = AfxGetApp()->GetProfileInt("", "wKey", 192);
	m_wMod = AfxGetApp()->GetProfileInt("", "wMod", HOTKEYF_CONTROL);
	m_nWidth = AfxGetApp()->GetProfileInt("", "nWidth", 40);
	m_nFactor = AfxGetApp()->GetProfileInt("", "nFactor", 4);
	m_bNoPersist = AfxGetApp()->GetProfileInt("", "bNoPersist", FALSE);
	
	m_factorSpin.SetRange(2, 6);
	m_widthSpin.SetRange(20, 60);
	m_hotKey.SetHotKey(m_wKey, m_wMod);
	m_hotKey.SetRules(HKCOMB_NONE|HKCOMB_S, HOTKEYF_CONTROL);
	return CPropertyPage::OnSetActive();
}

BOOL CPropertyDlg::StoreData() 
{
	if (!UpdateData(TRUE))
		return FALSE;

	m_hotKey.GetHotKey(m_wKey, m_wMod);
	KHSetZoomParams(m_nWidth, m_nWidth, m_wKey, m_wMod,
		DEFAULT_ZOOM_RATE, m_nFactor, !m_bNoPersist);

	AfxGetApp()->WriteProfileInt("", "wKey", m_wKey);
	AfxGetApp()->WriteProfileInt("", "wMod", m_wMod);
	AfxGetApp()->WriteProfileInt("", "nWidth", m_nWidth);
	AfxGetApp()->WriteProfileInt("", "nFactor", m_nFactor);
	AfxGetApp()->WriteProfileInt("", "bNoPersist", m_bNoPersist);
	return TRUE;
}

void CPropertyDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rect;
	CWnd* bmpWnd = GetDlgItem(IDC_BITMAP);
	ASSERT(bmpWnd);

	bmpWnd->GetWindowRect(rect);
	ScreenToClient(rect);
	if (StoreData() && rect.PtInRect(point))
	{
		SetCapture();
		KHEnableZoomWindow(TRUE);
		KHShowZoomWindow(TRUE);
	}

	CPropertyPage::OnLButtonDown(nFlags, point);
}

void CPropertyDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture();
	KHEnableZoomWindow(FALSE);
	CPropertyPage::OnLButtonUp(nFlags, point);
}

void CPropertyDlg::OnOK() 
{
	StoreData();
	CPropertyPage::OnOK();
}

void CPropertyDlg::OnPropertyChanged() 
{
	SetModified(TRUE);	
}

void CPropertyDlg::OnDestroy() 
{
	KHShowZoomWindow(FALSE);
	CPropertyPage::OnDestroy();
}
