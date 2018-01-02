// TimerSpeed.cpp : implementation file
//

#include "stdafx.h"
#include "RTDemo.h"
#include "RTDemoDoc.h"
#include "TimerSpeed.h"
#include "RTDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimerSpeed dialog


CTimerSpeed::CTimerSpeed(CWnd* pParent /*=NULL*/)
	: CDialog(CTimerSpeed::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimerSpeed)
	m_nTimerSpeed = 0;
	//}}AFX_DATA_INIT
	pWnd = pParent;
}


void CTimerSpeed::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimerSpeed)
	DDX_Control(pDX, IDC_SPPEDMSG, m_SpeedMsg);
	DDX_Control(pDX, IDC_STIMERSPEED, m_TimerSpeed);
	DDX_Slider(pDX, IDC_STIMERSPEED, m_nTimerSpeed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTimerSpeed, CDialog)
	//{{AFX_MSG_MAP(CTimerSpeed)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimerSpeed message handlers

BOOL CTimerSpeed::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString str;
	CRTDemoView* pView = (CRTDemoView*)pWnd;
	str.Format("%d millseconds per cycle", pView->m_Graph.m_SpeedLevel[m_nTimerSpeed]);
	m_SpeedMsg.SetWindowText((LPCTSTR)str);
	m_TimerSpeed.SetRange(0, 9, TRUE);
	m_TimerSpeed.SetPos(m_nTimerSpeed);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTimerSpeed::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	switch(nSBCode)
	{
	case SB_THUMBTRACK:
	case SB_PAGEUP:
	case SB_PAGEDOWN:
		{
			UpdateData();
			CString str;
			CRTDemoView* pView = (CRTDemoView*)pWnd;
			str.Format("%d millseconds per cycle", pView->m_Graph.m_SpeedLevel[m_nTimerSpeed]);
			m_SpeedMsg.SetWindowText((LPCTSTR)str);
		}
		break;
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
