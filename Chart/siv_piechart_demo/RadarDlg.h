#if !defined(AFX_RADARDLG_H__912D2E0F_0B8B_4701_A423_73EE196A1908__INCLUDED_)
#define AFX_RADARDLG_H__912D2E0F_0B8B_4701_A423_73EE196A1908__INCLUDED_

#include "PieChart.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RadarDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRadarDlg dialog

class CRadarDlg : public CDialog
{
// Construction
public:
	int m_nCurrentPos;
	CPieChart m_chart;
	CRadarDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRadarDlg)
	enum { IDD = IDD_RADAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRadarDlg)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADARDLG_H__912D2E0F_0B8B_4701_A423_73EE196A1908__INCLUDED_)
