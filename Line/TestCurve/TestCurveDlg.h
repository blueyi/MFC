// TestCurveDlg.h : header file
//

#if !defined(AFX_TESTCURVEDLG_H__76A466C8_1832_405D_9F69_0B84B3694E9C__INCLUDED_)
#define AFX_TESTCURVEDLG_H__76A466C8_1832_405D_9F69_0B84B3694E9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestCurveDlg dialog
#include "CurveCtrl.h"
class CTestCurveDlg : public CDialog
{
// Construction
public:
	CTestCurveDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CTestCurveDlg();

	CCurveCtrl*		m_pCurveCtrl;
	int				m_nCurveCount;
// Dialog Data
	//{{AFX_DATA(CTestCurveDlg)
	enum { IDD = IDD_TESTCURVE_DIALOG };
	CButton	m_StcCurve;
	int		m_iListIndex;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestCurveDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestCurveDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnAdd();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnAdddata();
	//}}AFX_MSG
    afx_msg void OnCurveMouseAdd(NMHDR *pNotifyStruct, LRESULT* pResult);	
	afx_msg void OnCurveMouseModify(NMHDR *pNotifyStruct, LRESULT* pResult);
    afx_msg void OnCurveMouseDelete(NMHDR *pNotifyStruct, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCURVEDLG_H__76A466C8_1832_405D_9F69_0B84B3694E9C__INCLUDED_)
