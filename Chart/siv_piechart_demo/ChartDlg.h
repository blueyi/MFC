#if !defined(AFX_CHARTDLG_H__AA597B38_3701_4711_BC51_0B4C027DC06C__INCLUDED_)
#define AFX_CHARTDLG_H__AA597B38_3701_4711_BC51_0B4C027DC06C__INCLUDED_

#include "PieChart.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChartDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChartDlg dialog

class CChartDlg : public CDialog
{
// Construction
public:
	CPieChart m_chart;
	CChartDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChartDlg)
	enum { IDD = IDD_CHART };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChartDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTDLG_H__AA597B38_3701_4711_BC51_0B4C027DC06C__INCLUDED_)
