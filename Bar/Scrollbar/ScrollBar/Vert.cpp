// Vert.cpp : implementation file
//

#include "stdafx.h"
#include "XScrollBarTest.h"
#include "Vert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVert dialog

BEGIN_MESSAGE_MAP(CVert, CDialog)
	//{{AFX_MSG_MAP(CVert)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_THUMB_COLOR_VERT, OnThumb)
	ON_BN_CLICKED(IDC_THUMB_GRIPPER_VERT, OnThumb)
	ON_BN_CLICKED(IDC_CHANNEL_COLOR_VERT, OnThumb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CVert::CVert(CWnd* pParent /*=NULL*/)
	: CDialog(CVert::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVert)
	//}}AFX_DATA_INIT
	m_bThumbColor = TRUE;
	m_bThumbGripper = TRUE;
	m_bChannelColor = TRUE;
	m_nRed = m_nGreen = m_nBlue = 0;
	m_nSaturation = m_nLuminance = 0;
	m_dHue = m_dLuminance = m_dSaturation = 0.0;
}

void CVert::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVert)
	DDX_Control(pDX, IDC_SAMPLE_VERT, m_Sample);
	DDX_Check(pDX, IDC_THUMB_COLOR_VERT, m_bThumbColor);
	DDX_Check(pDX, IDC_THUMB_GRIPPER_VERT, m_bThumbGripper);
	DDX_Check(pDX, IDC_CHANNEL_COLOR_VERT, m_bChannelColor);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CVert message handlers

BOOL CVert::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	///////////////////////////////////////////////////////////////////////////	

	// initialize sample display
	m_Sample.SetBackgroundColor(RGB(0,0,0));
	
	// red
	VERIFY(m_VerticalScrollBar1.CreateFromStatic(
		SBS_VERT | WS_CHILD | SS_LEFT | SS_NOTIFY | WS_VISIBLE,
		this, IDC_SCROLL1_RECT_VERT, IDC_SCROLL1_VERT));

	m_VerticalScrollBar1.SetScrollRange(0, 255);
	m_VerticalScrollBar1.SetThumbColor(RGB(255,0,0));
	m_VerticalScrollBar1.EnableThumbGripper(m_bThumbGripper);
	GetDlgItem(IDC_RED_VERT)->SetWindowText(_T("0"));

	// green
	VERIFY(m_VerticalScrollBar2.CreateFromStatic(
		SBS_VERT | WS_CHILD | SS_LEFT | SS_NOTIFY | WS_VISIBLE,
		this, IDC_SCROLL2_RECT_VERT, IDC_SCROLL2_VERT));

	m_VerticalScrollBar2.SetScrollRange(0, 255);
	m_VerticalScrollBar2.SetThumbColor(RGB(0,172,89));
	m_VerticalScrollBar2.EnableThumbGripper(m_bThumbGripper);
	GetDlgItem(IDC_GREEN_VERT)->SetWindowText(_T("0"));

	// blue
	VERIFY(m_VerticalScrollBar3.CreateFromStatic(
		SBS_VERT | WS_CHILD | SS_LEFT | SS_NOTIFY | WS_VISIBLE,
		this, IDC_SCROLL3_RECT_VERT, IDC_SCROLL3_VERT));

	m_VerticalScrollBar3.SetScrollRange(0, 255);
	m_VerticalScrollBar3.SetThumbColor(RGB(0,0,255));
	m_VerticalScrollBar3.EnableThumbGripper(m_bThumbGripper);
	GetDlgItem(IDC_BLUE_VERT)->SetWindowText(_T("0"));

	// saturation
	VERIFY(m_VerticalScrollBar4.CreateFromStatic(
		SBS_VERT|WS_CHILD|SS_LEFT|SS_NOTIFY|WS_VISIBLE,
		this, IDC_SCROLL4_RECT_VERT, IDC_SCROLL4_VERT));

	m_VerticalScrollBar4.SetScrollRange(0, 100);
	m_VerticalScrollBar4.EnableThumbGripper(m_bThumbGripper);
	GetDlgItem(IDC_SATURATION_VERT)->SetWindowText(_T("0"));

	// luminance
	VERIFY(m_VerticalScrollBar5.CreateFromStatic(
		SBS_VERT|WS_CHILD|SS_LEFT|SS_NOTIFY|WS_VISIBLE,
		this, IDC_SCROLL5_RECT_VERT, IDC_SCROLL5_VERT));

	m_VerticalScrollBar5.SetScrollRange(0, 100);
	m_VerticalScrollBar5.EnableThumbGripper(m_bThumbGripper);
	GetDlgItem(IDC_LUMINANCE_VERT)->SetWindowText(_T("0"));

	///////////////////////////////////////////////////////////////////////////	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVert::OnVScroll(UINT /*nSBCode*/, UINT /*nPos*/, CScrollBar* pScrollBar) 
{
	if (pScrollBar == NULL)
		return;

	BOOL bRGB = FALSE;
	BOOL bSL  = FALSE;
	CString str = _T("");

	if (pScrollBar->m_hWnd == m_VerticalScrollBar1.m_hWnd)
	{
		TRACE(_T("scroll bar message ===== \n"));

		m_nRed = m_VerticalScrollBar1.GetScrollPos();
		str.Format("%d", m_nRed);
		GetDlgItem(IDC_RED_VERT)->SetWindowText(str);
		bRGB = TRUE;
	}
	else if (pScrollBar->m_hWnd == m_VerticalScrollBar2.m_hWnd)
	{
		TRACE(_T("scroll bar message ===== \n"));

		m_nGreen = m_VerticalScrollBar2.GetScrollPos();
		str.Format("%d", m_nGreen);
		GetDlgItem(IDC_GREEN_VERT)->SetWindowText(str);
		bRGB = TRUE;
	}
	else if (pScrollBar->m_hWnd == m_VerticalScrollBar3.m_hWnd)
	{
		TRACE(_T("scroll bar message ===== \n"));

		m_nBlue = m_VerticalScrollBar3.GetScrollPos();
		str.Format("%d", m_nBlue);
		GetDlgItem(IDC_BLUE_VERT)->SetWindowText(str);
		bRGB = TRUE;
	}
	else if (pScrollBar->m_hWnd == m_VerticalScrollBar4.m_hWnd)
	{
		m_nSaturation = m_VerticalScrollBar4.GetScrollPos();
		m_dSaturation = (float) m_nSaturation;
		m_dSaturation /= 100.;
		str.Format("%d%%", m_nSaturation);
		GetDlgItem(IDC_SATURATION_VERT)->SetWindowText(str);
		bSL = TRUE;
	}
	else if (pScrollBar->m_hWnd == m_VerticalScrollBar5.m_hWnd)
	{
		m_nLuminance = m_VerticalScrollBar5.GetScrollPos();
		m_dLuminance  = (float) m_nLuminance;
		m_dLuminance /= 100.;
		str.Format("%d%%", m_nLuminance);
		GetDlgItem(IDC_LUMINANCE_VERT)->SetWindowText(str);
		bSL = TRUE;
	}

	if (bRGB)
	{
		m_color.SetRGB(m_nRed, m_nGreen, m_nBlue);
		m_color.ToHLS();
		m_dLuminance = m_color.GetLuminance();
		m_dSaturation = m_color.GetSaturation();
		m_dHue = m_color.GetHue();

		int l = (int) (m_dLuminance * 100.);
		int s = (int) (m_dSaturation * 100.);
		TRACE("l=%d  s=%d\n", l, s);

		m_VerticalScrollBar4.SetScrollPos(s);
		str.Format("%d%%", s);
		GetDlgItem(IDC_SATURATION_VERT)->SetWindowText(str);

		m_VerticalScrollBar5.SetScrollPos(l);
		str.Format("%d%%", l);
		GetDlgItem(IDC_LUMINANCE_VERT)->SetWindowText(str);
	}

	if (bSL)
	{
		m_color.SetHLS(m_dHue, m_dLuminance, m_dSaturation);
		m_color.ToRGB();
		m_nRed   = m_color.GetRed();
		m_nGreen = m_color.GetGreen();
		m_nBlue  = m_color.GetBlue();

		m_VerticalScrollBar1.SetScrollPos(m_nRed);
		str.Format("%d", m_nRed);
		GetDlgItem(IDC_RED_VERT)->SetWindowText(str);

		m_VerticalScrollBar2.SetScrollPos(m_nGreen);
		str.Format("%d", m_nGreen);
		GetDlgItem(IDC_GREEN_VERT)->SetWindowText(str);

		m_VerticalScrollBar3.SetScrollPos(m_nBlue);
		str.Format("%d", m_nBlue);
		GetDlgItem(IDC_BLUE_VERT)->SetWindowText(str);
	}

	m_Sample.SetBackgroundColor(RGB(m_nRed, m_nGreen, m_nBlue));

//	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CVert::OnThumb() 
{
	UpdateData(TRUE);

	m_VerticalScrollBar1.EnableThumbGripper(m_bThumbGripper);
	m_VerticalScrollBar2.EnableThumbGripper(m_bThumbGripper);
	m_VerticalScrollBar3.EnableThumbGripper(m_bThumbGripper);

	m_VerticalScrollBar1.EnableThumbColor(m_bThumbColor);
	m_VerticalScrollBar2.EnableThumbColor(m_bThumbColor);
	m_VerticalScrollBar3.EnableThumbColor(m_bThumbColor);

	m_VerticalScrollBar1.EnableChannelColor(m_bChannelColor);
	m_VerticalScrollBar2.EnableChannelColor(m_bChannelColor);
	m_VerticalScrollBar3.EnableChannelColor(m_bChannelColor);

	m_VerticalScrollBar1.RedrawWindow();
	m_VerticalScrollBar2.RedrawWindow();
	m_VerticalScrollBar3.RedrawWindow();
}

