// ListCtrlDemoDlg.h : header file
//

#if !defined(AFX_LISTCTRLDEMODLG_H__3E67EA66_4129_464E_A380_23361CA8819F__INCLUDED_)
#define AFX_LISTCTRLDEMODLG_H__3E67EA66_4129_464E_A380_23361CA8819F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CListCtrlDemoDlg dialog
#include "NeuListCtrl.h"

class CListCtrlDemoDlg : public CDialog
{
// Construction
public:
	void InitializeListCtrl();
	CListCtrlDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CListCtrlDemoDlg)
	enum { IDD = IDD_LISTCTRLDEMO_DIALOG };
	CComboBox	m_ControlCombo;
	CComboBox	m_IndexCombo;
	CNeuListCtrl	m_NeuListCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	afx_msg void OnEndtrack(NMHDR* pNMHDR, LRESULT* pResult);

	// Generated message map functions
	//{{AFX_MSG(CListCtrlDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeComboColumnindex();
	afx_msg void OnSelchangeComboControlType();
	afx_msg void OnButtonInsert();
	afx_msg void OnButtonAddcontroltext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void MapeControlWithIndex();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLDEMODLG_H__3E67EA66_4129_464E_A380_23361CA8819F__INCLUDED_)
