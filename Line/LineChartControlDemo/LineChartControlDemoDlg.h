// LineChartControlDemoDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "LineChartCtrl.h"


// CLineChartControlDemoDlg dialog
class CLineChartControlDemoDlg : public CDialog
{
// Construction
public:
	CLineChartControlDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LINECHARTCONTROLDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CLineChartCtrl m_plot;

	CRect m_rectBtnExit;
	CRect m_rectOldWindow;
	CRect m_rectOldPlotWindow;
public:
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedSetting();
protected:
	CButton m_btnExit;
	int m_iBtnExitFromRight;
	int m_iBtnExitFromBottom;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnBnClickedDispLine1();
	afx_msg void OnBnClickedDispLine2();
};
