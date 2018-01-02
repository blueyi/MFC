// ChartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sdi.h"
#include "ChartDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartDlg dialog


CChartDlg::CChartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChartDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChartDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChartDlg, CDialog)
	//{{AFX_MSG_MAP(CChartDlg)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartDlg message handlers

BOOL CChartDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: add one-time construction code here
	m_chart.SetBorderColor( PIECOLOR_BLACK );
	m_chart.SetAutoDelete( TRUE );
	m_chart.SetTitle( _T("Breakdown of mail traffic (fictional)") );

	CPieSlice* sl = new CPieSlice( 31, PIECOLOR_GREEN, _T("Delivered") );
	m_chart.AddSlice( *sl );

	sl = new CPieSlice( 57, PIECOLOR_BLUE, _T("Spam") );
	m_chart.AddSlice( *sl );

	sl = new CPieSlice( 10, PIECOLOR_GRAY, _T("Suspected Spam") );
	m_chart.AddSlice( *sl );

	sl = new CPieSlice( 1, PIECOLOR_RED, _T("Viral") );
	m_chart.AddSlice( *sl );

	sl = new CPieSlice( 0, PIECOLOR_YELLOW, _T("Content") );
	m_chart.AddSlice( *sl );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChartDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	RedrawWindow();	
}

void CChartDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect; GetClientRect( &rect );
	CPoint center;
	center = rect.CenterPoint();
	center.x /= 2;

	m_chart.Draw2D( &dc, center, 70, TRUE, PIELEGEND_RIGHT, TRUE );
}

void CChartDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	if ( ( nID & 0xFFF0 ) == SC_CLOSE )
	{
		PostMessage( WM_CLOSE );
		PostMessage( WM_DESTROY );
		return;
	}

	CDialog::OnSysCommand(nID, lParam);
}
