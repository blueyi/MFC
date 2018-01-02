// ScrollbarSampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScrollbarSample.h"
#include "ScrollbarSampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScrollbarSampleDlg dialog

CScrollbarSampleDlg::CScrollbarSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScrollbarSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScrollbarSampleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bThumbColor = TRUE;
	m_bThumbGripper = TRUE;
	m_bChannelColor = TRUE;
	m_nRed = 0;
}

void CScrollbarSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScrollbarSampleDlg)
	DDX_Check(pDX, IDC_THUMB_COLOR_HORZ, m_bThumbColor);
	DDX_Check(pDX, IDC_THUMB_GRIPPER_HORZ, m_bThumbGripper);
	DDX_Check(pDX, IDC_CHANNEL_COLOR_HORZ, m_bChannelColor);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScrollbarSampleDlg, CDialog)
	//{{AFX_MSG_MAP(CScrollbarSampleDlg)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_THUMB_COLOR_HORZ, OnThumb)
	ON_BN_CLICKED(IDC_THUMB_GRIPPER_HORZ, OnThumb)
	ON_BN_CLICKED(IDC_CHANNEL_COLOR_HORZ, OnThumb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScrollbarSampleDlg message handlers

BOOL CScrollbarSampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	// initialize sample display
	
	// red
	VERIFY(m_HorizontalScrollBar1.CreateFromWindow(
		SBS_HORZ | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		this, 
		GetDlgItem(IDC_SCROLL1_RECT_HORZ)->m_hWnd,
		GetDlgItem(IDC_RECT_LEFTARROW)->m_hWnd,
		GetDlgItem(IDC_RECT_RIGHTARROW)->m_hWnd,
		IDC_SCROLL1_HORZ
		));
	
	m_HorizontalScrollBar1.SetScrollRange(0, 255)
						  .SetThumbColor(RGB(255,0,0))
						  .EnableThumbGripper(m_bThumbGripper);
	GetDlgItem(IDC_RED_HORZ)->SetWindowText(_T("0"));

	Init();

	// =====  Test =====
	
// 	HBITMAP hBitmap;
// 	hBitmap = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_HORIZONTAL_SCROLLBAR_LEFTARROW2));
	
	// =====  Test end ========

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CScrollbarSampleDlg::Init()
{
	CString str = _T("");

	m_HorizontalScrollBar1.SetScrollPos(m_nRed);
	str.Format(_T("%d"), m_nRed);
	GetDlgItem(IDC_RED_HORZ)->SetWindowText(str);
}

void CScrollbarSampleDlg::OnHScroll(UINT /*nSBCode*/, UINT /*nPos*/, CScrollBar* pScrollBar) 
{
	if (pScrollBar == NULL)
		return;

	CString str = _T("");

	if (pScrollBar->m_hWnd == m_HorizontalScrollBar1.m_hWnd)
	{
		TRACE(_T("scroll bar message ===== \n"));

		m_nRed = m_HorizontalScrollBar1.GetScrollPos();
		str.Format(_T("%d"), m_nRed);
		GetDlgItem(IDC_RED_HORZ)->SetWindowText(str);
	}

	GetDlgItem(IDC_RED_HORZ)->SetFocus();
//	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CScrollbarSampleDlg::OnThumb() 
{
	UpdateData(TRUE);

	m_HorizontalScrollBar1.EnableThumbGripper(m_bThumbGripper);
	m_HorizontalScrollBar1.EnableThumbColor(m_bThumbColor);
	m_HorizontalScrollBar1.EnableChannelColor(m_bChannelColor);
	m_HorizontalScrollBar1.RedrawWindow();
}

