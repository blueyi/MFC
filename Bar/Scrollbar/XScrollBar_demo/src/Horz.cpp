// Horz.cpp : implementation file
//

#include "stdafx.h"
#include "XScrollBarTest.h"
#include "Horz.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHorz dialog

BEGIN_MESSAGE_MAP(CHorz, CDialog)
	//{{AFX_MSG_MAP(CHorz)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_THUMB_COLOR_HORZ, OnThumb)
	ON_BN_CLICKED(IDC_THUMB_GRIPPER_HORZ, OnThumb)
	ON_BN_CLICKED(IDC_CHANNEL_COLOR_HORZ, OnThumb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CHorz::CHorz(CWnd* pParent /*=NULL*/)
	: CDialog(CHorz::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHorz)
	//}}AFX_DATA_INIT
	m_bThumbColor = TRUE;
	m_bThumbGripper = TRUE;
	m_bChannelColor = TRUE;
	m_nRed = 255;
	m_nGreen = 153;
	m_nBlue = 0;
	m_nSaturation = m_nLuminance = 0;
	m_dHue = m_dLuminance = m_dSaturation = 0.0;
}

void CHorz::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHorz)
	DDX_Control(pDX, IDC_SAMPLE_HORZ, m_Sample);
	DDX_Check(pDX, IDC_THUMB_COLOR_HORZ, m_bThumbColor);
	DDX_Check(pDX, IDC_THUMB_GRIPPER_HORZ, m_bThumbGripper);
	DDX_Check(pDX, IDC_CHANNEL_COLOR_HORZ, m_bChannelColor);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CHorz message handlers

BOOL CHorz::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	///////////////////////////////////////////////////////////////////////////	

	// initialize sample display
	m_Sample.SetBackgroundColor(RGB(0,0,0));
	
	// red
	VERIFY(m_HorizontalScrollBar1.CreateFromWindow(
		SBS_HORZ | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		this, GetDlgItem(IDC_SCROLL1_RECT_HORZ)->m_hWnd, IDC_SCROLL1_HORZ));

	m_HorizontalScrollBar1.SetScrollRange(0, 255)
						  .SetThumbColor(RGB(255,0,0))
						  .EnableThumbGripper(m_bThumbGripper);
	GetDlgItem(IDC_RED_HORZ)->SetWindowText(_T("0"));
	
	// green
	VERIFY(m_HorizontalScrollBar2.CreateFromWindow(
		SBS_HORZ | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		this, GetDlgItem(IDC_SCROLL2_RECT_HORZ)->m_hWnd, IDC_SCROLL2_HORZ));

	m_HorizontalScrollBar2.SetScrollRange(0, 255)
						  .SetThumbColor(RGB(0,172,89))
						  .EnableThumbGripper(m_bThumbGripper);
	GetDlgItem(IDC_GREEN_HORZ)->SetWindowText(_T("0"));
	
	// blue
	VERIFY(m_HorizontalScrollBar3.CreateFromWindow(
		SBS_HORZ | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		this, GetDlgItem(IDC_SCROLL3_RECT_HORZ)->m_hWnd, IDC_SCROLL3_HORZ));

	m_HorizontalScrollBar3.SetScrollRange(0, 255)
						  .SetThumbColor(RGB(0,0,255))
						  .EnableThumbGripper(m_bThumbGripper);
	GetDlgItem(IDC_BLUE_HORZ)->SetWindowText(_T("0"));

	// saturation
	VERIFY(m_HorizontalScrollBar4.CreateFromWindow(
		SBS_HORZ | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		this, GetDlgItem(IDC_SCROLL4_RECT_HORZ)->m_hWnd, IDC_SCROLL4_HORZ));

	m_HorizontalScrollBar4.SetScrollRange(0, 100)
						  .EnableThumbGripper(m_bThumbGripper);
	GetDlgItem(IDC_SATURATION_HORZ)->SetWindowText(_T("0"));

	// luminance
	VERIFY(m_HorizontalScrollBar5.CreateFromWindow(
		SBS_HORZ | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		this, GetDlgItem(IDC_SCROLL5_RECT_HORZ)->m_hWnd, IDC_SCROLL5_HORZ));

	m_HorizontalScrollBar5.SetScrollRange(0, 100)
						  .EnableThumbGripper(m_bThumbGripper);
	GetDlgItem(IDC_LUMINANCE_HORZ)->SetWindowText(_T("0"));

	Init();

	TRACE(_T("..... sending SBM_GETSCROLLINFO ====================================================\n"));
	SCROLLINFO si;
	si.cbSize = sizeof(si);
	::SendMessage(m_HorizontalScrollBar1.m_hWnd, SBM_GETSCROLLINFO, 0, (LPARAM)&si);
	::SendMessage(m_HorizontalScrollBar1.m_hWnd, SBM_GETPOS, 0, 0);
	::SendMessage(m_HorizontalScrollBar1.m_hWnd, SBM_GETRANGE, 0, 0);

	///////////////////////////////////////////////////////////////////////////	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHorz::Init()
{
	CString str = _T("");

	m_HorizontalScrollBar1.SetScrollPos(m_nRed);
	str.Format(_T("%d"), m_nRed);
	GetDlgItem(IDC_RED_HORZ)->SetWindowText(str);

	m_HorizontalScrollBar2.SetScrollPos(m_nGreen);
	str.Format(_T("%d"), m_nGreen);
	GetDlgItem(IDC_GREEN_HORZ)->SetWindowText(str);

	m_HorizontalScrollBar3.SetScrollPos(m_nBlue);
	str.Format(_T("%d"), m_nBlue);
	GetDlgItem(IDC_BLUE_HORZ)->SetWindowText(str);

	m_color.SetRGB(m_nRed, m_nGreen, m_nBlue);
	m_color.ToHLS();
	m_dLuminance = m_color.GetLuminance();
	m_dSaturation = m_color.GetSaturation();
	m_dHue = m_color.GetHue();

	int l = (int) (m_dLuminance * 100.);
	int s = (int) (m_dSaturation * 100.);
	TRACE(_T("l=%d  s=%d\n"), l, s);

	m_HorizontalScrollBar4.SetScrollPos(s);
	str.Format(_T("%d%%"), s);
	GetDlgItem(IDC_SATURATION_HORZ)->SetWindowText(str);

	m_HorizontalScrollBar5.SetScrollPos(l);
	str.Format(_T("%d%%"), l);
	GetDlgItem(IDC_LUMINANCE_HORZ)->SetWindowText(str);

	m_Sample.SetBackgroundColor(RGB(m_nRed, m_nGreen, m_nBlue));
}

void CHorz::OnHScroll(UINT /*nSBCode*/, UINT /*nPos*/, CScrollBar* pScrollBar) 
{
	if (pScrollBar == NULL)
		return;

	TRACE(_T("..... sending SBM_GETSCROLLINFO ====================================================\n"));
	SCROLLINFO si;
	si.cbSize = sizeof(si);
	::SendMessage(m_HorizontalScrollBar1.m_hWnd, SBM_GETSCROLLINFO, 0, (LPARAM)&si);

	BOOL bRGB = FALSE;
	BOOL bSL  = FALSE;
	CString str = _T("");

	if (pScrollBar->m_hWnd == m_HorizontalScrollBar1.m_hWnd)
	{
		TRACE(_T("scroll bar message ===== \n"));

		m_nRed = m_HorizontalScrollBar1.GetScrollPos();
		str.Format(_T("%d"), m_nRed);
		GetDlgItem(IDC_RED_HORZ)->SetWindowText(str);
		bRGB = TRUE;
	}
	else if (pScrollBar->m_hWnd == m_HorizontalScrollBar2.m_hWnd)
	{
		TRACE(_T("scroll bar message ===== \n"));

		m_nGreen = m_HorizontalScrollBar2.GetScrollPos();
		str.Format(_T("%d"), m_nGreen);
		GetDlgItem(IDC_GREEN_HORZ)->SetWindowText(str);
		bRGB = TRUE;
	}
	else if (pScrollBar->m_hWnd == m_HorizontalScrollBar3.m_hWnd)
	{
		TRACE(_T("scroll bar message ===== \n"));

		m_nBlue = m_HorizontalScrollBar3.GetScrollPos();
		str.Format(_T("%d"), m_nBlue);
		GetDlgItem(IDC_BLUE_HORZ)->SetWindowText(str);
		bRGB = TRUE;
	}
	else if (pScrollBar->m_hWnd == m_HorizontalScrollBar4.m_hWnd)
	{
		m_nSaturation = m_HorizontalScrollBar4.GetScrollPos();
		m_dSaturation = (float) m_nSaturation;
		m_dSaturation /= 100.;
		str.Format(_T("%d%%"), m_nSaturation);
		GetDlgItem(IDC_SATURATION_HORZ)->SetWindowText(str);
		bSL = TRUE;
	}
	else if (pScrollBar->m_hWnd == m_HorizontalScrollBar5.m_hWnd)
	{
		m_nLuminance = m_HorizontalScrollBar5.GetScrollPos();
		m_dLuminance  = (float) m_nLuminance;
		m_dLuminance /= 100.;
		str.Format(_T("%d%%"), m_nLuminance);
		GetDlgItem(IDC_LUMINANCE_HORZ)->SetWindowText(str);
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
		TRACE(_T("l=%d  s=%d\n"), l, s);

		m_HorizontalScrollBar4.SetScrollPos(s);
		str.Format(_T("%d%%"), s);
		GetDlgItem(IDC_SATURATION_HORZ)->SetWindowText(str);

		m_HorizontalScrollBar5.SetScrollPos(l);
		str.Format(_T("%d%%"), l);
		GetDlgItem(IDC_LUMINANCE_HORZ)->SetWindowText(str);
	}

	if (bSL)
	{
		m_color.SetHLS(m_dHue, m_dLuminance, m_dSaturation);
		m_color.ToRGB();
		m_nRed   = m_color.GetRed();
		m_nGreen = m_color.GetGreen();
		m_nBlue  = m_color.GetBlue();

		m_HorizontalScrollBar1.SetScrollPos(m_nRed);
		str.Format(_T("%d"), m_nRed);
		GetDlgItem(IDC_RED_HORZ)->SetWindowText(str);

		m_HorizontalScrollBar2.SetScrollPos(m_nGreen);
		str.Format(_T("%d"), m_nGreen);
		GetDlgItem(IDC_GREEN_HORZ)->SetWindowText(str);

		m_HorizontalScrollBar3.SetScrollPos(m_nBlue);
		str.Format(_T("%d"), m_nBlue);
		GetDlgItem(IDC_BLUE_HORZ)->SetWindowText(str);
	}

	m_Sample.SetBackgroundColor(RGB(m_nRed, m_nGreen, m_nBlue));
	
//	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CHorz::OnThumb() 
{
	UpdateData(TRUE);

	m_HorizontalScrollBar1.EnableThumbGripper(m_bThumbGripper);
	m_HorizontalScrollBar2.EnableThumbGripper(m_bThumbGripper);
	m_HorizontalScrollBar3.EnableThumbGripper(m_bThumbGripper);

	m_HorizontalScrollBar1.EnableThumbColor(m_bThumbColor);
	m_HorizontalScrollBar2.EnableThumbColor(m_bThumbColor);
	m_HorizontalScrollBar3.EnableThumbColor(m_bThumbColor);

	m_HorizontalScrollBar1.EnableChannelColor(m_bChannelColor);
	m_HorizontalScrollBar2.EnableChannelColor(m_bChannelColor);
	m_HorizontalScrollBar3.EnableChannelColor(m_bChannelColor);

	m_HorizontalScrollBar1.RedrawWindow();
	m_HorizontalScrollBar2.RedrawWindow();
	m_HorizontalScrollBar3.RedrawWindow();
}

