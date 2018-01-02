// TDS_chartDlg.h : header file
//
//{{AFX_INCLUDES()
#include "mschart.h"
//}}AFX_INCLUDES

#if !defined(AFX_TDS_CHARTDLG_H__6CBBAFB1_CCD4_4D67_BF1D_591A4F0F5FD0__INCLUDED_)
#define AFX_TDS_CHARTDLG_H__6CBBAFB1_CCD4_4D67_BF1D_591A4F0F5FD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//#include <afxdb.h>
#include <list>
using namespace std;


//-------------------------------------------
// The structure where we fill data for the 
// chart
//-------------------------------------------
typedef struct filedetails
	{
	   CString login;
	   CString n9000;
	   CString n9002;
	   CString n9004;
	   CString nCancel;
	 }FILEDETAILS;

typedef list<FILEDETAILS> FILEDETAILS_LIST;

/////////////////////////////////////////////////////////////////////////////
// CTDS_chartDlg dialog

class CTDS_chartDlg : public CDialog
{
// Construction
public:
	virtual ~CTDS_chartDlg();
	CTDS_chartDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTDS_chartDlg)
	enum { IDD = IDD_TDS_CHART_DIALOG };
	CSpinButtonCtrl	m_SpinControl;
	CMSChart	m_ChartControl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTDS_chartDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	FILEDETAILS_LIST m_filedetails;
	FILEDETAILS_LIST::iterator i;

	// Generated message map functions
	//{{AFX_MSG(CTDS_chartDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRefresh();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnAutorefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	UINT m_Timer;
	int AddOrUpdateChartData(int noOfRows);
	int PopulateChartData();
	long lCharttype;
	//CDatabase m_oDB;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TDS_CHARTDLG_H__6CBBAFB1_CCD4_4D67_BF1D_591A4F0F5FD0__INCLUDED_)
