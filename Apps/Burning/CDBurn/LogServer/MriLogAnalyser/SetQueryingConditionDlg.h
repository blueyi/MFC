#if !defined(AFX_SETQUERYINGCONDITIONDLG_H__14A15902_6CE4_4E9A_935F_0C3721754A7F__INCLUDED_)
#define AFX_SETQUERYINGCONDITIONDLG_H__14A15902_6CE4_4E9A_935F_0C3721754A7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetQueryingConditionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetQueryingConditionDlg dialog

class CSetQueryingConditionDlg : public CDialog
{
// Construction
public:
	CSetQueryingConditionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetQueryingConditionDlg)
	enum { IDD = IDD_SET_QUERYING_CONDITION };
	CDateTimeCtrl	m_ctrlEndDate;
	CDateTimeCtrl	m_ctrlStartDate;
	CString	m_sStartDate;
	CString	m_sEndDate;
	CTime	m_sTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetQueryingConditionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetQueryingConditionDlg)
	afx_msg void OnDatetimechangeDatetimepickerStartDate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocusDatetimepickerStartDate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocusDatetimepickerEndDate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDatetimepickerEndDate(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETQUERYINGCONDITIONDLG_H__14A15902_6CE4_4E9A_935F_0C3721754A7F__INCLUDED_)
