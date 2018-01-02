// RadarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sdi.h"
#include "RadarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define THE_TIMER WM_APP+123

/////////////////////////////////////////////////////////////////////////////
// CRadarDlg dialog


CRadarDlg::CRadarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRadarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRadarDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRadarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRadarDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRadarDlg, CDialog)
	//{{AFX_MSG_MAP(CRadarDlg)
	ON_WM_TIMER()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRadarDlg message handlers

void CRadarDlg::OnTimer(UINT nIDEvent) 
{
	CPieSlice* temp = NULL;

	switch ( nIDEvent )
	{
	case THE_TIMER:
		{
			m_chart.DeleteAllSlices();

			if ( m_nCurrentPos == 99 )
			{
				temp = new CPieSlice( 98, m_chart.GetBorderColor() );
				m_chart.AddSlice( *temp );
				temp = new CPieSlice( 2, PIECOLOR_BLACK );
				m_chart.AddSlice( *temp );
				InvalidateRect(NULL,FALSE);
				m_nCurrentPos--;
			}
			else
			{
				temp = new CPieSlice( m_nCurrentPos, m_chart.GetBorderColor() );
				m_chart.AddSlice( *temp );
				temp = new CPieSlice( 2, PIECOLOR_BLACK );
				m_chart.AddSlice( *temp );
				temp = new CPieSlice( 100-m_nCurrentPos-2, m_chart.GetBorderColor() );
				m_chart.AddSlice( *temp );
				InvalidateRect(NULL,FALSE);
				m_nCurrentPos--;
				if ( m_nCurrentPos == 0 ) m_nCurrentPos = 99;
			}
		}
		break;
	default:
		CDialog::OnTimer(nIDEvent);
		break;
	}

}

void CRadarDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	if ( (nID & 0xFFF0) == SC_CLOSE )
	{
		KillTimer( THE_TIMER );
		PostMessage( WM_CLOSE );
		PostMessage( WM_DESTROY );
		return;
	}
	
	CDialog::OnSysCommand(nID, lParam);
}

void CRadarDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	CPoint center;

	GetClientRect( &rect );
	center = rect.CenterPoint();
//	center.x /= 2;
//	center.y /= 2;

	m_chart.Draw2D( &dc, center, 30, FALSE );
}

BOOL CRadarDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_chart.SetAutoDelete( TRUE );
	m_chart.SetBorderColor( RGB(0,255,150) );
	m_nCurrentPos = 60;
	this->SetTimer( THE_TIMER, 15, NULL );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
