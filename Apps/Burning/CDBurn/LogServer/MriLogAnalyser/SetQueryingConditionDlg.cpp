// SetQueryingConditionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MriLogAnalyser.h"
#include "SetQueryingConditionDlg.h"
#include "DataManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetQueryingConditionDlg dialog


CSetQueryingConditionDlg::CSetQueryingConditionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetQueryingConditionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetQueryingConditionDlg)
	m_sStartDate = _T("");
	m_sEndDate = _T("");
	m_sTime = 0;
	//}}AFX_DATA_INIT
}


void CSetQueryingConditionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetQueryingConditionDlg)
	DDX_Control(pDX, IDC_DATETIMEPICKER_END_DATE, m_ctrlEndDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START_DATE, m_ctrlStartDate);
	DDX_Text(pDX, IDC_EDIT_START_DATE, m_sStartDate);
	DDX_Text(pDX, IDC_EDIT_END_DATE, m_sEndDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START_DATE, m_sTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetQueryingConditionDlg, CDialog)
	//{{AFX_MSG_MAP(CSetQueryingConditionDlg)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_START_DATE, OnDatetimechangeDatetimepickerStartDate)
	ON_NOTIFY(NM_SETFOCUS, IDC_DATETIMEPICKER_START_DATE, OnSetfocusDatetimepickerStartDate)
	ON_NOTIFY(NM_SETFOCUS, IDC_DATETIMEPICKER_END_DATE, OnSetfocusDatetimepickerEndDate)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_END_DATE, OnDatetimechangeDatetimepickerEndDate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetQueryingConditionDlg message handlers

void CSetQueryingConditionDlg::OnDatetimechangeDatetimepickerStartDate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CTime oTime;
	m_ctrlStartDate.GetTime( oTime );
	int iYear = oTime.GetYear();
	int iMonth = oTime.GetMonth();
	int iDay = oTime.GetDay();
	
	UpdateData( TRUE );
	m_sStartDate.Format( "%04d%02d%02d", iYear, iMonth, iDay );
	UpdateData( FALSE );
	
	*pResult = 0;
}

void CSetQueryingConditionDlg::OnSetfocusDatetimepickerStartDate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int iYear, iMonth, iDay;
	sscanf( CDataManager::GetHandle().m_sStartDate, "%4d%2d%2d", &iYear, &iMonth, &iDay );
	CTime oTime( iYear, iMonth, iDay, 0, 0, 0);
	m_ctrlStartDate.SetTime( &oTime );
	
	*pResult = 0;
}

void CSetQueryingConditionDlg::OnSetfocusDatetimepickerEndDate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int iYear, iMonth, iDay;
	sscanf( CDataManager::GetHandle().m_sStartDate, "%4d%2d%2d", &iYear, &iMonth, &iDay );
	CTime oTime( iYear, iMonth, iDay, 0, 0, 0);
	m_ctrlStartDate.SetTime( &oTime );
	
	*pResult = 0;
}

void CSetQueryingConditionDlg::OnDatetimechangeDatetimepickerEndDate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CTime oTime;
	m_ctrlEndDate.GetTime( oTime );
	int iYear = oTime.GetYear();
	int iMonth = oTime.GetMonth();
	int iDay = oTime.GetDay();
	
	UpdateData( TRUE );
	m_sEndDate.Format( "%04d%02d%02d", iYear, iMonth, iDay );
	UpdateData( FALSE );
	
	*pResult = 0;
}
